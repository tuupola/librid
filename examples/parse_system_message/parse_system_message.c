/*
 * Parse a system message from raw bytes and display the contents.
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
    printf("\n");
}

int
main(void)
{
    const uint8_t data[] = {
        0x42, 0x04, 0x34, 0x12, 0xef, 0x23, 0xc3, 0x76,
        0xa0, 0x0e, 0x01, 0x00, 0x0a, 0xc0, 0x08, 0xd0,
        0x07, 0x12, 0x34, 0x08, 0x61, 0x42, 0x21, 0x0d,
        0x00
    };

    const rid_system_t *system = (const rid_system_t *)data;

    printf("Hex dump:\n");
    hexdump(data, sizeof(data));
    printf("\n");

    printf("System message (%zu bytes):\n", sizeof(data));
    printf("  Protocol version:   %u\n", rid_get_protocol_version(system));
    printf("  Message type:       %u\n", rid_get_message_type(system));
    printf("  Operator loc type:  %u\n", rid_get_operator_location_type(system));
    printf("  Classification:     %u\n", rid_get_classification_type(system));
    printf("  Operator latitude:  %.6f\n", rid_get_operator_latitude(system));
    printf("  Operator longitude: %.6f\n", rid_get_operator_longitude(system));
    printf("  Area count:         %u\n", rid_get_area_count(system));
    printf("  Area radius:        %u m\n", rid_get_area_radius(system));
    printf("  Area ceiling:       %.1f m\n", rid_get_area_ceiling(system));
    printf("  Area floor:         %.1f m\n", rid_get_area_floor(system));
    printf("  UA class:           %u\n", rid_get_ua_classification_class(system));
    printf("  UA category:        %u\n", rid_get_ua_classification_category(system));
    printf("  Operator altitude:  %.1f m\n", rid_get_operator_altitude(system));
    printf("  Timestamp:          %u\n", rid_get_system_timestamp(system));

    return 0;
}
