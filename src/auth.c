#include <string.h>
#include <stdint.h>
#include <stddef.h>

#include "rid/message.h"
#include "rid/auth_page.h"
#include "rid/auth.h"

int
rid_auth_init(rid_auth_t *data) {
    if (NULL == data) {
        return RID_ERROR_NULL_POINTER;
    }

    memset(data, 0, sizeof(rid_auth_t));
    rid_auth_page_0_init(&data->page_0);
    data->page_count = 1;

    return RID_SUCCESS;
}

uint8_t
rid_auth_get_page_count(const rid_auth_t *data) {
    if (NULL == data) {
        return 0;
    }

    return data->page_count;
}

int
rid_auth_set_type(rid_auth_t *auth, rid_auth_type_t type) {
    if (NULL == auth) {
        return RID_ERROR_NULL_POINTER;
    }

    return rid_auth_page_0_set_type(&auth->page_0, type);
}

rid_auth_type_t
rid_auth_get_type(const rid_auth_t *auth) {
    if (NULL == auth) {
        return RID_AUTH_TYPE_NONE;
    }

    return rid_auth_page_0_get_type(&auth->page_0);
}

int
rid_auth_set_timestamp(rid_auth_t *auth, uint32_t timestamp) {
    if (NULL == auth) {
        return RID_ERROR_NULL_POINTER;
    }

    return rid_auth_page_0_set_timestamp(&auth->page_0, timestamp);
}

uint32_t
rid_auth_get_timestamp(const rid_auth_t *auth) {
    if (NULL == auth) {
        return 0;
    }

    return rid_auth_page_0_get_timestamp(&auth->page_0);
}

int
rid_auth_set_unixtime(rid_auth_t *auth, uint32_t unixtime) {
    if (NULL == auth) {
        return RID_ERROR_NULL_POINTER;
    }

    if (unixtime < RID_AUTH_EPOCH_OFFSET) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    return rid_auth_page_0_set_timestamp(&auth->page_0, unixtime - RID_AUTH_EPOCH_OFFSET);
}

uint32_t
rid_auth_get_unixtime(const rid_auth_t *auth) {
    if (NULL == auth) {
        return 0;
    }

    return rid_auth_page_0_get_timestamp(&auth->page_0) + RID_AUTH_EPOCH_OFFSET;
}
