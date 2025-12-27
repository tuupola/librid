#ifndef _RID_AUTH_H
#define _RID_AUTH_H

/**
 * @file auth.h
 * @brief High-level authentication data API per ASTM F3411-22a.
 *
 * Provides a container struct and functions that automatically handle
 * splitting authentication data across multiple pages.
 *
 * Example usage:
 * @code
 * rid_auth_t auth;
 * uint8_t signature[64] = { ... };
 *
 * rid_auth_init(&auth);
 * rid_auth_set(&auth, RID_AUTH_TYPE_UAS_ID_SIGNATURE,
 *                   timestamp, signature, sizeof(signature));
 *
 * uint8_t page_count = rid_auth_get_page_count(&auth);
 * @endcode
 */

#include <stdint.h>
#include <stddef.h>

#include "rid/auth_page.h"

/** Maximum authentication data size in bytes */
#define RID_AUTH_MAX_DATA_SIZE 255

/**
 * @brief Container for multi-page authentication data.
 *
 * Holds page 0 and up to 15 additional pages, along with the total page count.
 */
typedef struct rid_auth {
    rid_auth_page_0_t page_0;
    rid_auth_page_x_t page_x[15];
    uint8_t page_count;
} rid_auth_t;

/**
 * @brief Initialize an authentication data container.
 *
 * Zeros the structure and initializes page0 with protocol version and
 * message type. Sets page_count to 1.
 *
 * @param data Pointer to the authentication data container.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if data is NULL.
 */
int rid_auth_init(rid_auth_t *data);

/**
 * @brief Set authentication data, automatically splitting across pages.
 *
 * Distributes the provided data across page 0 (17 bytes max) and additional
 * pages (23 bytes each) as needed. Sets all required fields including
 * last_page_index and length.
 *
 * @param data Pointer to the authentication data container.
 * @param type The authentication type.
 * @param timestamp Seconds since 2019-01-01 00:00:00 UTC.
 * @param buffer Pointer to the authentication data.
 * @param size Size of the data (max 255 bytes).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if data or buffer is NULL.
 * @retval RID_ERROR_BUFFER_TOO_LARGE if size > 255.
 */
int rid_auth_set(rid_auth_t *data, rid_auth_type_t type,
    uint32_t timestamp, const uint8_t *buffer, size_t size);

/**
 * @brief Get authentication data, reassembling from all pages.
 *
 * Copies data from page 0 and all additional pages into the provided buffer.
 *
 * @param data Pointer to the authentication data container.
 * @param buffer Buffer to store the reassembled data.
 * @param buffer_size Size of the buffer.
 * @param size Pointer to store the actual data size (can be NULL).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if data or buffer is NULL.
 * @retval RID_ERROR_BUFFER_TOO_SMALL if buffer_size is insufficient.
 */
int rid_auth_get(const rid_auth_t *data, uint8_t *buffer,
    size_t buffer_size, size_t *size);

/**
 * @brief Get the number of pages used.
 *
 * @param data Pointer to the authentication data container.
 *
 * @return The page count (1-16), or 0 if data is NULL.
 */
uint8_t rid_auth_get_page_count(const rid_auth_t *data);

#endif
