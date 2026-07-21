# Machine-readable global localization state. The string status topic remains
# a human-facing compatibility channel and is not part of the control contract.
uint8 STATE_UNINITIALIZED=0
uint8 STATE_SEARCHING=1
uint8 STATE_VERIFYING=2
uint8 STATE_TRACKING=3
uint8 STATE_DEGRADED=4
uint8 STATE_RECOVERING=5
uint8 STATE_LOST=6
uint8 STATE_ERROR=7

uint16 ERROR_NONE=0
uint16 ERROR_MAP_NOT_READY=100
uint16 ERROR_SCAN_TOO_SMALL=101
uint16 ERROR_BACKEND_FAILED=102
uint16 ERROR_FITNESS_REJECTED=103
uint16 ERROR_INVALID_INITIAL_GUESS=104
uint16 ERROR_INVALID_REQUEST=105
uint16 ERROR_TIMEOUT=106
uint16 ERROR_CANCELED=107
uint16 ERROR_AMBIGUOUS_RESULT=108
uint16 ERROR_STALE_STATUS=109
uint16 ERROR_TF_UNAVAILABLE=110
uint16 ERROR_MAP_HASH_MISMATCH=111
uint16 ERROR_NO_CANDIDATES=112

std_msgs/Header header
uint8 state
bool pose_valid
bool localization_accepted
bool has_converged
bool ambiguous_result
bool status_stale
uint16 error_code

string backend
string candidate_source
string candidate_id
string map_id
string map_hash

geometry_msgs/PoseWithCovarianceStamped global_pose

float64 fitness_score
float64 overlap_ratio
float64 inlier_ratio
float64 ambiguity_score
float64 translation_innovation
float64 yaw_innovation
float64 runtime_ms

uint32 tested_candidates
uint32 total_candidates
uint32 consecutive_successes
uint32 consecutive_failures

string message
