#ifndef _RID_MESSAGE_BASIC_ID_H
#define _RID_MESSAGE_BASIC_ID_H

#include <stdint.h>

typedef struct
__attribute__((__packed__)) rid_message_basic_id {
    uint8_t protocol_version: 4;
    uint8_t message_type : 4;
    uint8_t ua_type: 4;
    uint8_t id_type: 4;
    char uas_id[20];
    char reserved[3];
} rid_message_basic_id_t;

typedef enum rid_message_id_type {
    RID_MESSAGE_ID_TYPE_NONE,
    RID_MESSAGE_ID_TYPE_SERIAL_NUMBER,
    RID_MESSAGE_ID_TYPE_CAA_REGISTRATION_ID,
    RID_MESSAGE_ID_TYPE_UTM_ASSIGNED_UUID,
    RID_MESSAGE_ID_TYPE_SPECIFIC_SESSION_ID,
} rid_message_id_type_t;

typedef enum rid_message_ua_type {
    RID_MESSAGE_UA_TYPE_NONE,
    RID_MESSAGE_UA_TYPE_AEROPLANE_OR_FIXED_WING,
    RID_MESSAGE_UA_TYPE_HELICOPTER_OR_MULTIROTOR,
    RID_MESSAGE_UA_TYPE_GYROPLANE,
    RID_MESSAGE_UA_TYPE_HYBRID_LIFT,
    RID_MESSAGE_UA_TYPE_ORNITHOPTER,
    RID_MESSAGE_UA_TYPE_GLIDER,
    RID_MESSAGE_UA_TYPE_KITE,
    RID_MESSAGE_UA_TYPE_FREE_BALLOON,
    RID_MESSAGE_UA_TYPE_CAPTIVE_BALLOON,
    RID_MESSAGE_UA_TYPE_AIRSHIP,
    RID_MESSAGE_UA_TYPE_FREE_FALL_PARACHUTE,
    RID_MESSAGE_UA_TYPE_ROCKET,
    RID_MESSAGE_UA_TYPE_TETHERED_POWERED_AIRCRAFT,
    RID_MESSAGE_UA_TYPE_GROUND_OBSTACLE,
    RID_MESSAGE_UA_TYPE_OTHER,
} rid_message_ua_type_t;

uint8_t rid_message_get_id_type(const rid_message_basic_id_t *message);
uint8_t rid_message_get_ua_type(const rid_message_basic_id_t *message);
int32_t rid_message_set_id_type(rid_message_basic_id_t *message, rid_message_id_type_t type);
int32_t rid_message_set_ua_type(rid_message_basic_id_t *message, rid_message_ua_type_t type);

#endif