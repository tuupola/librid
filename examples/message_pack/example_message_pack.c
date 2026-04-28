#include <stdint.h>
#include <stdio.h>

#include "rid/message.h"
#include "rid/rid.h"

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
    rid_message_pack_t pack;
    rid_basic_id_t basic_id_1;
    rid_basic_id_t basic_id_2;
    rid_location_t location;
    rid_self_id_t self_id;
    rid_operator_id_t operator_id;
    rid_system_t system;

    rid_message_pack_init(&pack);

    rid_basic_id_init(&basic_id_1);
    rid_basic_id_init(&basic_id_2);
    rid_location_init(&location);
    rid_self_id_init(&self_id);
    rid_operator_id_init(&operator_id);
    rid_system_init(&system);

    rid_message_pack_add_message(&pack, &basic_id_1);
    rid_message_pack_add_message(&pack, &basic_id_2);
    rid_message_pack_add_message(&pack, &location);
    rid_message_pack_add_message(&pack, &self_id);
    rid_message_pack_add_message(&pack, &operator_id);
    rid_message_pack_add_message(&pack, &system);

    printf("%s:\n", rid_message_type_to_string(rid_message_get_type(&pack)));
    hexdump(&pack, rid_message_pack_get_size(&pack));

    uint8_t count = rid_message_pack_get_message_count(&pack);

    for (uint8_t i = 0; i < count; i++) {
        rid_message_t message;
        int status = rid_message_pack_get_message_at(&pack, i, &message);
        if (status == RID_SUCCESS) {
            printf("%s:\n", rid_message_type_to_string(rid_message_get_type(&message)));
            hexdump(&message, sizeof(rid_message_t));
        }
    }
    /* [full_example] */

    return 0;
}
