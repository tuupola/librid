/*

MIT License

Copyright (c) 2025-2026 Mika Tuupola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-cut-

This file is part of librid: https://github.com/tuupola/librid

SPDX-License-Identifier: MIT

*/

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "rid/message.h"
#include "rid/system.h"

int
rid_system_init(rid_system_t *system) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    memset(system, 0, sizeof(rid_system_t));
    system->protocol_version = RID_PROTOCOL_VERSION_2;
    system->message_type = RID_MESSAGE_TYPE_SYSTEM;
    system->area_count = 1;

    return RID_SUCCESS;
}

int
rid_system_validate(const rid_system_t *system) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* Valid protocol versions: 0, 1, 2, or 0x0F (private use) */
    if (system->protocol_version > RID_PROTOCOL_VERSION_2 &&
        system->protocol_version != RID_PROTOCOL_PRIVATE_USE) {
        return RID_ERROR_INVALID_PROTOCOL_VERSION;
    }

    if (system->message_type != RID_MESSAGE_TYPE_SYSTEM) {
        return RID_ERROR_WRONG_MESSAGE_TYPE;
    }

    /* Operator latitude: encoded as value * 10^7, valid range -90 to +90 degrees */
    if (system->operator_latitude < -900000000 ||
        system->operator_latitude > 900000000) {
        return RID_ERROR_INVALID_LATITUDE;
    }

    /* Operator longitude: encoded as value * 10^7, valid range -180 to +180 degrees */
    if (system->operator_longitude < -1800000000 ||
        system->operator_longitude > 1800000000) {
        return RID_ERROR_INVALID_LONGITUDE;
    }

    return RID_SUCCESS;
}

int
rid_system_set_operator_location_type(rid_system_t *system, rid_operator_location_type_t type) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (type > RID_OPERATOR_LOCATION_TYPE_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    system->operator_location_type = (uint8_t)type;

    return RID_SUCCESS;
}

rid_operator_location_type_t
rid_system_get_operator_location_type(const rid_system_t *system) {
    return (rid_operator_location_type_t)system->operator_location_type;
}

int
rid_system_set_classification_type(rid_system_t *system, rid_classification_type_t type) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (type > RID_CLASSIFICATION_TYPE_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    system->classification_type = (uint8_t)type;

    return RID_SUCCESS;
}

rid_classification_type_t
rid_system_get_classification_type(const rid_system_t *system) {
    return (rid_classification_type_t)system->classification_type;
}

int
rid_system_set_ua_classification_category(rid_system_t *system, rid_ua_classification_category_t category) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (category > RID_UA_CLASSIFICATION_CATEGORY_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    system->ua_classification_category = (uint8_t)category;

    return RID_SUCCESS;
}

rid_ua_classification_category_t
rid_system_get_ua_classification_category(const rid_system_t *system) {
    return (rid_ua_classification_category_t)system->ua_classification_category;
}

int
rid_system_set_ua_classification_class(rid_system_t *system, rid_ua_classification_class_t class) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (class > RID_UA_CLASSIFICATION_CLASS_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    system->ua_classification_class = (uint8_t)class;

    return RID_SUCCESS;
}

rid_ua_classification_class_t
rid_system_get_ua_classification_class(const rid_system_t *system) {
    return (rid_ua_classification_class_t)system->ua_classification_class;
}

int
rid_system_set_operator_latitude(rid_system_t *system, double degrees) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* ASTM F3411-22 Table 7
     * Encoded = value * 10^7
     * -90 to +90 degrees
     * Invalid or unknown: 0.0
     */

    if (degrees > 90.0 || degrees < -90.0) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    /* Encode with rounding */
    if (degrees >= 0.0) {
        system->operator_latitude = (int32_t)((degrees * 10000000.0) + 0.5);
    } else {
        system->operator_latitude = (int32_t)((degrees * 10000000.0) - 0.5);
    }

    return RID_SUCCESS;
}

double
rid_system_get_operator_latitude(const rid_system_t *system) {
    return (double)system->operator_latitude / 10000000.0;
}

int
rid_system_set_operator_longitude(rid_system_t *system, double degrees) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* ASTM F3411-22 Table 7
     * Encoded = value * 10^7
     * -180 to +180 degrees
     * Invalid or unknown: 0.0
     */

    if (degrees > 180.0 || degrees < -180.0) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    /* Encode with rounding */
    if (degrees >= 0.0) {
        system->operator_longitude = (int32_t)((degrees * 10000000.0) + 0.5);
    } else {
        system->operator_longitude = (int32_t)((degrees * 10000000.0) - 0.5);
    }

    return RID_SUCCESS;
}

double
rid_system_get_operator_longitude(const rid_system_t *system) {
    return (double)system->operator_longitude / 10000000.0;
}

int
rid_system_set_operator_altitude(rid_system_t *system, float altitude) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* Invalid or unknown altitude */
    if (altitude == RID_OPERATOR_ALTITUDE_INVALID) {
        system->operator_altitude = RID_OPERATOR_ALTITUDE_INVALID_ENCODED;
        return RID_SUCCESS;
    }

    /* ASTM F3411-22 Table 7
     * Encoded = (value + 1000) / 0.5
     * -1000 to 31767 meters
     * Invalid or unknown: -1000
     */

    if (altitude < -1000.0f || altitude > 31767.0f) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    /* Encode with rounding */
    system->operator_altitude = (uint16_t)(((altitude + 1000.0f) / 0.5f) + 0.5f);

    return RID_SUCCESS;
}

float
rid_system_get_operator_altitude(const rid_system_t *system) {
    return ((float)system->operator_altitude * 0.5f) - 1000.0f;
}

int
rid_system_set_area_count(rid_system_t *system, uint16_t count) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    system->area_count = count;

    return RID_SUCCESS;
}

uint16_t
rid_system_get_area_count(const rid_system_t *system) {
    return system->area_count;
}

int
rid_system_set_area_radius(rid_system_t *system, uint16_t meters) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* ASTM F3411-22 Table 11
     * meters * 10
     * 0 to 2550 meters
     */

    if (meters > RID_AREA_RADIUS_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    system->area_radius = (uint8_t)(meters / 10);

    return RID_SUCCESS;
}

uint16_t
rid_system_get_area_radius(const rid_system_t *system) {
    return (uint16_t)system->area_radius * 10;
}

int
rid_system_set_area_ceiling(rid_system_t *system, float altitude) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* ASTM F3411-22 Table 11
     * WGS-84 HAE
     * (altitude + 1000m) / 0.5
     * -1000 to 31767 meters
     */

    if (altitude < RID_AREA_CEILING_MIN || altitude > RID_AREA_CEILING_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    system->area_ceiling = (uint16_t)(((altitude + 1000.0f) / 0.5f) + 0.5f);

    return RID_SUCCESS;
}

float
rid_system_get_area_ceiling(const rid_system_t *system) {
    return ((float)system->area_ceiling * 0.5f) - 1000.0f;
}

int
rid_system_set_area_floor(rid_system_t *system, float altitude) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* ASTM F3411-22 Table 7
     * (altitude + 1000) / 0.5
     * -1000 to 31767 meters
     */

    if (altitude < RID_AREA_FLOOR_MIN || altitude > RID_AREA_FLOOR_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    system->area_floor = (uint16_t)(((altitude + 1000.0f) / 0.5f) + 0.5f);

    return RID_SUCCESS;
}

float
rid_system_get_area_floor(const rid_system_t *system) {
    return ((float)system->area_floor * 0.5f) - 1000.0f;
}

int
rid_system_set_timestamp(rid_system_t *system, uint32_t timestamp) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    system->timestamp = timestamp;

    return RID_SUCCESS;
}

uint32_t
rid_system_get_timestamp(const rid_system_t *system) {
    return system->timestamp;
}

int
rid_system_set_unixtime(rid_system_t *system, uint32_t unixtime) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    system->timestamp = unixtime - RID_SYSTEM_TIMESTAMP_EPOCH;

    return RID_SUCCESS;
}

const char *
rid_operator_location_type_to_string(rid_operator_location_type_t type) {
    switch (type) {
        case RID_OPERATOR_LOCATION_TYPE_TAKEOFF:
            return "RID_OPERATOR_LOCATION_TYPE_TAKEOFF";
        case RID_OPERATOR_LOCATION_TYPE_DYNAMIC:
            return "RID_OPERATOR_LOCATION_TYPE_DYNAMIC";
        case RID_OPERATOR_LOCATION_TYPE_FIXED:
            return "RID_OPERATOR_LOCATION_TYPE_FIXED";
        default:
            return "UNKNOWN";
    }
}

const char *
rid_classification_type_to_string(rid_classification_type_t type) {
    switch (type) {
        case RID_CLASSIFICATION_TYPE_UNDECLARED:
            return "RID_CLASSIFICATION_TYPE_UNDECLARED";
        case RID_CLASSIFICATION_TYPE_EUROPEAN_UNION:
            return "RID_CLASSIFICATION_TYPE_EUROPEAN_UNION";
        default:
            return "UNKNOWN";
    }
}

const char *
rid_ua_classification_category_to_string(rid_ua_classification_category_t category) {
    switch (category) {
        case RID_UA_CLASSIFICATION_CATEGORY_UNDEFINED:
            return "RID_UA_CLASSIFICATION_CATEGORY_UNDEFINED";
        case RID_UA_CLASSIFICATION_CATEGORY_OPEN:
            return "RID_UA_CLASSIFICATION_CATEGORY_OPEN";
        case RID_UA_CLASSIFICATION_CATEGORY_SPECIFIC:
            return "RID_UA_CLASSIFICATION_CATEGORY_SPECIFIC";
        case RID_UA_CLASSIFICATION_CATEGORY_CERTIFIED:
            return "RID_UA_CLASSIFICATION_CATEGORY_CERTIFIED";
        default:
            return "UNKNOWN";
    }
}

const char *
rid_ua_classification_class_to_string(rid_ua_classification_class_t class) {
    switch (class) {
        case RID_UA_CLASSIFICATION_CLASS_UNDEFINED:
            return "RID_UA_CLASSIFICATION_CLASS_UNDEFINED";
        case RID_UA_CLASSIFICATION_CLASS_0:
            return "RID_UA_CLASSIFICATION_CLASS_0";
        case RID_UA_CLASSIFICATION_CLASS_1:
            return "RID_UA_CLASSIFICATION_CLASS_1";
        case RID_UA_CLASSIFICATION_CLASS_2:
            return "RID_UA_CLASSIFICATION_CLASS_2";
        case RID_UA_CLASSIFICATION_CLASS_3:
            return "RID_UA_CLASSIFICATION_CLASS_3";
        case RID_UA_CLASSIFICATION_CLASS_4:
            return "RID_UA_CLASSIFICATION_CLASS_4";
        case RID_UA_CLASSIFICATION_CLASS_5:
            return "RID_UA_CLASSIFICATION_CLASS_5";
        case RID_UA_CLASSIFICATION_CLASS_6:
            return "RID_UA_CLASSIFICATION_CLASS_6";
        default:
            return "UNKNOWN";
    }
}
