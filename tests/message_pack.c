#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "greatest.h"
#include "rid/message.h"
#include "rid/message_pack.h"
#include "rid/basic_id.h"

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

    rid_error_t status = rid_message_pack_init(NULL);
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
        rid_error_t status = rid_message_pack_set_message_count(&message, i);
        ASSERT_EQ(RID_SUCCESS, status);
        ASSERT_EQ(i, rid_message_pack_get_message_count(&message));
    }

    PASS();
}

TEST
test_set_count_null_pointer(void) {
    rid_error_t status = rid_message_pack_set_message_count(NULL, 1);
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

    rid_error_t status = rid_message_pack_set_message_count(&message, RID_MESSAGE_PACK_MAX_MESSAGES + 1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_message_pack_set_message_count(&message, UINT8_MAX);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_decode_message_pack_buffer(void) {
    rid_message_pack_t *message = (rid_message_pack_t *)buffer;

    ASSERT_EQ(RID_PROTOCOL_VERSION_2, rid_get_protocol_version(message));
    ASSERT_EQ(RID_MESSAGE_TYPE_MESSAGE_PACK, rid_get_message_type(message));
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
    rid_set_uas_id(&basic_id, "1596A3037164309A");
    rid_set_basic_id_type(&basic_id, RID_ID_TYPE_SERIAL_NUMBER);
    rid_set_ua_type(&basic_id, RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR);

    rid_error_t status = rid_message_pack_add_message(&pack, &basic_id);
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
        rid_error_t status = rid_message_pack_add_message(&pack, &basic_id);
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
    rid_error_t status = rid_message_pack_add_message(&pack, &basic_id);
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

    rid_error_t status = rid_message_pack_add_message(NULL, &basic_id);
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
        rid_set_uas_id(&basic_id, uas_id);
        rid_message_pack_add_message(&pack, &basic_id);
    }

    for (uint8_t i = 0; i < 3; ++i) {
        const rid_basic_id_t *msg = rid_message_pack_get_message_at(&pack, i);
        ASSERT(msg != NULL);

        rid_get_uas_id(msg, uas_id, sizeof(uas_id));
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
}
