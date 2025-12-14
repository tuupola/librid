#include <string.h>
#include <stdint.h>
#include <stddef.h>

#include "rid/header.h"
#include "rid/message_pack.h"

rid_error_t
rid_message_pack_init(rid_message_pack_t *message) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    memset(message, 0, sizeof(rid_message_pack_t));

    message->protocol_version = RID_PROTOCOL_VERSION_2;
    message->message_type = RID_MESSAGE_TYPE_MESSAGE_PACK;
    message->message_size = RID_MESSAGE_SIZE;

    return RID_SUCCESS;
}
