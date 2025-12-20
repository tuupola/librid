#include <string.h>
#include <stdint.h>
#include <stddef.h>

#include "rid/message.h"
#include "rid/message_pack.h"

rid_error_t
rid_message_pack_init(rid_message_pack_t *pack) {
    if (pack == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    memset(pack, 0, sizeof(rid_message_pack_t));

    pack->protocol_version = RID_PROTOCOL_VERSION_2;
    pack->message_type = RID_MESSAGE_TYPE_MESSAGE_PACK;
    pack->message_size = RID_MESSAGE_SIZE;

    return RID_SUCCESS;
}

rid_error_t
rid_message_pack_set_message_count(rid_message_pack_t *pack, uint8_t count) {
    if (pack == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (count > RID_MESSAGE_PACK_MAX_MESSAGES) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    pack->message_count = count;

    return RID_SUCCESS;
}

uint8_t
rid_message_pack_get_message_count(const rid_message_pack_t *pack) {
    if (pack == NULL) {
        return 0;
    }
    return pack->message_count;
}

rid_error_t
rid_message_pack_add_message(rid_message_pack_t *pack, const void *message) {
    if (pack == NULL || message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (pack->message_count >= RID_MESSAGE_PACK_MAX_MESSAGES) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    size_t offset = pack->message_count * RID_MESSAGE_SIZE;
    memcpy(&pack->messages[offset], message, RID_MESSAGE_SIZE);
    ++pack->message_count;

    return RID_SUCCESS;
}

const void *
rid_message_pack_get_message_at(const rid_message_pack_t *pack, uint8_t index) {
    if (pack == NULL || index >= pack->message_count) {
        return NULL;
    }

    size_t offset = index * RID_MESSAGE_SIZE;
    return &pack->messages[offset];
}

rid_error_t
rid_message_pack_delete_message_at(rid_message_pack_t *pack, uint8_t index) {
    if (pack == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (index >= pack->message_count) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    /* Shift remaining messages down */
    size_t offset = index * RID_MESSAGE_SIZE;
    size_t remaining = (pack->message_count - index - 1) * RID_MESSAGE_SIZE;
    if (remaining > 0) {
        memmove(&pack->messages[offset], &pack->messages[offset + RID_MESSAGE_SIZE], remaining);
    }

    --pack->message_count;

    return RID_SUCCESS;
}
