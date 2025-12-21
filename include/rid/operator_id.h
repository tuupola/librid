#ifndef _RID_OPERATOR_ID_H
#define _RID_OPERATOR_ID_H

#include <stdint.h>
#include <stddef.h>

#include "rid/message.h"

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
 * @brief Get the ID type from an Operator ID message.
 *
 * @param message Pointer to the Operator ID message structure.
 *
 * @return The ID type.
 */
rid_operator_id_type_t rid_get_operator_id_type(const rid_operator_id_t *message);

/**
 * @brief Set the ID type for an Operator ID message.
 *
 * @param message Pointer to the Operator ID message structure.
 * @param type The ID type to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 */
int rid_set_operator_id_type(rid_operator_id_t *message, rid_operator_id_type_t type);

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
int rid_get_operator_id(const rid_operator_id_t *message, char *buffer, size_t buffer_size);

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
int rid_set_operator_id(rid_operator_id_t *message, const char *uas_id);

#endif
