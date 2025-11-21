#include <string.h>
#include <stdint.h>
#include <stddef.h>

#include "rid/header.h"
#include "rid/basic_id.h"

rid_error_t
rid_basic_id_init(rid_basic_id_t *message) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    memset(message, 0, sizeof(rid_basic_id_t));

    message->protocol_version = VERSION_2;
    message->message_type = RID_MESSAGE_TYPE_BASIC_ID;

    return RID_SUCCESS;
}

rid_basic_id_type_t
rid_get_basic_id_type(const rid_basic_id_t *message) {
    return (rid_basic_id_type_t)message->id_type;
}

rid_ua_type_t
rid_get_ua_type(const rid_basic_id_t *message) {
    return (rid_ua_type_t)message->ua_type;
}

rid_error_t
rid_set_basic_id_type(rid_basic_id_t *message, rid_basic_id_type_t type) {
    if (message == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (type > RID_ID_TYPE_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    message->id_type = type;

    return RID_SUCCESS;
}

rid_error_t
rid_set_ua_type(rid_basic_id_t *message, rid_ua_type_t type) {
    if (NULL == message) {
        return RID_ERROR_NULL_POINTER;
    }

    if (type > RID_UA_TYPE_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    message->ua_type = type;

    return RID_SUCCESS;
}

rid_error_t
rid_get_uas_id(const rid_basic_id_t *message, char *buffer, size_t buffer_size) {
    if (message == NULL || buffer == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (buffer_size < 21) {
        return RID_ERROR_BUFFER_TOO_SMALL;
    }

    memcpy(buffer, message->uas_id, 20);
    buffer[20] = '\0';

    return RID_SUCCESS;
}

rid_error_t
rid_set_uas_id(rid_basic_id_t *message, const char *uas_id) {
    if (message == NULL || uas_id == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    size_t len = strlen(uas_id);

    if (len > 20) {
        return RID_ERROR_BUFFER_TOO_LARGE;
    }

    memset(message->uas_id, 0, 20);
    memcpy(message->uas_id, uas_id, len);

    return RID_SUCCESS;
}