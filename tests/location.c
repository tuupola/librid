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

        /* Slow speed has 0.25 m/s steps  */
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

        /* Fast speed has 0.75 m/s steps  */
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

SUITE(location_suite) {
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
}
