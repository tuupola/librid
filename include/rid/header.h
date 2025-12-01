#ifndef _RID_MESSAGE_H
#define _RID_MESSAGE_H

#include <stdint.h>

typedef enum {
    RID_SUCCESS = 0,
    RID_ERROR_NULL_POINTER = -1,
    RID_ERROR_BUFFER_TOO_SMALL = -2,
    RID_ERROR_BUFFER_TOO_LARGE = -3,
    RID_ERROR_INVALID_CHARACTER = -4,
    RID_ERROR_OUT_OF_RANGE = -5,
} rid_error_t;

typedef struct
__attribute__((__packed__)) rid_message_header {
    uint8_t protocol_version: 4;
    uint8_t message_type : 4;
} rid_message_header_t;

typedef enum rid_message_type {
    RID_MESSAGE_TYPE_BASIC_ID,
    RID_MESSAGE_TYPE_LOCATION,
    RID_MESSAGE_TYPE_AUTH,
    RID_MESSAGE_TYPE_SELF_ID,
    RID_MESSAGE_TYPE_SYSTEM,
    RID_MESSAGE_TYPE_OPERATOR_ID,
    RID_MESSAGE_TYPE_MESSAGE_PACK = 0x0F,
} rid_message_type_t;

typedef enum rid_protocol_version {
    RID_PROTOCOL_VERSION_0,
    RID_PROTOCOL_VERSION_1,
    RID_PROTOCOL_VERSION_2,
    RID_PROTOCOL_PRIVATE_USE = 0x0F,
} rid_protocol_version_t;

rid_message_type_t rid_get_message_type(const void *message);
rid_protocol_version_t rid_get_protocol_version(const void *message);

#endif