#include <stdint.h>
#include <string.h>

#include "greatest.h"
#include "rid/message.h"
#include "rid/operator_id.h"

/* Real life captured message */
static uint8_t buffer[] = {
    0x52, 0x00, 0x46, 0x49, 0x4e, 0x38, 0x37, 0x61, 0x73,
    0x74, 0x72, 0x64, 0x67, 0x65, 0x31, 0x32, 0x6b, 0x38,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

TEST
test_set_and_get_operator_id_type(void) {
    rid_operator_id_type_t types[] = {
        RID_ID_TYPE_OPERATOR_ID
    };

    for (size_t i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
        rid_operator_id_t message;

        memset(&message, 0, sizeof(message));
        int status = rid_operator_id_set_type(&message, types[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        rid_operator_id_type_t result = rid_operator_id_get_type(&message);

        ASSERT_EQ(types[i], result);
    }

    PASS();
}

TEST
test_set_operator_id_type_null_pointer(void) {
    int status = rid_operator_id_set_type(NULL, RID_ID_TYPE_OPERATOR_ID);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_and_get_operator_id(void) {
    const char *test_ids[] = {
        "ABC123",
        "12345678901234567890",
        "TEST-ID",
        "",
        "X"
    };

    for (size_t i = 0; i < sizeof(test_ids) / sizeof(test_ids[0]); i++) {
        rid_operator_id_t message;
        int status;

        memset(&message, 0, sizeof(message));

        status = rid_operator_id_set(&message, test_ids[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        char buffer[21];
        status = rid_operator_id_get(&message, buffer, sizeof(buffer));
        ASSERT_EQ(RID_SUCCESS, status);

        ASSERT_STR_EQ(test_ids[i], buffer);
    }

    PASS();
}

TEST
test_set_operator_id_must_be_ascii(void) {
    rid_operator_id_t message;
    int status;

    memset(&message, 0, sizeof(message));

    /* Test with non-ASCII character (UTF-8 encoded) */
    status = rid_operator_id_set(&message, "TEST\xC3\xA4");
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    /* Test with character > 127 */
    status = rid_operator_id_set(&message, "TEST\xFF");
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    /* Test valid ASCII */
    status = rid_operator_id_set(&message, "BRAWND0");
    ASSERT_EQ(RID_SUCCESS, status);

    PASS();
}

TEST
test_set_operator_id_too_long(void) {
    rid_operator_id_t message;
    memset(&message, 0, sizeof(message));

    /* 21 characters - one over limit */
    int status = rid_operator_id_set(&message, "123456789012345678901");
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_LARGE, status);

    /* Much longer string */
    status = rid_operator_id_set(&message, "12345678901234567890123456789012345678901234567890");
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_LARGE, status);

    /* Exactly 20 characters should work */
    status = rid_operator_id_set(&message, "12345678901234567890");
    ASSERT_EQ(RID_SUCCESS, status);

    PASS();
}

TEST
test_set_operator_id_null_pointer(void) {
    int status;
    rid_operator_id_t message;
    memset(&message, 0, sizeof(message));

    status = rid_operator_id_set(NULL, "TEST");
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_operator_id_set(&message, NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_decode_operator_id_buffer(void) {
    rid_operator_id_t *message = (rid_operator_id_t *)buffer;

    ASSERT_EQ(RID_ID_TYPE_OPERATOR_ID, rid_operator_id_get_type(message));

    char operator_id[21];
    int status = rid_operator_id_get(message, operator_id, sizeof(operator_id));
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_STR_EQ("FIN87astrdge12k8", operator_id);

    PASS();
}

TEST
test_get_operator_id_null_pointer(void) {
    int status;
    rid_operator_id_t message;
    char buf[21];

    memset(&message, 0, sizeof(message));

    status = rid_operator_id_get(NULL, buf, sizeof(buf));
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_operator_id_get(&message, NULL, sizeof(buf));
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_get_operator_id_buffer_too_small(void) {
    rid_operator_id_t message;
    int status;
    char buf[10];

    memset(&message, 0, sizeof(message));
    rid_operator_id_set(&message, "I like money");

    status = rid_operator_id_get(&message, buf, sizeof(buf));
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_SMALL, status);

    PASS();
}

TEST
test_operator_id_init(void) {
    rid_operator_id_t message;
    int status;

    memset(&message, 0xFF, sizeof(message));

    status = rid_operator_id_init(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    ASSERT_EQ(RID_PROTOCOL_VERSION_2, message.protocol_version);
    ASSERT_EQ(RID_MESSAGE_TYPE_OPERATOR_ID, message.message_type);
    ASSERT_EQ(RID_ID_TYPE_OPERATOR_ID, message.id_type);

    for (size_t i = 0; i < 20; i++) {
        ASSERT_EQ(0, message.operator_id[i]);
    }

    PASS();
}

TEST
test_operator_id_init_null_pointer(void) {
    int status = rid_operator_id_init(NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

SUITE(operator_id_suite) {
    RUN_TEST(test_operator_id_init);
    RUN_TEST(test_operator_id_init_null_pointer);

    RUN_TEST(test_set_and_get_operator_id_type);
    RUN_TEST(test_set_operator_id_type_null_pointer);

    RUN_TEST(test_set_and_get_operator_id);
    RUN_TEST(test_set_operator_id_must_be_ascii);
    RUN_TEST(test_set_operator_id_too_long);
    RUN_TEST(test_set_operator_id_null_pointer);
    RUN_TEST(test_get_operator_id_null_pointer);
    RUN_TEST(test_get_operator_id_buffer_too_small);

    RUN_TEST(test_decode_operator_id_buffer);
}
