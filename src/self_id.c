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

#include "rid/message.h"
#include "rid/self_id.h"

int
rid_self_id_init(rid_self_id_t *message) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    memset(message, 0, sizeof(rid_self_id_t));
    message->protocol_version = RID_PROTOCOL_VERSION_2;
    message->message_type = RID_MESSAGE_TYPE_SELF_ID;

    return RID_SUCCESS;
}

rid_description_type_t
rid_self_id_get_description_type(const rid_self_id_t *message) {
    return (rid_description_type_t)message->description_type;
}

int
rid_self_id_set_description_type(rid_self_id_t *message, rid_description_type_t type) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    message->description_type = type;

    return RID_SUCCESS;
}

int
rid_self_id_get_description(const rid_self_id_t *message, char *buffer, size_t buffer_size) {
    if (message == NULL || buffer == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (buffer_size < 24) {
        return RID_ERROR_BUFFER_TOO_SMALL;
    }

    memcpy(buffer, message->description, 23);
    buffer[23] = '\0';

    return RID_SUCCESS;
}

int
rid_self_id_set_description(rid_self_id_t *message, const char *description) {
    if (message == NULL || description == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    size_t size = strlen(description);

    if (size > 23) {
        return RID_ERROR_BUFFER_TOO_LARGE;
    }

    /* Must be ASCII only */
    for (size_t i = 0; i < size; i++) {
        if ((unsigned char)description[i] > 127) {
            return RID_ERROR_INVALID_CHARACTER;
        }
    }

    memset(message->description, 0, 23);
    memcpy(message->description, description, size);

    return RID_SUCCESS;
}
