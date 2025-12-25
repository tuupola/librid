#ifndef _RID_SELF_ID_H
#define _RID_SELF_ID_H

/**
 * @file self_id.h
 * @brief Self ID message handling per ASTM F3411-22a.
 *
 * Example usage:
 * @snippet self_id/self_id.c full_example
 */

#include <stdint.h>
#include <stddef.h>

#include "rid/message.h"

/**
 * @brief Self ID message structure per ASTM F3411-22a.
 */
typedef struct
__attribute__((__packed__)) rid_self_id {
    uint8_t protocol_version: 4;
    uint8_t message_type : 4;
    uint8_t description_type;
    char description[23];
} rid_self_id_t;

/**
 * @brief Description type classification per ASTM F3411-22a.
 */
typedef enum rid_description_type {
    RID_DESCRIPTION_TYPE_TEXT = 0,
    RID_DESCRIPTION_TYPE_EMERGENCY = 1,
    RID_DESCRIPTION_TYPE_EXTENDED_STATUS = 2,
    /* 3-200: Reserved */
    /* 201-255: Private use*/
} rid_description_type_t;

/**
 * @brief Get the description type from a Self ID message.
 *
 * @param message Pointer to the Self ID message structure.
 *
 * @return The description type value.
 */
rid_description_type_t rid_get_description_type(const rid_self_id_t *message);

/**
 * @brief Set the description type for a Self ID message.
 *
 * @param message Pointer to the Self ID message structure.
 * @param type The description type to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 */
int rid_set_description_type(rid_self_id_t *message, rid_description_type_t type);

/**
 * @brief Get the description from a Self ID message.
 *
 * Copies the description to the provided buffer as a null-terminated string.
 *
 * @param message Pointer to the Self ID message structure.
 * @param buffer Buffer to store the description.
 * @param buffer_size Size of the buffer (must be at least 24 for full description).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message or buffer is NULL.
 * @retval RID_ERROR_BUFFER_TOO_SMALL if buffer_size is insufficient.
 */
int rid_get_description(const rid_self_id_t *message, char *buffer, size_t buffer_size);

/**
 * @brief Set the description for a Self ID message.
 *
 * The description is a null-terminated string up to 23 characters.
 *
 * @param message Pointer to the Self ID message structure.
 * @param description The description string to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message or description is NULL.
 * @retval RID_ERROR_BUFFER_TOO_LARGE if description exceeds 23 characters.
 */
int rid_set_description(rid_self_id_t *message, const char *description);

/**
 * @brief Initialize a Self ID message with default values.
 *
 * Sets protocol version to 2 and message type to SELF_ID.
 * All other fields are set to zero.
 *
 * @param message Pointer to the Self ID message structure.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 */
int rid_self_id_init(rid_self_id_t *message);

#endif
