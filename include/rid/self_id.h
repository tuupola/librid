#ifndef _RID_SELF_ID_H
#define _RID_SELF_ID_H

#include <stdint.h>
#include <stddef.h>

#include "rid/header.h"

typedef struct
__attribute__((__packed__)) rid_self_id {
    uint8_t protocol_version: 4;
    uint8_t message_type : 4;
    uint8_t description_type;
    char description[23];
} rid_self_id_t;

typedef enum rid_description_type {
    RID_DESCRIPTION_TYPE_TEXT,
    RID_DESCRIPTION_TYPE_EMERGENCY,
    RID_DESCRIPTION_TYPE_EXTENDED_STATUS,
    /* 3-200: Reserved */
    /* 201-255: Private use*/
} rid_description_type_t;

rid_description_type_t rid_get_description_type(const rid_self_id_t *message);
rid_error_t rid_set_description_type(rid_self_id_t *message, rid_description_type_t type);
rid_error_t rid_get_description(const rid_self_id_t *message, char *buffer, size_t buffer_size);
rid_error_t rid_set_description(rid_self_id_t *message, const char *description);

#endif
