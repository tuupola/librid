#include <stddef.h>
#include <stdint.h>

#include "rid/header.h"
#include "rid/location.h"

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
