#ifndef _RID_BASIC_ID_H
#define _RID_BASIC_ID_H

#include <stdint.h>

typedef struct
__attribute__((__packed__)) rid_basic_id {
    uint8_t protocol_version: 4;
    uint8_t message_type : 4;
    uint8_t ua_type: 4;
    uint8_t id_type: 4;
    char uas_id[20];
    char reserved[3];
} rid_basic_id_t;

typedef enum rid_basic_id_type {
    RID_ID_TYPE_NONE,
    RID_ID_TYPE_SERIAL_NUMBER,
    RID_ID_TYPE_CAA_REGISTRATION_ID,
    RID_ID_TYPE_UTM_ASSIGNED_UUID,
    RID_ID_TYPE_SPECIFIC_SESSION_ID,
} rid_basic_id_type_t;

typedef enum rid_ua_type {
    RID_UA_TYPE_NONE,
    RID_UA_TYPE_AEROPLANE_OR_FIXED_WING,
    RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR,
    RID_UA_TYPE_GYROPLANE,
    RID_UA_TYPE_HYBRID_LIFT,
    RID_UA_TYPE_ORNITHOPTER,
    RID_UA_TYPE_GLIDER,
    RID_UA_TYPE_KITE,
    RID_UA_TYPE_FREE_BALLOON,
    RID_UA_TYPE_CAPTIVE_BALLOON,
    RID_UA_TYPE_AIRSHIP,
    RID_UA_TYPE_FREE_FALL_PARACHUTE,
    RID_UA_TYPE_ROCKET,
    RID_UA_TYPE_TETHERED_POWERED_AIRCRAFT,
    RID_UA_TYPE_GROUND_OBSTACLE,
    RID_UA_TYPE_OTHER,
} rid_ua_type_t;

rid_basic_id_type_t rid_get_basic_id_type(const rid_basic_id_t *message);
rid_error_t rid_set_basic_id_type(rid_basic_id_t *message, rid_basic_id_type_t type);
rid_ua_type_t rid_get_ua_type(const rid_basic_id_t *message);
rid_error_t rid_set_ua_type(rid_basic_id_t *message, rid_ua_type_t type);
rid_error_t rid_get_uas_id(const rid_basic_id_t *message, char *buffer, size_t buffer_size);
rid_error_t rid_set_uas_id(rid_basic_id_t *message, const char *uas_id);

#endif