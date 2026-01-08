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

    int status = rid_basic_id_init(NULL);
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
        int status = rid_basic_id_set_type(&message, types[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        rid_basic_id_type_t result = rid_basic_id_get_type(&message);

        ASSERT_EQ(types[i], result);
    }

    PASS();
}

TEST
test_set_basic_id_type_out_of_range(void) {
    rid_basic_id_t message;
    memset(&message, 0, sizeof(message));

    int status = rid_basic_id_set_type(&message, RID_ID_TYPE_MAX + 1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_basic_id_set_type(&message, UINT8_MAX);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_basic_id_type_null_pointer(void) {
    int status = rid_basic_id_set_type(NULL, RID_ID_TYPE_SERIAL_NUMBER);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_get_basic_id_type_null_pointer(void) {
    rid_basic_id_type_t type = rid_basic_id_get_type(NULL);
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
        int status = rid_basic_id_set_ua_type(&message, types[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        rid_ua_type_t result = rid_basic_id_get_ua_type(&message);

        ASSERT_EQ(types[i], result);
    }

    PASS();
}

TEST
test_set_ua_type_out_of_range(void) {
    rid_basic_id_t message;
    memset(&message, 0, sizeof(message));

    int status = rid_basic_id_set_ua_type(&message, RID_UA_TYPE_MAX + 1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_basic_id_set_ua_type(&message, UINT8_MAX);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_ua_type_null_pointer(void) {
    int status = rid_basic_id_set_ua_type(NULL, RID_UA_TYPE_AEROPLANE_OR_FIXED_WING);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_get_ua_type_null_pointer(void) {
    rid_ua_type_t type = rid_basic_id_get_ua_type(NULL);
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
        int status;

        memset(&message, 0, sizeof(message));

        status = rid_basic_id_set_uas_id(&message, test_ids[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        char buffer[21];
        status = rid_basic_id_get_uas_id(&message, buffer, sizeof(buffer));
        ASSERT_EQ(RID_SUCCESS, status);

        ASSERT_STR_EQ(test_ids[i], buffer);
    }

    PASS();
}

TEST
test_set_uas_id_null_pointer_message(void) {
    int status = rid_basic_id_set_uas_id(NULL, "TEST");
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_uas_id_null_pointer_id(void) {
    rid_basic_id_t message;
    memset(&message, 0, sizeof(message));

    int status = rid_basic_id_set_uas_id(&message, NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_get_uas_id_null_pointer_message(void) {
    char buffer[21];
    int status = rid_basic_id_get_uas_id(NULL, buffer, sizeof(buffer));
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_get_uas_id_null_pointer_buffer(void) {
    rid_basic_id_t message;
    rid_basic_id_init(&message);

    int status = rid_basic_id_get_uas_id(&message, NULL, 21);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_uas_id_too_long(void) {
    rid_basic_id_t message;
    rid_basic_id_init(&message);

    /* 21 characters - one over limit */
    int status = rid_basic_id_set_uas_id(&message, "123456789012345678901");
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_LARGE, status);

    /* Even longer string */
    status = rid_basic_id_set_uas_id(&message, "Welcome to Costco, I love you.");
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_LARGE, status);

    PASS();
}

TEST
test_get_uas_id_buffer_too_small(void) {
    rid_basic_id_t message;
    rid_basic_id_init(&message);
    rid_basic_id_set_uas_id(&message, "TEST-DRONE-001");

    char buffer[10];
    int status = rid_basic_id_get_uas_id(&message, buffer, sizeof(buffer));
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_SMALL, status);

    PASS();
}

TEST
test_decode_basic_id_buffer(void) {
    rid_basic_id_t *message = (rid_basic_id_t *)buffer;

    ASSERT_EQ(RID_UA_TYPE_NONE, rid_basic_id_get_ua_type(message));
    ASSERT_EQ(RID_ID_TYPE_SERIAL_NUMBER, rid_basic_id_get_type(message));

    char uas_id[21];
    int status = rid_basic_id_get_uas_id(message, uas_id, sizeof(uas_id));
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_STR_EQ("2596A403716430B", uas_id);
    PASS();
}

TEST
test_basic_id_type_to_string(void) {
    ASSERT_STR_EQ("RID_ID_TYPE_NONE", rid_basic_id_type_to_string(RID_ID_TYPE_NONE));
    ASSERT_STR_EQ("RID_ID_TYPE_SERIAL_NUMBER", rid_basic_id_type_to_string(RID_ID_TYPE_SERIAL_NUMBER));
    ASSERT_STR_EQ("RID_ID_TYPE_CAA_REGISTRATION_ID", rid_basic_id_type_to_string(RID_ID_TYPE_CAA_REGISTRATION_ID));
    ASSERT_STR_EQ("RID_ID_TYPE_UTM_ASSIGNED_UUID", rid_basic_id_type_to_string(RID_ID_TYPE_UTM_ASSIGNED_UUID));
    ASSERT_STR_EQ("RID_ID_TYPE_SPECIFIC_SESSION_ID", rid_basic_id_type_to_string(RID_ID_TYPE_SPECIFIC_SESSION_ID));
    ASSERT_STR_EQ("UNKNOWN", rid_basic_id_type_to_string((rid_basic_id_type_t)99));
    PASS();
}

TEST
test_ua_type_to_string(void) {
    ASSERT_STR_EQ("RID_UA_TYPE_NONE", rid_ua_type_to_string(RID_UA_TYPE_NONE));
    ASSERT_STR_EQ("RID_UA_TYPE_AEROPLANE_OR_FIXED_WING", rid_ua_type_to_string(RID_UA_TYPE_AEROPLANE_OR_FIXED_WING));
    ASSERT_STR_EQ("RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR", rid_ua_type_to_string(RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR));
    ASSERT_STR_EQ("RID_UA_TYPE_GYROPLANE", rid_ua_type_to_string(RID_UA_TYPE_GYROPLANE));
    ASSERT_STR_EQ("RID_UA_TYPE_HYBRID_LIFT", rid_ua_type_to_string(RID_UA_TYPE_HYBRID_LIFT));
    ASSERT_STR_EQ("RID_UA_TYPE_ORNITHOPTER", rid_ua_type_to_string(RID_UA_TYPE_ORNITHOPTER));
    ASSERT_STR_EQ("RID_UA_TYPE_GLIDER", rid_ua_type_to_string(RID_UA_TYPE_GLIDER));
    ASSERT_STR_EQ("RID_UA_TYPE_KITE", rid_ua_type_to_string(RID_UA_TYPE_KITE));
    ASSERT_STR_EQ("RID_UA_TYPE_FREE_BALLOON", rid_ua_type_to_string(RID_UA_TYPE_FREE_BALLOON));
    ASSERT_STR_EQ("RID_UA_TYPE_CAPTIVE_BALLOON", rid_ua_type_to_string(RID_UA_TYPE_CAPTIVE_BALLOON));
    ASSERT_STR_EQ("RID_UA_TYPE_AIRSHIP", rid_ua_type_to_string(RID_UA_TYPE_AIRSHIP));
    ASSERT_STR_EQ("RID_UA_TYPE_FREE_FALL_PARACHUTE", rid_ua_type_to_string(RID_UA_TYPE_FREE_FALL_PARACHUTE));
    ASSERT_STR_EQ("RID_UA_TYPE_ROCKET", rid_ua_type_to_string(RID_UA_TYPE_ROCKET));
    ASSERT_STR_EQ("RID_UA_TYPE_TETHERED_POWERED_AIRCRAFT", rid_ua_type_to_string(RID_UA_TYPE_TETHERED_POWERED_AIRCRAFT));
    ASSERT_STR_EQ("RID_UA_TYPE_GROUND_OBSTACLE", rid_ua_type_to_string(RID_UA_TYPE_GROUND_OBSTACLE));
    ASSERT_STR_EQ("RID_UA_TYPE_OTHER", rid_ua_type_to_string(RID_UA_TYPE_OTHER));
    ASSERT_STR_EQ("UNKNOWN", rid_ua_type_to_string((rid_ua_type_t)99));
    PASS();
}

TEST
test_basic_id_validate_valid_message(void) {
    rid_basic_id_t message;

    rid_basic_id_init(&message);

    int status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    PASS();
}

TEST
test_basic_id_validate_null_pointer(void) {
    int status = rid_basic_id_validate(NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_basic_id_validate_invalid_protocol_version(void) {
    rid_basic_id_t message;

    rid_basic_id_init(&message);

    /* Value between 2 and 0x0F is invalid */
    message.protocol_version = 5;
    int status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_PROTOCOL_VERSION, status);

    /* Valid versions should pass */
    message.protocol_version = RID_PROTOCOL_VERSION_0;
    status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    message.protocol_version = RID_PROTOCOL_VERSION_1;
    status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    message.protocol_version = RID_PROTOCOL_VERSION_2;
    status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    message.protocol_version = RID_PROTOCOL_PRIVATE_USE;
    status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    PASS();
}

TEST
test_basic_id_validate_invalid_message_type(void) {
    rid_basic_id_t message;

    rid_basic_id_init(&message);
    message.message_type = RID_MESSAGE_TYPE_LOCATION;

    int status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_ERROR_WRONG_MESSAGE_TYPE, status);

    PASS();
}

TEST
test_basic_id_validate_registration_id_valid(void) {
    rid_basic_id_t message;

    rid_basic_id_init(&message);
    rid_basic_id_set_type(&message, RID_ID_TYPE_CAA_REGISTRATION_ID);

    rid_basic_id_set_uas_id(&message, "FIN.ABC123");
    int status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    rid_basic_id_set_uas_id(&message, "USA123456789");
    status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    rid_basic_id_set_uas_id(&message, "X.Y.Z");
    status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    PASS();
}

TEST
test_basic_id_validate_registration_id_invalid_lowercase(void) {
    rid_basic_id_t message;

    rid_basic_id_init(&message);
    rid_basic_id_set_type(&message, RID_ID_TYPE_CAA_REGISTRATION_ID);
    rid_basic_id_set_uas_id(&message, "FIN.abc123");

    int status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    PASS();
}

TEST
test_basic_id_validate_registration_id_invalid_char(void) {
    rid_basic_id_t message;

    rid_basic_id_init(&message);
    rid_basic_id_set_type(&message, RID_ID_TYPE_CAA_REGISTRATION_ID);

    rid_basic_id_set_uas_id(&message, "FIN-ABC123");
    int status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    rid_basic_id_set_uas_id(&message, "FIN_ABC123");
    status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    rid_basic_id_set_uas_id(&message, "FIN ABC123");
    status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    PASS();
}

TEST
test_basic_id_validate_serial_number_valid(void) {
    rid_basic_id_t message;

    rid_basic_id_init(&message);
    rid_basic_id_set_type(&message, RID_ID_TYPE_SERIAL_NUMBER);

    rid_basic_id_set_uas_id(&message, "1234567890ABCDEFGHJK");
    int status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    rid_basic_id_set_uas_id(&message, "LMNPQRSTUVWXYZ");
    status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    rid_basic_id_set_uas_id(&message, "2596A403716430B");
    status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    PASS();
}

TEST
test_basic_id_validate_serial_number_invalid_i(void) {
    rid_basic_id_t message;

    rid_basic_id_init(&message);
    rid_basic_id_set_type(&message, RID_ID_TYPE_SERIAL_NUMBER);
    rid_basic_id_set_uas_id(&message, "ABC123I456");

    int status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    PASS();
}

TEST
test_basic_id_validate_serial_number_invalid_o(void) {
    rid_basic_id_t message;

    rid_basic_id_init(&message);
    rid_basic_id_set_type(&message, RID_ID_TYPE_SERIAL_NUMBER);
    rid_basic_id_set_uas_id(&message, "ABC123O456");

    int status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    PASS();
}

TEST
test_basic_id_validate_serial_number_invalid_lowercase(void) {
    rid_basic_id_t message;

    rid_basic_id_init(&message);
    rid_basic_id_set_type(&message, RID_ID_TYPE_SERIAL_NUMBER);
    rid_basic_id_set_uas_id(&message, "abc123");

    int status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    PASS();
}

TEST
test_basic_id_validate_utm_uuid_valid(void) {
    rid_basic_id_t message;

    rid_basic_id_init(&message);
    rid_basic_id_set_type(&message, RID_ID_TYPE_UTM_ASSIGNED_UUID);

    /* Valid UUID v4: 550e8400-e29b-41d4-a716-446655440000 */
    uint8_t uuid[20] = {
        0x55, 0x0e, 0x84, 0x00, 0xe2, 0x9b, 0x41, 0xd4,
        0xa7, 0x16, 0x44, 0x66, 0x55, 0x44, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    memcpy(message.uas_id, uuid, 20);

    int status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    /* Test all valid versions 1-5 */
    for (uint8_t v = 1; v <= 5; ++v) {
        message.uas_id[6] = (v << 4) | 0x0d;
        status = rid_basic_id_validate(&message);
        ASSERT_EQ(RID_SUCCESS, status);
    }

    PASS();
}

TEST
test_basic_id_validate_utm_uuid_invalid_version_0(void) {
    rid_basic_id_t message;

    rid_basic_id_init(&message);
    rid_basic_id_set_type(&message, RID_ID_TYPE_UTM_ASSIGNED_UUID);

    /* UUID with version 0 (nil UUID) */
    uint8_t uuid[20] = {
        0x55, 0x0e, 0x84, 0x00, 0xe2, 0x9b, 0x01, 0xd4,
        0xa7, 0x16, 0x44, 0x66, 0x55, 0x44, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    memcpy(message.uas_id, uuid, 20);

    int status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_UUID_VERSION, status);

    PASS();
}

TEST
test_basic_id_validate_utm_uuid_invalid_version_6(void) {
    rid_basic_id_t message;

    rid_basic_id_init(&message);
    rid_basic_id_set_type(&message, RID_ID_TYPE_UTM_ASSIGNED_UUID);

    /* UUID with version 6 (invalid for RFC4122) */
    uint8_t uuid[20] = {
        0x55, 0x0e, 0x84, 0x00, 0xe2, 0x9b, 0x61, 0xd4,
        0xa7, 0x16, 0x44, 0x66, 0x55, 0x44, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    memcpy(message.uas_id, uuid, 20);

    int status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_UUID_VERSION, status);

    PASS();
}

TEST
test_basic_id_validate_utm_uuid_invalid_variant(void) {
    rid_basic_id_t message;

    rid_basic_id_init(&message);
    rid_basic_id_set_type(&message, RID_ID_TYPE_UTM_ASSIGNED_UUID);

    /* UUID with variant 0b00 (NCS backward compatibility) */
    uint8_t uuid[20] = {
        0x55, 0x0e, 0x84, 0x00, 0xe2, 0x9b, 0x41, 0xd4,
        0x27, 0x16, 0x44, 0x66, 0x55, 0x44, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    memcpy(message.uas_id, uuid, 20);

    int status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_UUID_VARIANT, status);

    /* UUID with variant 0b11 (reserved) */
    message.uas_id[8] = 0xe7;
    status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_UUID_VARIANT, status);

    PASS();
}

TEST
test_basic_id_validate_utm_uuid_invalid_padding(void) {
    rid_basic_id_t message;

    rid_basic_id_init(&message);
    rid_basic_id_set_type(&message, RID_ID_TYPE_UTM_ASSIGNED_UUID);

    /* Valid UUID but with non-zero padding */
    uint8_t uuid[20] = {
        0x55, 0x0e, 0x84, 0x00, 0xe2, 0x9b, 0x41, 0xd4,
        0xa7, 0x16, 0x44, 0x66, 0x55, 0x44, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01
    };
    memcpy(message.uas_id, uuid, 20);

    int status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_UUID_PADDING, status);

    /* Non-zero in middle of padding */
    message.uas_id[19] = 0x00;
    message.uas_id[17] = 0xff;
    status = rid_basic_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_UUID_PADDING, status);

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

    RUN_TEST(test_basic_id_type_to_string);
    RUN_TEST(test_ua_type_to_string);

    RUN_TEST(test_basic_id_validate_valid_message);
    RUN_TEST(test_basic_id_validate_null_pointer);
    RUN_TEST(test_basic_id_validate_invalid_protocol_version);
    RUN_TEST(test_basic_id_validate_invalid_message_type);
    RUN_TEST(test_basic_id_validate_registration_id_valid);
    RUN_TEST(test_basic_id_validate_registration_id_invalid_lowercase);
    RUN_TEST(test_basic_id_validate_registration_id_invalid_char);
    RUN_TEST(test_basic_id_validate_serial_number_valid);
    RUN_TEST(test_basic_id_validate_serial_number_invalid_i);
    RUN_TEST(test_basic_id_validate_serial_number_invalid_o);
    RUN_TEST(test_basic_id_validate_serial_number_invalid_lowercase);
    RUN_TEST(test_basic_id_validate_utm_uuid_valid);
    RUN_TEST(test_basic_id_validate_utm_uuid_invalid_version_0);
    RUN_TEST(test_basic_id_validate_utm_uuid_invalid_version_6);
    RUN_TEST(test_basic_id_validate_utm_uuid_invalid_variant);
    RUN_TEST(test_basic_id_validate_utm_uuid_invalid_padding);
}