#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "rid/header.h"
#include "rid/location.h"

rid_error_t
rid_location_init(rid_location_t *location) {
    if (location == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* ASTM F3411-22 Table 7 */
    memset(location, 0, sizeof(rid_location_t));

    location->protocol_version = VERSION_2;
    location->message_type = RID_MESSAGE_TYPE_LOCATION;

    location->track_direction = RID_TRACK_DIRECTION_UNKNOWN_ENCODED;
    location->ew_direction = RID_EW_DIRECTION_EAST;

    location->speed = RID_SPEED_INVALID_ENCODED;
    location->speed_multiplier = 1;

    location->vertical_speed = RID_VERTICAL_SPEED_INVALID_ENCODED;

    return RID_SUCCESS;
}

rid_error_t
rid_set_track_direction(rid_location_t *location, uint16_t degrees) {
    if (location == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* ASTM F3411-22 Table 6 */
    /* True north based direction in clockwise degrees. */
    /* If aircraft is not moving horizontally use unknown. */
    if (degrees == RID_TRACK_DIRECTION_UNKNOWN) {
        location->track_direction = RID_TRACK_DIRECTION_UNKNOWN_ENCODED;
        location->ew_direction = RID_EW_DIRECTION_EAST;
        return RID_SUCCESS;
    }

    /* Impossible direction */
    if (degrees > 359) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    /* Choose the EW direction flag */
    if (degrees < 180) {
        location->track_direction = (uint8_t)degrees;
        location->ew_direction = RID_EW_DIRECTION_EAST;
    } else {
        location->track_direction = (uint8_t)(degrees - 180);
        location->ew_direction = RID_EW_DIRECTION_WEST;
    }

    return RID_SUCCESS;
}

uint16_t
rid_get_track_direction(const rid_location_t *location) {

    /* Unknown or invalid */
    if (location->track_direction == RID_TRACK_DIRECTION_UNKNOWN_ENCODED) {
        return RID_TRACK_DIRECTION_UNKNOWN;
    }

    /* Add 180 to 8 bit value if facing west(ish) */
    if (location->ew_direction == RID_EW_DIRECTION_EAST) {
        return (uint16_t)location->track_direction;
    } else {
        return (uint16_t)(location->track_direction + 180);
    }
}

rid_error_t
rid_set_speed(rid_location_t *location, float speed_ms) {
    if (location == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* Cannot have negative speed */
    if (speed_ms < 0.0f) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    /* Invalid or unknown speed */
    if (speed_ms == RID_SPEED_INVALID) {
        location->speed = 255;
        location->speed_multiplier = 1;
        return RID_SUCCESS;
    }

    /* ASTM F3411-22 Table 7
     *
     * If Value <= 255*0.25
     *   EncodedValue = Value/0.25
     *   Set Multiplier Flag to 0
     * else if Value > 255*0.25 and Value < 254.25
     *   EncodedValue = (Value - (255*0.25))/0.75
     *   Set Multiplier Flag to 1
     * else (Value >= 254.25 m/s)
     *   EncodedValue = 254
     *   Set Multiplier Flag to 1
     */

    if (speed_ms <= 255.0f * 0.25f) {
        location->speed = (uint8_t)((speed_ms / 0.25f) + 0.5f);
        location->speed_multiplier = 0;
    } else if (speed_ms < 254.25f) {
        location->speed = (uint8_t)(((speed_ms - (255.0f * 0.25f)) / 0.75f) + 0.5f);
        location->speed_multiplier = 1;
    } else {
        location->speed = 254;
        location->speed_multiplier = 1;
    }

    return RID_SUCCESS;
}

float
rid_get_speed(const rid_location_t *location) {

    /* Invalid or unknown speed */
    if (location->speed == 255 && location->speed_multiplier == 1) {
        return RID_SPEED_INVALID;
    }

    if (location->speed_multiplier == 0) {
        /* Slow ie. 0 to 63.75 m/s */
        return (float)location->speed * 0.25f;
    } else {
        /* Fast ie. 63.76 to 254.25 m/s */
        return ((float)location->speed * 0.75f) + (255.0f * 0.25f);
    }
}

rid_error_t
rid_set_vertical_speed(rid_location_t *location, float speed_ms) {
    if (location == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* Invalid or unknown speed */
    if (speed_ms == RID_VERTICAL_SPEED_INVALID) {
        location->vertical_speed = RID_VERTICAL_SPEED_INVALID_ENCODED;
        return RID_SUCCESS;
    }

    /* ASTM F3411-22 Table 7 */

    if (speed_ms > 62.0f || speed_ms < -62.0f) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    if (speed_ms >= 0.0f) {
        location->vertical_speed = (int8_t)((speed_ms / 0.5f) + 0.5f);
    } else {
        location->vertical_speed = (int8_t)((speed_ms / 0.5f) - 0.5f);
    }

    return RID_SUCCESS;
}

float
rid_get_vertical_speed(const rid_location_t *location) {

    if (location->vertical_speed == RID_VERTICAL_SPEED_INVALID_ENCODED) {
        return RID_VERTICAL_SPEED_INVALID;
    }

    return (float)location->vertical_speed * 0.5f;
}

rid_error_t
rid_set_latitude(rid_location_t *location, double degrees) {
    if (location == NULL) {
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
        location->latitude = (int32_t)((degrees * 10000000.0) + 0.5);
    } else {
        location->latitude = (int32_t)((degrees * 10000000.0) - 0.5);
    }

    return RID_SUCCESS;
}

double
rid_get_latitude(const rid_location_t *location) {
    return (double)location->latitude / 10000000.0;
}

rid_error_t
rid_set_longitude(rid_location_t *location, double degrees) {
    if (location == NULL) {
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
        location->longitude = (int32_t)((degrees * 10000000.0) + 0.5);
    } else {
        location->longitude = (int32_t)((degrees * 10000000.0) - 0.5);
    }

    return RID_SUCCESS;
}

double
rid_get_longitude(const rid_location_t *location) {
    return (double)location->longitude / 10000000.0;
}

rid_error_t
rid_set_height(rid_location_t *location, float height_m) {
    if (location == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* Invalid or unknown height */
    if (height_m == RID_HEIGHT_INVALID) {
        location->height = RID_HEIGHT_INVALID_ENCODED;
        return RID_SUCCESS;
    }

    /* ASTM F3411-22 Table 7
     * Encoded = (value + 1000) / 0.5
     * -1000 to 31767 meters
     * Invalid or unknown: -1000
     */

    if (height_m < -1000.0f || height_m > 31767.0f) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    /* Encode with rounding */
    location->height = (uint16_t)(((height_m + 1000.0f) / 0.5f) + 0.5f);

    return RID_SUCCESS;
}

float
rid_get_height(const rid_location_t *location) {
    return ((float)location->height * 0.5f) - 1000.0f;
}

rid_error_t
rid_set_pressure_altitude(rid_location_t *location, float altitude_m) {
    if (location == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* Invalid or unknown altitude */
    if (altitude_m == RID_PRESSURE_ALTITUDE_INVALID) {
        location->pressure_altitude = RID_PRESSURE_ALTITUDE_INVALID_ENCODED;
        return RID_SUCCESS;
    }

    /* ASTM F3411-22 Table 7
     * Encoded = (value + 1000) / 0.5
     * -1000 to 31767 meters
     * Invalid or unknown: -1000
     */

    if (altitude_m < -1000.0f || altitude_m > 31767.0f) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    /* Encode with rounding */
    location->pressure_altitude = (uint16_t)(((altitude_m + 1000.0f) / 0.5f) + 0.5f);

    return RID_SUCCESS;
}

float
rid_get_pressure_altitude(const rid_location_t *location) {
    return ((float)location->pressure_altitude * 0.5f) - 1000.0f;
}

rid_error_t
rid_set_geodetic_altitude(rid_location_t *location, float altitude_m) {
    if (location == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* Invalid or unknown altitude */
    if (altitude_m == RID_GEODETIC_ALTITUDE_INVALID) {
        location->geodetic_altitude = RID_GEODETIC_ALTITUDE_INVALID_ENCODED;
        return RID_SUCCESS;
    }

    /* ASTM F3411-22 Table 7
     * Encoded = (value + 1000) / 0.5
     * -1000 to 31767 meters
     * Invalid or unknown: -1000
     */

    if (altitude_m < -1000.0f || altitude_m > 31767.0f) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    /* Encode with rounding */
    location->geodetic_altitude = (uint16_t)(((altitude_m + 1000.0f) / 0.5f) + 0.5f);

    return RID_SUCCESS;
}

float
rid_get_geodetic_altitude(const rid_location_t *location) {
    return ((float)location->geodetic_altitude * 0.5f) - 1000.0f;
}

rid_error_t
rid_set_height_type(rid_location_t *location, rid_height_type_t type) {
    if (location == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (type != RID_HEIGHT_TYPE_ABOVE_TAKEOFF && type != RID_HEIGHT_TYPE_AGL) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    location->height_type = (uint8_t)type;

    return RID_SUCCESS;
}

rid_height_type_t
rid_get_height_type(const rid_location_t *location) {
    return (rid_height_type_t)location->height_type;
}

rid_error_t
rid_set_operational_status(rid_location_t *location, rid_operational_status_t status) {
    if (location == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (status > RID_OPERATIONAL_STATUS_RESERVED_15) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    location->operational_status = (uint8_t)status;

    return RID_SUCCESS;
}

rid_operational_status_t
rid_get_operational_status(const rid_location_t *location) {
    return (rid_operational_status_t)location->operational_status;
}

rid_error_t
rid_set_speed_accuracy(rid_location_t *location, rid_speed_accuracy_t accuracy) {
    if (location == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (accuracy > RID_SPEED_ACCURACY_RESERVED_15) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    location->speed_accuracy = (uint8_t)accuracy;

    return RID_SUCCESS;
}

rid_speed_accuracy_t
rid_get_speed_accuracy(const rid_location_t *location) {
    return (rid_speed_accuracy_t)location->speed_accuracy;
}

rid_error_t
rid_set_horizontal_accuracy(rid_location_t *location, rid_horizontal_accuracy_t accuracy) {
    if (location == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (accuracy > RID_HORIZONTAL_ACCURACY_RESERVED_15) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    location->horizontal_accuracy = (uint8_t)accuracy;

    return RID_SUCCESS;
}

rid_horizontal_accuracy_t
rid_get_horizontal_accuracy(const rid_location_t *location) {
    return (rid_horizontal_accuracy_t)location->horizontal_accuracy;
}

rid_error_t
rid_set_vertical_accuracy(rid_location_t *location, rid_vertical_accuracy_t accuracy) {
    if (location == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (accuracy > RID_VERTICAL_ACCURACY_RESERVED_15) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    location->vertical_accuracy = (uint8_t)accuracy;

    return RID_SUCCESS;
}

rid_vertical_accuracy_t
rid_get_vertical_accuracy(const rid_location_t *location) {
    return (rid_vertical_accuracy_t)location->vertical_accuracy;
}
