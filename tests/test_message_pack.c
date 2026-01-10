#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "greatest.h"
#include "rid/message.h"
#include "rid/message_pack.h"
#include "rid/basic_id.h"
#include "rid/location.h"

/* Captured from a booting DroneTag */
static uint8_t buffer[] = {
    0xf2, 0x19, 0x04, 0x02, 0x10, 0x31, 0x35, 0x39, 0x36, 0x41,
    0x33, 0x30, 0x33, 0x37, 0x31, 0x36, 0x34, 0x33, 0x30, 0x41,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x07,
    0xb5, 0xff, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x52, 0x00, 0x46, 0x49, 0x4e, 0x38, 0x37, 0x61,
    0x73, 0x74, 0x72, 0x64, 0x67, 0x65, 0x31, 0x32, 0x6b, 0x38,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

TEST
test_message_pack_init(void) {
    rid_message_pack_t message;

    int status = rid_message_pack_init(NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_message_pack_init(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    ASSERT_EQ(RID_PROTOCOL_VERSION_2, message.protocol_version);
    ASSERT_EQ(RID_MESSAGE_TYPE_MESSAGE_PACK, message.message_type);
    ASSERT_EQ(RID_MESSAGE_SIZE, message.message_size);
    ASSERT_EQ(0, message.message_count);

    for (size_t i = 0; i < sizeof(message.messages); i++) {
        ASSERT_EQ(0, message.messages[i]);
    }

    PASS();
}

TEST
test_message_pack_size(void) {
    ASSERT_EQ(228, sizeof(rid_message_pack_t));
    PASS();
}

TEST
test_set_and_get_count(void) {
    rid_message_pack_t message;
    rid_message_pack_init(&message);

    for (uint8_t i = 0; i <= RID_MESSAGE_PACK_MAX_MESSAGES; i++) {
        int status = rid_message_pack_set_message_count(&message, i);
        ASSERT_EQ(RID_SUCCESS, status);
        ASSERT_EQ(i, rid_message_pack_get_message_count(&message));
    }

    PASS();
}

TEST
test_set_count_null_pointer(void) {
    int status = rid_message_pack_set_message_count(NULL, 1);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);
    PASS();
}

TEST
test_get_count_null_pointer(void) {
    uint8_t count = rid_message_pack_get_message_count(NULL);
    ASSERT_EQ(0, count);
    PASS();
}

TEST
test_set_count_out_of_range(void) {
    rid_message_pack_t message;
    rid_message_pack_init(&message);

    int status = rid_message_pack_set_message_count(&message, RID_MESSAGE_PACK_MAX_MESSAGES + 1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_message_pack_set_message_count(&message, UINT8_MAX);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_decode_message_pack_buffer(void) {
    rid_message_pack_t *message = (rid_message_pack_t *)buffer;

    ASSERT_EQ(RID_PROTOCOL_VERSION_2, rid_message_get_protocol_version(message));
    ASSERT_EQ(RID_MESSAGE_TYPE_MESSAGE_PACK, rid_message_get_type(message));
    // ASSERT_EQ(RID_MESSAGE_SIZE, rid_message_get_message_size());

    ASSERT_EQ(4, rid_message_pack_get_message_count(message));

    PASS();
}

TEST
test_add_message(void) {
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;

    rid_message_pack_init(&pack);
    rid_basic_id_init(&basic_id);
    rid_basic_id_set_uas_id(&basic_id, "1596A3037164309A");
    rid_basic_id_set_type(&basic_id, RID_ID_TYPE_SERIAL_NUMBER);
    rid_basic_id_set_ua_type(&basic_id, RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR);

    int status = rid_message_pack_add_message(&pack, &basic_id);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(1, rid_message_pack_get_message_count(&pack));

    PASS();
}

TEST
test_add_message_multiple(void) {
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;

    rid_message_pack_init(&pack);

    for (uint8_t i = 0; i < RID_MESSAGE_PACK_MAX_MESSAGES; ++i) {
        rid_basic_id_init(&basic_id);
        basic_id.uas_id[0] = '0' + i;
        int status = rid_message_pack_add_message(&pack, &basic_id);
        ASSERT_EQ(RID_SUCCESS, status);
        ASSERT_EQ(i + 1, rid_message_pack_get_message_count(&pack));

        /* Verify the message was stored at correct offset */
        size_t offset = i * RID_MESSAGE_SIZE;
        ASSERT_EQ('0' + i, pack.messages[offset + 2]);
    }

    PASS();
}

TEST
test_add_message_pack_full(void) {
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;

    rid_message_pack_init(&pack);
    rid_basic_id_init(&basic_id);

    /* Fill the pack */
    for (uint8_t i = 0; i < RID_MESSAGE_PACK_MAX_MESSAGES; ++i) {
        rid_message_pack_add_message(&pack, &basic_id);
    }

    /* Try adding one more */
    int status = rid_message_pack_add_message(&pack, &basic_id);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);
    ASSERT_EQ(RID_MESSAGE_PACK_MAX_MESSAGES, rid_message_pack_get_message_count(&pack));

    PASS();
}

TEST
test_add_message_null_pointer(void) {
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;

    rid_message_pack_init(&pack);
    rid_basic_id_init(&basic_id);

    int status = rid_message_pack_add_message(NULL, &basic_id);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_message_pack_add_message(&pack, NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_message_pack_add_message(NULL, NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_get_message_at(void) {
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;
    char uas_id[21];
    char expected[21];

    rid_message_pack_init(&pack);

    for (uint8_t i = 0; i < 3; ++i) {
        rid_basic_id_init(&basic_id);
        snprintf(uas_id, sizeof(uas_id), "DRONE%03u", i + 1);
        rid_basic_id_set_uas_id(&basic_id, uas_id);
        rid_message_pack_add_message(&pack, &basic_id);
    }

    for (uint8_t i = 0; i < 3; ++i) {
        const rid_basic_id_t *msg = rid_message_pack_get_message_at(&pack, i);
        ASSERT(msg != NULL);

        rid_basic_id_get_uas_id(msg, uas_id, sizeof(uas_id));
        snprintf(expected, sizeof(expected), "DRONE%03u", i + 1);
        ASSERT_STR_EQ(expected, uas_id);
    }

    PASS();
}

TEST
test_get_message_at_null_pointer(void) {
    const void *msg = rid_message_pack_get_message_at(NULL, 0);
    ASSERT(msg == NULL);

    PASS();
}

TEST
test_get_message_at_out_of_range(void) {
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;

    rid_message_pack_init(&pack);
    rid_basic_id_init(&basic_id);
    rid_message_pack_add_message(&pack, &basic_id);

    const void *msg = rid_message_pack_get_message_at(&pack, 0);
    ASSERT(msg != NULL);

    msg = rid_message_pack_get_message_at(&pack, 1);
    ASSERT(msg == NULL);

    msg = rid_message_pack_get_message_at(&pack, UINT8_MAX);
    ASSERT(msg == NULL);

    PASS();
}

TEST
test_delete_message_at(void) {
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;
    char uas_id[21];

    rid_message_pack_init(&pack);

    /* Add 5 messages: DRONE001 through DRONE005 */
    for (uint8_t i = 0; i < 5; ++i) {
        rid_basic_id_init(&basic_id);
        snprintf(uas_id, sizeof(uas_id), "DRONE%03u", i + 1);
        rid_basic_id_set_uas_id(&basic_id, uas_id);
        rid_message_pack_add_message(&pack, &basic_id);
    }
    ASSERT_EQ(5, rid_message_pack_get_message_count(&pack));

    /* Delete middle message (index 2, DRONE003) */
    int status = rid_message_pack_delete_message_at(&pack, 2);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(4, rid_message_pack_get_message_count(&pack));

    /* Verify remaining messages shifted correctly */
    const rid_basic_id_t *msg = rid_message_pack_get_message_at(&pack, 0);
    rid_basic_id_get_uas_id(msg, uas_id, sizeof(uas_id));
    ASSERT_STR_EQ("DRONE001", uas_id);

    msg = rid_message_pack_get_message_at(&pack, 1);
    rid_basic_id_get_uas_id(msg, uas_id, sizeof(uas_id));
    ASSERT_STR_EQ("DRONE002", uas_id);

    msg = rid_message_pack_get_message_at(&pack, 2);
    rid_basic_id_get_uas_id(msg, uas_id, sizeof(uas_id));
    ASSERT_STR_EQ("DRONE004", uas_id);

    msg = rid_message_pack_get_message_at(&pack, 3);
    rid_basic_id_get_uas_id(msg, uas_id, sizeof(uas_id));
    ASSERT_STR_EQ("DRONE005", uas_id);

    PASS();
}

TEST
test_delete_message_at_first(void) {
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;
    char uas_id[21];

    rid_message_pack_init(&pack);

    for (uint8_t i = 0; i < 3; ++i) {
        rid_basic_id_init(&basic_id);
        snprintf(uas_id, sizeof(uas_id), "DRONE%03u", i + 1);
        rid_basic_id_set_uas_id(&basic_id, uas_id);
        rid_message_pack_add_message(&pack, &basic_id);
    }

    int status = rid_message_pack_delete_message_at(&pack, 0);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(2, rid_message_pack_get_message_count(&pack));

    const rid_basic_id_t *msg = rid_message_pack_get_message_at(&pack, 0);
    rid_basic_id_get_uas_id(msg, uas_id, sizeof(uas_id));
    ASSERT_STR_EQ("DRONE002", uas_id);

    msg = rid_message_pack_get_message_at(&pack, 1);
    rid_basic_id_get_uas_id(msg, uas_id, sizeof(uas_id));
    ASSERT_STR_EQ("DRONE003", uas_id);

    PASS();
}

TEST
test_delete_message_at_last(void) {
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;
    char uas_id[21];

    rid_message_pack_init(&pack);

    for (uint8_t i = 0; i < 3; ++i) {
        rid_basic_id_init(&basic_id);
        snprintf(uas_id, sizeof(uas_id), "DRONE%03u", i + 1);
        rid_basic_id_set_uas_id(&basic_id, uas_id);
        rid_message_pack_add_message(&pack, &basic_id);
    }

    int status = rid_message_pack_delete_message_at(&pack, 2);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(2, rid_message_pack_get_message_count(&pack));

    const rid_basic_id_t *msg = rid_message_pack_get_message_at(&pack, 0);
    rid_basic_id_get_uas_id(msg, uas_id, sizeof(uas_id));
    ASSERT_STR_EQ("DRONE001", uas_id);

    msg = rid_message_pack_get_message_at(&pack, 1);
    rid_basic_id_get_uas_id(msg, uas_id, sizeof(uas_id));
    ASSERT_STR_EQ("DRONE002", uas_id);

    PASS();
}

TEST
test_delete_message_at_null_pointer(void) {
    int status = rid_message_pack_delete_message_at(NULL, 0);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_delete_message_at_out_of_range(void) {
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;

    rid_message_pack_init(&pack);
    rid_basic_id_init(&basic_id);
    rid_message_pack_add_message(&pack, &basic_id);

    int status = rid_message_pack_delete_message_at(&pack, 1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_message_pack_delete_message_at(&pack, UINT8_MAX);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    /* Empty pack */
    rid_message_pack_init(&pack);
    status = rid_message_pack_delete_message_at(&pack, 0);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_replace_message_at(void) {
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;
    char uas_id[21];

    rid_message_pack_init(&pack);

    /* Add 3 messages */
    for (uint8_t i = 0; i < 3; ++i) {
        rid_basic_id_init(&basic_id);
        snprintf(uas_id, sizeof(uas_id), "DRONE%03u", i + 1);
        rid_basic_id_set_uas_id(&basic_id, uas_id);
        rid_message_pack_add_message(&pack, &basic_id);
    }

    /* Replace middle message */
    rid_basic_id_init(&basic_id);
    rid_basic_id_set_uas_id(&basic_id, "REPLACED");
    int status = rid_message_pack_replace_message_at(&pack, 1, &basic_id);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(3, rid_message_pack_get_message_count(&pack));

    /* Verify messages */
    const rid_basic_id_t *msg = rid_message_pack_get_message_at(&pack, 0);
    rid_basic_id_get_uas_id(msg, uas_id, sizeof(uas_id));
    ASSERT_STR_EQ("DRONE001", uas_id);

    msg = rid_message_pack_get_message_at(&pack, 1);
    rid_basic_id_get_uas_id(msg, uas_id, sizeof(uas_id));
    ASSERT_STR_EQ("REPLACED", uas_id);

    msg = rid_message_pack_get_message_at(&pack, 2);
    rid_basic_id_get_uas_id(msg, uas_id, sizeof(uas_id));
    ASSERT_STR_EQ("DRONE003", uas_id);

    PASS();
}

TEST
test_replace_message_at_null_pointer(void) {
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;

    rid_message_pack_init(&pack);
    rid_basic_id_init(&basic_id);
    rid_message_pack_add_message(&pack, &basic_id);

    int status = rid_message_pack_replace_message_at(NULL, 0, &basic_id);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_message_pack_replace_message_at(&pack, 0, NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_message_pack_replace_message_at(NULL, 0, NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_replace_message_at_out_of_range(void) {
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;

    rid_message_pack_init(&pack);
    rid_basic_id_init(&basic_id);
    rid_message_pack_add_message(&pack, &basic_id);

    int status = rid_message_pack_replace_message_at(&pack, 1, &basic_id);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_message_pack_replace_message_at(&pack, 6, &basic_id);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    /* Empty pack */
    rid_message_pack_init(&pack);
    status = rid_message_pack_replace_message_at(&pack, 0, &basic_id);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_message_pack_validate_valid(void) {
    rid_message_pack_t pack;

    rid_message_pack_init(&pack);

    int status = rid_message_pack_validate(&pack);
    ASSERT_EQ(RID_SUCCESS, status);

    PASS();
}

TEST
test_message_pack_validate_null_pointer(void) {
    int status = rid_message_pack_validate(NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_message_pack_validate_invalid_protocol_version(void) {
    rid_message_pack_t pack;

    rid_message_pack_init(&pack);

    /* Value between 2 and 0x0F is invalid */
    pack.protocol_version = 5;
    int status = rid_message_pack_validate(&pack);
    ASSERT_EQ(RID_ERROR_INVALID_PROTOCOL_VERSION, status);

    /* Valid versions should pass */
    pack.protocol_version = RID_PROTOCOL_VERSION_0;
    status = rid_message_pack_validate(&pack);
    ASSERT_EQ(RID_SUCCESS, status);

    pack.protocol_version = RID_PROTOCOL_VERSION_1;
    status = rid_message_pack_validate(&pack);
    ASSERT_EQ(RID_SUCCESS, status);

    pack.protocol_version = RID_PROTOCOL_VERSION_2;
    status = rid_message_pack_validate(&pack);
    ASSERT_EQ(RID_SUCCESS, status);

    pack.protocol_version = RID_PROTOCOL_PRIVATE_USE;
    status = rid_message_pack_validate(&pack);
    ASSERT_EQ(RID_SUCCESS, status);

    PASS();
}

TEST
test_message_pack_validate_invalid_message_type(void) {
    rid_message_pack_t pack;

    rid_message_pack_init(&pack);
    pack.message_type = RID_MESSAGE_TYPE_LOCATION;

    int status = rid_message_pack_validate(&pack);
    ASSERT_EQ(RID_ERROR_UNKNOWN_MESSAGE_TYPE, status);

    PASS();
}

TEST
test_message_pack_validate_invalid_message_size(void) {
    rid_message_pack_t pack;

    rid_message_pack_init(&pack);
    pack.message_size = 24;

    int status = rid_message_pack_validate(&pack);
    ASSERT_EQ(RID_ERROR_INVALID_MESSAGE_SIZE, status);

    pack.message_size = 26;
    status = rid_message_pack_validate(&pack);
    ASSERT_EQ(RID_ERROR_INVALID_MESSAGE_SIZE, status);

    PASS();
}

TEST
test_message_pack_validate_invalid_message_count(void) {
    rid_message_pack_t pack;

    rid_message_pack_init(&pack);
    pack.message_count = RID_MESSAGE_PACK_MAX_MESSAGES + 1;

    int status = rid_message_pack_validate(&pack);
    ASSERT_EQ(RID_ERROR_INVALID_MESSAGE_COUNT, status);

    pack.message_count = UINT8_MAX;
    status = rid_message_pack_validate(&pack);
    ASSERT_EQ(RID_ERROR_INVALID_MESSAGE_COUNT, status);

    PASS();
}

TEST
test_message_pack_to_json(void) {
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;
    rid_location_t location;
    char buffer[2048];

    rid_message_pack_init(&pack);
    rid_basic_id_init(&basic_id);
    rid_location_init(&location);

    rid_basic_id_set_uas_id(&basic_id, "1ABCD2345EF678XYZ");
    rid_location_set_latitude(&location, 60.1699);

    rid_message_pack_add_message(&pack, &basic_id);
    rid_message_pack_add_message(&pack, &location);

    int result = rid_message_pack_to_json(&pack, buffer, sizeof(buffer));
    ASSERT(result > 0);
    ASSERT(strstr(buffer, "\"message_count\": 2") != NULL);
    ASSERT(strstr(buffer, "\"messages\":") != NULL);
    ASSERT(strstr(buffer, "1ABCD2345EF678XYZ") != NULL);

    PASS();
}

TEST
test_message_pack_to_json_null(void) {
    rid_message_pack_t pack;
    char buffer[2048];

    rid_message_pack_init(&pack);

    ASSERT_EQ(RID_ERROR_NULL_POINTER, rid_message_pack_to_json(NULL, buffer, sizeof(buffer)));
    ASSERT_EQ(RID_ERROR_NULL_POINTER, rid_message_pack_to_json(&pack, NULL, sizeof(buffer)));

    PASS();
}

SUITE(message_pack_suite) {
    RUN_TEST(test_message_pack_init);
    RUN_TEST(test_message_pack_size);

    RUN_TEST(test_set_and_get_count);
    RUN_TEST(test_set_count_null_pointer);
    RUN_TEST(test_get_count_null_pointer);
    RUN_TEST(test_set_count_out_of_range);
    RUN_TEST(test_decode_message_pack_buffer);

    RUN_TEST(test_add_message);
    RUN_TEST(test_add_message_multiple);
    RUN_TEST(test_add_message_pack_full);
    RUN_TEST(test_add_message_null_pointer);

    RUN_TEST(test_get_message_at);
    RUN_TEST(test_get_message_at_null_pointer);
    RUN_TEST(test_get_message_at_out_of_range);

    RUN_TEST(test_delete_message_at);
    RUN_TEST(test_delete_message_at_first);
    RUN_TEST(test_delete_message_at_last);
    RUN_TEST(test_delete_message_at_null_pointer);
    RUN_TEST(test_delete_message_at_out_of_range);

    RUN_TEST(test_replace_message_at);
    RUN_TEST(test_replace_message_at_null_pointer);
    RUN_TEST(test_replace_message_at_out_of_range);

    RUN_TEST(test_message_pack_validate_valid);
    RUN_TEST(test_message_pack_validate_null_pointer);
    RUN_TEST(test_message_pack_validate_invalid_protocol_version);
    RUN_TEST(test_message_pack_validate_invalid_message_type);
    RUN_TEST(test_message_pack_validate_invalid_message_size);
    RUN_TEST(test_message_pack_validate_invalid_message_count);

    RUN_TEST(test_message_pack_to_json);
    RUN_TEST(test_message_pack_to_json_null);
}
