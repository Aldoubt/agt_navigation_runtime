from setuptools import find_packages
from setuptools import setup

setup(
    name='agt_experiment_manager',
    version='0.1.0',
    packages=find_packages(
        include=('agt_experiment_manager', 'agt_experiment_manager.*')),
)
