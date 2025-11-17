#ifndef _RID_LOCATION_H
#define _RID_LOCATION_H

#include <stdint.h>

#include "rid/header.h"

#define RID_TRACK_DIRECTION_UNKNOWN 361
#define RID_TRACK_DIRECTION_UNKNOWN_ENCODED 255

typedef enum rid_ew_direction {
    RID_EW_DIRECTION_EAST,
    RID_EW_DIRECTION_WEST,
} rid_ew_direction_t;

typedef enum rid_height_type {
    RID_HEIGHT_TYPE_ABOVE_TAKEOFF,
    RID_HEIGHT_TYPE_AGL,
} rid_height_type_t;

typedef enum rid_operational_status {
    RID_OPERATIONAL_STATUS_UNDECLARED,
    RID_OPERATIONAL_STATUS_GROUND,
    RID_OPERATIONAL_STATUS_AIRBORNE,
    RID_OPERATIONAL_STATUS_EMERGENCY,
    RID_OPERATIONAL_STATUS_REMOTE_ID_SYSTEM_FAILURE,
    RID_OPERATIONAL_STATUS_RESERVED_5,
    RID_OPERATIONAL_STATUS_RESERVED_6,
    RID_OPERATIONAL_STATUS_RESERVED_7,
    RID_OPERATIONAL_STATUS_RESERVED_8,
    RID_OPERATIONAL_STATUS_RESERVED_9,
    RID_OPERATIONAL_STATUS_RESERVED_10,
    RID_OPERATIONAL_STATUS_RESERVED_11,
    RID_OPERATIONAL_STATUS_RESERVED_12,
    RID_OPERATIONAL_STATUS_RESERVED_13,
    RID_OPERATIONAL_STATUS_RESERVED_14,
    RID_OPERATIONAL_STATUS_RESERVED_15,
} rid_operational_status_t;

typedef enum rid_horizontal_accuracy {
    RID_HORIZONTAL_ACCURACY_UNKNOWN,
    RID_HORIZONTAL_ACCURACY_18520M,
    RID_HORIZONTAL_ACCURACY_7408M,
    RID_HORIZONTAL_ACCURACY_3704M,
    RID_HORIZONTAL_ACCURACY_1852M,
    RID_HORIZONTAL_ACCURACY_926M,
    RID_HORIZONTAL_ACCURACY_555M,
    RID_HORIZONTAL_ACCURACY_185M,
    RID_HORIZONTAL_ACCURACY_93M,
    RID_HORIZONTAL_ACCURACY_30M,
    RID_HORIZONTAL_ACCURACY_10M,
    RID_HORIZONTAL_ACCURACY_3M,
    RID_HORIZONTAL_ACCURACY_1M,
    RID_HORIZONTAL_ACCURACY_RESERVED_13,
    RID_HORIZONTAL_ACCURACY_RESERVED_14,
    RID_HORIZONTAL_ACCURACY_RESERVED_15,
} rid_horizontal_accuracy_t;

typedef enum rid_vertical_accuracy {
    RID_VERTICAL_ACCURACY_UNKNOWN,
    RID_VERTICAL_ACCURACY_150M,
    RID_VERTICAL_ACCURACY_45M,
    RID_VERTICAL_ACCURACY_25M,
    RID_VERTICAL_ACCURACY_10M,
    RID_VERTICAL_ACCURACY_3M,
    RID_VERTICAL_ACCURACY_1M,
    RID_VERTICAL_ACCURACY_RESERVED_7,
    RID_VERTICAL_ACCURACY_RESERVED_8,
    RID_VERTICAL_ACCURACY_RESERVED_9,
    RID_VERTICAL_ACCURACY_RESERVED_10,
    RID_VERTICAL_ACCURACY_RESERVED_11,
    RID_VERTICAL_ACCURACY_RESERVED_12,
    RID_VERTICAL_ACCURACY_RESERVED_13,
    RID_VERTICAL_ACCURACY_RESERVED_14,
    RID_VERTICAL_ACCURACY_RESERVED_15,
} rid_vertical_accuracy_t;

typedef enum rid_speed_accuracy {
    RID_SPEED_ACCURACY_UNKNOWN,
    RID_SPEED_ACCURACY_10MS,
    RID_SPEED_ACCURACY_3MS,
    RID_SPEED_ACCURACY_1MS,
    RID_SPEED_ACCURACY_03MS,
    RID_SPEED_ACCURACY_RESERVED_5,
    RID_SPEED_ACCURACY_RESERVED_6,
    RID_SPEED_ACCURACY_RESERVED_7,
    RID_SPEED_ACCURACY_RESERVED_8,
    RID_SPEED_ACCURACY_RESERVED_9,
    RID_SPEED_ACCURACY_RESERVED_10,
    RID_SPEED_ACCURACY_RESERVED_11,
    RID_SPEED_ACCURACY_RESERVED_12,
    RID_SPEED_ACCURACY_RESERVED_13,
    RID_SPEED_ACCURACY_RESERVED_14,
    RID_SPEED_ACCURACY_RESERVED_15,
} rid_speed_accuracy_t;

typedef enum rid_timestamp_accuracy {
    RID_TIMESTAMP_ACCURACY_UNKNOWN,
    RID_TIMESTAMP_ACCURACY_0_1S,
    RID_TIMESTAMP_ACCURACY_0_2S,
    RID_TIMESTAMP_ACCURACY_0_3S,
    RID_TIMESTAMP_ACCURACY_0_4S,
    RID_TIMESTAMP_ACCURACY_0_5S,
    RID_TIMESTAMP_ACCURACY_0_6S,
    RID_TIMESTAMP_ACCURACY_0_7S,
    RID_TIMESTAMP_ACCURACY_0_8S,
    RID_TIMESTAMP_ACCURACY_0_9S,
    RID_TIMESTAMP_ACCURACY_1_0S,
    RID_TIMESTAMP_ACCURACY_1_1S,
    RID_TIMESTAMP_ACCURACY_1_2S,
    RID_TIMESTAMP_ACCURACY_1_3S,
    RID_TIMESTAMP_ACCURACY_1_4S,
    RID_TIMESTAMP_ACCURACY_1_5S,
} rid_timestamp_accuracy_t;

typedef struct
__attribute__((__packed__)) rid_location {
    /* Network byte order */
    uint8_t protocol_version: 4;
    uint8_t message_type : 4;

    uint8_t speed_multiplier: 1;
    uint8_t ew_direction: 1;
    uint8_t height_type: 1;
    uint8_t reserved_1: 1;
    uint8_t operational_status: 4;

    uint8_t track_direction;
    uint8_t speed;
    int8_t vertical_speed;

    /* Little-endian */
    int32_t latitude;
    int32_t longitude;
    uint16_t pressure_altitude;
    uint16_t geodetic_altitude;
    uint16_t height;

    uint8_t horizontal_accuracy: 4;
    uint8_t vertical_accuracy: 4;

    uint8_t speed_accuracy: 4;
    uint8_t baro_accuracy: 4;

    /* Little-endian */
    uint16_t timestamp;

    uint8_t timestamp_accuracy: 4;
    uint8_t reserved_2: 4;
    uint8_t reserved_3;
} rid_location_t;

rid_error_t rid_set_track_direction(rid_location_t *location, uint16_t degrees);
uint16_t rid_get_track_direction(const rid_location_t *location);

rid_error_t rid_set_speed(rid_location_t *location, float speed_ms);
float rid_get_speed(const rid_location_t *location);

#endif