
uint16 ERROR_NONE=0
uint16 ERROR_INVALID_REQUEST=1
uint16 ERROR_REVISION_CONFLICT=2
uint16 ERROR_CONTENT_HASH_MISMATCH=3
uint16 ERROR_SCHEMA_INVALID=4
uint16 ERROR_MAP_NOT_READY=5
uint16 ERROR_INTERNAL=255

bool success
uint16 error_code
string blocker_code
string operator_message
string technical_message
bool duplicate_request
string map_id
string map_version_id
string task_group_id
uint32 revision
string content_sha256
string task_json
