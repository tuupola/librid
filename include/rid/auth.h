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

#ifndef RID_AUTH_H
#define RID_AUTH_H

/**
 * @file auth.h
 * @brief High-level authentication data API per ASTM F3411-22a.
 *
 * Provides a container struct and functions for managing multi-page
 * authentication data.
 *
 * Example usage:
 * @snippet auth/example_sign.c full_example
 */

#include <stddef.h>
#include <stdint.h>

#include "rid/auth_page.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Container for multi-page authentication data.
 *
 * Holds page 0 and up to 15 additional pages.
 */
typedef struct rid_auth {
    rid_auth_page_0_t page_0;
    rid_auth_page_x_t page_x[15];
} rid_auth_t;

/**
 * @brief Callback function type for verifying authentication signatures.
 *
 * Called by rid_auth_verify() to perform the actual verification of
 * the signed payload.
 *
 * @param context Opaque context passed to the callback.
 * @param input Pointer to the signed payload data.
 * @param input_length Length of the signed payload in bytes.
 * @param signature Pointer to the signature data to verify against.
 * @param signature_length Length of the signature in bytes.
 *
 * @retval 0 on success.
 * @retval Non-zero on verification failure.
 */
typedef int (*rid_auth_verify_cb_t)(
    void *context,
    const uint8_t *input,
    size_t input_length,
    const uint8_t *signature,
    size_t signature_length
);

/**
 * @brief Callback function type for producing authentication signatures.
 *
 * Called by rid_auth_sign() to perform the actual signing of the payload.
 *
 * @param context Opaque context passed to the callback.
 * @param input Pointer to the payload to sign.
 * @param input_length Length of the payload in bytes.
 * @param signature Output buffer for the signature.
 * @param signature_size Size of the signature buffer in bytes.
 * @param signature_length Output: actual signature length written.
 *
 * @retval 0 on success.
 * @retval Non-zero on signing failure.
 */
typedef int (*rid_auth_sign_cb_t)(
    void *context,
    const uint8_t *input,
    size_t input_length,
    uint8_t *signature,
    size_t signature_size,
    size_t *signature_length
);

/**
 * @brief Verify an authentication signature using a caller supplied callback.
 *
 * Validates the auth container and the input message. Constructs the signed
 * payload internally, extracts the signature and then invokes the verify
 * callback with the payload and signature.
 *
 * Only `rid_message_pack_t` is currently supported.
 *
 * Only `RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE` is currently supported.
 *
 * @param auth Pointer to the authentication data container.
 * @param message Pointer to a rid_message_pack_t whose non-AUTH messages
 *                were signed.
 * @param callback Callback function used to verify the signature.
 * @param context Opaque context passed to the callback.
 *
 * @retval RID_SUCCESS if verification succeeded.
 * @retval RID_ERROR_NULL_POINTER if auth, message, or callback is NULL.
 * @retval RID_ERROR_NOT_IMPLEMENTED if message is not a message pack, or
 *         if auth type is not MESSAGE_SET_SIGNATURE.
 * @retval RID_ERROR_OUT_OF_RANGE if the signature length is zero.
 * @retval Validation error codes from rid_auth_validate() or
 *         rid_message_pack_validate().
 * @retval Any non-zero value returned by the callback on verification failure.
 */
int rid_auth_verify(
    const rid_auth_t *auth,
    const void *message,
    rid_auth_verify_cb_t callback,
    void *context
);

/**
 * @brief Create an authentication signature with a caller supplied callback.
 *
 * Validates the auth container and the input message. Constructs the payload
 * to be signed internally, invokes the sign callback, then stores the
 * resulting signature in the auth container.
 *
 * The caller must set the timestamp before calling this function. The
 * auth type is set automatically to RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE.
 *
 * Only `rid_message_pack_t` is currently supported.
 *
 * @param auth Pointer to the authentication data container. The signature
 *             produced by the callback is stored here.
 * @param message Pointer to a rid_message_pack_t whose non-AUTH messages
 *                are to be signed.
 * @param callback Callback function used to produce the signature.
 * @param context Opaque context passed to the callback.
 *
 * @retval RID_SUCCESS if signing succeeded.
 * @retval RID_ERROR_NULL_POINTER if auth, message, or callback is NULL.
 * @retval RID_ERROR_NOT_IMPLEMENTED if message is not a message pack.
 * @retval RID_ERROR_OUT_OF_RANGE if the callback produced a zero-length
 *         signature.
 * @retval Validation error codes from rid_auth_validate() or
 *         rid_message_pack_validate().
 * @retval Any non-zero value returned by the callback on signing failure.
 */
int rid_auth_sign(
    rid_auth_t *auth,
    const void *message,
    rid_auth_sign_cb_t callback,
    void *context
);

/**
 * @brief Initialize an authentication data container.
 *
 * Zeros the structure and initializes page0 with protocol version and
 * message type. Sets page_count to 1.
 *
 * @param auth Pointer to the authentication data container.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if auth is NULL.
 */
int rid_auth_init(rid_auth_t *auth);

/**
 * @brief Validate an Auth container structure.
 *
 * Checks that page_0 fields contain valid values according to ASTM F3411-22a.
 *
 * @param auth Pointer to the Auth container structure to validate.
 *
 * @retval RID_SUCCESS if all fields are valid.
 * @retval RID_ERROR_NULL_POINTER if auth is NULL.
 * @retval RID_ERROR_INVALID_PROTOCOL_VERSION if protocol version is invalid.
 * @retval RID_ERROR_UNKNOWN_MESSAGE_TYPE if message type is not AUTH.
 * @retval RID_ERROR_INVALID_PAGE_NUMBER if page_number is invalid.
 * @retval RID_ERROR_INVALID_LAST_PAGE_INDEX if last_page_index exceeds maximum.
 * @retval RID_ERROR_NON_EMPTY_SIGNATURE if auth type is NETWORK_REMOTE_ID but signature is not empty.
 */
int rid_auth_validate(const rid_auth_t *auth);

/**
 * @brief Get the number of pages used.
 *
 * @param auth Pointer to the authentication data container.
 *
 * @return The page count (1-16), or 0 if auth is NULL.
 */
uint8_t rid_auth_get_page_count(const rid_auth_t *auth);

/**
 * @brief Set the authentication type.
 *
 * @param auth Pointer to the authentication data container.
 * @param type The authentication type to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if auth is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if type exceeds RID_AUTH_TYPE_MAX.
 */
int rid_auth_set_type(rid_auth_t *auth, rid_auth_type_t type);

/**
 * @brief Get the authentication type.
 *
 * @param auth Pointer to the authentication data container.
 *
 * @return The authentication type, or RID_AUTH_TYPE_NONE if auth is NULL.
 */
rid_auth_type_t rid_auth_get_type(const rid_auth_t *auth);

/**
 * @brief Set the timestamp.
 *
 * @param auth Pointer to the authentication data container.
 * @param timestamp Seconds since 2019-01-01 00:00:00 UTC.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if auth is NULL.
 */
int rid_auth_set_timestamp(rid_auth_t *auth, uint32_t timestamp);

/**
 * @brief Get the timestamp.
 *
 * @param auth Pointer to the authentication data container.
 *
 * @return Seconds since 2019-01-01 00:00:00 UTC, or 0 if auth is NULL.
 */
uint32_t rid_auth_get_timestamp(const rid_auth_t *auth);

/**
 * @brief Set the timestamp from Unix time.
 *
 * Converts Unix timestamp to RID timestamp (seconds since 2019-01-01).
 *
 * @param auth Pointer to the authentication data container.
 * @param unixtime Unix timestamp (seconds since 1970-01-01 00:00:00 UTC).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if auth is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if unixtime is before RID epoch (2019-01-01).
 */
int rid_auth_set_unixtime(rid_auth_t *auth, uint32_t unixtime);

/**
 * @brief Get the timestamp as Unix time.
 *
 * Converts RID timestamp to Unix timestamp.
 *
 * @param auth Pointer to the authentication data container.
 *
 * @return Unix timestamp (seconds since 1970-01-01 00:00:00 UTC),
 *         or 0 if auth is NULL.
 */
uint32_t rid_auth_get_unixtime(const rid_auth_t *auth);

/**
 * @brief Set the signature data.
 *
 * Distributes signature data across page 0 and additional pages as needed.
 * Page 0 holds up to 17 bytes, each additional page holds up to 23 bytes.
 *
 * @param auth Pointer to the authentication data container.
 * @param signature Pointer to the signature data.
 * @param size Size of the signature data (max 255 bytes).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if auth or signature is NULL.
 * @retval RID_ERROR_BUFFER_TOO_LARGE if size exceeds 255 bytes.
 */
int rid_auth_set_signature(rid_auth_t *auth, const uint8_t *signature, size_t size);

/**
 * @brief Get the total signature length in bytes.
 *
 * @param auth Pointer to the authentication data container.
 *
 * @return The total signature length in bytes, or 0 if auth is NULL.
 */
uint8_t rid_auth_get_length(const rid_auth_t *auth);

/**
 * @brief Get the signature data.
 *
 * Retrieves signature data from page 0 and additional pages.
 *
 * @param auth Pointer to the authentication data container.
 * @param buffer Buffer to store the signature data.
 * @param buffer_size Size of the buffer (must be at least the signature length).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if auth or buffer is NULL.
 * @retval RID_ERROR_BUFFER_TOO_SMALL if buffer_size is less than signature length.
 */
int rid_auth_get_signature(const rid_auth_t *auth, uint8_t *buffer, size_t buffer_size);

/**
 * @brief Format an Auth message as a JSON string.
 *
 * @param auth Pointer to the Auth container structure.
 * @param buffer Buffer to store the JSON string.
 * @param buffer_size Size of the buffer.
 *
 * @return Number of characters written (excluding null terminator),
 *         or negative value on error.
 */
int rid_auth_to_json(const rid_auth_t *auth, char *buffer, size_t buffer_size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
