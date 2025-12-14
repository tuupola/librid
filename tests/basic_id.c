#include <stdint.h>
#include <string.h>

#include "greatest.h"
#include "rid/message.h"
#include "rid/basic_id.h"

/* Real life captured message */
static uint8_t buffer[] = {
    0x02, 0x10, 0x32, 0x35, 0x39, 0x36, 0x41, 0x34, 0x30,
    0x33, 0x37, 0x31, 0x36, 0x34, 0x33, 0x30, 0x42, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

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
test_set_basic_id_type_null_pointer(void) {
    rid_error_t status = rid_set_basic_id_type(NULL, RID_ID_TYPE_SERIAL_NUMBER);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_get_basic_id_type_null_pointer(void) {
    rid_basic_id_type_t type = rid_get_basic_id_type(NULL);
    ASSERT_EQ(RID_ID_TYPE_NONE, type);

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
test_set_ua_type_null_pointer(void) {
    rid_error_t status = rid_set_ua_type(NULL, RID_UA_TYPE_AEROPLANE_OR_FIXED_WING);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_get_ua_type_null_pointer(void) {
    rid_ua_type_t type = rid_get_ua_type(NULL);
    ASSERT_EQ(RID_UA_TYPE_NONE, type);

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

TEST
test_set_uas_id_null_pointer_message(void) {
    rid_error_t status = rid_set_uas_id(NULL, "TEST");
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_uas_id_null_pointer_id(void) {
    rid_basic_id_t message;
    memset(&message, 0, sizeof(message));

    rid_error_t status = rid_set_uas_id(&message, NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_get_uas_id_null_pointer_message(void) {
    char buffer[21];
    rid_error_t status = rid_get_uas_id(NULL, buffer, sizeof(buffer));
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_get_uas_id_null_pointer_buffer(void) {
    rid_basic_id_t message;
    rid_basic_id_init(&message);

    rid_error_t status = rid_get_uas_id(&message, NULL, 21);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_uas_id_too_long(void) {
    rid_basic_id_t message;
    rid_basic_id_init(&message);

    /* 21 characters - one over limit */
    rid_error_t status = rid_set_uas_id(&message, "123456789012345678901");
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_LARGE, status);

    /* Even longer string */
    status = rid_set_uas_id(&message, "Welcome to Costco, I love you.");
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_LARGE, status);

    PASS();
}

TEST
test_get_uas_id_buffer_too_small(void) {
    rid_basic_id_t message;
    rid_basic_id_init(&message);
    rid_set_uas_id(&message, "TEST-DRONE-001");

    char buffer[10];
    rid_error_t status = rid_get_uas_id(&message, buffer, sizeof(buffer));
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_SMALL, status);

    PASS();
}

TEST
test_decode_basic_id_buffer(void) {
    rid_basic_id_t *message = (rid_basic_id_t *)buffer;

    ASSERT_EQ(RID_UA_TYPE_NONE, rid_get_ua_type(message));
    ASSERT_EQ(RID_ID_TYPE_SERIAL_NUMBER, rid_get_basic_id_type(message));

    char uas_id[21];
    rid_error_t status = rid_get_uas_id(message, uas_id, sizeof(uas_id));
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_STR_EQ("2596A403716430B", uas_id);
    PASS();
}

SUITE(basic_id_suite) {
    RUN_TEST(test_basic_id_init);

    RUN_TEST(test_set_and_get_basic_id_type);
    RUN_TEST(test_set_basic_id_type_out_of_range);
    RUN_TEST(test_set_basic_id_type_null_pointer);
    RUN_TEST(test_get_basic_id_type_null_pointer);

    RUN_TEST(test_set_and_get_ua_type);
    RUN_TEST(test_set_ua_type_out_of_range);
    RUN_TEST(test_set_ua_type_null_pointer);
    RUN_TEST(test_get_ua_type_null_pointer);

    RUN_TEST(test_set_and_get_uas_id);
    RUN_TEST(test_set_uas_id_null_pointer_message);
    RUN_TEST(test_set_uas_id_null_pointer_id);
    RUN_TEST(test_set_uas_id_too_long);
    RUN_TEST(test_get_uas_id_null_pointer_message);
    RUN_TEST(test_get_uas_id_null_pointer_buffer);
    RUN_TEST(test_get_uas_id_buffer_too_small);

    RUN_TEST(test_decode_basic_id_buffer);
}