#include <string.h>

#include "greatest.h"
#include "rid/header.h"
#include "rid/location.h"

TEST
test_set_and_get_track_direction(void) {
    /* Test all valid directions 0-359 */
    for (uint16_t degrees = 0; degrees <= 359; degrees++) {
        rid_location_t location;
        memset(&location, 0, sizeof(location));

        rid_error_t status = rid_set_track_direction(&location, degrees);
        ASSERT_EQ(RID_SUCCESS, status);

        uint16_t result = rid_get_track_direction(&location);
        ASSERT_EQ(degrees, result);
    }

    PASS();
}

TEST
test_track_direction_unknown(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test unknown or invalid value */
    rid_error_t status = rid_set_track_direction(&location, RID_TRACK_DIRECTION_UNKNOWN);
    ASSERT_EQ(RID_SUCCESS, status);

    uint16_t result = rid_get_track_direction(&location);
    ASSERT_EQ(RID_TRACK_DIRECTION_UNKNOWN, result);

    PASS();
}

TEST
test_track_direction_out_of_range(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test degrees > 359 but != 361 */
    rid_error_t status = rid_set_track_direction(&location, 360);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    /* Test degrees > 361 */
    status = rid_set_track_direction(&location, 500);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_and_get_speed_slow(void) {
    rid_location_t location;

    float test_speeds[] = {0.0f, 10.5f, 25.25f, 50.0f, 63.5f};

    for (size_t i = 0; i < sizeof(test_speeds) / sizeof(test_speeds[0]); i++) {
        memset(&location, 0, sizeof(location));

        rid_error_t status = rid_set_speed(&location, test_speeds[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        ASSERT_EQ(0, location.speed_multiplier);

        float result = rid_get_speed(&location);

        /*  0.25 m/s resolution  */
        ASSERT_IN_RANGE(test_speeds[i] - 0.13f, result, test_speeds[i] + 0.13f);
    }

    PASS();
}

TEST
test_set_and_get_speed_fast(void) {
    rid_location_t location;

    float test_speeds[] = {64.0f, 100.0f, 150.5f, 200.0f, 254.0f};

    for (size_t i = 0; i < sizeof(test_speeds) / sizeof(test_speeds[0]); i++) {
        memset(&location, 0, sizeof(location));

        rid_error_t status = rid_set_speed(&location, test_speeds[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        ASSERT_EQ(1, location.speed_multiplier);

        float result = rid_get_speed(&location);

        /* 0.75 m/s resolution  */
        ASSERT_IN_RANGE(test_speeds[i] - 0.38f, result, test_speeds[i] + 0.38f);
    }

    PASS();
}

TEST
test_speed_boundary_transition(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* 63.75 should use multiplier = 0 */
    rid_error_t status = rid_set_speed(&location, 63.75f);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(0, location.speed_multiplier);
    /* 255 * 0.25 = 63.75 */
    ASSERT_EQ(255, location.speed);

    /* 64.0 should use multiplier = 1 */
    memset(&location, 0, sizeof(location));
    status = rid_set_speed(&location, 64.0f);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(1, location.speed_multiplier);
    /* round((0 * 0.75) + 63.75) = 64 */
    ASSERT_EQ(0, location.speed);

    PASS();
}

TEST
test_maximum_speed(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test maximum speed (>= 254.25 m/s) */
    rid_error_t status = rid_set_speed(&location, 300.0f);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(1, location.speed_multiplier);
    ASSERT_EQ(254, location.speed);

    float result = rid_get_speed(&location);
    ASSERT_EQ(254.25f, result);

    PASS();
}

TEST
test_negative_speed(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Speed cannot be negative  */
    rid_error_t status = rid_set_speed(&location, -10.0f);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_invalid_speed(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test invalid or unknown speed */
    rid_error_t status = rid_set_speed(&location, RID_SPEED_INVALID);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(255, location.speed);
    ASSERT_EQ(1, location.speed_multiplier);

    /* Should decode back to RID_SPEED_INVALID */
    float result = rid_get_speed(&location);
    ASSERT_EQ(RID_SPEED_INVALID, result);

    PASS();
}

TEST
test_set_and_get_vertical_speed(void) {
    rid_location_t location;

    float test_speeds[] = {0.0f, 7.5f, 30.0f, 62.0f, -7.5f, -30.0f, -62.0f};

    for (size_t i = 0; i < sizeof(test_speeds) / sizeof(test_speeds[0]); i++) {
        memset(&location, 0, sizeof(location));

        rid_error_t status = rid_set_vertical_speed(&location, test_speeds[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        float result = rid_get_vertical_speed(&location);
        ASSERT_EQ(test_speeds[i], result);
    }

    PASS();
}

TEST
test_vertical_speed_out_of_range(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test speed > 62 m/s */
    rid_error_t status = rid_set_vertical_speed(&location, 70.0f);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    /* Test speed < -62 m/s */
    status = rid_set_vertical_speed(&location, -70.0f);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_vertical_speed_invalid(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test invalid or unknown speed */
    rid_error_t status = rid_set_vertical_speed(&location, RID_VERTICAL_SPEED_INVALID);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(RID_VERTICAL_SPEED_INVALID_ENCODED, location.vertical_speed);

    /* Should decode back to RID_VERTICAL_SPEED_INVALID */
    float result = rid_get_vertical_speed(&location);
    ASSERT_EQ(RID_VERTICAL_SPEED_INVALID, result);

    PASS();
}

TEST
test_set_and_get_latitude(void) {
    rid_location_t location;

    double test_latitudes[] = {0.0, 45.5, 60.123456, -45.5, -90.0, 90.0};

    for (size_t i = 0; i < sizeof(test_latitudes) / sizeof(test_latitudes[0]); i++) {
        memset(&location, 0, sizeof(location));

        rid_error_t status = rid_set_latitude(&location, test_latitudes[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        double result = rid_get_latitude(&location);

        /* 7 decimal digits precision (about 11mm) */
        double diff = result > test_latitudes[i] ? result - test_latitudes[i] : test_latitudes[i] - result;
        ASSERT(diff < 0.00000006);
    }

    PASS();
}

TEST
test_set_and_get_longitude(void) {
    rid_location_t location;

    double test_longitudes[] = {0.0, 90.5, 120.987654, -90.5, -180.0, 180.0};

    for (size_t i = 0; i < sizeof(test_longitudes) / sizeof(test_longitudes[0]); i++) {
        memset(&location, 0, sizeof(location));

        rid_error_t status = rid_set_longitude(&location, test_longitudes[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        double result = rid_get_longitude(&location);

        /* 7 decimal digits precision (about 11mm) */
        double diff = result > test_longitudes[i] ? result - test_longitudes[i] : test_longitudes[i] - result;
        ASSERT(diff < 0.00000006);
    }

    PASS();
}

TEST
test_latitude_out_of_range(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test > 90 degrees */
    rid_error_t status = rid_set_latitude(&location, 95.0);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    /* Test < -90 degrees */
    status = rid_set_latitude(&location, -95.0);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_longitude_out_of_range(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test > 180 degrees */
    rid_error_t status = rid_set_longitude(&location, 185.0);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    /* Test < -180 degrees */
    status = rid_set_longitude(&location, -185.0);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_and_get_height(void) {
    rid_location_t location;

    float test_heights[] = {0.0f, 10.5f, 100.0f, 500.0f, -100.0f, -500.0f, -1000.0f, 31767.0f};

    for (size_t i = 0; i < sizeof(test_heights) / sizeof(test_heights[0]); i++) {
        memset(&location, 0, sizeof(location));

        rid_error_t status = rid_set_height(&location, test_heights[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        float result = rid_get_height(&location);

        /* 0.5 meter resolution */
        float diff = result > test_heights[i] ? result - test_heights[i] : test_heights[i] - result;
        ASSERT(diff < 0.26f);
    }

    PASS();
}

TEST
test_height_out_of_range(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test > 31767 meters */
    rid_error_t status = rid_set_height(&location, 32000.0f);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    /* Test < -1000 meters */
    status = rid_set_height(&location, -1001.0f);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_height_invalid(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test invalid or unknown height */
    rid_error_t status = rid_set_height(&location, RID_HEIGHT_INVALID);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(RID_HEIGHT_INVALID_ENCODED, location.height);

    /* Invalid also means -1000m */
    float result = rid_get_height(&location);
    // TODO: How to handle this?
    // ASSERT_EQ(RID_HEIGHT_INVALID, result);
    ASSERT_EQ(-1000.0f, result);

    PASS();
}

TEST
test_set_and_get_pressure_altitude(void) {
    rid_location_t location;

    float test_altitudes[] = {0.0f, 10.5f, 100.0f, 500.0f, -100.0f, -500.0f, -1000.0f, 31767.0f};

    for (size_t i = 0; i < sizeof(test_altitudes) / sizeof(test_altitudes[0]); i++) {
        memset(&location, 0, sizeof(location));

        rid_error_t status = rid_set_pressure_altitude(&location, test_altitudes[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        float result = rid_get_pressure_altitude(&location);

        /* 0.5 meter resolution */
        float diff = result > test_altitudes[i] ? result - test_altitudes[i] : test_altitudes[i] - result;
        ASSERT(diff < 0.26f);
    }

    PASS();
}

TEST
test_pressure_altitude_out_of_range(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test > 31767 meters */
    rid_error_t status = rid_set_pressure_altitude(&location, 32000.0f);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    /* Test < -1000 meters */
    status = rid_set_pressure_altitude(&location, -1001.0f);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_pressure_altitude_invalid(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test invalid or unknown altitude */
    rid_error_t status = rid_set_pressure_altitude(&location, RID_PRESSURE_ALTITUDE_INVALID);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(RID_PRESSURE_ALTITUDE_INVALID_ENCODED, location.pressure_altitude);

    /* Invalid also means -1000m */
    float result = rid_get_pressure_altitude(&location);
    ASSERT_EQ(-1000.0f, result);

    PASS();
}

TEST
test_set_and_get_geodetic_altitude(void) {
    rid_location_t location;

    float test_altitudes[] = {0.0f, 10.5f, 100.0f, 500.0f, -100.0f, -500.0f, -1000.0f, 31767.0f};

    for (size_t i = 0; i < sizeof(test_altitudes) / sizeof(test_altitudes[0]); i++) {
        memset(&location, 0, sizeof(location));

        rid_error_t status = rid_set_geodetic_altitude(&location, test_altitudes[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        float result = rid_get_geodetic_altitude(&location);

        /* 0.5 meter resolution */
        float diff = result > test_altitudes[i] ? result - test_altitudes[i] : test_altitudes[i] - result;
        ASSERT(diff < 0.26f);
    }

    PASS();
}

TEST
test_geodetic_altitude_out_of_range(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test below minimum */
    rid_error_t status = rid_set_geodetic_altitude(&location, -1001.0f);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    /* Test above maximum */
    status = rid_set_geodetic_altitude(&location, 31768.0f);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_geodetic_altitude_invalid(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test invalid or unknown altitude */
    rid_error_t status = rid_set_geodetic_altitude(&location, RID_GEODETIC_ALTITUDE_INVALID);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(RID_GEODETIC_ALTITUDE_INVALID_ENCODED, location.geodetic_altitude);

    /* Invalid also means -1000m */
    float result = rid_get_geodetic_altitude(&location);
    ASSERT_EQ(-1000.0f, result);

    PASS();
}

TEST
test_set_and_get_height_type(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test RID_HEIGHT_TYPE_ABOVE_TAKEOFF */
    rid_error_t status = rid_set_height_type(&location, RID_HEIGHT_TYPE_ABOVE_TAKEOFF);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(0, location.height_type);

    rid_height_type_t result = rid_get_height_type(&location);
    ASSERT_EQ(RID_HEIGHT_TYPE_ABOVE_TAKEOFF, result);

    /* Test RID_HEIGHT_TYPE_AGL */
    memset(&location, 0, sizeof(location));
    status = rid_set_height_type(&location, RID_HEIGHT_TYPE_AGL);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(1, location.height_type);

    result = rid_get_height_type(&location);
    ASSERT_EQ(RID_HEIGHT_TYPE_AGL, result);

    PASS();
}

TEST
test_height_type_out_of_range(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test invalid enum value */
    rid_error_t status = rid_set_height_type(&location, (rid_height_type_t)2);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_set_height_type(&location, (rid_height_type_t)255);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_and_gte_operational_status(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test RID_OPERATIONAL_STATUS_UNDECLARED */
    rid_error_t status = rid_set_operational_status(&location, RID_OPERATIONAL_STATUS_UNDECLARED);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(0, location.operational_status);

    rid_operational_status_t result = rid_get_operational_status(&location);
    ASSERT_EQ(RID_OPERATIONAL_STATUS_UNDECLARED, result);

    /* Test RID_OPERATIONAL_STATUS_GROUND */
    memset(&location, 0, sizeof(location));
    status = rid_set_operational_status(&location, RID_OPERATIONAL_STATUS_GROUND);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(1, location.operational_status);

    result = rid_get_operational_status(&location);
    ASSERT_EQ(RID_OPERATIONAL_STATUS_GROUND, result);

    /* Test RID_OPERATIONAL_STATUS_AIRBORNE */
    memset(&location, 0, sizeof(location));
    status = rid_set_operational_status(&location, RID_OPERATIONAL_STATUS_AIRBORNE);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(2, location.operational_status);

    result = rid_get_operational_status(&location);
    ASSERT_EQ(RID_OPERATIONAL_STATUS_AIRBORNE, result);

    /* Test RID_OPERATIONAL_STATUS_EMERGENCY */
    memset(&location, 0, sizeof(location));
    status = rid_set_operational_status(&location, RID_OPERATIONAL_STATUS_EMERGENCY);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(3, location.operational_status);

    result = rid_get_operational_status(&location);
    ASSERT_EQ(RID_OPERATIONAL_STATUS_EMERGENCY, result);

    /* Test RID_OPERATIONAL_STATUS_REMOTE_ID_SYSTEM_FAILURE */
    memset(&location, 0, sizeof(location));
    status = rid_set_operational_status(&location, RID_OPERATIONAL_STATUS_REMOTE_ID_SYSTEM_FAILURE);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(4, location.operational_status);

    result = rid_get_operational_status(&location);
    ASSERT_EQ(RID_OPERATIONAL_STATUS_REMOTE_ID_SYSTEM_FAILURE, result);

    /* Test RID_OPERATIONAL_STATUS_RESERVED_15  */
    memset(&location, 0, sizeof(location));
    status = rid_set_operational_status(&location, RID_OPERATIONAL_STATUS_RESERVED_15);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(15, location.operational_status);

    result = rid_get_operational_status(&location);
    ASSERT_EQ(RID_OPERATIONAL_STATUS_RESERVED_15, result);

    PASS();
}

TEST
test_operational_status_out_of_range(void) {
    rid_location_t location;
    memset(&location, 0, sizeof(location));

    /* Test value > 15 */
    rid_error_t status = rid_set_operational_status(&location, (rid_operational_status_t)16);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_set_operational_status(&location, (rid_operational_status_t)255);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_location_init(void) {
    rid_location_t location;

    rid_error_t status = rid_location_init(NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_location_init(&location);
    ASSERT_EQ(RID_SUCCESS, status);

    /* Verify header fields */
    ASSERT_EQ(VERSION_2, location.protocol_version);
    ASSERT_EQ(RID_MESSAGE_TYPE_LOCATION, location.message_type);

    /* Verify default flags */
    ASSERT_EQ(1, location.speed_multiplier);
    ASSERT_EQ(RID_EW_DIRECTION_EAST, location.ew_direction);
    ASSERT_EQ(RID_HEIGHT_TYPE_ABOVE_TAKEOFF, location.height_type);
    ASSERT_EQ(RID_OPERATIONAL_STATUS_UNDECLARED, location.operational_status);

    /* Verify track direction is unknown */
    uint16_t track = rid_get_track_direction(&location);
    ASSERT_EQ(RID_TRACK_DIRECTION_UNKNOWN, track);

    /* Verify speed is invalid */
    float speed = rid_get_speed(&location);
    ASSERT_EQ(RID_SPEED_INVALID, speed);

    /* Verify vertical speed is invalid */
    float vspeed = rid_get_vertical_speed(&location);
    ASSERT_EQ(RID_VERTICAL_SPEED_INVALID, vspeed);

    /* Verify latitude and longitude are 0 */
    double lat = rid_get_latitude(&location);
    double lon = rid_get_longitude(&location);
    ASSERT_EQ(0.0, lat);
    ASSERT_EQ(0.0, lon);

    /* Verify height and altitude fields are 0 ie -1000m */
    float height = rid_get_height(&location);
    float pressure_alt = rid_get_pressure_altitude(&location);
    float geodetic_alt = rid_get_geodetic_altitude(&location);
    ASSERT_EQ(-1000.0f, height);
    ASSERT_EQ(-1000.0f, pressure_alt);
    ASSERT_EQ(-1000.0f, geodetic_alt);

    /* TODO: horizontal, vertical, speed and timestamp accuracy */

    /* TODO: timestamp */

    /* Verify reserved fields are 0 */
    ASSERT_EQ(0, location.reserved_1);
    ASSERT_EQ(0, location.reserved_2);
    ASSERT_EQ(0, location.reserved_3);

    PASS();
}

SUITE(location_suite) {
    RUN_TEST(test_location_init);
    RUN_TEST(test_set_and_get_track_direction);
    RUN_TEST(test_track_direction_unknown);
    RUN_TEST(test_track_direction_out_of_range);
    RUN_TEST(test_set_and_get_speed_slow);
    RUN_TEST(test_set_and_get_speed_fast);
    RUN_TEST(test_speed_boundary_transition);
    RUN_TEST(test_maximum_speed);
    RUN_TEST(test_negative_speed);
    RUN_TEST(test_invalid_speed);
    RUN_TEST(test_set_and_get_vertical_speed);
    RUN_TEST(test_vertical_speed_out_of_range);
    RUN_TEST(test_vertical_speed_invalid);
    RUN_TEST(test_set_and_get_latitude);
    RUN_TEST(test_set_and_get_longitude);
    RUN_TEST(test_latitude_out_of_range);
    RUN_TEST(test_longitude_out_of_range);
    RUN_TEST(test_set_and_get_height);
    RUN_TEST(test_height_out_of_range);
    RUN_TEST(test_height_invalid);
    RUN_TEST(test_set_and_get_pressure_altitude);
    RUN_TEST(test_pressure_altitude_out_of_range);
    RUN_TEST(test_pressure_altitude_invalid);
    RUN_TEST(test_set_and_get_geodetic_altitude);
    RUN_TEST(test_geodetic_altitude_out_of_range);
    RUN_TEST(test_geodetic_altitude_invalid);
    RUN_TEST(test_set_and_get_height_type);
    RUN_TEST(test_height_type_out_of_range);
    RUN_TEST(test_set_and_gte_operational_status);
    RUN_TEST(test_operational_status_out_of_range);
}
