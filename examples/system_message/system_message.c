/*
 * System message example
 *
 * Demonstrates creating a Remote ID System message and parsing it back.
 */

#include <stdio.h>
#include <stdint.h>

#include "rid/message.h"
#include "rid/system.h"

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
    rid_system_t system;

    rid_system_init(&system);

    rid_set_operator_location_type(&system, RID_OPERATOR_LOCATION_TYPE_TAKEOFF);
    rid_set_classification_type(&system, RID_CLASSIFICATION_TYPE_EUROPEAN_UNION);
    rid_set_ua_classification_category(&system, RID_UA_CLASSIFICATION_CATEGORY_OPEN);
    rid_set_ua_classification_class(&system, RID_UA_CLASSIFICATION_CLASS_1);

    rid_set_operator_latitude(&system, 60.2870324);
    rid_set_operator_longitude(&system, 24.5397187);
    rid_set_operator_altitude(&system, 50.0f);

    rid_set_area_count(&system, 1);
    rid_set_area_radius(&system, 100);
    rid_set_area_ceiling(&system, 120.0f);
    rid_set_area_floor(&system, 0.0f);

    rid_set_system_timestamp(&system, 3600);

    hexdump(&system, sizeof(system));

    printf("Protocol version:   %u\n", rid_get_protocol_version(&system));
    printf("Message type:       %u\n", rid_get_message_type(&system));
    printf("Operator loc type:  %u\n", rid_get_operator_location_type(&system));
    printf("Classification:     %u\n", rid_get_classification_type(&system));
    printf("Operator latitude:  %.6f\n", rid_get_operator_latitude(&system));
    printf("Operator longitude: %.6f\n", rid_get_operator_longitude(&system));
    printf("Area count:         %u\n", rid_get_area_count(&system));
    printf("Area radius:        %u m\n", rid_get_area_radius(&system));
    printf("Area ceiling:       %.1f m\n", rid_get_area_ceiling(&system));
    printf("Area floor:         %.1f m\n", rid_get_area_floor(&system));
    printf("UA class:           %u\n", rid_get_ua_classification_class(&system));
    printf("UA category:        %u\n", rid_get_ua_classification_category(&system));
    printf("Operator altitude:  %.1f m\n", rid_get_operator_altitude(&system));
    printf("Timestamp:          %u\n", rid_get_system_timestamp(&system));
    /* [full_example] */

    return 0;
}
