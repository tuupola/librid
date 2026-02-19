#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "rid/basic_id.h"
#include "rid/message.h"

int main(void) {
    /* [full_example] */
    rid_basic_id_t message;
    int status;

    /* Valid Serial Number */
    rid_basic_id_init(&message);
    rid_basic_id_set_type(&message, RID_ID_TYPE_SERIAL_NUMBER);
    rid_basic_id_set_uas_id(&message, "1ABCD2345EF678XYZ");

    status = rid_basic_id_validate(&message);
    printf("Valid Serial Number:   %s\n", rid_error_to_string(status));

    /* Invalid Serial Number (contains 'I') */
    rid_basic_id_set_uas_id(&message, "INVALID123");

    status = rid_basic_id_validate(&message);
    printf("Invalid Serial Number: %s\n", rid_error_to_string(status));

    /* Valid UTM UUID (version 4, variant RFC4122) */
    rid_basic_id_init(&message);
    rid_basic_id_set_type(&message, RID_ID_TYPE_UTM_ASSIGNED_UUID);
    uint8_t valid_uuid[20] = {
        0x55, 0x0e, 0x84, 0x00, 0xe2, 0x9b, 0x41, 0xd4,
        0xa7, 0x16, 0x44, 0x66, 0x55, 0x44, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    memcpy(message.uas_id, valid_uuid, 20);

    status = rid_basic_id_validate(&message);
    printf("Valid UTM UUID:        %s\n", rid_error_to_string(status));

    /* Invalid UTM UUID (version 0) */
    message.uas_id[6] = 0x01;

    status = rid_basic_id_validate(&message);
    printf("Invalid UTM UUID:      %s\n", rid_error_to_string(status));
    /* [full_example] */

    return 0;
}
