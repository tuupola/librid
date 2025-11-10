#include <stdint.h>
#include <stddef.h>

#include "rid/message/basic_id.h"

uint8_t
rid_message_get_id_type(const rid_message_basic_id_t *message)
{
    return (rid_message_id_type_t)message->id_type;
}

uint8_t
rid_message_get_ua_type(const rid_message_basic_id_t *message)
{
    return (rid_message_ua_type_t)message->ua_type;
}

int32_t
rid_message_set_id_type(rid_message_basic_id_t *message, rid_message_id_type_t type) {
    if (message == NULL) {
        return -1;
    }

    message->id_type = type;

    return 0;
}

int32_t
rid_message_set_ua_type(rid_message_basic_id_t *message, rid_message_ua_type_t type) {
    if (NULL == message) {
        return -1;
    }

    message->ua_type = type;

    return 0;
}
