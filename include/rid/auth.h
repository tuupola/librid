#ifndef _RID_AUTH_H
#define _RID_AUTH_H

/**
 * @file auth.h
 * @brief Authentication message handling per ASTM F3411-22a.
 *
 * Authentication messages support multi-page transmission with up to 16 pages
 * (0-15). Page 0 has a different structure than pages 1-15.
 *
 * Example usage:
 * @snippet auth/auth.c full_example
 */

#include <stdint.h>
#include <stddef.h>

/** Timestamp epoch offset (2019-01-01 00:00:00 UTC as Unix timestamp) */
#define RID_AUTH_EPOCH_OFFSET 1546300800

/** Auth data size for page 0 */
#define RID_AUTH_PAGE_0_DATA_SIZE 17

/** Auth data size for pages 1-15 */
#define RID_AUTH_PAGE_DATA_SIZE 23

/** Maximum number of authentication pages */
#define RID_AUTH_MAX_PAGES 16

/** Maximum page index (0-15) */
#define RID_AUTH_MAX_PAGE_INDEX 15

/**
 * @brief Authentication type classification per ASTM F3411-22a.
 */
typedef enum rid_auth_type {
    RID_AUTH_TYPE_NONE = 0,
    /* uas id + auth timestamp */
    RID_AUTH_TYPE_UAS_ID_SIGNATURE = 1,
    /* operator id + auth timestamp */
    RID_AUTH_TYPE_OPERATOR_ID_SIGNATURE = 2,
    /* bytes of each message + auth timestamp */
    RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE = 3,
    RID_AUTH_TYPE_NETWORK_REMOTE_ID = 4,
    RID_AUTH_TYPE_SPECIFIC_METHOD = 5,
    /* 6-9: Reserved for ASTM spec */
    /* 0xA-0xF: Available for private use */
    RID_AUTH_TYPE_MAX = 0x0F,
} rid_auth_type_t;

/**
 * @brief Authentication message page 0 structure per ASTM F3411-22a.
 *
 * Page 0 contains header information including timestamp and total length.
 */
typedef struct
__attribute__((__packed__)) rid_auth {
    uint8_t protocol_version: 4;
    uint8_t message_type: 4;
    uint8_t page_number: 4;
    uint8_t auth_type: 4;
    uint8_t last_page_index;
    uint8_t length;
    uint32_t timestamp;
    uint8_t auth_data[17];
} rid_auth_t;

/**
 * @brief Authentication message pages 1-15 structure per ASTM F3411-22a.
 *
 * Pages 1-15 contain only auth type, page number, and authentication data.
 */
typedef struct
__attribute__((__packed__)) rid_auth_page {
    uint8_t protocol_version: 4;
    uint8_t message_type: 4;
    uint8_t page_number: 4;
    uint8_t auth_type: 4;
    uint8_t auth_data[23];
} rid_auth_page_t;

/**
 * @brief Initialize an Authentication message page 0 structure.
 *
 * Sets protocol version to RID_PROTOCOL_VERSION_2, message type to
 * RID_MESSAGE_TYPE_AUTH, and page number to 0. All other fields are zeroed.
 *
 * @param message Pointer to the Authentication message structure to initialize.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 */
int rid_auth_init(rid_auth_t *message);

/**
 * @brief Initialize an Authentication message page 1-15 structure.
 *
 * Sets protocol version to RID_PROTOCOL_VERSION_2, message type to
 * RID_MESSAGE_TYPE_AUTH, and page number to specified value.
 *
 * @param message Pointer to the Authentication page structure to initialize.
 * @param page_number Page number (1-15).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if page_number is 0 or > 15.
 */
int rid_auth_page_init(rid_auth_page_t *message, uint8_t page_number);

/**
 * @brief Set the authentication type for page 0.
 *
 * @param message Pointer to the Authentication message structure.
 * @param type The authentication type to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if type exceeds RID_AUTH_TYPE_MAX.
 */
int rid_auth_set_type(rid_auth_t *message, rid_auth_type_t type);

/**
 * @brief Get the authentication type from page 0.
 *
 * @param message Pointer to the Authentication message structure.
 *
 * @return The authentication type, or RID_AUTH_TYPE_NONE if message is NULL.
 */
rid_auth_type_t rid_auth_get_type(const rid_auth_t *message);

/**
 * @brief Set the last page index for page 0.
 *
 * @param message Pointer to the Authentication message structure.
 * @param index The last page index (0-15).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if index > 15.
 */
int rid_auth_set_last_page_index(rid_auth_t *message, uint8_t index);

/**
 * @brief Get the last page index from page 0.
 *
 * @param message Pointer to the Authentication message structure.
 *
 * @return The last page index, or 0 if message is NULL.
 */
uint8_t rid_auth_get_last_page_index(const rid_auth_t *message);

/**
 * @brief Set the total authentication data length for page 0.
 *
 * @param message Pointer to the Authentication message structure.
 * @param length The total length of authentication data across all pages.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 */
int rid_auth_set_length(rid_auth_t *message, uint8_t length);

/**
 * @brief Get the total authentication data length from page 0.
 *
 * @param message Pointer to the Authentication message structure.
 *
 * @return The total length, or 0 if message is NULL.
 */
uint8_t rid_auth_get_length(const rid_auth_t *message);

/**
 * @brief Set the timestamp for page 0.
 *
 * Timestamp is seconds since 2019-01-01 00:00:00 UTC.
 *
 * @param message Pointer to the Authentication message structure.
 * @param timestamp Seconds since 2019-01-01 00:00:00 UTC.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 */
int rid_auth_set_timestamp(rid_auth_t *message, uint32_t timestamp);

/**
 * @brief Set the timestamp for page 0 from Unix time.
 *
 * Converts Unix timestamp to RID timestamp (seconds since 2019-01-01).
 *
 * @param message Pointer to the Authentication message structure.
 * @param unixtime Unix timestamp (seconds since 1970-01-01 00:00:00 UTC).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if unixtime is before RID epoch (2019-01-01).
 */
int rid_auth_set_timestamp_from_unixtime(rid_auth_t *message, uint32_t unixtime);

/**
 * @brief Get the timestamp from page 0.
 *
 * @param message Pointer to the Authentication message structure.
 *
 * @return Seconds since 2019-01-01 00:00:00 UTC, or 0 if message is NULL.
 */
uint32_t rid_auth_get_timestamp(const rid_auth_t *message);

/**
 * @brief Set the authentication data for page 0.
 *
 * @param message Pointer to the Authentication message structure.
 * @param data Pointer to the authentication data.
 * @param size Size of the data (max 17 bytes).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message or data is NULL.
 * @retval RID_ERROR_BUFFER_TOO_LARGE if size > 17.
 */
int rid_auth_set_data(rid_auth_t *message, const uint8_t *data, size_t size);

/**
 * @brief Get the authentication data from page 0.
 *
 * @param message Pointer to the Authentication message structure.
 * @param buffer Buffer to store the authentication data.
 * @param buffer_size Size of the buffer (must be at least 17).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message or buffer is NULL.
 * @retval RID_ERROR_BUFFER_TOO_SMALL if buffer_size < 17.
 */
int rid_auth_get_data(const rid_auth_t *message, uint8_t *buffer, size_t buffer_size);

/**
 * @brief Set the authentication type for pages 1-15.
 *
 * @param message Pointer to the Authentication page structure.
 * @param type The authentication type to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if type exceeds RID_AUTH_TYPE_MAX.
 */
int rid_auth_page_set_type(rid_auth_page_t *message, rid_auth_type_t type);

/**
 * @brief Get the authentication type from pages 1-15.
 *
 * @param message Pointer to the Authentication page structure.
 *
 * @return The authentication type, or RID_AUTH_TYPE_NONE if message is NULL.
 */
rid_auth_type_t rid_auth_page_get_type(const rid_auth_page_t *message);

/**
 * @brief Set the page number for pages 1-15.
 *
 * @param message Pointer to the Authentication page structure.
 * @param page_number The page number (1-15).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if page_number is 0 or > 15.
 */
int rid_auth_page_set_number(rid_auth_page_t *message, uint8_t page_number);

/**
 * @brief Get the page number from pages 1-15.
 *
 * @param message Pointer to the Authentication page structure.
 *
 * @return The page number, or 0 if message is NULL.
 */
uint8_t rid_auth_page_get_number(const rid_auth_page_t *message);

/**
 * @brief Set the authentication data for pages 1-15.
 *
 * @param message Pointer to the Authentication page structure.
 * @param data Pointer to the authentication data.
 * @param size Size of the data (max 23 bytes).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message or data is NULL.
 * @retval RID_ERROR_BUFFER_TOO_LARGE if size > 23.
 */
int rid_auth_page_set_data(rid_auth_page_t *message, const uint8_t *data, size_t size);

/**
 * @brief Get the authentication data from pages 1-15.
 *
 * @param message Pointer to the Authentication page structure.
 * @param buffer Buffer to store the authentication data.
 * @param buffer_size Size of the buffer (must be at least 23).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message or buffer is NULL.
 * @retval RID_ERROR_BUFFER_TOO_SMALL if buffer_size < 23.
 */
int rid_auth_page_get_data(const rid_auth_page_t *message, uint8_t *buffer, size_t buffer_size);

#endif
