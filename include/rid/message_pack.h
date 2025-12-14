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
 * @param message Pointer to the Message Pack structure to initialize.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 */
rid_error_t rid_message_pack_init(rid_message_pack_t *message);

#endif
