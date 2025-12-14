#include <string.h>
#include <stdint.h>
#include <stddef.h>

#include "rid/header.h"
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
rid_set_message_count(rid_message_pack_t *pack, uint8_t count) {
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
rid_get_message_count(const rid_message_pack_t *pack) {
    if (pack == NULL) {
        return 0;
    }
    return pack->message_count;
}
