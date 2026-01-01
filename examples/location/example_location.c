#include <stdio.h>
#include <stdint.h>

#include "rid/location.h"

static void
hexdump(const void *data, size_t size)
{
    const uint8_t *bytes = (const uint8_t *)data;

    for (size_t i = 0; i < size; ++i) {
        if (i > 0 && i % 16 == 0) {
            printf("\n");
        } else if (i > 0 && i % 8 == 0) {
            printf(" ");
        }
        printf("%02x ", bytes[i]);
    }
    printf("\n\n");
}

int
main(void)
{
    /* [full_example] */
    rid_location_t location;

    rid_location_init(&location);
    rid_location_set_operational_status(&location, RID_OPERATIONAL_STATUS_AIRBORNE);
    rid_location_set_height_type(&location, RID_HEIGHT_TYPE_ABOVE_TAKEOFF);
    rid_location_set_latitude(&location, 60.1699);
    rid_location_set_longitude(&location, 24.9384);
    rid_location_set_geodetic_altitude(&location, 120.5f);
    rid_location_set_height(&location, 50.0f);
    rid_location_set_speed(&location, 15.5f);
    rid_location_set_vertical_speed(&location, 2.0f);
    rid_location_set_track_direction(&location, 45);
    rid_location_set_timestamp(&location, 12345);
    rid_location_set_horizontal_accuracy(&location, RID_HORIZONTAL_ACCURACY_10M);
    rid_location_set_vertical_accuracy(&location, RID_VERTICAL_ACCURACY_10M);
    rid_location_set_speed_accuracy(&location, RID_SPEED_ACCURACY_1MS);
    rid_location_set_timestamp_accuracy(&location, RID_TIMESTAMP_ACCURACY_0_1S);

    hexdump(&location, sizeof(location));

    double latitude = rid_location_get_latitude(&location);
    double longitude = rid_location_get_longitude(&location);
    float altitude = rid_location_get_geodetic_altitude(&location);
    float height = rid_location_get_height(&location);
    float speed = rid_location_get_speed(&location);
    float vspeed = rid_location_get_vertical_speed(&location);
    uint16_t direction = rid_location_get_track_direction(&location);
    rid_operational_status_t status = rid_location_get_operational_status(&location);

    printf("Latitude:   %.4f\n", latitude);
    printf("Longitude:  %.4f\n", longitude);
    printf("Altitude:   %.1f m\n", altitude);
    printf("Height:     %.1f m\n", height);
    printf("Speed:      %.1f m/s\n", speed);
    printf("V.Speed:    %.1f m/s\n", vspeed);
    printf("Direction:  %u deg\n", direction);
    printf("Status:     %d\n", status);
    /* [full_example] */

    return 0;
}
