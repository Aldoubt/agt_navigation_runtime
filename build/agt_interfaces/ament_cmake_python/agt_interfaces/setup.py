from setuptools import find_packages
from setuptools import setup

setup(
    name='agt_interfaces',
    version='0.1.0',
    packages=find_packages(
        include=('agt_interfaces', 'agt_interfaces.*')),
)
