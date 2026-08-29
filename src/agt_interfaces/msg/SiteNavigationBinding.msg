# Read-only binding from the authoritative Active Site to navigation assets.
# This is asset identity evidence only; Nav2 lifecycle/readiness belongs to P1-05.
uint8 STATE_UNKNOWN=0
uint8 STATE_READY=1
uint8 STATE_BLOCKED=2
uint8 STATE_ERROR=3

std_msgs/Header header
uint8 state

string site_id
string site_revision
string site_hash
string manifest_sha256

string navigation_yaml
string navigation_yaml_sha256
string navigation_image
string navigation_image_sha256

string localization_pcd
string localization_pcd_sha256
string processing_record

string[] blocker_codes
string[] messages
