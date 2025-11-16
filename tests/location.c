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

SUITE(location_suite) {
    RUN_TEST(test_set_and_get_track_direction);
    RUN_TEST(test_track_direction_unknown);
    RUN_TEST(test_track_direction_out_of_range);
}
