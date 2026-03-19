#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "rid/basic_id.h"

/* Suppress warnings from MAVLink generated headers. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#pragma GCC diagnostic ignored "-Waddress-of-packed-member"
#include "common/mavlink.h"
#pragma GCC diagnostic pop

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

    /* Create a Remote ID Basic ID message */
    rid_basic_id_t basic_id;
    rid_basic_id_init(&basic_id);
    rid_basic_id_set_type(&basic_id, RID_ID_TYPE_SERIAL_NUMBER);
    rid_basic_id_set_ua_type(&basic_id, RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR);
    rid_basic_id_set_uas_id(&basic_id, "1ABCD2345EF678XYZ");

    char uas_id[21];
    rid_basic_id_get_uas_id(&basic_id, uas_id, sizeof(uas_id));

    printf("=== Remote ID to MAVLink =======================\n\n");
    printf("Remote ID Basic ID (%zu bytes):\n", sizeof(basic_id));
    hexdump(&basic_id, sizeof(basic_id));
    printf("  ID type: %s\n", rid_basic_id_type_to_string(rid_basic_id_get_type(&basic_id)));
    printf("  UA type: %s\n", rid_ua_type_to_string(rid_basic_id_get_ua_type(&basic_id)));
    printf("  UAS ID:  %s\n\n", uas_id);

    /* Convert to MAVLink Open Drone ID Basic ID message */
    mavlink_open_drone_id_basic_id_t mavlink_basid_id;
    memset(&mavlink_basid_id, 0, sizeof(mavlink_basid_id));
    mavlink_basid_id.target_system = 0;
    mavlink_basid_id.target_component = 0;
    mavlink_basid_id.id_type = rid_basic_id_get_type(&basic_id);
    mavlink_basid_id.ua_type = rid_basic_id_get_ua_type(&basic_id);
    memcpy(mavlink_basid_id.uas_id, uas_id, sizeof(mavlink_basid_id.uas_id));

    /* Encode into a MAVLink message frame */
    mavlink_message_t mavlink;
    mavlink_msg_open_drone_id_basic_id_encode(1, 1, &mavlink, &mavlink_basid_id);

    printf("MAVLink Basic ID (%d bytes):\n", mavlink.len);
    printf("  Message ID: %u\n", mavlink.msgid);
    hexdump(&mavlink, mavlink.len);

    printf("=== MAVLink to Remote ID =======================\n\n");

    /* Decode the MAVLink message frame */
    mavlink_open_drone_id_basic_id_t decoded;
    mavlink_msg_open_drone_id_basic_id_decode(&mavlink, &decoded);

    /* Convert MAVLink fields back to Remote ID Basic ID */
    rid_basic_id_t roundtrip;
    rid_basic_id_init(&roundtrip);
    rid_basic_id_set_type(&roundtrip, decoded.id_type);
    rid_basic_id_set_ua_type(&roundtrip, decoded.ua_type);

    /* MAVLink uas_id is not guaranteed to be null terminated */
    char decoded_id[21];
    memcpy(decoded_id, decoded.uas_id, 20);
    decoded_id[20] = '\0';
    rid_basic_id_set_uas_id(&roundtrip, decoded_id);

    char roundtrip_id[21];
    rid_basic_id_get_uas_id(&roundtrip, roundtrip_id, sizeof(roundtrip_id));

    printf("Remote ID Basic ID (%zu bytes):\n", sizeof(roundtrip));
    hexdump(&roundtrip, sizeof(roundtrip));
    printf("  ID type: %s\n", rid_basic_id_type_to_string(rid_basic_id_get_type(&roundtrip)));
    printf("  UA type: %s\n", rid_ua_type_to_string(rid_basic_id_get_ua_type(&roundtrip)));
    printf("  UAS ID:  %s\n\n", roundtrip_id);
    /* [full_example] */

    return 0;
}
