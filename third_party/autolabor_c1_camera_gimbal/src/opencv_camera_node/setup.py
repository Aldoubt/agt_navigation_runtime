from setuptools import setup
setup(
    name='opencv_camera_node',
    version='1.0.0',
    packages=['opencv_camera_node'],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/opencv_camera_node']),
        ('share/opencv_camera_node', ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    entry_points={'console_scripts': [
        'opencv_camera_node = opencv_camera_node.opencv_camera_node:main',
    ]},
)
