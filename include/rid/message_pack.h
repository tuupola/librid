#ifndef _RID_MESSAGE_PACK_H
#define _RID_MESSAGE_PACK_H

#include <stdint.h>

#define RID_MESSAGE_PACK_MAX_MESSAGES 9
#define RID_MESSAGE_SIZE 25

/**
 * @brief Message Pack structure per ASTM F3411-22a.
 *
 * Contains up to 9 concatenated messages of 25 bytes each.
 */
typedef struct
__attribute__((__packed__)) rid_message_pack {
    uint8_t protocol_version: 4;
    uint8_t message_type: 4;
    uint8_t message_size;
    uint8_t message_count;
    uint8_t messages[225];
} rid_message_pack_t;

/**
 * @brief Initialize a Message Pack structure.
 *
 * Sets protocol version to RID_PROTOCOL_VERSION_2 and message type to
 * RID_MESSAGE_TYPE_MESSAGE_PACK. The message_size is set to RID_MESSAGE_SIZE.
 * All other fields are zeroed.
 *
 * @param pack Pointer to the Message Pack structure to initialize.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if pack is NULL.
 */
rid_error_t rid_message_pack_init(rid_message_pack_t *pack);

/**
 * @brief Set the message count for a Message Pack.
 *
 * @param pack Pointer to the Message Pack structure.
 * @param count The number of messages (0-9).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if pack is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if count exceeds RID_MESSAGE_PACK_MAX_MESSAGES.
 */
rid_error_t rid_message_pack_set_message_count(rid_message_pack_t *pack, uint8_t count);

/**
 * @brief Get the message count from a Message Pack.
 *
 * @param pack Pointer to the Message Pack structure.
 *
 * @return The message count, or 0 if pack is NULL.
 */
uint8_t rid_message_pack_get_message_count(const rid_message_pack_t *pack);

/**
 * @brief Add a message to a Message Pack.
 *
 * @param pack Pointer to the Message Pack structure.
 * @param message Pointer to the message to add.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if pack or message is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if pack already contains RID_MESSAGE_PACK_MAX_MESSAGES.
 */
rid_error_t rid_message_pack_add_message(rid_message_pack_t *pack, const void *message);

/**
 * @brief Get a pointer to a message at the specified index.
 *
 * @param pack Pointer to the Message Pack structure.
 * @param index Index of the message (0-based).
 *
 * @return Pointer to the message, or NULL if pack is NULL or index is out of range.
 */
const void *rid_message_pack_get_message_at(const rid_message_pack_t *pack, uint8_t index);

/**
 * @brief Delete a message at the specified index.
 *
 * Messages after the deleted one are shifted down to fill the gap.
 *
 * @param pack Pointer to the Message Pack structure.
 * @param index Index of the message to delete (0-based).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if pack is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if index is out of range.
 */
rid_error_t rid_message_pack_delete_message_at(rid_message_pack_t *pack, uint8_t index);

#endif
