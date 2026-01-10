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
#include "rid/auth.h"

int
rid_auth_init(rid_auth_t *auth) {
    if (NULL == auth) {
        return RID_ERROR_NULL_POINTER;
    }

    memset(auth, 0, sizeof(rid_auth_t));
    rid_auth_page_0_init(&auth->page_0);

    return RID_SUCCESS;
}

int
rid_auth_validate(const rid_auth_t *auth) {
    if (auth == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* Valid protocol versions: 0, 1, 2, or 0x0F (private use) */
    if (auth->page_0.protocol_version > RID_PROTOCOL_VERSION_2 &&
        auth->page_0.protocol_version != RID_PROTOCOL_PRIVATE_USE) {
        return RID_ERROR_INVALID_PROTOCOL_VERSION;
    }

    if (auth->page_0.message_type != RID_MESSAGE_TYPE_AUTH) {
        return RID_ERROR_UNKNOWN_MESSAGE_TYPE;
    }

    if (auth->page_0.page_number != 0) {
        return RID_ERROR_INVALID_PAGE_NUMBER;
    }

    if (auth->page_0.last_page_index > RID_AUTH_MAX_PAGE_INDEX) {
        return RID_ERROR_INVALID_LAST_PAGE_INDEX;
    }

    /* BMG0180: Network Remote ID requires an empty signature */
    if (auth->page_0.auth_type == RID_AUTH_TYPE_NETWORK_REMOTE_ID) {
        if (auth->page_0.length != 0) {
            return RID_ERROR_NON_EMPTY_SIGNATURE;
        }
    }

    return RID_SUCCESS;
}

uint8_t
rid_auth_get_page_count(const rid_auth_t *auth) {
    if (NULL == auth) {
        return 0;
    }

    return rid_auth_page_0_get_last_page_index(&auth->page_0) + 1;
}

int
rid_auth_set_type(rid_auth_t *auth, rid_auth_type_t type) {
    if (NULL == auth) {
        return RID_ERROR_NULL_POINTER;
    }

    /* BMG0180: Network Remote ID requires an empty signature */
    if (RID_AUTH_TYPE_NETWORK_REMOTE_ID == type) {
        memset(auth->page_0.auth_data, 0, RID_AUTH_PAGE_0_DATA_SIZE);
        auth->page_0.last_page_index = 0;
        auth->page_0.length = 0;
        memset(auth->page_x, 0, sizeof(auth->page_x));
    }

    return rid_auth_page_0_set_type(&auth->page_0, type);
}

rid_auth_type_t
rid_auth_get_type(const rid_auth_t *auth) {
    if (NULL == auth) {
        return RID_AUTH_TYPE_NONE;
    }

    return rid_auth_page_0_get_type(&auth->page_0);
}

int
rid_auth_set_timestamp(rid_auth_t *auth, uint32_t timestamp) {
    if (NULL == auth) {
        return RID_ERROR_NULL_POINTER;
    }

    return rid_auth_page_0_set_timestamp(&auth->page_0, timestamp);
}

uint32_t
rid_auth_get_timestamp(const rid_auth_t *auth) {
    if (NULL == auth) {
        return 0;
    }

    return rid_auth_page_0_get_timestamp(&auth->page_0);
}

int
rid_auth_set_unixtime(rid_auth_t *auth, uint32_t unixtime) {
    if (NULL == auth) {
        return RID_ERROR_NULL_POINTER;
    }

    if (unixtime < RID_AUTH_EPOCH_OFFSET) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    return rid_auth_page_0_set_timestamp(&auth->page_0, unixtime - RID_AUTH_EPOCH_OFFSET);
}

uint32_t
rid_auth_get_unixtime(const rid_auth_t *auth) {
    if (NULL == auth) {
        return 0;
    }

    return rid_auth_page_0_get_timestamp(&auth->page_0) + RID_AUTH_EPOCH_OFFSET;
}

int
rid_auth_set_signature(rid_auth_t *auth, const uint8_t *signature, size_t size) {
    if (NULL == auth || NULL == signature) {
        return RID_ERROR_NULL_POINTER;
    }

    if (size > 255) {
        return RID_ERROR_BUFFER_TOO_LARGE;
    }

    /* Calculate last page index */
    uint8_t last_page_index = 0;
    if (size > RID_AUTH_PAGE_0_DATA_SIZE) {
        size_t remaining = size - RID_AUTH_PAGE_0_DATA_SIZE;
        last_page_index = (remaining + RID_AUTH_PAGE_DATA_SIZE - 1) / RID_AUTH_PAGE_DATA_SIZE;
    }

    /* Set page 0 metadata */
    rid_auth_page_0_set_last_page_index(&auth->page_0, last_page_index);
    rid_auth_page_0_set_length(&auth->page_0, (uint8_t)size);

    /* Copy data to page 0 */
    size_t page_0_bytes = (size < RID_AUTH_PAGE_0_DATA_SIZE) ? size : RID_AUTH_PAGE_0_DATA_SIZE;
    rid_auth_page_0_set_data(&auth->page_0, signature, page_0_bytes);

    /* Copy remaining data to page_x entries */
    const uint8_t *remaining_data = signature + page_0_bytes;
    size_t remaining_size = size - page_0_bytes;

    for (uint8_t i = 0; i < last_page_index; ++i) {
        rid_auth_page_x_init(&auth->page_x[i], i + 1);
        rid_auth_page_x_set_type(&auth->page_x[i], auth->page_0.auth_type);

        size_t page_bytes = (remaining_size < RID_AUTH_PAGE_DATA_SIZE)
            ? remaining_size : RID_AUTH_PAGE_DATA_SIZE;
        rid_auth_page_x_set_data(&auth->page_x[i], remaining_data, page_bytes);

        remaining_data += page_bytes;
        remaining_size -= page_bytes;
    }

    return RID_SUCCESS;
}

uint8_t
rid_auth_get_length(const rid_auth_t *auth) {
    if (NULL == auth) {
        return 0;
    }

    return rid_auth_page_0_get_length(&auth->page_0);
}

int
rid_auth_get_signature(const rid_auth_t *auth, uint8_t *buffer, size_t buffer_size) {
    if (NULL == auth || NULL == buffer) {
        return RID_ERROR_NULL_POINTER;
    }

    uint8_t length = rid_auth_page_0_get_length(&auth->page_0);
    if (buffer_size < length) {
        return RID_ERROR_BUFFER_TOO_SMALL;
    }

    /* Copy data from page 0 */
    size_t page_0_bytes = (length < RID_AUTH_PAGE_0_DATA_SIZE) ? length : RID_AUTH_PAGE_0_DATA_SIZE;
    memcpy(buffer, auth->page_0.auth_data, page_0_bytes);

    /* Copy data from page_x entries */
    uint8_t *remaining_buffer = buffer + page_0_bytes;
    size_t remaining_size = length - page_0_bytes;
    uint8_t last_page_index = rid_auth_page_0_get_last_page_index(&auth->page_0);

    for (uint8_t i = 0; i < last_page_index && remaining_size > 0; ++i) {
        size_t page_bytes = (remaining_size < RID_AUTH_PAGE_DATA_SIZE)
            ? remaining_size : RID_AUTH_PAGE_DATA_SIZE;
        memcpy(remaining_buffer, auth->page_x[i].auth_data, page_bytes);

        remaining_buffer += page_bytes;
        remaining_size -= page_bytes;
    }

    return RID_SUCCESS;
}

int
rid_auth_to_json(const rid_auth_t *auth, char *buffer, size_t buffer_size) {
    if (auth == NULL || buffer == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    uint8_t sig_length = rid_auth_get_length(auth);
    uint8_t signature[255];
    rid_auth_get_signature(auth, signature, sizeof(signature));

    /* Convert signature to hex string */
    char sig_hex[512];
    size_t hex_pos = 0;
    for (uint8_t i = 0; i < sig_length && hex_pos < sizeof(sig_hex) - 2; ++i) {
        hex_pos += snprintf(sig_hex + hex_pos, sizeof(sig_hex) - hex_pos, "%02x", signature[i]);
    }
    sig_hex[hex_pos] = '\0';

    return snprintf(
            buffer,
            buffer_size,
            "{\"protocol_version\": %u, \"message_type\": %u, "
            "\"type\": %u, \"page_count\": %u, \"timestamp\": %lu, "
            "\"length\": %u, \"signature\": \"%s\"}",
            rid_message_get_protocol_version(&auth->page_0),
            rid_message_get_type(&auth->page_0),
            rid_auth_get_type(auth),
            rid_auth_get_page_count(auth),
            (unsigned long)rid_auth_get_timestamp(auth),
            sig_length,
            sig_hex
        );
}
