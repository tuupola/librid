#include <stdint.h>

#include "rid/message.h"

uint8_t
rid_message_get_type(const void *message)
{
    rid_message_byte_0_t byte_0 = *((rid_message_byte_0_t *)message);
    return (rid_message_type_t)byte_0.message_type;
}

uint8_t
rid_message_get_protocol_version(const void *message)
{
    rid_message_byte_0_t byte_0 = *((rid_message_byte_0_t *)message);
    return byte_0.protocol_version;
}

