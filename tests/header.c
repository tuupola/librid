#include <string.h>

#include "greatest.h"
#include "rid/header.h"

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

        rid_message_type_t result = rid_get_message_type(&message);

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

        rid_protocol_version_t result = rid_get_protocol_version(&message);

        ASSERT_EQ(versions[i], result);
    }

    PASS();
}

SUITE(header_suite) {
    RUN_TEST(test_get_message_type);
    RUN_TEST(test_get_protocol_version);
}
