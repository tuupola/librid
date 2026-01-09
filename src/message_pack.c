/*

MIT License

Copyright (c) 2025-2026 Mika Tuupola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-cut-

This file is part of librid: https://github.com/tuupola/librid

SPDX-License-Identifier: MIT

*/

#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#include "rid/message.h"
#include "rid/message_pack.h"
#include "rid/basic_id.h"
#include "rid/location.h"
#include "rid/auth.h"
#include "rid/self_id.h"
#include "rid/system.h"
#include "rid/operator_id.h"

int
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

int
rid_message_pack_validate(const rid_message_pack_t *pack) {
    if (pack == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* Valid protocol versions: 0, 1, 2, or 0x0F (private use) */
    if (pack->protocol_version > RID_PROTOCOL_VERSION_2 &&
        pack->protocol_version != RID_PROTOCOL_PRIVATE_USE) {
        return RID_ERROR_INVALID_PROTOCOL_VERSION;
    }

    if (pack->message_type != RID_MESSAGE_TYPE_MESSAGE_PACK) {
        return RID_ERROR_WRONG_MESSAGE_TYPE;
    }

    if (pack->message_size != RID_MESSAGE_SIZE) {
        return RID_ERROR_INVALID_MESSAGE_SIZE;
    }

    if (pack->message_count > RID_MESSAGE_PACK_MAX_MESSAGES) {
        return RID_ERROR_INVALID_MESSAGE_COUNT;
    }

    return RID_SUCCESS;
}

int
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

int
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

int
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

int
rid_message_pack_replace_message_at(rid_message_pack_t *pack, uint8_t index, const void *message) {
    if (pack == NULL || message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (index >= pack->message_count) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    size_t offset = index * RID_MESSAGE_SIZE;
    memcpy(&pack->messages[offset], message, RID_MESSAGE_SIZE);

    return RID_SUCCESS;
}

int
rid_message_pack_snprintf(const rid_message_pack_t *pack, char *buffer, size_t buffer_size) {
    if (pack == NULL || buffer == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    int written = snprintf(buffer, buffer_size,
            "{\"protocol_version\": %u, \"message_type\": %u, "
            "\"message_count\": %u, \"messages\": [",
            rid_message_get_protocol_version(pack),
            rid_message_get_type(pack),
            rid_message_pack_get_message_count(pack));

    if (written < 0) {
        return written;
    }

    size_t pos = (size_t)written;
    uint8_t count = rid_message_pack_get_message_count(pack);

    for (uint8_t i = 0; i < count; ++i) {
        const void *msg = rid_message_pack_get_message_at(pack, i);
        rid_message_type_t type = rid_message_get_type(msg);

        if (i > 0 && pos < buffer_size) {
            written = snprintf(buffer + pos, buffer_size - pos, ", ");
            if (written > 0) {
                pos += (size_t)written;
            }
        }

        if (pos >= buffer_size) {
            break;
        }

        int msg_written = 0;
        switch (type) {
            case RID_MESSAGE_TYPE_BASIC_ID:
                msg_written = rid_basic_id_snprintf(
                        (const rid_basic_id_t *)msg,
                        buffer + pos,
                        buffer_size - pos
                    );
                break;
            case RID_MESSAGE_TYPE_LOCATION:
                msg_written = rid_location_snprintf(
                        (const rid_location_t *)msg,
                        buffer + pos,
                        buffer_size - pos
                    );
                break;
            case RID_MESSAGE_TYPE_SELF_ID:
                msg_written = rid_self_id_snprintf(
                        (const rid_self_id_t *)msg,
                        buffer + pos,
                        buffer_size - pos
                    );
                break;
            case RID_MESSAGE_TYPE_SYSTEM:
                msg_written = rid_system_snprintf(
                        (const rid_system_t *)msg,
                        buffer + pos,
                        buffer_size - pos
                    );
                break;
            case RID_MESSAGE_TYPE_OPERATOR_ID:
                msg_written = rid_operator_id_snprintf(
                        (const rid_operator_id_t *)msg,
                        buffer + pos,
                        buffer_size - pos
                    );
                break;
            default:
                msg_written = snprintf(
                        buffer + pos,
                        buffer_size - pos,
                        "{\"type\": %u}",
                        type
                    );
                break;
        }

        if (msg_written > 0) {
            pos += (size_t)msg_written;
        }
    }

    if (pos < buffer_size) {
        written = snprintf(buffer + pos, buffer_size - pos, "]}");
        if (written > 0) {
            pos += (size_t)written;
        }
    }

    return (int)pos;
}
