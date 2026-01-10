#include <stdio.h>

#include "rid/basic_id.h"
#include "rid/location.h"
#include "rid/self_id.h"
#include "rid/operator_id.h"
#include "rid/message_pack.h"

int
main(void)
{
    char buffer[2048];

    rid_message_pack_t pack;
    rid_message_pack_init(&pack);

    /* Basic ID */
    rid_basic_id_t basic_id;
    rid_basic_id_init(&basic_id);
    rid_basic_id_set_type(&basic_id, RID_ID_TYPE_SERIAL_NUMBER);
    rid_basic_id_set_ua_type(&basic_id, RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR);
    rid_basic_id_set_uas_id(&basic_id, "1ABCD2345EF678XYZ");
    rid_message_pack_add_message(&pack, &basic_id);

    /* Location */
    rid_location_t location;
    rid_location_init(&location);
    rid_location_set_latitude(&location, 60.169857);
    rid_location_set_longitude(&location, 24.938379);
    rid_location_set_geodetic_altitude(&location, 25.5);
    rid_location_set_height(&location, 15.0);
    rid_location_set_height_type(&location, RID_HEIGHT_TYPE_AGL);
    rid_location_set_speed(&location, 5.25);
    rid_location_set_operational_status(&location, RID_OPERATIONAL_STATUS_AIRBORNE);
    rid_message_pack_add_message(&pack, &location);

    /* Self ID */
    rid_self_id_t self_id;
    rid_self_id_init(&self_id);
    rid_self_id_set_description(&self_id, "Survey drone");
    rid_message_pack_add_message(&pack, &self_id);

    /* Operator ID */
    rid_operator_id_t operator_id;
    rid_operator_id_init(&operator_id);
    rid_operator_id_set(&operator_id, "FIN87astrdge12k8");
    rid_message_pack_add_message(&pack, &operator_id);

    /* Print the Message Pack as JSON */
    rid_message_pack_to_json(&pack, buffer, sizeof(buffer));
    printf("%s\n", buffer);

    return 0;
}
