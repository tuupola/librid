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
#include "rid/basic_id.h"

int
rid_basic_id_init(rid_basic_id_t *message) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    memset(message, 0, sizeof(rid_basic_id_t));

    message->protocol_version = RID_PROTOCOL_VERSION_2;
    message->message_type = RID_MESSAGE_TYPE_BASIC_ID;

    return RID_SUCCESS;
}

int
rid_basic_id_set_type(rid_basic_id_t *message, rid_basic_id_type_t type) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (type > RID_ID_TYPE_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    message->id_type = type;

    return RID_SUCCESS;
}

rid_basic_id_type_t
rid_basic_id_get_type(const rid_basic_id_t *message) {
    if (message == NULL) {
        return RID_ID_TYPE_NONE;
    }
    return (rid_basic_id_type_t)message->id_type;
}

int
rid_basic_id_set_ua_type(rid_basic_id_t *message, rid_ua_type_t type) {
    if (NULL == message) {
        return RID_ERROR_NULL_POINTER;
    }

    if (type > RID_UA_TYPE_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    message->ua_type = type;

    return RID_SUCCESS;
}

rid_ua_type_t
rid_basic_id_get_ua_type(const rid_basic_id_t *message) {
    if (message == NULL) {
        return RID_UA_TYPE_NONE;
    }
    return (rid_ua_type_t)message->ua_type;
}

int
rid_basic_id_set_uas_id(rid_basic_id_t *message, const char *uas_id) {
    if (message == NULL || uas_id == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    size_t len = strlen(uas_id);

    if (len > 20) {
        return RID_ERROR_BUFFER_TOO_LARGE;
    }

    memset(message->uas_id, 0, 20);
    memcpy(message->uas_id, uas_id, len);

    return RID_SUCCESS;
}

int
rid_basic_id_get_uas_id(const rid_basic_id_t *message, char *buffer, size_t buffer_size) {
    if (message == NULL || buffer == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (buffer_size < 21) {
        return RID_ERROR_BUFFER_TOO_SMALL;
    }

    memcpy(buffer, message->uas_id, 20);
    buffer[20] = '\0';

    return RID_SUCCESS;
}

const char *
rid_basic_id_type_to_string(rid_basic_id_type_t type) {
    switch (type) {
        case RID_ID_TYPE_NONE:
            return "RID_ID_TYPE_NONE";
        case RID_ID_TYPE_SERIAL_NUMBER:
            return "RID_ID_TYPE_SERIAL_NUMBER";
        case RID_ID_TYPE_CAA_REGISTRATION_ID:
            return "RID_ID_TYPE_CAA_REGISTRATION_ID";
        case RID_ID_TYPE_UTM_ASSIGNED_UUID:
            return "RID_ID_TYPE_UTM_ASSIGNED_UUID";
        case RID_ID_TYPE_SPECIFIC_SESSION_ID:
            return "RID_ID_TYPE_SPECIFIC_SESSION_ID";
        default:
            return "UNKNOWN";
    }
}

const char *
rid_ua_type_to_string(rid_ua_type_t type) {
    switch (type) {
        case RID_UA_TYPE_NONE:
            return "RID_UA_TYPE_NONE";
        case RID_UA_TYPE_AEROPLANE_OR_FIXED_WING:
            return "RID_UA_TYPE_AEROPLANE_OR_FIXED_WING";
        case RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR:
            return "RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR";
        case RID_UA_TYPE_GYROPLANE:
            return "RID_UA_TYPE_GYROPLANE";
        case RID_UA_TYPE_HYBRID_LIFT:
            return "RID_UA_TYPE_HYBRID_LIFT";
        case RID_UA_TYPE_ORNITHOPTER:
            return "RID_UA_TYPE_ORNITHOPTER";
        case RID_UA_TYPE_GLIDER:
            return "RID_UA_TYPE_GLIDER";
        case RID_UA_TYPE_KITE:
            return "RID_UA_TYPE_KITE";
        case RID_UA_TYPE_FREE_BALLOON:
            return "RID_UA_TYPE_FREE_BALLOON";
        case RID_UA_TYPE_CAPTIVE_BALLOON:
            return "RID_UA_TYPE_CAPTIVE_BALLOON";
        case RID_UA_TYPE_AIRSHIP:
            return "RID_UA_TYPE_AIRSHIP";
        case RID_UA_TYPE_FREE_FALL_PARACHUTE:
            return "RID_UA_TYPE_FREE_FALL_PARACHUTE";
        case RID_UA_TYPE_ROCKET:
            return "RID_UA_TYPE_ROCKET";
        case RID_UA_TYPE_TETHERED_POWERED_AIRCRAFT:
            return "RID_UA_TYPE_TETHERED_POWERED_AIRCRAFT";
        case RID_UA_TYPE_GROUND_OBSTACLE:
            return "RID_UA_TYPE_GROUND_OBSTACLE";
        case RID_UA_TYPE_OTHER:
            return "RID_UA_TYPE_OTHER";
        default:
            return "UNKNOWN";
    }
}
