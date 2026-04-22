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

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "rid/auth.h"
#include "rid/message.h"
#include "rid/message_pack.h"

int rid_message_pack_init(rid_message_pack_t *pack) {
    if (pack == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    memset(pack, 0, sizeof(rid_message_pack_t));

    pack->protocol_version = RID_PROTOCOL_VERSION_2;
    pack->message_type = RID_MESSAGE_TYPE_MESSAGE_PACK;
    pack->message_size = RID_MESSAGE_SIZE;

    return RID_SUCCESS;
}

int rid_message_pack_validate(const rid_message_pack_t *pack) {
    if (pack == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* Valid protocol versions: 0, 1, 2, or 0x0F (private use) */
    if (pack->protocol_version > RID_PROTOCOL_VERSION_2 &&
        pack->protocol_version != RID_PROTOCOL_PRIVATE_USE) {
        return RID_ERROR_INVALID_PROTOCOL_VERSION;
    }

    if (pack->message_type != RID_MESSAGE_TYPE_MESSAGE_PACK) {
        return RID_ERROR_UNKNOWN_MESSAGE_TYPE;
    }

    if (pack->message_size != RID_MESSAGE_SIZE) {
        return RID_ERROR_INVALID_MESSAGE_SIZE;
    }

    if (pack->message_count > RID_MESSAGE_PACK_MAX_MESSAGES) {
        return RID_ERROR_INVALID_MESSAGE_COUNT;
    }

    return RID_SUCCESS;
}

uint8_t rid_message_pack_get_message_count(const rid_message_pack_t *pack) {
    if (pack == NULL) {
        return 0;
    }
    return pack->message_count;
}

size_t rid_message_pack_get_size(const rid_message_pack_t *pack) {
    if (pack == NULL) {
        return 0;
    }
    return RID_MESSAGE_PACK_HEADER_SIZE + (pack->message_count * RID_MESSAGE_SIZE);
}

size_t rid_message_pack_get_messages_size(const rid_message_pack_t *pack) {
    if (pack == NULL) {
        return 0;
    }
    return pack->message_count * RID_MESSAGE_SIZE;
}

const void *rid_message_pack_get_messages(const rid_message_pack_t *pack) {
    if (pack == NULL) {
        return NULL;
    }
    return pack->messages;
}

int rid_message_pack_add_message(rid_message_pack_t *pack, const void *message) {
    if (pack == NULL || message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    rid_message_type_t type = rid_message_get_type(message);

    if (type == RID_MESSAGE_TYPE_AUTH) {
        return RID_ERROR_INVALID_MESSAGE_TYPE;
    }

    if (pack->message_count >= RID_MESSAGE_PACK_MAX_MESSAGES) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    size_t offset = pack->message_count * RID_MESSAGE_SIZE;
    memcpy(&pack->messages[offset], message, RID_MESSAGE_SIZE);
    ++pack->message_count;

    return RID_SUCCESS;
}

const void *rid_message_pack_get_message_at(const rid_message_pack_t *pack, uint8_t index) {
    if (pack == NULL || index >= pack->message_count) {
        return NULL;
    }

    size_t offset = index * RID_MESSAGE_SIZE;
    return &pack->messages[offset];
}

const void *rid_message_pack_get_message_by_type(const rid_message_pack_t *pack, rid_message_type_t type) {
    if (pack == NULL) {
        return NULL;
    }

    for (uint8_t i = 0; i < pack->message_count; ++i) {
        const void *message = rid_message_pack_get_message_at(pack, i);
        if (message != NULL && rid_message_get_type(message) == type) {
            return message;
        }
    }

    return NULL;
}

int rid_message_pack_get_auth(const rid_message_pack_t *pack, rid_auth_t *auth) {
    if (pack == NULL || auth == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    rid_auth_init(auth);

    uint8_t index = 0;

    for (uint8_t i = 0; i < pack->message_count; ++i) {
        const void *message = rid_message_pack_get_message_at(pack, i);

        if (rid_message_get_type(message) == RID_MESSAGE_TYPE_AUTH) {
            if (index == 0) {
                memcpy(&auth->page_0, message, RID_MESSAGE_SIZE);
            } else {
                memcpy(&auth->page_x[index - 1], message, RID_MESSAGE_SIZE);
            }
            ++index;
        }
    }

    if (index == 0) {
        return RID_ERROR_NOT_FOUND;
    }

    return RID_SUCCESS;
}

int rid_message_pack_set_auth(rid_message_pack_t *pack, const rid_auth_t *auth) {
    if (pack == NULL || auth == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    uint8_t i = pack->message_count;
    while (i > 0) {
        --i;
        const void *message = rid_message_pack_get_message_at(pack, i);
        if (rid_message_get_type(message) == RID_MESSAGE_TYPE_AUTH) {
            rid_message_pack_delete_message_at(pack, i);
        }
    }

    uint8_t page_count = rid_auth_get_page_count(auth);

    if (pack->message_count + page_count > RID_MESSAGE_PACK_MAX_MESSAGES) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    for (uint8_t i = 0; i < page_count; ++i) {
        size_t offset = pack->message_count * RID_MESSAGE_SIZE;
        if (i == 0) {
            memcpy(&pack->messages[offset], &auth->page_0, RID_MESSAGE_SIZE);
        } else {
            memcpy(&pack->messages[offset], &auth->page_x[i - 1], RID_MESSAGE_SIZE);
        }
        ++pack->message_count;
    }

    return RID_SUCCESS;
}

int rid_message_pack_delete_message_at(rid_message_pack_t *pack, uint8_t index) {
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

int rid_message_pack_replace_message_at(rid_message_pack_t *pack, uint8_t index, const void *message) {
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

int rid_message_pack_to_json(const rid_message_pack_t *pack, char *buffer, size_t buffer_size) {
    if (pack == NULL || buffer == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    int written = snprintf(
        buffer, buffer_size,
        "{\"protocol_version\": %u, \"message_type\": %u, "
        "\"message_count\": %u, \"messages\": [",
        rid_message_get_protocol_version(pack),
        rid_message_get_type(pack),
        rid_message_pack_get_message_count(pack)
    );

    if (written < 0) {
        return written;
    }

    size_t pos = (size_t)written;
    uint8_t count = rid_message_pack_get_message_count(pack);

    for (uint8_t i = 0; i < count; ++i) {
        const void *msg = rid_message_pack_get_message_at(pack, i);

        if (i > 0 && pos < buffer_size) {
            written = snprintf(buffer + pos, buffer_size - pos, ", ");
            if (written > 0) {
                pos += (size_t)written;
            }
        }

        if (pos >= buffer_size) {
            break;
        }

        int msg_written = rid_message_to_json(msg, buffer + pos, buffer_size - pos);
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
