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

#ifndef _RID_MESSAGE_PACK_H
#define _RID_MESSAGE_PACK_H

/**
 * @file message_pack.h
 * @brief Message pack handling per ASTM F3411-22a.
 *
 * Example usage:
 * @snippet message_pack/example_message_pack.c full_example
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

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
int rid_message_pack_init(rid_message_pack_t *pack);

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
int rid_message_pack_set_message_count(rid_message_pack_t *pack, uint8_t count);

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
int rid_message_pack_add_message(rid_message_pack_t *pack, const void *message);

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
int rid_message_pack_delete_message_at(rid_message_pack_t *pack, uint8_t index);

/**
 * @brief Replace a message at the specified index.
 *
 * @param pack Pointer to the Message Pack structure.
 * @param index Index of the message to replace (0-based).
 * @param message Pointer to the new message.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if pack or message is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if index is out of range.
 */
int rid_message_pack_replace_message_at(rid_message_pack_t *pack, uint8_t index, const void *message);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
