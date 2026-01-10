#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "rid/rid.h"

static int
hex_to_bytes(const char *hex, uint8_t *bytes, size_t max_len)
{
    size_t hex_len = strlen(hex);
    if (hex_len % 2 != 0) {
        return -1;
    }

    size_t byte_len = hex_len / 2;
    if (byte_len > max_len) {
        return -1;
    }

    for (size_t i = 0; i < byte_len; ++i) {
        unsigned int byte;
        if (sscanf(hex + 2 * i, "%2x", &byte) != 1) {
            return -1;
        }
        bytes[i] = (uint8_t)byte;
    }

    return (int)byte_len;
}

int
main(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "--decode") != 0) {
        fprintf(stderr, "Usage: %s --decode <hex_string>\n", argv[0]);
        return 1;
    }

    uint8_t buffer[256];
    int len = hex_to_bytes(argv[2], buffer, sizeof(buffer));
    if (len < 0) {
        fprintf(stderr, "Error: Invalid hex string\n");
        return 1;
    }

    int rc = rid_message_validate(buffer);
    if (rc < 0) {
        fprintf(stderr, "Error: %s\n", rid_error_to_string(rc));
        return 1;
    }

    char json[4096];
    rc = rid_message_to_json(buffer, json, sizeof(json));
    if (rc < 0) {
        fprintf(stderr, "Error: %s\n", rid_error_to_string(rc));
        return 1;
    }

    printf("%s\n", json);

    return 0;
}
