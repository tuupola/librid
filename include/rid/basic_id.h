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

#ifndef RID_BASIC_ID_H
#define RID_BASIC_ID_H

/**
 * @file basic_id.h
 * @brief Basic ID message handling per ASTM F3411-22a.
 *
 * Example usage:
 * @snippet basic_id/example_basic_id.c full_example
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Basic ID message structure per ASTM F3411-22a.
 */
typedef struct
__attribute__((__packed__)) rid_basic_id {
    uint8_t protocol_version: 4;
    uint8_t message_type : 4;
    uint8_t ua_type: 4;
    uint8_t id_type: 4;
    char uas_id[20];
    char reserved[3];
} rid_basic_id_t;

/**
 * @brief UAS ID type classification per ASTM F3411-22a.
 */
typedef enum rid_basic_id_type {
    RID_ID_TYPE_NONE = 0,
    RID_ID_TYPE_SERIAL_NUMBER = 1,
    RID_ID_TYPE_CAA_REGISTRATION_ID = 2,
    RID_ID_TYPE_UTM_ASSIGNED_UUID = 3,
    RID_ID_TYPE_SPECIFIC_SESSION_ID = 4,
    RID_ID_TYPE_MAX = 15,
    /* 5-15: unused */
} rid_basic_id_type_t;

/**
 * @brief Unmanned aircraft type classification per ASTM F3411-22a.
 */
typedef enum rid_ua_type {
    RID_UA_TYPE_NONE = 0,
    RID_UA_TYPE_AEROPLANE_OR_FIXED_WING = 1,
    RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR = 2,
    RID_UA_TYPE_GYROPLANE = 3,
    RID_UA_TYPE_HYBRID_LIFT = 4,
    RID_UA_TYPE_ORNITHOPTER = 5,
    RID_UA_TYPE_GLIDER = 6,
    RID_UA_TYPE_KITE = 7,
    RID_UA_TYPE_FREE_BALLOON = 8,
    RID_UA_TYPE_CAPTIVE_BALLOON = 9,
    RID_UA_TYPE_AIRSHIP = 10,
    RID_UA_TYPE_FREE_FALL_PARACHUTE = 11,
    RID_UA_TYPE_ROCKET = 12,
    RID_UA_TYPE_TETHERED_POWERED_AIRCRAFT = 13,
    RID_UA_TYPE_GROUND_OBSTACLE = 14,
    RID_UA_TYPE_OTHER = 15,
    RID_UA_TYPE_MAX = 15,
} rid_ua_type_t;

/**
 * @brief Initialize a Basic ID message structure.
 *
 * Sets protocol version to RID_PROTOCOL_VERSION_2 and message type to
 * RID_MESSAGE_TYPE_BASIC_ID. All other fields are zeroed.
 *
 * @param message Pointer to the Basic ID message structure to initialize.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 */
int rid_basic_id_init(rid_basic_id_t *message);

/**
 * @brief Set the ID type for a Basic ID message.
 *
 * @param message Pointer to the Basic ID message structure.
 * @param type The ID type to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if type exceeds RID_ID_TYPE_MAX.
 */
int rid_basic_id_set_type(rid_basic_id_t *message, rid_basic_id_type_t type);

/**
 * @brief Get the ID type from a Basic ID message.
 *
 * @param message Pointer to the Basic ID message structure.
 *
 * @return The ID type, or RID_ID_TYPE_NONE if message is NULL.
 */
rid_basic_id_type_t rid_basic_id_get_type(const rid_basic_id_t *message);

/**
 * @brief Set the UA (unmanned aircraft) type for a Basic ID message.
 *
 * @param message Pointer to the Basic ID message structure.
 * @param type The UA type to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if type exceeds RID_UA_TYPE_MAX.
 */
int rid_basic_id_set_ua_type(rid_basic_id_t *message, rid_ua_type_t type);

/**
 * @brief Get the UA (unmanned aircraft) type from a Basic ID message.
 *
 * @param message Pointer to the Basic ID message structure.
 *
 * @return The UA type, or RID_UA_TYPE_NONE if message is NULL.
 */
rid_ua_type_t rid_basic_id_get_ua_type(const rid_basic_id_t *message);

/**
 * @brief Set the UAS ID for a Basic ID message.
 *
 * The UAS ID is a null-terminated string up to 20 characters.
 *
 * @param message Pointer to the Basic ID message structure.
 * @param uas_id The UAS ID string to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message or uas_id is NULL.
 * @retval RID_ERROR_BUFFER_TOO_LARGE if uas_id exceeds 20 characters.
 */
int rid_basic_id_set_uas_id(rid_basic_id_t *message, const char *uas_id);

/**
 * @brief Get the UAS ID from a Basic ID message.
 *
 * Copies the UAS ID to the provided buffer as a null-terminated string.
 *
 * @param message Pointer to the Basic ID message structure.
 * @param buffer Buffer to store the UAS ID.
 * @param buffer_size Size of the buffer (must be at least 21 for full ID).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message or buffer is NULL.
 * @retval RID_ERROR_BUFFER_TOO_SMALL if buffer_size is insufficient.
 */
int rid_basic_id_get_uas_id(const rid_basic_id_t *message, char *buffer, size_t buffer_size);

/**
 * @brief Convert ID type to string representation.
 *
 * @param type The ID type to convert.
 *
 * @return String representation of the ID type (e.g., "RID_ID_TYPE_NONE").
 *         Returns "UNKNOWN" for invalid values.
 */
const char *rid_basic_id_type_to_string(rid_basic_id_type_t type);

/**
 * @brief Convert UA type to string representation.
 *
 * @param type The UA type to convert.
 *
 * @return String representation of the UA type (e.g., "RID_UA_TYPE_NONE").
 *         Returns "UNKNOWN" for invalid values.
 */
const char *rid_ua_type_to_string(rid_ua_type_t type);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif