
uint16 ERROR_NONE=0
uint16 ERROR_INVALID_REQUEST=1
uint16 ERROR_MAP_NOT_READY=2
uint16 ERROR_INTERNAL=255

bool success
uint16 error_code
string blocker_code
string operator_message
string technical_message
string map_id
string map_version_id
string[] task_group_ids
string[] names
uint32[] revisions
string[] content_sha256
uint32[] enabled_point_counts
string[] updated_at
string[] validation_states
