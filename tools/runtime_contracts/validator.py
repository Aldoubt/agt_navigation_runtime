"""Backward-compatible repository tooling import path.

The canonical implementation lives in the installable ``agt_runtime_contracts``
package so installed Runtime components do not depend on the repository ``tools``
tree. When this wrapper is executed directly from a source checkout, it adds the
canonical package source directory to ``sys.path`` only for tooling compatibility.
"""

from pathlib import Path
import sys

try:
    from agt_runtime_contracts.validator import (
        ValidationIssue,
        ValidationReport,
        load_hashes,
        load_yaml,
        navigation_image_asset,
        resolve_relative_path,
        sha256_file,
        validate_runtime_contracts,
        validate_site_package,
        validate_vehicle_profile,
    )
except ModuleNotFoundError as exc:
    if exc.name != "agt_runtime_contracts":
        raise
    canonical_src = Path(__file__).resolve().parents[2] / "src/agt_runtime_contracts"
    if str(canonical_src) not in sys.path:
        sys.path.insert(0, str(canonical_src))
    from agt_runtime_contracts.validator import (
        ValidationIssue,
        ValidationReport,
        load_hashes,
        load_yaml,
        navigation_image_asset,
        resolve_relative_path,
        sha256_file,
        validate_runtime_contracts,
        validate_site_package,
        validate_vehicle_profile,
    )

__all__ = [
    "ValidationIssue",
    "ValidationReport",
    "load_hashes",
    "load_yaml",
    "navigation_image_asset",
    "resolve_relative_path",
    "sha256_file",
    "validate_runtime_contracts",
    "validate_site_package",
    "validate_vehicle_profile",
]
