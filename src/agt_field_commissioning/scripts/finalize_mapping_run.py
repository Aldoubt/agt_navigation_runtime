#!/usr/bin/env python3

import argparse
import json

from agt_field_commissioning.mapping_artifacts import finalize_mapping_run


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Validate FAST-LIVO2 shutdown artifacts and freeze mapping-run evidence."
    )
    parser.add_argument("--runtime-dir", default="runtime")
    parser.add_argument("--site-id", required=True)
    parser.add_argument("--run-id", required=True)
    args = parser.parse_args()

    evidence = finalize_mapping_run(args.runtime_dir, args.site_id, args.run_id)
    print(json.dumps(evidence, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
