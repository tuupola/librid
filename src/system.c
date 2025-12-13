#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "rid/header.h"
#include "rid/system.h"

rid_error_t
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

rid_error_t
rid_set_operator_location_type(rid_system_t *system, rid_operator_location_type_t type) {
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
rid_get_operator_location_type(const rid_system_t *system) {
    return (rid_operator_location_type_t)system->operator_location_type;
}

rid_error_t
rid_set_classification_type(rid_system_t *system, rid_classification_type_t type) {
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
rid_get_classification_type(const rid_system_t *system) {
    return (rid_classification_type_t)system->classification_type;
}

rid_error_t
rid_set_ua_classification_category(rid_system_t *system, rid_ua_classification_category_t category) {
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
rid_get_ua_classification_category(const rid_system_t *system) {
    return (rid_ua_classification_category_t)system->ua_classification_category;
}

rid_error_t
rid_set_ua_classification_class(rid_system_t *system, rid_ua_classification_class_t class) {
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
rid_get_ua_classification_class(const rid_system_t *system) {
    return (rid_ua_classification_class_t)system->ua_classification_class;
}

rid_error_t
rid_set_operator_latitude(rid_system_t *system, double degrees) {
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
rid_get_operator_latitude(const rid_system_t *system) {
    return (double)system->operator_latitude / 10000000.0;
}

rid_error_t
rid_set_operator_longitude(rid_system_t *system, double degrees) {
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
rid_get_operator_longitude(const rid_system_t *system) {
    return (double)system->operator_longitude / 10000000.0;
}

rid_error_t
rid_set_operator_altitude(rid_system_t *system, float altitude) {
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
rid_get_operator_altitude(const rid_system_t *system) {
    return ((float)system->operator_altitude * 0.5f) - 1000.0f;
}

rid_error_t
rid_set_area_count(rid_system_t *system, uint16_t count) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    system->area_count = count;

    return RID_SUCCESS;
}

uint16_t
rid_get_area_count(const rid_system_t *system) {
    return system->area_count;
}

rid_error_t
rid_set_area_radius(rid_system_t *system, uint16_t meters) {
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
rid_get_area_radius(const rid_system_t *system) {
    return (uint16_t)system->area_radius * 10;
}

rid_error_t
rid_set_area_ceiling(rid_system_t *system, float altitude) {
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
rid_get_area_ceiling(const rid_system_t *system) {
    return ((float)system->area_ceiling * 0.5f) - 1000.0f;
}

rid_error_t
rid_set_area_floor(rid_system_t *system, float altitude) {
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
rid_get_area_floor(const rid_system_t *system) {
    return ((float)system->area_floor * 0.5f) - 1000.0f;
}

rid_error_t
rid_set_system_timestamp(rid_system_t *system, uint32_t timestamp) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    system->timestamp = timestamp;

    return RID_SUCCESS;
}

uint32_t
rid_get_system_timestamp(const rid_system_t *system) {
    return system->timestamp;
}

rid_error_t
rid_set_system_timestamp_from_unixtime(rid_system_t *system, uint32_t unixtime) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    system->timestamp = unixtime - RID_SYSTEM_TIMESTAMP_EPOCH;

    return RID_SUCCESS;
}
