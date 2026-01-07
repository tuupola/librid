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

#ifndef RID_OPERATOR_ID_H
#define RID_OPERATOR_ID_H

/**
 * @file operator_id.h
 * @brief Operator ID message handling per ASTM F3411-22a.
 *
 * Example usage:
 * @snippet operator_id/example_operator_id.c full_example
 */

#include <stdint.h>
#include <stddef.h>

#include "rid/message.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Operator ID message structure per ASTM F3411-22a.
 */
typedef struct
__attribute__((__packed__)) rid_operator_id {
    uint8_t protocol_version: 4;
    uint8_t message_type : 4;
    uint8_t id_type;
    char operator_id[20];
    char reserved[3];
} rid_operator_id_t;

/**
 * @brief Operator ID type classification per ASTM F3411-22a.
 */
typedef enum rid_operator_id_type {
    RID_ID_TYPE_OPERATOR_ID = 0,
    /* 1-200: Reserved */
    /* 201-255: Private use*/
} rid_operator_id_type_t;

/**
 * @brief Initialize an Operator ID message with default values.
 *
 * Sets protocol version to 2 and message type to OPERATOR_ID.
 * All other fields are set to zero.
 *
 * @param message Pointer to the Operator ID message structure.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 */
int rid_operator_id_init(rid_operator_id_t *message);

/**
 * @brief Validate an Operator ID message structure.
 *
 * Checks that all fields contain valid encoded values according to
 * ASTM F3411-22a.
 *
 * @param message Pointer to the Operator ID message structure to validate.
 *
 * @retval RID_SUCCESS if all fields are valid.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 * @retval RID_ERROR_INVALID_PROTOCOL_VERSION if protocol version is invalid.
 * @retval RID_ERROR_WRONG_MESSAGE_TYPE if message type is not OPERATOR_ID.
 */
int rid_operator_id_validate(const rid_operator_id_t *message);

/**
 * @brief Get the ID type from an Operator ID message.
 *
 * @param message Pointer to the Operator ID message structure.
 *
 * @return The ID type.
 */
rid_operator_id_type_t rid_operator_id_get_type(const rid_operator_id_t *message);

/**
 * @brief Set the ID type for an Operator ID message.
 *
 * @param message Pointer to the Operator ID message structure.
 * @param type The ID type to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 */
int rid_operator_id_set_type(rid_operator_id_t *message, rid_operator_id_type_t type);

/**
 * @brief Get the Operator ID from an Operator ID message.
 *
 * Copies the Operator ID to the provided buffer as a null-terminated string.
 *
 * @param message Pointer to the Operator ID message structure.
 * @param buffer Buffer to store the Operator ID.
 * @param buffer_size Size of the buffer (must be at least 21 for full ID).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message or buffer is NULL.
 * @retval RID_ERROR_BUFFER_TOO_SMALL if buffer_size is insufficient.
 */
int rid_operator_id_get(const rid_operator_id_t *message, char *buffer, size_t buffer_size);

/**
 * @brief Set the Operator ID for an Operator ID message.
 *
 * The Operator ID is a null-terminated string up to 20 characters.
 *
 * @param message Pointer to the Operator ID message structure.
 * @param uas_id The Operator ID string to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message or uas_id is NULL.
 * @retval RID_ERROR_BUFFER_TOO_LARGE if uas_id exceeds 20 characters.
 */
int rid_operator_id_set(rid_operator_id_t *message, const char *uas_id);

/**
 * @brief Convert operator ID type to string representation.
 *
 * @param type The operator ID type to convert.
 *
 * @return String representation of the operator ID type.
 *         Returns "UNKNOWN" for invalid values.
 */
const char *rid_operator_id_type_to_string(rid_operator_id_type_t type);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
