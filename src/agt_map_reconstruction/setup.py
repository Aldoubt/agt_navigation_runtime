from setuptools import find_packages, setup

package_name = "agt_map_reconstruction"

setup(
    name=package_name,
    version="0.1.0",
    packages=find_packages(),
    data_files=[
        ("share/ament_index/resource_index/packages", ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
        ("share/" + package_name + "/config", ["config/reconstruction.yaml", "config/reconstruction_realbag.yaml", "config/reconstruction_lio_bag.yaml"]),
        ("share/" + package_name + "/launch", ["launch/reconstruction.launch.py", "launch/lio_mapping_bag.launch.py"]),
        ("share/" + package_name + "/rviz", ["rviz/reconstruction.rviz"]),
    ],
    install_requires=["setuptools", "numpy", "PyYAML"],
    entry_points={
        "console_scripts": [
            "reconstruction_node = agt_map_reconstruction.reconstruction_node:main",
        ],
    },
)
