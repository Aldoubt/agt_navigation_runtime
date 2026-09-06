#include "map_widget.h"
#include <QContextMenuEvent>
#include <QMenu>
#include <QPainter>
MapWidget::MapWidget(QWidget*p):QGraphicsView(p){setScene(&scene_);setBackgroundBrush(QColor("#111820"));setDragMode(QGraphicsView::ScrollHandDrag);}
void MapWidget::setMap(const nav_msgs::msg::OccupancyGrid::SharedPtr&m){QImage im(m->info.width,m->info.height,QImage::Format_RGB32);for(unsigned y=0;y<m->info.height;y++)for(unsigned x=0;x<m->info.width;x++){int v=m->data[y*m->info.width+x];int c=v<0?80:255-v*2.55;im.setPixelColor(x,m->info.height-y-1,QColor(c,c,c));}if(map_)scene_.removeItem(map_);map_=scene_.addPixmap(QPixmap::fromImage(im));map_->setScale(m->info.resolution);fitInView(map_,Qt::KeepAspectRatio);}
void MapWidget::setPose(double x,double y,double yaw){Q_UNUSED(x);Q_UNUSED(y);Q_UNUSED(yaw);}
void MapWidget::contextMenuEvent(QContextMenuEvent*e){QMenu menu(this);auto*a=menu.addAction(tr("Add inspection point"));auto*g=menu.addAction(tr("Set navigation goal"));auto chosen=menu.exec(e->globalPos());QPointF p=mapToScene(e->pos());if(chosen==a)emit addInspectionPoint(p.x(),p.y());else if(chosen==g)emit navigationGoal(p.x(),p.y());}
