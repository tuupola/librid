/*
 * Note: For typical use cases, you should use the higher-level API in auth.h
 * instead which manages multi-page authentication data automatically. This
 * example is provided for completeness sake.
 */

#include <stdio.h>
#include <stdint.h>

#include "rid/auth_page.h"

static void
hexdump(const void *data, size_t size)
{
    const uint8_t *bytes = (const uint8_t *)data;

    for (size_t i = 0; i < size; ++i) {
        if (i > 0 && i % 16 == 0) {
            printf("\n");
        } else if (i > 0 && i % 8 == 0) {
            printf(" ");
        }
        printf("%02x ", bytes[i]);
    }
    printf("\n\n");
}

int
main(void)
{
    /* [full_example] */
    rid_auth_page_0_t page_0;
    rid_auth_page_x_t page_1;
    rid_auth_page_x_t page_2;

    /* sample authentication data */
    const uint8_t page_0_data[] = {
        0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09,
        0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01,
        0x01
    };

    const uint8_t page_1_data[] = {
        0x05, 0x00, 0x03, 0x82, 0x01, 0x0f, 0x00, 0x30,
        0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01, 0x00,
        0xbb, 0x6a, 0x8c, 0x7e, 0x5f, 0x2a, 0x9b
    };

    const uint8_t page_2_data[] = {
        0xc5, 0x7b, 0x99, 0x3a, 0x1d, 0x03, 0x66, 0x81,
        0xf4, 0x9e, 0x2c, 0x87, 0xab, 0x4f, 0xe0, 0x12
    };

    /* page 0 example */
    rid_auth_page_0_init(&page_0);
    rid_auth_page_0_set_type(&page_0, RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE);
    rid_auth_page_0_set_last_page_index(&page_0, 2);
    rid_auth_page_0_set_length(&page_0, 56);
    rid_auth_page_0_set_timestamp(&page_0, 189302400);
    rid_auth_page_0_set_data(&page_0, page_0_data, sizeof(page_0_data));

    printf("Page 0:\n");
    hexdump(&page_0, sizeof(page_0));

    uint8_t data_buffer[RID_AUTH_PAGE_0_DATA_SIZE];
    rid_auth_page_0_get_data(&page_0, data_buffer, sizeof(data_buffer));

    printf("Auth type:       %d\n", rid_auth_page_0_get_type(&page_0));
    printf("Last page index: %d\n", rid_auth_page_0_get_last_page_index(&page_0));
    printf("Length:          %d\n", rid_auth_page_0_get_length(&page_0));
    printf("Timestamp:       %u\n", rid_auth_page_0_get_timestamp(&page_0));
    printf("\n");

    /* page 1 example */
    rid_auth_page_x_init(&page_1, 1);
    rid_auth_page_x_set_type(&page_1, RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE);
    rid_auth_page_x_set_data(&page_1, page_1_data, sizeof(page_1_data));

    printf("Page 1:\n");
    hexdump(&page_1, sizeof(page_1));

    printf("Auth type:   %d\n", rid_auth_page_x_get_type(&page_1));
    printf("Page number: %d\n", rid_auth_page_x_get_number(&page_1));
    printf("\n");

    /* page 2 example */
    rid_auth_page_x_init(&page_2, 2);
    rid_auth_page_x_set_type(&page_2, RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE);
    rid_auth_page_x_set_data(&page_2, page_2_data, sizeof(page_2_data));

    printf("Page 2:\n");
    hexdump(&page_2, sizeof(page_2));

    printf("Auth type:   %d\n", rid_auth_page_x_get_type(&page_2));
    printf("Page number: %d\n", rid_auth_page_x_get_number(&page_2));
    /* [full_example] */

    return 0;
}
