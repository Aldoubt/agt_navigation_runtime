#!/usr/bin/env python3
import argparse
import json
from agt_inspection_exporter import validate_dataset

parser = argparse.ArgumentParser()
parser.add_argument("dataset")
parser.add_argument("--tolerance-ms", type=float, default=50.0)
args = parser.parse_args()
report = validate_dataset(args.dataset, args.tolerance_ms)
print(json.dumps(report, ensure_ascii=False, indent=2))
raise SystemExit(0 if report["valid"] else 1)
