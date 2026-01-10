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
#include "rid/operator_id.h"

int
rid_operator_id_init(rid_operator_id_t *message) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    memset(message, 0, sizeof(rid_operator_id_t));
    message->protocol_version = RID_PROTOCOL_VERSION_2;
    message->message_type = RID_MESSAGE_TYPE_OPERATOR_ID;

    return RID_SUCCESS;
}

int
rid_operator_id_validate(const rid_operator_id_t *message) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* Valid protocol versions: 0, 1, 2, or 0x0F (private use) */
    if (message->protocol_version > RID_PROTOCOL_VERSION_2 &&
        message->protocol_version != RID_PROTOCOL_PRIVATE_USE) {
        return RID_ERROR_INVALID_PROTOCOL_VERSION;
    }

    if (message->message_type != RID_MESSAGE_TYPE_OPERATOR_ID) {
        return RID_ERROR_UNKNOWN_MESSAGE_TYPE;
    }

    /* Operator ID must be ASCII only */
    for (size_t i = 0; i < 20; ++i) {
        if ((unsigned char)message->operator_id[i] > 127) {
            return RID_ERROR_INVALID_CHARACTER;
        }
    }

    return RID_SUCCESS;
}

rid_operator_id_type_t
rid_operator_id_get_type(const rid_operator_id_t *message) {
    return (rid_operator_id_type_t)message->id_type;
}

int
rid_operator_id_set_type(rid_operator_id_t *message, rid_operator_id_type_t type) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    message->id_type = type;

    return RID_SUCCESS;
}

int
rid_operator_id_get(const rid_operator_id_t *message, char *buffer, size_t buffer_size) {
    if (message == NULL || buffer == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (buffer_size < 21) {
        return RID_ERROR_BUFFER_TOO_SMALL;
    }

    memcpy(buffer, message->operator_id, 20);
    buffer[20] = '\0';

    return RID_SUCCESS;
}

int
rid_operator_id_set(rid_operator_id_t *message, const char *operator_id) {
    if (message == NULL || operator_id == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    size_t size = strlen(operator_id);

    if (size > 20) {
        return RID_ERROR_BUFFER_TOO_LARGE;
    }

    /* Must be ASCII only */
    for (size_t i = 0; i < size; i++) {
        if ((unsigned char)operator_id[i] > 127) {
            return RID_ERROR_INVALID_CHARACTER;
        }
    }

    memset(message->operator_id, 0, 20);
    memcpy(message->operator_id, operator_id, size);

    return RID_SUCCESS;
}

const char *
rid_operator_id_type_to_string(rid_operator_id_type_t type) {
    switch (type) {
        case RID_ID_TYPE_OPERATOR_ID:
            return "RID_ID_TYPE_OPERATOR_ID";
        default:
            return "UNKNOWN";
    }
}

int
rid_operator_id_to_json(const rid_operator_id_t *message, char *buffer, size_t buffer_size) {
    if (message == NULL || buffer == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    char operator_id[21];
    rid_operator_id_get(message, operator_id, sizeof(operator_id));

    return snprintf(
            buffer,
            buffer_size,
            "{\"protocol_version\": %u, \"message_type\": %u, "
            "\"id_type\": %u, \"operator_id\": \"%s\"}",
            rid_message_get_protocol_version(message),
            rid_message_get_type(message),
            rid_operator_id_get_type(message),
            operator_id
        );
}
