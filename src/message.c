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

#include <stdint.h>

#include "rid/message.h"

rid_message_type_t
rid_message_get_type(const void *message) {
    rid_message_t *msg = (rid_message_t *)message;
    return (rid_message_type_t)msg->message_type;
}

rid_protocol_version_t
rid_message_get_protocol_version(const void *message) {
    rid_message_t *msg = (rid_message_t *)message;
    return msg->protocol_version;
}

const char *
rid_message_type_to_string(rid_message_type_t type) {
    switch (type) {
        case RID_MESSAGE_TYPE_BASIC_ID:
            return "RID_MESSAGE_TYPE_BASIC_ID";
        case RID_MESSAGE_TYPE_LOCATION:
            return "RID_MESSAGE_TYPE_LOCATION";
        case RID_MESSAGE_TYPE_AUTH:
            return "RID_MESSAGE_TYPE_AUTH";
        case RID_MESSAGE_TYPE_SELF_ID:
            return "RID_MESSAGE_TYPE_SELF_ID";
        case RID_MESSAGE_TYPE_SYSTEM:
            return "RID_MESSAGE_TYPE_SYSTEM";
        case RID_MESSAGE_TYPE_OPERATOR_ID:
            return "RID_MESSAGE_TYPE_OPERATOR_ID";
        case RID_MESSAGE_TYPE_MESSAGE_PACK:
            return "RID_MESSAGE_TYPE_MESSAGE_PACK";
        default:
            return "UNKNOWN";
    }
}

const char *
rid_protocol_version_to_string(rid_protocol_version_t version) {
    switch (version) {
        case RID_PROTOCOL_VERSION_0:
            return "RID_PROTOCOL_VERSION_0";
        case RID_PROTOCOL_VERSION_1:
            return "RID_PROTOCOL_VERSION_1";
        case RID_PROTOCOL_VERSION_2:
            return "RID_PROTOCOL_VERSION_2";
        case RID_PROTOCOL_PRIVATE_USE:
            return "RID_PROTOCOL_PRIVATE_USE";
        default:
            return "UNKNOWN";
    }
}

const char *
rid_error_to_string(rid_error_t error) {
    switch (error) {
        case RID_SUCCESS:
            return "RID_SUCCESS";
        case RID_ERROR_NULL_POINTER:
            return "RID_ERROR_NULL_POINTER";
        case RID_ERROR_BUFFER_TOO_SMALL:
            return "RID_ERROR_BUFFER_TOO_SMALL";
        case RID_ERROR_BUFFER_TOO_LARGE:
            return "RID_ERROR_BUFFER_TOO_LARGE";
        case RID_ERROR_INVALID_CHARACTER:
            return "RID_ERROR_INVALID_CHARACTER";
        case RID_ERROR_OUT_OF_RANGE:
            return "RID_ERROR_OUT_OF_RANGE";
        case RID_ERROR_WRONG_MESSAGE_TYPE:
            return "RID_ERROR_WRONG_MESSAGE_TYPE";
        case RID_ERROR_INVALID_LATITUDE:
            return "RID_ERROR_INVALID_LATITUDE";
        case RID_ERROR_INVALID_LONGITUDE:
            return "RID_ERROR_INVALID_LONGITUDE";
        case RID_ERROR_INVALID_TRACK_DIRECTION:
            return "RID_ERROR_INVALID_TRACK_DIRECTION";
        case RID_ERROR_INVALID_TIMESTAMP:
            return "RID_ERROR_INVALID_TIMESTAMP";
        case RID_ERROR_INVALID_PROTOCOL_VERSION:
            return "RID_ERROR_INVALID_PROTOCOL_VERSION";
        case RID_ERROR_INVALID_MESSAGE_COUNT:
            return "RID_ERROR_INVALID_MESSAGE_COUNT";
        case RID_ERROR_INVALID_MESSAGE_SIZE:
            return "RID_ERROR_INVALID_MESSAGE_SIZE";
        default:
            return "UNKNOWN";
    }
}
