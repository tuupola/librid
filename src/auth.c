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

int
rid_auth_set(rid_auth_t *data, rid_auth_type_t type,
    uint32_t timestamp, const uint8_t *buffer, size_t size) {

    if (NULL == data || NULL == buffer) {
        return RID_ERROR_NULL_POINTER;
    }

    if (size > RID_AUTH_MAX_DATA_SIZE) {
        return RID_ERROR_BUFFER_TOO_LARGE;
    }

    /* Initialize and set up page 0 */
    rid_auth_init(data);
    rid_auth_page_0_set_type(&data->page_0, type);
    rid_auth_page_0_set_timestamp(&data->page_0, timestamp);
    rid_auth_page_0_set_length(&data->page_0, (uint8_t)size);

    /* Copy data to page 0 (up to 17 bytes) */
    size_t page0_size = size;
    if (page0_size > RID_AUTH_PAGE_0_DATA_SIZE) {
        page0_size = RID_AUTH_PAGE_0_DATA_SIZE;
    }
    rid_auth_page_0_set_data(&data->page_0, buffer, page0_size);

    /* Calculate number of pages needed */
    if (size <= RID_AUTH_PAGE_0_DATA_SIZE) {
        data->page_count = 1;
        rid_auth_page_0_set_last_page_index(&data->page_0, 0);
    } else {
        size_t remaining = size - RID_AUTH_PAGE_0_DATA_SIZE;
        uint8_t extra_pages = (uint8_t)((remaining + RID_AUTH_PAGE_DATA_SIZE - 1) / RID_AUTH_PAGE_DATA_SIZE);
        data->page_count = 1 + extra_pages;
        rid_auth_page_0_set_last_page_index(&data->page_0, extra_pages);

        /* Fill additional pages */
        const uint8_t *src = buffer + RID_AUTH_PAGE_0_DATA_SIZE;
        for (uint8_t i = 0; i < extra_pages; ++i) {
            rid_auth_page_x_init(&data->page_x[i], i + 1);
            rid_auth_page_x_set_type(&data->page_x[i], type);

            size_t chunk = remaining;
            if (chunk > RID_AUTH_PAGE_DATA_SIZE) {
                chunk = RID_AUTH_PAGE_DATA_SIZE;
            }
            rid_auth_page_x_set_data(&data->page_x[i], src, chunk);

            src += chunk;
            remaining -= chunk;
        }
    }

    return RID_SUCCESS;
}

int
rid_auth_get(const rid_auth_t *data, uint8_t *buffer,
    size_t buffer_size, size_t *size) {
    if (NULL == data || NULL == buffer) {
        return RID_ERROR_NULL_POINTER;
    }

    uint8_t total_length = rid_auth_page_0_get_length(&data->page_0);

    if (buffer_size < total_length) {
        return RID_ERROR_BUFFER_TOO_SMALL;
    }

    /* Copy from page 0 */
    size_t page0_size = total_length;
    if (page0_size > RID_AUTH_PAGE_0_DATA_SIZE) {
        page0_size = RID_AUTH_PAGE_0_DATA_SIZE;
    }

    uint8_t temp[RID_AUTH_PAGE_0_DATA_SIZE];
    rid_auth_page_0_get_data(&data->page_0, temp, sizeof(temp));
    memcpy(buffer, temp, page0_size);

    /* Copy from additional pages */
    if (total_length > RID_AUTH_PAGE_0_DATA_SIZE) {
        size_t remaining = total_length - RID_AUTH_PAGE_0_DATA_SIZE;
        uint8_t *dst = buffer + RID_AUTH_PAGE_0_DATA_SIZE;
        uint8_t last_page = rid_auth_page_0_get_last_page_index(&data->page_0);

        for (uint8_t i = 0; i < last_page; ++i) {
            uint8_t page_temp[RID_AUTH_PAGE_DATA_SIZE];
            rid_auth_page_x_get_data(&data->page_x[i], page_temp, sizeof(page_temp));

            size_t chunk = remaining;
            if (chunk > RID_AUTH_PAGE_DATA_SIZE) {
                chunk = RID_AUTH_PAGE_DATA_SIZE;
            }
            memcpy(dst, page_temp, chunk);

            dst += chunk;
            remaining -= chunk;
        }
    }

    if (NULL != size) {
        *size = total_length;
    }

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
