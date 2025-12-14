#include <stdint.h>
#include <string.h>

#include "greatest.h"
#include "rid/header.h"
#include "rid/message_pack.h"

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

SUITE(message_pack_suite) {
    RUN_TEST(test_message_pack_init);
    RUN_TEST(test_message_pack_size);
}
