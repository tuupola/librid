#include <stdint.h>
#include <string.h>

#include "greatest.h"
#include "rid/header.h"
#include "rid/message_pack.h"

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
        rid_error_t status = rid_set_message_count(&message, i);
        ASSERT_EQ(RID_SUCCESS, status);
        ASSERT_EQ(i, rid_get_message_count(&message));
    }

    PASS();
}

TEST
test_set_count_null_pointer(void) {
    rid_error_t status = rid_set_message_count(NULL, 1);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);
    PASS();
}

TEST
test_get_count_null_pointer(void) {
    uint8_t count = rid_get_message_count(NULL);
    ASSERT_EQ(0, count);
    PASS();
}

TEST
test_set_count_out_of_range(void) {
    rid_message_pack_t message;
    rid_message_pack_init(&message);

    rid_error_t status = rid_set_message_count(&message, RID_MESSAGE_PACK_MAX_MESSAGES + 1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_set_message_count(&message, UINT8_MAX);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_decode_message_pack_buffer(void) {
    rid_message_pack_t *message = (rid_message_pack_t *)buffer;

    ASSERT_EQ(RID_PROTOCOL_VERSION_2, rid_get_protocol_version(message));
    ASSERT_EQ(RID_MESSAGE_TYPE_MESSAGE_PACK, rid_get_message_type(message));
    // ASSERT_EQ(RID_MESSAGE_SIZE, rid_message_get_message_size());

    ASSERT_EQ(4, rid_get_message_count(message));

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
}
