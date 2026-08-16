from setuptools import find_packages
from setuptools import setup

setup(
    name='agt_navigation',
    version='0.1.0',
    packages=find_packages(
        include=('agt_navigation', 'agt_navigation.*')),
)
