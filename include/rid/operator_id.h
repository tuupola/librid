#ifndef _RID_OPERATOR_ID_H
#define _RID_OPERATOR_ID_H

#include <stdint.h>
#include <stddef.h>

#include "rid/header.h"

typedef struct
__attribute__((__packed__)) rid_operator_id {
    uint8_t protocol_version: 4;
    uint8_t message_type : 4;
    uint8_t id_type;
    char operator_id[20];
    char reserved[3];
} rid_operator_id_t;

typedef enum rid_operator_id_type {
    RID_ID_TYPE_OPERATOR_ID,
    /* 1-200: Reserved */
    /* 201-255: Private use*/
} rid_operator_id_type_t;

rid_operator_id_type_t rid_get_operator_id_type(const rid_operator_id_t *message);
rid_error_t rid_set_operator_id_type(rid_operator_id_t *message, rid_operator_id_type_t type);
rid_error_t rid_get_operator_id(const rid_operator_id_t *message, char *buffer, size_t buffer_size);
rid_error_t rid_set_operator_id(rid_operator_id_t *message, const char *uas_id);

#endif
