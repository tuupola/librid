#include <math.h>
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
