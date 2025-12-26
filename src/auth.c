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

int
rid_set_auth_type(rid_auth_t *message, rid_auth_type_t type) {
    if (NULL == message) {
        return RID_ERROR_NULL_POINTER;
    }

    if (type > RID_AUTH_TYPE_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    message->auth_type = type;

    return RID_SUCCESS;
}

rid_auth_type_t
rid_get_auth_type(const rid_auth_t *message) {
    if (NULL == message) {
        return RID_AUTH_TYPE_NONE;
    }

    return (rid_auth_type_t)message->auth_type;
}

int
rid_set_auth_last_page_index(rid_auth_t *message, uint8_t index) {
    if (NULL == message) {
        return RID_ERROR_NULL_POINTER;
    }

    if (index > RID_AUTH_MAX_PAGE_INDEX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    message->last_page_index = index;

    return RID_SUCCESS;
}

uint8_t
rid_get_auth_last_page_index(const rid_auth_t *message) {
    if (NULL == message) {
        return 0;
    }

    return message->last_page_index;
}

int
rid_set_auth_length(rid_auth_t *message, uint8_t length) {
    if (NULL == message) {
        return RID_ERROR_NULL_POINTER;
    }

    message->length = length;

    return RID_SUCCESS;
}

uint8_t
rid_get_auth_length(const rid_auth_t *message) {
    if (NULL == message) {
        return 0;
    }

    return message->length;
}

int
rid_set_auth_timestamp(rid_auth_t *message, uint32_t timestamp) {
    if (NULL == message) {
        return RID_ERROR_NULL_POINTER;
    }

    message->timestamp = timestamp;

    return RID_SUCCESS;
}

uint32_t
rid_get_auth_timestamp(const rid_auth_t *message) {
    if (NULL == message) {
        return 0;
    }

    return message->timestamp;
}
