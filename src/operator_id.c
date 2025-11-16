#include <string.h>
#include <stdint.h>
#include <stddef.h>

#include "rid/header.h"
#include "rid/operator_id.h"

rid_operator_id_type_t
rid_get_operator_id_type(const rid_operator_id_t *message) {
    return (rid_operator_id_type_t)message->id_type;
}

rid_error_t
rid_set_operator_id_type(rid_operator_id_t *message, rid_operator_id_type_t type) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    message->id_type = type;

    return RID_SUCCESS;
}

rid_error_t
rid_get_operator_id(const rid_operator_id_t *message, char *buffer, size_t buffer_size) {
    if (message == NULL || buffer == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (buffer_size < 21) {
        return RID_ERROR_BUFFER_TOO_SMALL;
    }

    memcpy(buffer, message->operator_id, 20);
    buffer[20] = '\0';

    return RID_SUCCESS;
}

rid_error_t
rid_set_operator_id(rid_operator_id_t *message, const char *operator_id) {
    if (message == NULL || operator_id == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    size_t size = strlen(operator_id);

    if (size > 20) {
        return RID_ERROR_BUFFER_TOO_LARGE;
    }

    /* Must be ASCII only */
    for (size_t i = 0; i < size; i++) {
        if ((unsigned char)operator_id[i] > 127) {
            return RID_ERROR_INVALID_CHARACTER;
        }
    }

    memset(message->operator_id, 0, 20);
    memcpy(message->operator_id, operator_id, size);

    return RID_SUCCESS;
}
