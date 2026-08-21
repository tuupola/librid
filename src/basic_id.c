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

#include "rid/basic_id.h"
#include "rid/message.h"

#ifndef RID_DISABLE_JSON
#include <stdio.h>

#include "json.h"
#endif

int rid_basic_id_init(rid_basic_id_t *message) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    memset(message, 0, sizeof(rid_basic_id_t));

    message->protocol_version = RID_PROTOCOL_VERSION_2;
    message->message_type = RID_MESSAGE_TYPE_BASIC_ID;

    return RID_SUCCESS;
}

int rid_basic_id_validate(const rid_basic_id_t *message) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    /* Valid protocol versions: 0, 1, 2, or 0x0F (private use) */
    if (message->protocol_version > RID_PROTOCOL_VERSION_2 &&
        message->protocol_version != RID_PROTOCOL_PRIVATE_USE) {
        return RID_ERROR_INVALID_PROTOCOL_VERSION;
    }

    if (message->message_type != RID_MESSAGE_TYPE_BASIC_ID) {
        return RID_ERROR_UNKNOWN_MESSAGE_TYPE;
    }

    /* Validate Registration ID characters per ASTM F3411-22a Table 1 */
    if (message->id_type == RID_ID_TYPE_CAA_REGISTRATION_ID) {
        for (size_t i = 0; i < sizeof(message->uas_id); ++i) {
            char c = message->uas_id[i];
            if (c == '\0') {
                break;
            }
            int valid = (c >= 'A' && c <= 'Z') ||
                (c >= '0' && c <= '9') ||
                (c == '.');
            if (!valid) {
                return RID_ERROR_INVALID_CAA_REGISTRATION_ID;
            }
        }
    }

    /* Validate Serial Number characters per ANSI/CTA-2063 section 3.1.1 */
    if (message->id_type == RID_ID_TYPE_SERIAL_NUMBER) {
        for (size_t i = 0; i < sizeof(message->uas_id); ++i) {
            char c = message->uas_id[i];
            if (c == '\0') {
                break;
            }
            /* Valid: A-H, J-N, P-Z, 0-9 (excludes I and O) */
            int valid = (c >= 'A' && c <= 'H') ||
                (c >= 'J' && c <= 'N') ||
                (c >= 'P' && c <= 'Z') ||
                (c >= '0' && c <= '9');
            if (!valid) {
                return RID_ERROR_INVALID_SERIAL_NUMBER;
            }
        }
    }

    /* Validate UTM UUID format per RFC4122 */
    if (message->id_type == RID_ID_TYPE_UTM_ASSIGNED_UUID) {
        /* Check version field (byte 6, high nibble): valid 1-5 */
        uint8_t version = (message->uas_id[6] >> 4) & 0x0F;
        if (version < 1 || version > 5) {
            return RID_ERROR_INVALID_UUID_VERSION;
        }

        /* Check variant field (byte 8, high 2 bits): must be 0b10 */
        uint8_t variant = (message->uas_id[8] >> 6) & 0x03;
        if (variant != 0x02) {
            return RID_ERROR_INVALID_UUID_VARIANT;
        }

        /* Check padding bytes (16-19) are zero */
        for (size_t i = 16; i < RID_UAS_ID_SIZE; ++i) {
            if (message->uas_id[i] != 0) {
                return RID_ERROR_INVALID_UUID_PADDING;
            }
        }
    }

    return RID_SUCCESS;
}

int rid_basic_id_set_type(rid_basic_id_t *message, rid_basic_id_type_t type) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (type > RID_ID_TYPE_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    message->id_type = type;

    return RID_SUCCESS;
}

rid_basic_id_type_t rid_basic_id_get_type(const rid_basic_id_t *message) {
    if (message == NULL) {
        return RID_ID_TYPE_NONE;
    }
    return (rid_basic_id_type_t)message->id_type;
}

int rid_basic_id_set_ua_type(rid_basic_id_t *message, rid_ua_type_t type) {
    if (NULL == message) {
        return RID_ERROR_NULL_POINTER;
    }

    if (type > RID_UA_TYPE_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    message->ua_type = type;

    return RID_SUCCESS;
}

rid_ua_type_t rid_basic_id_get_ua_type(const rid_basic_id_t *message) {
    if (message == NULL) {
        return RID_UA_TYPE_NONE;
    }
    return (rid_ua_type_t)message->ua_type;
}

int rid_basic_id_set_uas_id(rid_basic_id_t *message, const char *uas_id) {
    if (message == NULL || uas_id == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    size_t len = strlen(uas_id);

    if (len > RID_UAS_ID_SIZE) {
        return RID_ERROR_BUFFER_TOO_LARGE;
    }

    memset(message->uas_id, 0, RID_UAS_ID_SIZE);
    memcpy(message->uas_id, uas_id, len);

    return RID_SUCCESS;
}

int rid_basic_id_get_uas_id(const rid_basic_id_t *message, char *buffer, size_t buffer_size) {
    if (message == NULL || buffer == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (buffer_size < RID_UAS_ID_SIZE + 1) {
        return RID_ERROR_BUFFER_TOO_SMALL;
    }

    memcpy(buffer, message->uas_id, RID_UAS_ID_SIZE);
    buffer[RID_UAS_ID_SIZE] = '\0';

    return RID_SUCCESS;
}

const char *rid_basic_id_type_to_string(rid_basic_id_type_t type) {
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

const char *rid_ua_type_to_string(rid_ua_type_t type) {
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

#ifndef RID_DISABLE_JSON
static void uuid_to_string(const unsigned char uuid[16], char *buffer, size_t buffer_size) {
    if (buffer_size < 37) {
        return;
    }

    /* clang-format off */
    snprintf(
        buffer, buffer_size,
        "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
        uuid[0], uuid[1], uuid[2],  uuid[3],
        uuid[4], uuid[5],
        uuid[6], uuid[7],
        uuid[8], uuid[9],
        uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]
    );
    /* clang-format on */
}

static size_t session_id_to_hex(const uint8_t *data, size_t data_size, char *hex, size_t hex_size) {
    size_t pos = 0;
    for (size_t i = 0; i < data_size && pos + 2 < hex_size; ++i) {
        int written = snprintf(hex + pos, hex_size - pos, "%02x", data[i]);
        if (written > 0) {
            pos += (size_t)written;
        }
    }
    return pos;
}

int rid_basic_id_to_json(const rid_basic_id_t *message, char *buffer, size_t buffer_size, size_t *needed_size) {
    rid_json_t json;
    char uas_id[RID_UAS_ID_SIZE * 2 + 1];

    if (message == NULL || (buffer == NULL && needed_size == NULL)) {
        return RID_ERROR_NULL_POINTER;
    }

    if (rid_basic_id_get_type(message) == RID_ID_TYPE_UTM_ASSIGNED_UUID) {
        char raw[RID_UAS_ID_SIZE + 1];
        rid_basic_id_get_uas_id(message, raw, sizeof(raw));
        uuid_to_string((const unsigned char *)raw, uas_id, sizeof(uas_id));
    } else if (rid_basic_id_get_type(message) == RID_ID_TYPE_SPECIFIC_SESSION_ID) {
        char raw[RID_UAS_ID_SIZE + 1];
        rid_basic_id_get_uas_id(message, raw, sizeof(raw));
        session_id_to_hex((const uint8_t *)raw, RID_UAS_ID_SIZE, uas_id, sizeof(uas_id));
    } else {
        rid_basic_id_get_uas_id(message, uas_id, sizeof(uas_id));
    }

    rid_json_start(&json, buffer, buffer_size);
    rid_json_key(&json, "protocol_version");
    rid_json_uint(&json, rid_message_get_protocol_version(message));
    rid_json_key(&json, "message_type");
    rid_json_uint(&json, rid_message_get_type(message));
    rid_json_key(&json, "id_type");
    rid_json_uint(&json, rid_basic_id_get_type(message));
    rid_json_key(&json, "ua_type");
    rid_json_uint(&json, rid_basic_id_get_ua_type(message));
    rid_json_key(&json, "uas_id");
    rid_json_string(&json, uas_id);
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
