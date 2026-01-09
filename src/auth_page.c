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
#include "rid/auth_page.h"

int
rid_auth_page_0_init(rid_auth_page_0_t *message) {
    if (NULL == message) {
        return RID_ERROR_NULL_POINTER;
    }

    memset(message, 0, sizeof(rid_auth_page_0_t));

    message->protocol_version = RID_PROTOCOL_VERSION_2;
    message->message_type = RID_MESSAGE_TYPE_AUTH;
    message->page_number = 0;

    return RID_SUCCESS;
}

int
rid_auth_page_x_init(rid_auth_page_x_t *message, uint8_t page_number) {
    if (NULL == message) {
        return RID_ERROR_NULL_POINTER;
    }

    if (0 == page_number || page_number > RID_AUTH_MAX_PAGE_INDEX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    memset(message, 0, sizeof(rid_auth_page_x_t));

    message->protocol_version = RID_PROTOCOL_VERSION_2;
    message->message_type = RID_MESSAGE_TYPE_AUTH;
    message->page_number = page_number;

    return RID_SUCCESS;
}

int
rid_auth_page_0_set_type(rid_auth_page_0_t *message, rid_auth_type_t type) {
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
rid_auth_page_0_get_type(const rid_auth_page_0_t *message) {
    if (NULL == message) {
        return RID_AUTH_TYPE_NONE;
    }

    return (rid_auth_type_t)message->auth_type;
}

int
rid_auth_page_0_set_last_page_index(rid_auth_page_0_t *message, uint8_t index) {
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
rid_auth_page_0_get_last_page_index(const rid_auth_page_0_t *message) {
    if (NULL == message) {
        return 0;
    }

    /* Mask reserved bits [7..4] per ASTM F3411-22a Table 8 */
    return message->last_page_index & 0x0F;
}

int
rid_auth_page_0_set_length(rid_auth_page_0_t *message, uint8_t length) {
    if (NULL == message) {
        return RID_ERROR_NULL_POINTER;
    }

    message->length = length;

    return RID_SUCCESS;
}

uint8_t
rid_auth_page_0_get_length(const rid_auth_page_0_t *message) {
    if (NULL == message) {
        return 0;
    }

    return message->length;
}

int
rid_auth_page_0_set_timestamp(rid_auth_page_0_t *message, uint32_t timestamp) {
    if (NULL == message) {
        return RID_ERROR_NULL_POINTER;
    }

    message->timestamp = timestamp;

    return RID_SUCCESS;
}

uint32_t
rid_auth_page_0_get_timestamp(const rid_auth_page_0_t *message) {
    if (NULL == message) {
        return 0;
    }

    return message->timestamp;
}

int
rid_auth_page_0_set_data(rid_auth_page_0_t *message, const uint8_t *data, size_t size) {
    if (NULL == message || NULL == data) {
        return RID_ERROR_NULL_POINTER;
    }

    if (size > RID_AUTH_PAGE_0_DATA_SIZE) {
        return RID_ERROR_BUFFER_TOO_LARGE;
    }

    memset(message->auth_data, 0, RID_AUTH_PAGE_0_DATA_SIZE);
    memcpy(message->auth_data, data, size);

    return RID_SUCCESS;
}

int
rid_auth_page_0_get_data(const rid_auth_page_0_t *message, uint8_t *buffer, size_t buffer_size) {
    if (NULL == message || NULL == buffer) {
        return RID_ERROR_NULL_POINTER;
    }

    if (buffer_size < RID_AUTH_PAGE_0_DATA_SIZE) {
        return RID_ERROR_BUFFER_TOO_SMALL;
    }

    memcpy(buffer, message->auth_data, RID_AUTH_PAGE_0_DATA_SIZE);

    return RID_SUCCESS;
}

int
rid_auth_page_x_set_type(rid_auth_page_x_t *message, rid_auth_type_t type) {
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
rid_auth_page_x_get_type(const rid_auth_page_x_t *message) {
    if (NULL == message) {
        return RID_AUTH_TYPE_NONE;
    }

    return (rid_auth_type_t)message->auth_type;
}

int
rid_auth_page_x_set_number(rid_auth_page_x_t *message, uint8_t page_number) {
    if (NULL == message) {
        return RID_ERROR_NULL_POINTER;
    }

    if (0 == page_number || page_number > RID_AUTH_MAX_PAGE_INDEX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    message->page_number = page_number;

    return RID_SUCCESS;
}

uint8_t
rid_auth_page_x_get_number(const rid_auth_page_x_t *message) {
    if (NULL == message) {
        return 0;
    }

    return message->page_number;
}

int
rid_auth_page_x_set_data(rid_auth_page_x_t *message, const uint8_t *data, size_t size) {
    if (NULL == message || NULL == data) {
        return RID_ERROR_NULL_POINTER;
    }

    if (size > RID_AUTH_PAGE_DATA_SIZE) {
        return RID_ERROR_BUFFER_TOO_LARGE;
    }

    memset(message->auth_data, 0, RID_AUTH_PAGE_DATA_SIZE);
    memcpy(message->auth_data, data, size);

    return RID_SUCCESS;
}

int
rid_auth_page_x_get_data(const rid_auth_page_x_t *message, uint8_t *buffer, size_t buffer_size) {
    if (NULL == message || NULL == buffer) {
        return RID_ERROR_NULL_POINTER;
    }

    if (buffer_size < RID_AUTH_PAGE_DATA_SIZE) {
        return RID_ERROR_BUFFER_TOO_SMALL;
    }

    memcpy(buffer, message->auth_data, RID_AUTH_PAGE_DATA_SIZE);

    return RID_SUCCESS;
}

const char *
rid_auth_type_to_string(rid_auth_type_t type) {
    switch (type) {
        case RID_AUTH_TYPE_NONE:
            return "RID_AUTH_TYPE_NONE";
        case RID_AUTH_TYPE_UAS_ID_SIGNATURE:
            return "RID_AUTH_TYPE_UAS_ID_SIGNATURE";
        case RID_AUTH_TYPE_OPERATOR_ID_SIGNATURE:
            return "RID_AUTH_TYPE_OPERATOR_ID_SIGNATURE";
        case RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE:
            return "RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE";
        case RID_AUTH_TYPE_NETWORK_REMOTE_ID:
            return "RID_AUTH_TYPE_NETWORK_REMOTE_ID";
        case RID_AUTH_TYPE_SPECIFIC_METHOD:
            return "RID_AUTH_TYPE_SPECIFIC_METHOD";
        default:
            return "UNKNOWN";
    }
}

static size_t
auth_data_to_hex(const uint8_t *data, size_t data_size, char *hex, size_t hex_size) {
    size_t pos = 0;
    for (size_t i = 0; i < data_size && pos + 2 < hex_size; ++i) {
        int written = snprintf(hex + pos, hex_size - pos, "%02x", data[i]);
        if (written > 0) {
            pos += (size_t)written;
        }
    }
    return pos;
}

int
rid_auth_page_to_json(const void *message, char *buffer, size_t buffer_size) {
    if (NULL == message || NULL == buffer) {
        return RID_ERROR_NULL_POINTER;
    }

    const rid_auth_page_0_t *page = (const rid_auth_page_0_t *)message;
    uint8_t page_number = page->page_number;

    if (0 == page_number) {
        const rid_auth_page_0_t *page_0 = (const rid_auth_page_0_t *)message;

        char auth_hex[RID_AUTH_PAGE_0_DATA_SIZE * 2 + 1];
        auth_data_to_hex(page_0->auth_data, RID_AUTH_PAGE_0_DATA_SIZE,
                         auth_hex, sizeof(auth_hex));

        return snprintf(
            buffer,
            buffer_size,
            "{\"protocol_version\": %u, \"message_type\": %u, "
            "\"page_number\": %u, \"auth_type\": %u, "
            "\"last_page_index\": %u, \"length\": %u, "
            "\"timestamp\": %lu, \"auth_data\": \"%s\"}",
            rid_message_get_protocol_version(page_0),
            rid_message_get_type(page_0),
            page_0->page_number,
            rid_auth_page_0_get_type(page_0),
            rid_auth_page_0_get_last_page_index(page_0),
            rid_auth_page_0_get_length(page_0),
            (unsigned long)rid_auth_page_0_get_timestamp(page_0),
            auth_hex
        );
    } else {
        const rid_auth_page_x_t *page_x = (const rid_auth_page_x_t *)message;

        char auth_hex[RID_AUTH_PAGE_DATA_SIZE * 2 + 1];
        auth_data_to_hex(page_x->auth_data, RID_AUTH_PAGE_DATA_SIZE,
                         auth_hex, sizeof(auth_hex));

        return snprintf(
            buffer,
            buffer_size,
            "{\"protocol_version\": %u, \"message_type\": %u, "
            "\"page_number\": %u, \"auth_type\": %u, "
            "\"auth_data\": \"%s\"}",
            rid_message_get_protocol_version(page_x),
            rid_message_get_type(page_x),
            rid_auth_page_x_get_number(page_x),
            rid_auth_page_x_get_type(page_x),
            auth_hex
        );
    }
}
