#include <stdint.h>
#include <string.h>

#include "greatest.h"
#include "rid/header.h"
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

SUITE(system_suite) {
    RUN_TEST(test_set_and_get_operator_location_type);
    RUN_TEST(test_set_operator_location_type_out_of_range);
    RUN_TEST(test_set_and_get_classification_type);
    RUN_TEST(test_set_classification_type_out_of_range);
    RUN_TEST(test_set_and_get_ua_classification_category);
    RUN_TEST(test_set_ua_classification_category_out_of_range);
    RUN_TEST(test_set_and_get_ua_classification_class);
    RUN_TEST(test_set_ua_classification_class_out_of_range);
    RUN_TEST(test_set_and_get_operator_latitude);
    RUN_TEST(test_set_operator_latitude_out_of_range);
    RUN_TEST(test_set_and_get_operator_longitude);
    RUN_TEST(test_set_operator_longitude_out_of_range);
    RUN_TEST(test_set_and_get_operator_altitude);
    RUN_TEST(test_set_operator_altitude_null_pointer);
    RUN_TEST(test_set_operator_altitude_out_of_range);
    RUN_TEST(test_set_operator_altitude_invalid);
}
