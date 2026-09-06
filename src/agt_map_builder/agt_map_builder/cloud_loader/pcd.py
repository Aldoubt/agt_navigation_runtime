from pathlib import Path
import numpy as np


def load_pcd(path: str | Path) -> np.ndarray:
    """Load x/y/z from an ASCII or ordinary binary PCD file."""
    path = Path(path)
    with path.open("rb") as stream:
        header = []
        while True:
            line = stream.readline()
            if not line:
                raise ValueError("PCD header has no DATA declaration")
            decoded = line.decode("ascii", errors="strict").strip()
            header.append(decoded)
            if decoded.upper().startswith("DATA"):
                break
        fields = next((line.split()[1:] for line in header if line.upper().startswith("FIELDS ")), None)
        if not fields or not all(name in fields for name in ("x", "y", "z")):
            raise ValueError("PCD must contain x, y and z fields")
        indices = [fields.index(name) for name in ("x", "y", "z")]
        data_mode = header[-1].split(None, 1)[1].lower() if len(header[-1].split()) > 1 else ""
        if data_mode == "binary":
            sizes = [int(x) for x in next(line.split()[1:] for line in header if line.upper().startswith("SIZE "))]
            types = next(line.split()[1:] for line in header if line.upper().startswith("TYPE "))
            counts_line = next((line.split()[1:] for line in header if line.upper().startswith("COUNT ")), ["1"] * len(fields))
            counts = [int(x) for x in counts_line]
            if any(count != 1 for count in counts):
                raise ValueError("Binary PCD fields with COUNT > 1 are not supported")
            dtype_map = {("F", 4): "<f4", ("F", 8): "<f8", ("I", 1): "<i1", ("I", 2): "<i2", ("I", 4): "<i4", ("I", 8): "<i8", ("U", 1): "<u1", ("U", 2): "<u2", ("U", 4): "<u4", ("U", 8): "<u8"}
            try:
                dtype = np.dtype([(name, dtype_map[(kind, size)]) for name, kind, size in zip(fields, types, sizes)])
            except KeyError as exc:
                raise ValueError("Unsupported binary PCD field type or size") from exc
            points_count = int(next(line.split()[1] for line in header if line.upper().startswith("POINTS ")))
            records = np.frombuffer(stream.read(), dtype=dtype, count=points_count)
            points = np.column_stack([records[fields[i]].astype(np.float64) for i in indices])
            return points[np.isfinite(points).all(axis=1)]
        if data_mode not in ("ascii",):
            raise ValueError("Unsupported PCD DATA format: " + data_mode)
        values = []
        for raw in stream:
            text = raw.decode("ascii", errors="strict").strip()
            if text and not text.startswith("#"):
                parts = text.split()
                try:
                    values.append([float(parts[i]) for i in indices])
                except (IndexError, ValueError) as exc:
                    raise ValueError(f"Invalid PCD data row: {text!r}") from exc
    points = np.asarray(values, dtype=np.float64).reshape((-1, 3))
    points = points[np.isfinite(points).all(axis=1)]
    if not len(points):
        raise ValueError("PCD contains no finite points")
    return points
