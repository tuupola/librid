#ifndef _RID_MESSAGE_H
#define _RID_MESSAGE_H

#include <stdint.h>

typedef struct
__attribute__((__packed__)) rid_message_byte_0 {
    uint8_t protocol_version: 4;
    uint8_t message_type : 4;
} rid_message_byte_0_t;

typedef enum rid_message_type {
    RID_MESSAGE_TYPE_BASIC_ID,
    RID_MESSAGE_TYPE_LOCATION,
    RID_MESSAGE_TYPE_AUTH,
    RID_MESSAGE_TYPE_SELF_ID,
    RID_MESSAGE_TYPE_SYSTEM,
    RID_MESSAGE_TYPE_OPERATOR_ID,
    RID_MESSAGE_TYPE_MESSAGE_PACK = 0x0F,
} rid_message_type_t;

uint8_t rid_message_get_type(const void *message);
uint8_t rid_message_get_protocol_version(const void *message);

#endif