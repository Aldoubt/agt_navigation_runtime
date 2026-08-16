from setuptools import find_packages
from setuptools import setup

setup(
    name='bunker_msgs',
    version='0.1.0',
    packages=find_packages(
        include=('bunker_msgs', 'bunker_msgs.*')),
)
