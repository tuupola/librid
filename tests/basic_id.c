#include <stdint.h>
#include <string.h>

#include "greatest.h"
#include "rid/header.h"
#include "rid/basic_id.h"

TEST
test_basic_id_init(void) {
    rid_basic_id_t message;

    rid_error_t status = rid_basic_id_init(NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_basic_id_init(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    /* Verify header fields */
    ASSERT_EQ(RID_PROTOCOL_VERSION_2, message.protocol_version);
    ASSERT_EQ(RID_MESSAGE_TYPE_BASIC_ID, message.message_type);

    /* Verify other fields are zeroed */
    ASSERT_EQ(RID_ID_TYPE_NONE, message.id_type);
    ASSERT_EQ(RID_UA_TYPE_NONE, message.ua_type);

    /* Verify uas_id is zeroed */
    for (size_t i = 0; i < sizeof(message.uas_id); i++) {
        ASSERT_EQ(0, message.uas_id[i]);
    }

    /* Verify reserved fields are zeroed */
    for (size_t i = 0; i < sizeof(message.reserved); i++) {
        ASSERT_EQ(0, message.reserved[i]);
    }

    PASS();
}

TEST
test_set_and_get_basic_id_type(void) {
    rid_basic_id_type_t types[] = {
        RID_ID_TYPE_NONE,
        RID_ID_TYPE_SERIAL_NUMBER,
        RID_ID_TYPE_CAA_REGISTRATION_ID,
        RID_ID_TYPE_UTM_ASSIGNED_UUID,
        RID_ID_TYPE_SPECIFIC_SESSION_ID
    };

    for (size_t i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
        rid_basic_id_t message;

        memset(&message, 0, sizeof(message));
        rid_error_t status = rid_set_basic_id_type(&message, types[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        rid_basic_id_type_t result = rid_get_basic_id_type(&message);

        ASSERT_EQ(types[i], result);
    }

    PASS();
}

TEST
test_set_basic_id_type_out_of_range(void) {
    rid_basic_id_t message;
    memset(&message, 0, sizeof(message));

    rid_error_t status = rid_set_basic_id_type(&message, RID_ID_TYPE_MAX + 1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_set_basic_id_type(&message, UINT8_MAX);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_and_get_ua_type(void) {
    rid_ua_type_t types[] = {
        RID_UA_TYPE_NONE,
        RID_UA_TYPE_AEROPLANE_OR_FIXED_WING,
        RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR,
        RID_UA_TYPE_GYROPLANE,
        RID_UA_TYPE_HYBRID_LIFT,
        RID_UA_TYPE_ORNITHOPTER,
        RID_UA_TYPE_GLIDER,
        RID_UA_TYPE_KITE,
        RID_UA_TYPE_FREE_BALLOON,
        RID_UA_TYPE_CAPTIVE_BALLOON,
        RID_UA_TYPE_AIRSHIP,
        RID_UA_TYPE_FREE_FALL_PARACHUTE,
        RID_UA_TYPE_ROCKET,
        RID_UA_TYPE_TETHERED_POWERED_AIRCRAFT,
        RID_UA_TYPE_GROUND_OBSTACLE,
        RID_UA_TYPE_OTHER
    };

    for (size_t i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
        rid_basic_id_t message;

        memset(&message, 0, sizeof(message));
        rid_error_t status = rid_set_ua_type(&message, types[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        rid_ua_type_t result = rid_get_ua_type(&message);

        ASSERT_EQ(types[i], result);
    }

    PASS();
}

TEST
test_set_ua_type_out_of_range(void) {
    rid_basic_id_t message;
    memset(&message, 0, sizeof(message));

    rid_error_t status = rid_set_ua_type(&message, RID_UA_TYPE_MAX + 1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_set_ua_type(&message, UINT8_MAX);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_and_get_uas_id(void) {
    const char *test_ids[] = {
        "ABC123",
        "12345678901234567890",
        "TEST-ID",
        "",
        "X"
    };

    for (size_t i = 0; i < sizeof(test_ids) / sizeof(test_ids[0]); i++) {
        rid_basic_id_t message;
        rid_error_t status;

        memset(&message, 0, sizeof(message));

        status = rid_set_uas_id(&message, test_ids[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        char buffer[21];
        status = rid_get_uas_id(&message, buffer, sizeof(buffer));
        ASSERT_EQ(RID_SUCCESS, status);

        ASSERT_STR_EQ(test_ids[i], buffer);
    }

    PASS();
}

SUITE(basic_id_suite) {
    RUN_TEST(test_basic_id_init);
    RUN_TEST(test_set_and_get_basic_id_type);
    RUN_TEST(test_set_basic_id_type_out_of_range);
    RUN_TEST(test_set_and_get_ua_type);
    RUN_TEST(test_set_ua_type_out_of_range);
    RUN_TEST(test_set_and_get_uas_id);
}