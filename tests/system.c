#include <string.h>

#include "greatest.h"
#include "rid/header.h"
#include "rid/system.h"

TEST
test_set_and_gte_operator_location_type(void) {
    rid_operator_location_type_t types[] = {
        RID_OPERATOR_LOCATION_TYPE_TAKEOFF,
        RID_OPERATOR_LOCATION_TYPE_DYNAMIC,
        RID_OPERATOR_LOCATION_TYPE_FIXED,
        RID_OPERATOR_LOCATION_TYPE_RESERVED
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

    rid_error_t status = rid_set_operator_location_type(&system, 4);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_set_operator_location_type(&system, 255);
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

SUITE(system_suite) {
    RUN_TEST(test_set_and_gte_operator_location_type);
    RUN_TEST(test_set_operator_location_type_out_of_range);
    RUN_TEST(test_set_and_get_classification_type);
    RUN_TEST(test_set_classification_type_out_of_range);
}
