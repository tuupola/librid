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
    rid_location_set_latitude(&location, 62.683472);
    rid_location_set_longitude(&location, 21.974944);
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
    rid_location_set_pressure_altitude(&location, 101.3f);
    rid_location_set_baro_altitude_accuracy(&location, RID_VERTICAL_ACCURACY_3M);

    hexdump(&location, sizeof(location));

    rid_height_type_t height_type = rid_location_get_height_type(&location);
    rid_operational_status_t status = rid_location_get_operational_status(&location);
    uint16_t direction = rid_location_get_track_direction(&location);
    float speed = rid_location_get_speed(&location);
    float vspeed = rid_location_get_vertical_speed(&location);
    double latitude = rid_location_get_latitude(&location);
    double longitude = rid_location_get_longitude(&location);
    float pressure_alt = rid_location_get_pressure_altitude(&location);
    float geodetic_alt = rid_location_get_geodetic_altitude(&location);
    float height = rid_location_get_height(&location);
    rid_horizontal_accuracy_t h_accuracy = rid_location_get_horizontal_accuracy(&location);
    rid_vertical_accuracy_t v_accuracy = rid_location_get_vertical_accuracy(&location);
    rid_speed_accuracy_t s_accuracy = rid_location_get_speed_accuracy(&location);
    rid_vertical_accuracy_t baro_accuracy = rid_location_get_baro_altitude_accuracy(&location);
    uint16_t timestamp = rid_location_get_timestamp(&location);
    rid_timestamp_accuracy_t ts_accuracy = rid_location_get_timestamp_accuracy(&location);

    printf("Height Type:         %s\n", rid_height_type_to_string(height_type));
    printf("Status:              %s\n", rid_operational_status_to_string(status));
    printf("Direction:           %u deg\n", direction);
    printf("Speed:               %.1f m/s\n", speed);
    printf("Vertical Speed:      %.1f m/s\n", vspeed);
    printf("Latitude:            %.6f\n", latitude);
    printf("Longitude:           %.6f\n", longitude);
    printf("Pressure Alt:        %.1f m\n", pressure_alt);
    printf("Geodetic Alt:        %.1f m\n", geodetic_alt);
    printf("Height:              %.1f m\n", height);
    printf("Horizontal Accuracy: %s\n", rid_horizontal_accuracy_to_string(h_accuracy));
    printf("Vertical Accuracy:   %s\n", rid_vertical_accuracy_to_string(v_accuracy));
    printf("Speed Accuracy:      %s\n", rid_speed_accuracy_to_string(s_accuracy));
    printf("Baro Accuracy:       %s\n", rid_vertical_accuracy_to_string(baro_accuracy));
    printf("Timestamp:           %u ds\n", timestamp);
    printf("Timestamp Accuracy:  %s\n", rid_timestamp_accuracy_to_string(ts_accuracy));
    /* [full_example] */

    return 0;
}
