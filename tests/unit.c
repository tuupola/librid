#include "greatest.h"
#include "rid/message.h"
#include "rid/message/basic_id.h"
#include "unit.h"

TEST
should_pass(void)
{
    PASS();
}

TEST
should_get_protocol_version(void)
{
    ASSERT(2 == rid_message_get_protocol_version(basic_id_message));
    ASSERT(2 == rid_message_get_protocol_version(system_message));
    ASSERT(2 == rid_message_get_protocol_version(operator_id_message));
    PASS();
}

TEST
should_get_message_type(void)
{
    ASSERT(RID_MESSAGE_TYPE_BASIC_ID == rid_message_get_type(basic_id_message));
    ASSERT(RID_MESSAGE_TYPE_SYSTEM == rid_message_get_type(system_message));
    ASSERT(RID_MESSAGE_TYPE_OPERATOR_ID == rid_message_get_type(operator_id_message));
    PASS();
}

TEST
should_get_id_type(void)
{
    ASSERT(RID_MESSAGE_ID_TYPE_SERIAL_NUMBER == rid_message_get_id_type((const rid_message_basic_id_t *)basic_id_message));
    ASSERT(RID_MESSAGE_ID_TYPE_SERIAL_NUMBER == ((const rid_message_basic_id_t *)basic_id_message)->id_type);
    PASS();
}

TEST
should_set_id_type(void)
{
    ASSERT(RID_MESSAGE_ID_TYPE_SERIAL_NUMBER == rid_message_get_id_type((const rid_message_basic_id_t *)basic_id_message));
    ASSERT(0 == rid_message_set_id_type((rid_message_basic_id_t *)basic_id_message, RID_MESSAGE_ID_TYPE_CAA_REGISTRATION_ID));
    ASSERT(RID_MESSAGE_ID_TYPE_CAA_REGISTRATION_ID == rid_message_get_id_type((const rid_message_basic_id_t *)basic_id_message));
    PASS();
}

TEST
should_get_ua_type(void)
{
    ASSERT(RID_MESSAGE_UA_TYPE_NONE == rid_message_get_ua_type((const rid_message_basic_id_t *)basic_id_message));
    ASSERT(RID_MESSAGE_UA_TYPE_NONE == ((const rid_message_basic_id_t *)basic_id_message)->ua_type);
    PASS();
}

TEST
should_set_ua_type(void)
{
    ASSERT(RID_MESSAGE_UA_TYPE_NONE == rid_message_get_ua_type((const rid_message_basic_id_t *)basic_id_message));
    ASSERT(0 == rid_message_set_ua_type((rid_message_basic_id_t *)basic_id_message, RID_MESSAGE_UA_TYPE_KITE));
    ASSERT(RID_MESSAGE_UA_TYPE_KITE == ((const rid_message_basic_id_t *)basic_id_message)->ua_type);
    PASS();
}

GREATEST_MAIN_DEFS();

int
main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN();

    RUN_TEST(should_pass);
    RUN_TEST(should_get_protocol_version);
    RUN_TEST(should_get_message_type);
    RUN_TEST(should_get_id_type);
    RUN_TEST(should_set_id_type);
    RUN_TEST(should_get_ua_type);
    RUN_TEST(should_set_ua_type);

    GREATEST_MAIN_END();
}
