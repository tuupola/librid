#include <stdint.h>

#include "rid/header.h"

rid_message_type_t
rid_get_message_type(const void *message) {
    rid_message_t *msg = (rid_message_t *)message;
    return (rid_message_type_t)msg->message_type;
}

rid_protocol_version_t
rid_get_protocol_version(const void *message) {
    rid_message_t *msg = (rid_message_t *)message;
    return msg->protocol_version;
}
