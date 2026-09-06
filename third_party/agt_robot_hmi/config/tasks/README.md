# Inspection task files

Each task contains a name and ordered points. `action` values are interpreted
by the runtime, not by the Qt application.

```yaml
task_name: field_inspection
inspection_points:
  - id: P001
    pose: {x: 10.5, y: 2.3, yaw: 1.57}
    action: [capture_image, inference]
```
