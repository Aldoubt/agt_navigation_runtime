#!/usr/bin/env python3
import argparse
from agt_inspection_exporter import export_run

parser = argparse.ArgumentParser()
parser.add_argument("run")
parser.add_argument("dataset")
args = parser.parse_args()
print(export_run(args.run, args.dataset))
