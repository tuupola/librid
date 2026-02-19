#include <stdint.h>
#include <stdio.h>

#include "rid/self_id.h"

static void hexdump(const void *data, size_t size) {
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

int main(void) {
    /* [full_example] */
    rid_self_id_t self_id;

    rid_self_id_init(&self_id);
    rid_self_id_set_description_type(&self_id, RID_DESCRIPTION_TYPE_TEXT);
    rid_self_id_set_description(&self_id, "Drone delivery test");

    hexdump(&self_id, sizeof(self_id));

    char description[24];
    rid_self_id_get_description(&self_id, description, sizeof(description));
    rid_description_type_t desc_type = rid_self_id_get_description_type(&self_id);

    printf("Description: %s\n", description);
    printf("Type:        %d\n", desc_type);
    /* [full_example] */

    return 0;
}
