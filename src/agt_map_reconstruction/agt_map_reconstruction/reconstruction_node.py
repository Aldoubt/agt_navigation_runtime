#!/usr/bin/env python3
"""2.5D terrain/elevation mapper for BUNKER inspection runs."""
from __future__ import annotations
import math
import time
from collections import defaultdict
from pathlib import Path
import numpy as np
import yaml
import rclpy
from nav_msgs.msg import OccupancyGrid, Odometry
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy
from sensor_msgs.msg import PointCloud2
from sensor_msgs_py import point_cloud2
from std_msgs.msg import Header

def stamp(msg):
    return float(msg.header.stamp.sec) + float(msg.header.stamp.nanosec) * 1e-9

def yaw(q):
    return math.atan2(2.0 * (q.w*q.z + q.x*q.y), 1.0 - 2.0*(q.y*q.y + q.z*q.z))

class ReconstructionNode(Node):
    def __init__(self):
        super().__init__('agt_map_reconstruction')
        defaults = {
            'cloud_topic':'/cloud_registered', 'odometry_topic':'/Odometry',
            'output_directory':'results', 'output_frame':'map', 'map_resolution':0.10,
            'max_points_per_cloud':3000, 'frame_stride':5, 'assume_registered_cloud':False,
            'raytrace_enabled':True, 'ray_step_limit':500, 'obstacle_height_threshold':0.18,
            'height_difference_limit':0.12, 'slope_limit_deg':25.0, 'roughness_limit_m':0.08,
            'min_observations':2, 'max_ray_points_per_cloud':500, 'publish_period':1.0,
            'finalize_after_idle_sec':5.0}
        for k,v in defaults.items(): self.declare_parameter(k,v)
        self.p = {k:self.get_parameter(k).value for k in defaults}
        self.out = Path(str(self.p['output_directory'])).expanduser(); self.out.mkdir(parents=True, exist_ok=True)
        self.latest_odom = None; self.odom_history=[]; self.frames=[]; self.cloud_count=0
        self.last_cloud_wall=time.monotonic(); self.finalized=False
        self.last_rendered_cloud_count=0
        self.cloud_sub=self.create_subscription(PointCloud2,str(self.p['cloud_topic']),self.cloud_cb,10)
        self.odom_sub=self.create_subscription(Odometry,str(self.p['odometry_topic']),self.odom_cb,20)
        map_qos=QoSProfile(depth=1, reliability=ReliabilityPolicy.RELIABLE,
                           durability=DurabilityPolicy.TRANSIENT_LOCAL)
        self.navigation_pub=self.create_publisher(OccupancyGrid,'/navigation_map',map_qos)
        self.elevation_pub=self.create_publisher(OccupancyGrid,'/elevation_map',map_qos)
        self.traversability_pub=self.create_publisher(OccupancyGrid,'/traversability_map',map_qos)
        self.map_pub=self.create_publisher(OccupancyGrid,'/map',map_qos)
        self.timer=self.create_timer(float(self.p['publish_period']),self.periodic)
        self.get_logger().info(f"cloud={self.p['cloud_topic']} odometry={self.p['odometry_topic']}")

    def odom_cb(self,msg):
        self.latest_odom=msg; self.odom_history.append((stamp(msg),msg)); self.odom_history=self.odom_history[-200:]

    def pose_for(self,t):
        return self.latest_odom if not self.odom_history else min(self.odom_history,key=lambda x:abs(x[0]-t))[1]

    def transform(self,points,pose):
        if pose is None: return points,None
        q=pose.pose.pose.orientation; c,s=math.cos(yaw(q)),math.sin(yaw(q))
        if not bool(self.p['assume_registered_cloud']):
            xy=points[:,:2] @ np.array([[c,s],[-s,c]],dtype=np.float32); points=points.copy()
            points[:,0]=xy[:,0]+pose.pose.pose.position.x; points[:,1]=xy[:,1]+pose.pose.pose.position.y; points[:,2]+=pose.pose.pose.position.z
        return points,np.array([pose.pose.pose.position.x,pose.pose.pose.position.y],dtype=np.float32)

    def cloud_cb(self,msg):
        if self.finalized:return
        self.cloud_count+=1
        if (self.cloud_count-1)%max(1,int(self.p['frame_stride'])):return
        try: points=np.asarray(point_cloud2.read_points_numpy(msg,field_names=('x','y','z'),skip_nans=True),dtype=np.float32).reshape(-1,3)
        except Exception as exc: self.get_logger().error(f'PointCloud2 read failed: {exc}'); return
        if not len(points):return
        limit=int(self.p['max_points_per_cloud'])
        if limit>0 and len(points)>limit: points=points[np.linspace(0,len(points)-1,limit,dtype=np.int64)]
        points,origin=self.transform(points,self.pose_for(stamp(msg))); self.frames.append((points,origin)); self.last_cloud_wall=time.monotonic()

    @staticmethod
    def ray_cells(a,b,limit,res):
        length=float(np.linalg.norm(b-a)); n=min(int(limit),max(1,int(math.ceil(length/res))))
        samples=np.linspace(a,b,n+1); cells=[]
        for p in samples:
            k=(int(math.floor(p[0]/res)),int(math.floor(p[1]/res)))
            if not cells or cells[-1]!=k:cells.append(k)
        return cells

    def periodic(self):
        if self.finalized or not self.frames:return
        idle=time.monotonic()-self.last_cloud_wall
        if idle>=float(self.p['finalize_after_idle_sec']):
            self.finalize()
        elif self.cloud_count>self.last_rendered_cloud_count:
            self.rebuild(False)

    @staticmethod
    def gradient_slope(h,res):
        valid=np.isfinite(h); fill=np.nanmedian(h[valid]) if np.any(valid) else 0.0; f=np.where(valid,h,fill)
        gy,gx=np.gradient(f,res,edge_order=1); result=np.degrees(np.arctan(np.hypot(gx,gy))).astype(np.float32); result[~valid]=np.nan; return result

    def finalize(self):
        if self.finalized or not self.frames:return
        self.rebuild(True); self.finalized=True

    def rebuild(self, final=False):
        res=float(self.p['map_resolution']); all_points=np.concatenate([x[0] for x in self.frames])
        origin=np.floor(all_points[:,:2].min(axis=0)/res)*res; keys=np.floor((all_points[:,:2]-origin)/res).astype(np.int64)
        width,height=(keys.max(axis=0)+1).tolist(); shape=(height,width); values=defaultdict(list); hit=np.zeros(shape,np.int32); free=np.zeros(shape,np.int32)
        for points,sensor in self.frames:
            point_keys=np.floor((points[:,:2]-origin)/res).astype(np.int64)
            ray_points = points
            ray_limit = int(self.p['max_ray_points_per_cloud'])
            if ray_limit > 0 and len(ray_points) > ray_limit:
                ray_points = ray_points[np.linspace(0, len(ray_points)-1, ray_limit, dtype=np.int64)]
            for p,k in zip(points,point_keys):
                r,c=int(k[1]),int(k[0])
                if 0<=r<height and 0<=c<width:values[(r,c)].append(float(p[2]));hit[r,c]+=1
            if sensor is not None and bool(self.p['raytrace_enabled']):
                # Ray tracing is intentionally bounded independently from
                # terrain statistics: a dense MID360 frame need not cast
                # thousands of near-identical rays.
                for p in ray_points:
                    for rx,ry in self.ray_cells(sensor,p[:2],int(self.p['ray_step_limit']),res)[:-1]:
                        rr=int(math.floor((ry-origin[1])/res));cc=int(math.floor((rx-origin[0])/res))
                        if 0<=rr<height and 0<=cc<width:free[rr,cc]+=1
        mean=np.full(shape,np.nan,np.float32); var=np.full(shape,np.nan,np.float32); minz=np.full(shape,np.nan,np.float32); maxz=np.full(shape,np.nan,np.float32)
        for (r,c),v in values.items():
            z=np.asarray(v,np.float32);mean[r,c]=z.mean();var[r,c]=z.var();minz[r,c]=z.min();maxz[r,c]=z.max()
        rough=np.sqrt(np.maximum(var,0)); slope=self.gradient_slope(mean,res); observed=hit>0
        obstacle=observed & ((maxz-minz)>float(self.p['height_difference_limit']))
        obstacle |= observed & (var>float(self.p['roughness_limit_m'])**2*4.0)
        score=np.full(shape,-1.,np.float32);score[observed|(free>0)]=1.
        score[observed]=np.minimum(score[observed],np.clip(1-slope[observed]/float(self.p['slope_limit_deg']),0,1));score[observed]=np.minimum(score[observed],np.clip(1-rough[observed]/float(self.p['roughness_limit_m']),0,1));score[obstacle]=0.
        nav=np.full(shape,-1,np.int8);nav[(free>0)|observed]=0;nav[(score>=0)&(score<0.35)]=100;nav[obstacle]=100
        terrain={'origin':[float(origin[0]),float(origin[1])],'resolution':res,'height_mean':mean,'height_variance':var,'min_z':minz,'max_z':maxz,'slope':slope,'roughness':rough,'occupancy_probability':np.where(nav<0,np.nan,nav/100.),'traversability':score}
        self.publish_maps(nav,mean,score,terrain); self.last_rendered_cloud_count=self.cloud_count
        if final:self.export(nav,terrain,len(all_points),len(self.frames))
        self.get_logger().info(f'finalized {width}x{height}: free={int(np.sum(nav==0))} occupied={int(np.sum(nav==100))} unknown={int(np.sum(nav<0))}')

    def publish_maps(self,nav,elevation,score,t):
        def make(data):
            m=OccupancyGrid();m.header=Header(frame_id=str(self.p['output_frame']),stamp=self.get_clock().now().to_msg());m.info.resolution=t['resolution'];m.info.width=data.shape[1];m.info.height=data.shape[0];m.info.origin.position.x,m.info.origin.position.y=t['origin'];m.info.origin.orientation.w=1.;m.data=data.reshape(-1).tolist();return m
        self.map_pub.publish(make(nav));self.navigation_pub.publish(make(nav))
        e=np.full(elevation.shape,-1,np.int8);valid=np.isfinite(elevation)
        if np.any(valid):lo,hi=np.nanpercentile(elevation,[2,98]);e[valid]=np.clip((elevation[valid]-lo)/max(hi-lo,1e-3)*100,0,100).astype(np.int8)
        self.elevation_pub.publish(make(e));self.traversability_pub.publish(make(np.where(score<0,-1,np.clip(score*100,0,100)).astype(np.int8)))

    def export(self,nav,t,points,frames):
        def pgm(path,a):path.write_bytes(f'P5\n{a.shape[1]} {a.shape[0]}\n255\n'.encode()+np.flipud(a).astype(np.uint8).tobytes())
        image=np.full(nav.shape,205,np.uint8);image[nav==0]=254;image[nav==100]=0;pgm(self.out/'navigation_map.pgm',image)
        (self.out/'navigation_map.yaml').write_text(yaml.safe_dump({'image':'navigation_map.pgm','resolution':t['resolution'],'origin':[*t['origin'],0.0],'negate':0,'occupied_thresh':0.65,'free_thresh':0.196,'mode':'trinary'},sort_keys=False),encoding='utf-8')
        # Keep the conventional map.pgm/map.yaml aliases for existing Nav2
        # launch files; the requested canonical artifacts remain navigation_map.*.
        pgm(self.out/'map.pgm',image)
        (self.out/'map.yaml').write_text(yaml.safe_dump({'image':'map.pgm','resolution':t['resolution'],'origin':[*t['origin'],0.0],'negate':0,'occupied_thresh':0.65,'free_thresh':0.196,'mode':'trinary'},sort_keys=False),encoding='utf-8')
        layers={'height_mean':'terrain_height_mean.npy','height_variance':'terrain_height_variance.npy','min_z':'terrain_min_z.npy','max_z':'terrain_max_z.npy','slope':'terrain_slope.npy','roughness':'terrain_roughness.npy','occupancy_probability':'terrain_occupancy_probability.npy','traversability':'traversability.npy'}
        for k,n in layers.items():np.save(self.out/n,t[k])
        desc={'frame_id':str(self.p['output_frame']),'resolution':t['resolution'],'origin':t['origin'],'grid_shape':list(nav.shape),'layers':layers,'rules':{'height_difference_m':float(self.p['height_difference_limit']),'slope_limit_deg':float(self.p['slope_limit_deg']),'roughness_limit_m':float(self.p['roughness_limit_m'])}}
        (self.out/'terrain.yaml').write_text(yaml.safe_dump(desc,sort_keys=False),encoding='utf-8')
        report={'points':points,'frames':frames,'free_cells':int(np.sum(nav==0)),'occupied_cells':int(np.sum(nav==100)),'unknown_cells':int(np.sum(nav<0)),'raytrace_used':bool(self.p['raytrace_enabled'])}
        (self.out/'reconstruction_report.md').write_text('# 2.5D reconstruction report\n\n'+yaml.safe_dump(report,sort_keys=False),encoding='utf-8')

def main(args=None):
    rclpy.init(args=args);node=ReconstructionNode()
    try:rclpy.spin(node)
    except KeyboardInterrupt:pass
    finally:
        if not node.finalized:node.finalize()
        node.destroy_node()
        try:rclpy.shutdown()
        except Exception:pass
