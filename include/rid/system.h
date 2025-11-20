#ifndef _RID_SYSTEM_H
#define _RID_SYSTEM_H

#include <stdint.h>
#include <stddef.h>

#include "rid/header.h"

typedef struct
__attribute__((__packed__)) rid_system {
    uint8_t protocol_version: 4;
    uint8_t message_type : 4;

    uint8_t operator_location_type: 2;
    uint8_t classification_type: 3;
    uint8_t reserved_1: 3;

    int32_t operator_latitude;
    int32_t operator_longitude;

    uint16_t area_count;
    uint8_t area_radius;
    uint16_t area_ceiling;
    uint16_t area_floor;

    uint8_t ua_classification_class: 4;
    uint8_t ua_classification_category: 4;

    uint16_t operator_altitude;
    uint32_t timestamp;

    uint8_t reserved_2;
} rid_system_t;

typedef enum rid_operator_location_type {
    RID_OPERATOR_LOCATION_TYPE_TAKEOFF,
    RID_OPERATOR_LOCATION_TYPE_DYNAMIC,
    RID_OPERATOR_LOCATION_TYPE_FIXED,
    RID_OPERATOR_LOCATION_TYPE_RESERVED,
} rid_operator_location_type_t;

typedef enum rid_classification_type {
    RID_CLASSIFICATION_TYPE_UNDECLARED,
    RID_CLASSIFICATION_TYPE_EUROPEAN_UNION,
    /* 2-7: Reserved */
} rid_classification_type_t;

typedef enum rid_ua_classification_category {
    RID_UA_CLASSIFICATION_CATEGORY_UNDEFINED,
    RID_UA_CLASSIFICATION_CATEGORY_OPEN,
    RID_UA_CLASSIFICATION_CATEGORY_SPECIFIC,
    RID_UA_CLASSIFICATION_CATEGORY_CERTIFIED,
    /* 4-15: Reserved */
} rid_ua_classification_category_t;

typedef enum rid_ua_classification_class {
    RID_UA_CLASSIFICATION_CLASS_UNDEFINED,
    RID_UA_CLASSIFICATION_CLASS_0,
    RID_UA_CLASSIFICATION_CLASS_1,
    RID_UA_CLASSIFICATION_CLASS_2,
    RID_UA_CLASSIFICATION_CLASS_3,
    RID_UA_CLASSIFICATION_CLASS_4,
    RID_UA_CLASSIFICATION_CLASS_5,
    RID_UA_CLASSIFICATION_CLASS_6,
    /* 8-15: Reserved */
} rid_ua_classification_class_t;

#endif
