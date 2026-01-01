#include <stdio.h>
#include <stdint.h>

#include "rid/message.h"

int
main(void)
{
    /* [full_example] */
    uint8_t buffer[] = {
        0xe3, 0xd2, 0x27, 0xcf, 0xfd, 0x7f, 0x00, 0x00,
        0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00
    };

    const rid_message_t *message = (const rid_message_t *)buffer;

    rid_protocol_version_t version = rid_message_get_protocol_version(message);
    rid_message_type_t type = rid_message_get_type(message);

    printf("Protocol version: %u\n", version);
    printf("Message type:     %u\n", type);
    /* [full_example] */

    return 0;
}
