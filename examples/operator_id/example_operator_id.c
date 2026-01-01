#include <stdio.h>
#include <stdint.h>

#include "rid/operator_id.h"

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
    rid_operator_id_t operator_id;

    rid_operator_id_init(&operator_id);
    rid_operator_id_set_type(&operator_id, RID_ID_TYPE_OPERATOR_ID);
    rid_operator_id_set(&operator_id, "FIN87astrdge12k8");

    hexdump(&operator_id, sizeof(operator_id));

    char id[21];
    rid_operator_id_get(&operator_id, id, sizeof(id));
    rid_operator_id_type_t id_type = rid_operator_id_get_type(&operator_id);

    printf("Operator ID: %s\n", id);
    printf("ID type:     %d\n", id_type);
    /* [full_example] */

    return 0;
}
