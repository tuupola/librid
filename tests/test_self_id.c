#include <string.h>

#include "greatest.h"
#include "rid/message.h"
#include "rid/self_id.h"

TEST
test_set_and_get_description_type(void) {
    rid_description_type_t types[] = {
        RID_DESCRIPTION_TYPE_TEXT,
        RID_DESCRIPTION_TYPE_EMERGENCY,
        RID_DESCRIPTION_TYPE_EXTENDED_STATUS
    };

    for (size_t i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
        rid_self_id_t message;

        memset(&message, 0, sizeof(message));
        int status = rid_self_id_set_description_type(&message, types[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        rid_description_type_t result = rid_self_id_get_description_type(&message);

        ASSERT_EQ(types[i], result);
    }

    PASS();
}

TEST
test_set_description_type_null_pointer(void) {
    int status = rid_self_id_set_description_type(NULL, RID_DESCRIPTION_TYPE_TEXT);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_and_get_description(void) {
    const char *test_descriptions[] = {
        "Kakotron:Survey",
        "12345678901234567890123",
        "Bearmetal photo shoot",
        "",
        "X"
    };

    for (size_t i = 0; i < sizeof(test_descriptions) / sizeof(test_descriptions[0]); i++) {
        rid_self_id_t message;
        int status;

        memset(&message, 0, sizeof(message));

        status = rid_self_id_set_description(&message, test_descriptions[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        char buffer[24];
        status = rid_self_id_get_description(&message, buffer, sizeof(buffer));
        ASSERT_EQ(RID_SUCCESS, status);

        ASSERT_STR_EQ(test_descriptions[i], buffer);
    }

    PASS();
}

TEST
test_set_description_must_be_ascii(void) {
    rid_self_id_t message;
    int status;

    memset(&message, 0, sizeof(message));

    /* Test with non-ASCII character (UTF-8 encoded) */
    status = rid_self_id_set_description(&message, "TEST\xC3\xA4");
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    /* Test with character > 127 */
    status = rid_self_id_set_description(&message, "TEST\xFF");
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    /* Test valid ASCII */
    status = rid_self_id_set_description(&message, "All your base are");
    ASSERT_EQ(RID_SUCCESS, status);

    PASS();
}

TEST
test_set_description_too_long(void) {
    rid_self_id_t message;
    int status;

    memset(&message, 0, sizeof(message));

    /* Test with description > 23 characters */
    status = rid_self_id_set_description(&message, "All your base are belong to us...");
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_LARGE, status);

    PASS();
}

TEST
test_set_description_null_pointer(void) {
    int status;
    rid_self_id_t message;
    memset(&message, 0, sizeof(message));

    status = rid_self_id_set_description(NULL, "TEST");
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_self_id_set_description(&message, NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_get_description_null_pointer(void) {
    int status;
    rid_self_id_t message;
    char buffer[24];

    memset(&message, 0, sizeof(message));

    status = rid_self_id_get_description(NULL, buffer, sizeof(buffer));
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_self_id_get_description(&message, NULL, sizeof(buffer));
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_get_description_buffer_too_small(void) {
    rid_self_id_t message;
    int status;
    char buffer[10];

    memset(&message, 0, sizeof(message));
    rid_self_id_set_description(&message, "Go away, batin!");

    status = rid_self_id_get_description(&message, buffer, sizeof(buffer));
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_SMALL, status);

    PASS();
}

TEST
test_self_id_init(void) {
    rid_self_id_t message;
    int status;

    memset(&message, 0xFF, sizeof(message));

    status = rid_self_id_init(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    ASSERT_EQ(RID_PROTOCOL_VERSION_2, message.protocol_version);
    ASSERT_EQ(RID_MESSAGE_TYPE_SELF_ID, message.message_type);
    ASSERT_EQ(RID_DESCRIPTION_TYPE_TEXT, message.description_type);

    for (size_t i = 0; i < 23; i++) {
        ASSERT_EQ(0, message.description[i]);
    }

    PASS();
}

TEST
test_self_id_init_null_pointer(void) {
    int status = rid_self_id_init(NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_description_type_to_string(void) {
    ASSERT_STR_EQ("RID_DESCRIPTION_TYPE_TEXT", rid_description_type_to_string(RID_DESCRIPTION_TYPE_TEXT));
    ASSERT_STR_EQ("RID_DESCRIPTION_TYPE_EMERGENCY", rid_description_type_to_string(RID_DESCRIPTION_TYPE_EMERGENCY));
    ASSERT_STR_EQ("RID_DESCRIPTION_TYPE_EXTENDED_STATUS", rid_description_type_to_string(RID_DESCRIPTION_TYPE_EXTENDED_STATUS));
    ASSERT_STR_EQ("UNKNOWN", rid_description_type_to_string((rid_description_type_t)99));
    PASS();
}

TEST
test_self_id_validate_valid_message(void) {
    rid_self_id_t message;

    rid_self_id_init(&message);

    int status = rid_self_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    PASS();
}

TEST
test_self_id_validate_null_pointer(void) {
    int status = rid_self_id_validate(NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_self_id_validate_invalid_protocol_version(void) {
    rid_self_id_t message;

    rid_self_id_init(&message);

    /* Value between 2 and 0x0F is invalid */
    message.protocol_version = 5;
    int status = rid_self_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_PROTOCOL_VERSION, status);

    /* Valid versions should pass */
    message.protocol_version = RID_PROTOCOL_VERSION_0;
    status = rid_self_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    message.protocol_version = RID_PROTOCOL_VERSION_1;
    status = rid_self_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    message.protocol_version = RID_PROTOCOL_VERSION_2;
    status = rid_self_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    message.protocol_version = RID_PROTOCOL_PRIVATE_USE;
    status = rid_self_id_validate(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    PASS();
}

TEST
test_self_id_validate_invalid_message_type(void) {
    rid_self_id_t message;

    rid_self_id_init(&message);
    message.message_type = RID_MESSAGE_TYPE_LOCATION;

    int status = rid_self_id_validate(&message);
    ASSERT_EQ(RID_ERROR_WRONG_MESSAGE_TYPE, status);

    PASS();
}

TEST
test_self_id_validate_invalid_description(void) {
    rid_self_id_t message;

    rid_self_id_init(&message);
    message.description[5] = (char)0xFF;

    int status = rid_self_id_validate(&message);
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    PASS();
}

SUITE(self_id_suite) {
    RUN_TEST(test_self_id_init);
    RUN_TEST(test_self_id_init_null_pointer);

    RUN_TEST(test_set_and_get_description_type);
    RUN_TEST(test_set_description_type_null_pointer);

    RUN_TEST(test_set_and_get_description);
    RUN_TEST(test_set_description_must_be_ascii);
    RUN_TEST(test_set_description_too_long);
    RUN_TEST(test_set_description_null_pointer);
    RUN_TEST(test_get_description_null_pointer);
    RUN_TEST(test_get_description_buffer_too_small);

    RUN_TEST(test_description_type_to_string);

    RUN_TEST(test_self_id_validate_valid_message);
    RUN_TEST(test_self_id_validate_null_pointer);
    RUN_TEST(test_self_id_validate_invalid_protocol_version);
    RUN_TEST(test_self_id_validate_invalid_message_type);
    RUN_TEST(test_self_id_validate_invalid_description);
}
