#include <stdint.h>
#include <string.h>

#include "greatest.h"
#include "rid/message.h"
#include "rid/system.h"

TEST
test_set_and_get_operator_location_type(void) {
    rid_operator_location_type_t types[] = {
        RID_OPERATOR_LOCATION_TYPE_TAKEOFF,
        RID_OPERATOR_LOCATION_TYPE_DYNAMIC,
        RID_OPERATOR_LOCATION_TYPE_FIXED
    };

    for (size_t i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
        rid_system_t system;
        memset(&system, 0, sizeof(system));

        rid_error_t status = rid_set_operator_location_type(&system, types[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        rid_operator_location_type_t result = rid_get_operator_location_type(&system);

        ASSERT_EQ(types[i], result);
    }

    PASS();
}


TEST
test_set_operator_location_type_out_of_range(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    rid_error_t status = rid_set_operator_location_type(&system, RID_OPERATOR_LOCATION_TYPE_MAX + 1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_set_operator_location_type(&system, UINT8_MAX);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_operator_location_type_null_pointer(void) {
    rid_error_t status = rid_set_operator_location_type(NULL, RID_OPERATOR_LOCATION_TYPE_TAKEOFF);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_and_get_classification_type(void) {
    rid_classification_type_t types[] = {
        RID_CLASSIFICATION_TYPE_UNDECLARED,
        RID_CLASSIFICATION_TYPE_EUROPEAN_UNION
    };

    for (size_t i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
        rid_system_t system;

        memset(&system, 0, sizeof(system));
        rid_error_t status = rid_set_classification_type(&system, types[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        rid_classification_type_t result = rid_get_classification_type(&system);

        ASSERT_EQ(types[i], result);
    }

    PASS();
}


TEST
test_set_classification_type_out_of_range(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    rid_error_t status = rid_set_classification_type(&system, RID_CLASSIFICATION_TYPE_MAX + 1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_set_classification_type(&system, UINT8_MAX);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_classification_type_null_pointer(void) {
    rid_error_t status = rid_set_classification_type(NULL, RID_CLASSIFICATION_TYPE_UNDECLARED);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_and_get_ua_classification_category(void) {
    rid_ua_classification_category_t categories[] = {
        RID_UA_CLASSIFICATION_CATEGORY_UNDEFINED,
        RID_UA_CLASSIFICATION_CATEGORY_OPEN,
        RID_UA_CLASSIFICATION_CATEGORY_SPECIFIC,
        RID_UA_CLASSIFICATION_CATEGORY_CERTIFIED
    };

    for (size_t i = 0; i < sizeof(categories) / sizeof(categories[0]); i++) {
        rid_system_t system;

        memset(&system, 0, sizeof(system));
        rid_error_t status = rid_set_ua_classification_category(&system, categories[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        rid_ua_classification_category_t result = rid_get_ua_classification_category(&system);

        ASSERT_EQ(categories[i], result);
    }

    PASS();
}


TEST
test_set_ua_classification_category_out_of_range(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    rid_error_t status = rid_set_ua_classification_category(&system, RID_UA_CLASSIFICATION_CATEGORY_MAX + 1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_set_ua_classification_category(&system, UINT8_MAX);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_ua_classification_category_null_pointer(void) {
    rid_error_t status = rid_set_ua_classification_category(NULL, RID_UA_CLASSIFICATION_CATEGORY_OPEN);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_and_get_ua_classification_class(void) {
    rid_ua_classification_class_t classes[] = {
        RID_UA_CLASSIFICATION_CLASS_UNDEFINED,
        RID_UA_CLASSIFICATION_CLASS_0,
        RID_UA_CLASSIFICATION_CLASS_1,
        RID_UA_CLASSIFICATION_CLASS_2,
        RID_UA_CLASSIFICATION_CLASS_3,
        RID_UA_CLASSIFICATION_CLASS_4,
        RID_UA_CLASSIFICATION_CLASS_5,
        RID_UA_CLASSIFICATION_CLASS_6
    };

    for (size_t i = 0; i < sizeof(classes) / sizeof(classes[0]); i++) {
        rid_system_t system;

        memset(&system, 0, sizeof(system));
        rid_error_t status = rid_set_ua_classification_class(&system, classes[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        rid_ua_classification_class_t result = rid_get_ua_classification_class(&system);

        ASSERT_EQ(classes[i], result);
    }

    PASS();
}

TEST
test_set_ua_classification_class_out_of_range(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    rid_error_t status = rid_set_ua_classification_class(&system, RID_UA_CLASSIFICATION_CLASS_MAX + 1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_set_ua_classification_class(&system, UINT8_MAX);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_ua_classification_class_null_pointer(void) {
    rid_error_t status = rid_set_ua_classification_class(NULL, RID_UA_CLASSIFICATION_CLASS_0);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_and_get_operator_latitude(void) {
    rid_system_t system;
    double test_values[] = {0.0, 45.5, 60.123456, -45.5, -90.0, 90.0};

    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        memset(&system, 0, sizeof(system));

        rid_error_t status = rid_set_operator_latitude(&system, test_values[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        double result = rid_get_operator_latitude(&system);

        /* Allow for small precision difference (11mm at equator) */
        double diff = result - test_values[i];
        if (diff < 0) diff = -diff;
        ASSERT(diff < 0.0000001);
    }

    PASS();
}

TEST
test_set_operator_latitude_out_of_range(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    /* Test latitude > 90 */
    rid_error_t status = rid_set_operator_latitude(&system, 90.1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    /* Test latitude < -90 */
    status = rid_set_operator_latitude(&system, -90.1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_operator_latitude_null_pointer(void) {
    rid_error_t status = rid_set_operator_latitude(NULL, 45.0);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_and_get_operator_longitude(void) {
    rid_system_t system;
    double test_values[] = {0.0, 90.5, 120.123456, -90.5, -180.0, 180.0};

    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        memset(&system, 0, sizeof(system));

        rid_error_t status = rid_set_operator_longitude(&system, test_values[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        double result = rid_get_operator_longitude(&system);

        /* Allow for small precision difference (11mm at equator) */
        double diff = result - test_values[i];
        if (diff < 0) diff = -diff;
        ASSERT(diff < 0.0000001);
    }

    PASS();
}

TEST
test_set_operator_longitude_out_of_range(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    /* Test longitude > 180 */
    rid_error_t status = rid_set_operator_longitude(&system, 180.1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    /* Test longitude < -180 */
    status = rid_set_operator_longitude(&system, -180.1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_operator_longitude_null_pointer(void) {
    rid_error_t status = rid_set_operator_longitude(NULL, 90.0);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_and_get_operator_altitude(void) {
    rid_system_t system;
    float test_altitudes[] = {0.0f, 10.5f, 100.0f, 500.0f, -100.0f, -500.0f, -1000.0f, 31767.0f};

    for (size_t i = 0; i < sizeof(test_altitudes) / sizeof(test_altitudes[0]); i++) {
        memset(&system, 0, sizeof(system));

        rid_error_t status = rid_set_operator_altitude(&system, test_altitudes[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        float result = rid_get_operator_altitude(&system);

        /* 0.5 meter resolution */
        float diff = result > test_altitudes[i] ? result - test_altitudes[i] : test_altitudes[i] - result;
        ASSERT(diff < 0.26f);
    }

    PASS();
}

TEST
test_set_operator_altitude_null_pointer(void) {
    rid_error_t status = rid_set_operator_altitude(NULL, 100.0f);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_operator_altitude_out_of_range(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    /* Test > 31767 meters */
    rid_error_t status = rid_set_operator_altitude(&system, 32000.0f);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    /* Test < -1000 meters */
    status = rid_set_operator_altitude(&system, -1001.0f);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_operator_altitude_invalid(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    /* Test invalid or unknown altitude */
    rid_error_t status = rid_set_operator_altitude(&system, RID_OPERATOR_ALTITUDE_INVALID);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(RID_OPERATOR_ALTITUDE_INVALID_ENCODED, system.operator_altitude);

    /* Invalid also means -1000m */
    float result = rid_get_operator_altitude(&system);
    ASSERT_EQ(-1000.0f, result);

    PASS();
}

TEST
test_system_init(void) {
    rid_system_t system;

    rid_error_t status = rid_system_init(&system);
    ASSERT_EQ(RID_SUCCESS, status);

    ASSERT_EQ(RID_PROTOCOL_VERSION_2, system.protocol_version);
    ASSERT_EQ(RID_MESSAGE_TYPE_SYSTEM, system.message_type);
    ASSERT_EQ(1, system.area_count);

    PASS();
}

TEST
test_system_init_null_pointer(void) {
    rid_error_t status = rid_system_init(NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_and_get_area_count(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    uint16_t test_values[] = {0, 1, 100, 1000, UINT16_MAX};

    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        rid_error_t status = rid_set_area_count(&system, test_values[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        uint16_t result = rid_get_area_count(&system);
        ASSERT_EQ(test_values[i], result);
    }

    PASS();
}

TEST
test_set_area_count_null_pointer(void) {
    rid_error_t status = rid_set_area_count(NULL, 1);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_and_get_area_radius(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    /* 10m resolution */
    uint16_t test_values[] = {0, 10, 100, 500, 1000, 2550};

    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        rid_error_t status = rid_set_area_radius(&system, test_values[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        uint16_t result = rid_get_area_radius(&system);
        ASSERT_EQ(test_values[i], result);
    }

    PASS();
}

TEST
test_set_area_radius_out_of_range(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    rid_error_t status = rid_set_area_radius(&system, 2551);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_set_area_radius(&system, 3000);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_area_radius_null_pointer(void) {
    rid_error_t status = rid_set_area_radius(NULL, 100);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_and_get_area_ceiling(void) {
    rid_system_t system;
    float test_values[] = {-1000.0f, 0.0f, 100.0f, 1000.0f, 31767.0f};

    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        memset(&system, 0, sizeof(system));

        rid_error_t status = rid_set_area_ceiling(&system, test_values[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        float result = rid_get_area_ceiling(&system);

        /* 0.5 meter resolution */
        float diff = result > test_values[i] ? result - test_values[i] : test_values[i] - result;
        ASSERT(diff < 0.26f);
    }

    PASS();
}

TEST
test_set_area_ceiling_out_of_range(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    rid_error_t status = rid_set_area_ceiling(&system, 31768.0f);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_set_area_ceiling(&system, -1001.0f);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_area_ceiling_null_pointer(void) {
    rid_error_t status = rid_set_area_ceiling(NULL, 100.0f);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_and_get_area_floor(void) {
    rid_system_t system;
    float test_values[] = {-1000.0f, 0.0f, 100.0f, 1000.0f, 31767.0f};

    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        memset(&system, 0, sizeof(system));

        rid_error_t status = rid_set_area_floor(&system, test_values[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        float result = rid_get_area_floor(&system);

        /* 0.5 meter resolution */
        float diff = result > test_values[i] ? result - test_values[i] : test_values[i] - result;
        ASSERT(diff < 0.26f);
    }

    PASS();
}

TEST
test_set_area_floor_out_of_range(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    rid_error_t status = rid_set_area_floor(&system, 31768.0f);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_set_area_floor(&system, -1001.0f);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_area_floor_null_pointer(void) {
    rid_error_t status = rid_set_area_floor(NULL, 100.0f);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_and_get_system_timestamp(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    uint32_t timestamp = 164205645;

    rid_error_t status = rid_set_system_timestamp(&system, timestamp);
    ASSERT_EQ(RID_SUCCESS, status);

    ASSERT_EQ(timestamp, system.timestamp);

    uint32_t result = rid_get_system_timestamp(&system);
    ASSERT_EQ(timestamp, result);

    PASS();
}

TEST
test_set_system_timestamp_from_unixtime(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    uint32_t unixtime = 1710506445;

    rid_error_t status = rid_set_system_timestamp_from_unixtime(&system, unixtime);
    ASSERT_EQ(RID_SUCCESS, status);

    /* Internal value should be offset by RID epoch */
    ASSERT_EQ(unixtime - RID_SYSTEM_TIMESTAMP_EPOCH, system.timestamp);

    PASS();
}

TEST
test_set_system_timestamp_from_unixtime_at_epoch(void) {
    rid_system_t system;
    memset(&system, 0, sizeof(system));

    uint32_t unixtime = RID_SYSTEM_TIMESTAMP_EPOCH;

    rid_error_t status = rid_set_system_timestamp_from_unixtime(&system, unixtime);
    ASSERT_EQ(RID_SUCCESS, status);

    /* Internal value should be 0 at epoch */
    ASSERT_EQ(0, system.timestamp);

    PASS();
}

TEST
test_set_system_timestamp_null_pointer(void) {
    rid_error_t status = rid_set_system_timestamp(NULL, 164205645);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_system_timestamp_from_unixtime_null_pointer(void) {
    rid_error_t status = rid_set_system_timestamp_from_unixtime(NULL, 1710506445);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

SUITE(system_suite) {
    RUN_TEST(test_set_and_get_operator_location_type);
    RUN_TEST(test_set_operator_location_type_out_of_range);
    RUN_TEST(test_set_operator_location_type_null_pointer);

    RUN_TEST(test_set_and_get_classification_type);
    RUN_TEST(test_set_classification_type_out_of_range);
    RUN_TEST(test_set_classification_type_null_pointer);

    RUN_TEST(test_set_and_get_ua_classification_category);
    RUN_TEST(test_set_ua_classification_category_out_of_range);
    RUN_TEST(test_set_ua_classification_category_null_pointer);

    RUN_TEST(test_set_and_get_ua_classification_class);
    RUN_TEST(test_set_ua_classification_class_out_of_range);
    RUN_TEST(test_set_ua_classification_class_null_pointer);

    RUN_TEST(test_set_and_get_operator_latitude);
    RUN_TEST(test_set_operator_latitude_out_of_range);
    RUN_TEST(test_set_operator_latitude_null_pointer);

    RUN_TEST(test_set_and_get_operator_longitude);
    RUN_TEST(test_set_operator_longitude_out_of_range);
    RUN_TEST(test_set_operator_longitude_null_pointer);

    RUN_TEST(test_set_and_get_operator_altitude);
    RUN_TEST(test_set_operator_altitude_out_of_range);
    RUN_TEST(test_set_operator_altitude_invalid);
    RUN_TEST(test_set_operator_altitude_null_pointer);

    RUN_TEST(test_system_init);
    RUN_TEST(test_system_init_null_pointer);

    RUN_TEST(test_set_and_get_area_count);
    RUN_TEST(test_set_area_count_null_pointer);

    RUN_TEST(test_set_and_get_area_radius);
    RUN_TEST(test_set_area_radius_out_of_range);
    RUN_TEST(test_set_area_radius_null_pointer);

    RUN_TEST(test_set_and_get_area_ceiling);
    RUN_TEST(test_set_area_ceiling_out_of_range);
    RUN_TEST(test_set_area_ceiling_null_pointer);

    RUN_TEST(test_set_and_get_area_floor);
    RUN_TEST(test_set_area_floor_out_of_range);
    RUN_TEST(test_set_area_floor_null_pointer);

    RUN_TEST(test_set_and_get_system_timestamp);
    RUN_TEST(test_set_system_timestamp_from_unixtime);
    RUN_TEST(test_set_system_timestamp_from_unixtime_at_epoch);
    RUN_TEST(test_set_system_timestamp_null_pointer);
    RUN_TEST(test_set_system_timestamp_from_unixtime_null_pointer);
}
