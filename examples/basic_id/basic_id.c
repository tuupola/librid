#include <stdio.h>
#include <stdint.h>

#include "rid/basic_id.h"

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
    rid_basic_id_t basic_id;

    rid_basic_id_init(&basic_id);
    rid_basic_id_set_type(&basic_id, RID_ID_TYPE_SERIAL_NUMBER);
    rid_basic_id_set_ua_type(&basic_id, RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR);
    rid_basic_id_set_uas_id(&basic_id, "1ABCD2345EF678XYZ");

    hexdump(&basic_id, sizeof(basic_id));

    char uas_id[21];
    rid_basic_id_get_uas_id(&basic_id, uas_id, sizeof(uas_id));
    rid_ua_type_t ua_type = rid_basic_id_get_ua_type(&basic_id);
    rid_basic_id_type_t id_type = rid_basic_id_get_type(&basic_id);

    printf("UAS ID:  %s\n", uas_id);
    printf("UA type: %d\n", ua_type);
    printf("ID type: %d\n", id_type);
    /* [full_example] */

    return 0;
}
