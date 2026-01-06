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

#ifndef _RID_MESSAGE_H
#define _RID_MESSAGE_H

/**
 * @file message.h
 * @brief Message header handling per ASTM F3411-22a.
 *
 * Example usage:
 * @snippet message/example_message.c full_example
 */

#include <stdint.h>

typedef enum {
    RID_SUCCESS = 0,
    RID_ERROR_NULL_POINTER = -1,
    RID_ERROR_BUFFER_TOO_SMALL = -2,
    RID_ERROR_BUFFER_TOO_LARGE = -3,
    RID_ERROR_INVALID_CHARACTER = -4,
    RID_ERROR_OUT_OF_RANGE = -5,
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

#endif