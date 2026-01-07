#include <string.h>

#include "greatest.h"
#include "rid/message.h"

TEST
test_get_message_type(void) {
    rid_message_type_t types[] = {
        RID_MESSAGE_TYPE_BASIC_ID,
        RID_MESSAGE_TYPE_LOCATION,
        RID_MESSAGE_TYPE_AUTH,
        RID_MESSAGE_TYPE_SELF_ID,
        RID_MESSAGE_TYPE_SYSTEM,
        RID_MESSAGE_TYPE_OPERATOR_ID,
        RID_MESSAGE_TYPE_MESSAGE_PACK
    };

    for (size_t i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
        rid_message_t message;

        memset(&message, 0, sizeof(message));
        message.message_type = types[i];

        rid_message_type_t result = rid_message_get_type(&message);

        ASSERT_EQ(types[i], result);
    }

    PASS();
}

TEST
test_get_protocol_version(void) {
    rid_protocol_version_t versions[] = {
        RID_PROTOCOL_VERSION_0,
        RID_PROTOCOL_VERSION_1,
        RID_PROTOCOL_VERSION_2,
        RID_PROTOCOL_PRIVATE_USE
    };

    for (size_t i = 0; i < sizeof(versions) / sizeof(versions[0]); i++) {
        rid_message_t message;

        memset(&message, 0, sizeof(message));
        message.protocol_version = versions[i];

        rid_protocol_version_t result = rid_message_get_protocol_version(&message);

        ASSERT_EQ(versions[i], result);
    }

    PASS();
}

TEST
test_message_type_to_string(void) {
    ASSERT_STR_EQ("RID_MESSAGE_TYPE_BASIC_ID", rid_message_type_to_string(RID_MESSAGE_TYPE_BASIC_ID));
    ASSERT_STR_EQ("RID_MESSAGE_TYPE_LOCATION", rid_message_type_to_string(RID_MESSAGE_TYPE_LOCATION));
    ASSERT_STR_EQ("RID_MESSAGE_TYPE_AUTH", rid_message_type_to_string(RID_MESSAGE_TYPE_AUTH));
    ASSERT_STR_EQ("RID_MESSAGE_TYPE_SELF_ID", rid_message_type_to_string(RID_MESSAGE_TYPE_SELF_ID));
    ASSERT_STR_EQ("RID_MESSAGE_TYPE_SYSTEM", rid_message_type_to_string(RID_MESSAGE_TYPE_SYSTEM));
    ASSERT_STR_EQ("RID_MESSAGE_TYPE_OPERATOR_ID", rid_message_type_to_string(RID_MESSAGE_TYPE_OPERATOR_ID));
    ASSERT_STR_EQ("RID_MESSAGE_TYPE_MESSAGE_PACK", rid_message_type_to_string(RID_MESSAGE_TYPE_MESSAGE_PACK));
    ASSERT_STR_EQ("UNKNOWN", rid_message_type_to_string((rid_message_type_t)99));
    PASS();
}

TEST
test_protocol_version_to_string(void) {
    ASSERT_STR_EQ("RID_PROTOCOL_VERSION_0", rid_protocol_version_to_string(RID_PROTOCOL_VERSION_0));
    ASSERT_STR_EQ("RID_PROTOCOL_VERSION_1", rid_protocol_version_to_string(RID_PROTOCOL_VERSION_1));
    ASSERT_STR_EQ("RID_PROTOCOL_VERSION_2", rid_protocol_version_to_string(RID_PROTOCOL_VERSION_2));
    ASSERT_STR_EQ("RID_PROTOCOL_PRIVATE_USE", rid_protocol_version_to_string(RID_PROTOCOL_PRIVATE_USE));
    ASSERT_STR_EQ("UNKNOWN", rid_protocol_version_to_string((rid_protocol_version_t)99));
    PASS();
}

TEST
test_error_to_string(void) {
    ASSERT_STR_EQ("RID_SUCCESS", rid_error_to_string(RID_SUCCESS));
    ASSERT_STR_EQ("RID_ERROR_NULL_POINTER", rid_error_to_string(RID_ERROR_NULL_POINTER));
    ASSERT_STR_EQ("RID_ERROR_BUFFER_TOO_SMALL", rid_error_to_string(RID_ERROR_BUFFER_TOO_SMALL));
    ASSERT_STR_EQ("RID_ERROR_BUFFER_TOO_LARGE", rid_error_to_string(RID_ERROR_BUFFER_TOO_LARGE));
    ASSERT_STR_EQ("RID_ERROR_INVALID_CHARACTER", rid_error_to_string(RID_ERROR_INVALID_CHARACTER));
    ASSERT_STR_EQ("RID_ERROR_OUT_OF_RANGE", rid_error_to_string(RID_ERROR_OUT_OF_RANGE));
    ASSERT_STR_EQ("UNKNOWN", rid_error_to_string((rid_error_t)99));
    PASS();
}

SUITE(header_suite) {
    RUN_TEST(test_get_message_type);
    RUN_TEST(test_get_protocol_version);
    RUN_TEST(test_message_type_to_string);
    RUN_TEST(test_protocol_version_to_string);
    RUN_TEST(test_error_to_string);
}
