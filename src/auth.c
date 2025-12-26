#include <string.h>
#include <stdint.h>
#include <stddef.h>

#include "rid/message.h"
#include "rid/auth.h"

int
rid_auth_init(rid_auth_t *message) {
    if (NULL == message) {
        return RID_ERROR_NULL_POINTER;
    }

    memset(message, 0, sizeof(rid_auth_t));

    message->protocol_version = RID_PROTOCOL_VERSION_2;
    message->message_type = RID_MESSAGE_TYPE_AUTH;
    message->page_number = 0;

    return RID_SUCCESS;
}

int
rid_auth_page_init(rid_auth_page_t *message, uint8_t page_number) {
    if (NULL == message) {
        return RID_ERROR_NULL_POINTER;
    }

    if (0 == page_number || page_number > RID_AUTH_MAX_PAGE_INDEX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    memset(message, 0, sizeof(rid_auth_page_t));

    message->protocol_version = RID_PROTOCOL_VERSION_2;
    message->message_type = RID_MESSAGE_TYPE_AUTH;
    message->page_number = page_number;

    return RID_SUCCESS;
}
