from setuptools import find_packages, setup

package_name = 'camera_gimbal_capability'

setup(
    name=package_name,
    version='1.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='autolabor',
    maintainer_email='autolabor@autolabor.com.cn',
    description='Navigation-independent camera-gimbal atomic capability for ROS2.',
    license='BSD-3-Clause',
    entry_points={
        'console_scripts': [
            'camera_gimbal_capability = camera_gimbal_capability.capability_node:main',
        ],
    },
)
