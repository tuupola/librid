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

#ifndef RID_MESSAGE_H
#define RID_MESSAGE_H

/**
 * @file message.h
 * @brief Message header handling per ASTM F3411-22a.
 *
 * Example usage:
 * @snippet message/example_message.c full_example
 */

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum {
    RID_SUCCESS = 0,
    RID_ERROR_NULL_POINTER = -1,
    RID_ERROR_BUFFER_TOO_SMALL = -2,
    RID_ERROR_BUFFER_TOO_LARGE = -3,
    RID_ERROR_INVALID_CHARACTER = -4,
    RID_ERROR_OUT_OF_RANGE = -5,
    RID_ERROR_UNKNOWN_MESSAGE_TYPE = -6,
    RID_ERROR_INVALID_LATITUDE = -7,
    RID_ERROR_INVALID_LONGITUDE = -8,
    RID_ERROR_INVALID_TRACK_DIRECTION = -9,
    RID_ERROR_INVALID_TIMESTAMP = -10,
    RID_ERROR_INVALID_PROTOCOL_VERSION = -11,
    RID_ERROR_INVALID_MESSAGE_COUNT = -12,
    RID_ERROR_INVALID_MESSAGE_SIZE = -13,
    RID_ERROR_INVALID_LAST_PAGE_INDEX = -14,
    RID_ERROR_INVALID_PAGE_NUMBER = -15,
    RID_ERROR_NON_EMPTY_SIGNATURE = -16,
    RID_ERROR_INVALID_UUID_VERSION = -17,
    RID_ERROR_INVALID_UUID_VARIANT = -18,
    RID_ERROR_INVALID_UUID_PADDING = -19,
} rid_error_t;

/**
 * @brief Generic message structure for any Remote ID message.
 *
 * All messages are 25 bytes with a common header. Cast to specific
 * message type after checking message_type field.
 */
typedef struct
__attribute__((__packed__)) rid_message {
    uint8_t protocol_version: 4;
    uint8_t message_type: 4;
    uint8_t body[24];
} rid_message_t;

typedef enum rid_message_type {
    RID_MESSAGE_TYPE_BASIC_ID = 0x00,
    RID_MESSAGE_TYPE_LOCATION = 0x01,
    RID_MESSAGE_TYPE_AUTH = 0x02,
    RID_MESSAGE_TYPE_SELF_ID = 0x03,
    RID_MESSAGE_TYPE_SYSTEM = 0x04,
    RID_MESSAGE_TYPE_OPERATOR_ID = 0x05,
    RID_MESSAGE_TYPE_MESSAGE_PACK = 0x0F,
} rid_message_type_t;

typedef enum rid_protocol_version {
    RID_PROTOCOL_VERSION_0 = 0x00,
    RID_PROTOCOL_VERSION_1 = 0x01,
    RID_PROTOCOL_VERSION_2 = 0x02,
    RID_PROTOCOL_PRIVATE_USE = 0x0F,
} rid_protocol_version_t;

rid_message_type_t rid_message_get_type(const void *message);
rid_protocol_version_t rid_message_get_protocol_version(const void *message);

/**
 * @brief Convert message type to string representation.
 *
 * @param type The message type to convert.
 *
 * @return String representation of the message type.
 *         Returns "UNKNOWN" for invalid values.
 */
const char *rid_message_type_to_string(rid_message_type_t type);

/**
 * @brief Convert protocol version to string representation.
 *
 * @param version The protocol version to convert.
 *
 * @return String representation of the protocol version.
 *         Returns "UNKNOWN" for invalid values.
 */
const char *rid_protocol_version_to_string(rid_protocol_version_t version);

/**
 * @brief Convert error code to string representation.
 *
 * @param error The error code to convert.
 *
 * @return String representation of the error code.
 *         Returns "UNKNOWN" for invalid values.
 */
const char *rid_error_to_string(rid_error_t error);

/**
 * @brief Format any Remote ID message as a JSON string.
 *
 * Determines the message type and calls the appropriate type-specific
 * snprintf function.
 *
 * @param message Pointer to any Remote ID message structure.
 * @param buffer Buffer to store the JSON string.
 * @param buffer_size Size of the buffer.
 *
 * @return Number of characters written (excluding null terminator),
 *         or negative error code on failure.
 *
 * @retval RID_ERROR_NULL_POINTER if message or buffer is NULL.
 */
int rid_message_to_json(const void *message, char *buffer, size_t buffer_size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif