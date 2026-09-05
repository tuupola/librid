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
#include <string.h>

#include "rid/message.h"
#include "rid/self_id.h"

#ifndef RID_DISABLE_JSON
#include "json.h"
#endif

int rid_self_id_init(rid_self_id_t *message) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    memset(message, 0, sizeof(rid_self_id_t));
    message->protocol_version = RID_PROTOCOL_VERSION_2;
    message->message_type = RID_MESSAGE_TYPE_SELF_ID;

    return RID_SUCCESS;
}

int rid_self_id_validate(const rid_self_id_t *message) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* Valid protocol versions: 0, 1, 2, or 0x0F (private use) */
    if (message->protocol_version > RID_PROTOCOL_VERSION_2 &&
        message->protocol_version != RID_PROTOCOL_PRIVATE_USE) {
        return RID_ERROR_INVALID_PROTOCOL_VERSION;
    }

    if (message->message_type != RID_MESSAGE_TYPE_SELF_ID) {
        return RID_ERROR_UNKNOWN_MESSAGE_TYPE;
    }

    /* Must be printable ASCII and NUL. */
    for (size_t i = 0; i < RID_DESCRIPTION_SIZE; ++i) {
        unsigned char c = (unsigned char)message->description[i];
        if (c != 0x00 && (c < 0x20 || c > 0x7E)) {
            return RID_ERROR_INVALID_CHARACTER;
        }
    }

    return RID_SUCCESS;
}

rid_description_type_t rid_self_id_get_description_type(const rid_self_id_t *message) {
    if (message == NULL) {
        return RID_DESCRIPTION_TYPE_TEXT;
    }
    return (rid_description_type_t)message->description_type;
}

int rid_self_id_set_description_type(rid_self_id_t *message, rid_description_type_t type) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if ((int)type < 0 || type > RID_DESCRIPTION_TYPE_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    message->description_type = type;

    return RID_SUCCESS;
}

int rid_self_id_get_description(const rid_self_id_t *message, char *buffer, size_t buffer_size) {
    if (message == NULL || buffer == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (buffer_size < RID_DESCRIPTION_SIZE + 1) {
        return RID_ERROR_BUFFER_TOO_SMALL;
    }

    memset(buffer, 0, RID_DESCRIPTION_SIZE + 1);
    memcpy(buffer, message->description, RID_DESCRIPTION_SIZE);

    return RID_SUCCESS;
}

int rid_self_id_set_description(rid_self_id_t *message, const char *description) {
    if (message == NULL || description == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    size_t size = strlen(description);

    if (size > RID_DESCRIPTION_SIZE) {
        return RID_ERROR_BUFFER_TOO_LARGE;
    }

    /* Must be printable ASCII */
    for (size_t i = 0; i < size; i++) {
        unsigned char c = (unsigned char)description[i];
        if (c < 0x20 || c > 0x7E) {
            return RID_ERROR_INVALID_CHARACTER;
        }
    }

    memset(message->description, 0, RID_DESCRIPTION_SIZE);
    memcpy(message->description, description, size);

    return RID_SUCCESS;
}

const char *rid_description_type_to_string(rid_description_type_t type) {
    switch (type) {
        case RID_DESCRIPTION_TYPE_TEXT:
            return "RID_DESCRIPTION_TYPE_TEXT";
        case RID_DESCRIPTION_TYPE_EMERGENCY:
            return "RID_DESCRIPTION_TYPE_EMERGENCY";
        case RID_DESCRIPTION_TYPE_EXTENDED_STATUS:
            return "RID_DESCRIPTION_TYPE_EXTENDED_STATUS";
        default:
            return "UNKNOWN";
    }
}

#ifndef RID_DISABLE_JSON
int rid_self_id_to_json(const rid_self_id_t *message, char *buffer, size_t buffer_size, size_t *needed_size) {
    rid_json_t json;
    char description[RID_DESCRIPTION_SIZE + 1];

    if (message == NULL || (buffer == NULL && needed_size == NULL)) {
        return RID_ERROR_NULL_POINTER;
    }

    rid_self_id_get_description(message, description, sizeof(description));

    rid_json_start(&json, buffer, buffer_size);
    rid_json_key(&json, "protocol_version");
    rid_json_uint(&json, rid_message_get_protocol_version(message));
    rid_json_key(&json, "message_type");
    rid_json_uint(&json, rid_message_get_type(message));
    rid_json_key(&json, "description_type");
    rid_json_uint(&json, rid_self_id_get_description_type(message));
    rid_json_key(&json, "description");
    rid_json_string(&json, description);
    rid_json_end(&json);

    if (needed_size != NULL) {
        *needed_size = json.position + 1;
    }

    if (buffer == NULL) {
        return RID_SUCCESS;
    }

    if (json.position + 1 > buffer_size) {
        return RID_ERROR_BUFFER_TOO_SMALL;
    }

    return RID_SUCCESS;
}
#endif /* RID_DISABLE_JSON */
