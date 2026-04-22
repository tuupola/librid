#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sodium.h>

#include "rid/auth.h"
#include "rid/message.h"
#include "rid/message_pack.h"

#include "keys.h"

static int hex_to_bytes(const char *hex, uint8_t *bytes, size_t max_length) {
    size_t hex_length = strlen(hex);
    if (hex_length % 2 != 0) {
        return -1;
    }

    size_t byte_length = hex_length / 2;
    if (byte_length > max_length) {
        return -1;
    }

    for (size_t i = 0; i < byte_length; ++i) {
        unsigned int byte;
        if (sscanf(hex + 2 * i, "%2x", &byte) != 1) {
            return -1;
        }
        bytes[i] = (uint8_t)byte;
    }

    return (int)byte_length;
}

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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <hex string>\n", argv[0]);
        return 1;
    }

    const char *hex_input = argv[1];

    if (sodium_init() < 0) {
        return 1;
    }

    uint8_t buffer[256];
    int length = hex_to_bytes(hex_input, buffer, sizeof(buffer));
    if (length < 0) {
        fprintf(stderr, "Error: Invalid hex string\n");
        return 1;
    }

    rid_message_pack_t *pack = (rid_message_pack_t *)buffer;
    rid_auth_t auth;

    int rc = rid_message_pack_get_auth(pack, &auth);
    if (rc != RID_SUCCESS) {
        fprintf(stderr, "Error: No auth message found\n");
        return 1;
    }

    printf("Auth type:  %d\n", rid_auth_get_type(&auth));
    printf("Timestamp:  %u\n", rid_auth_get_timestamp(&auth));
    printf("Page count: %d\n", rid_auth_get_page_count(&auth));
    printf("Length:     %d bytes\n\n", rid_auth_get_length(&auth));

    /* Only non Auth messages are verified */
    /* TODO: this needs proper API */
    uint8_t count = rid_message_pack_get_message_count(pack);
    for (uint8_t i = count; i > 0; --i) {
        const void *msg = rid_message_pack_get_message_at(pack, i - 1);
        if (rid_message_get_type(msg) == RID_MESSAGE_TYPE_AUTH) {
            rid_message_pack_delete_message_at(pack, i - 1);
        }
    }

    /* Combined size of non Auth Remote ID messages in the Message Pack */
    size_t messages_size = rid_message_pack_get_messages_size(pack);
    uint32_t timestamp = rid_auth_get_timestamp(&auth);

    /* The message to be verified, not to be confused with Remote ID message */
    uint8_t *message = malloc(messages_size + sizeof(timestamp));
    memcpy(message, rid_message_pack_get_messages(pack), messages_size);
    memcpy(message + messages_size, &timestamp, sizeof(timestamp));

    /* Get the signature and verify */
    uint8_t signature[crypto_sign_BYTES];
    rid_auth_get_signature(&auth, signature, sizeof(signature));

    printf("Signature:\n");
    hexdump(signature, sizeof(signature));

    if (crypto_sign_verify_detached(signature, message, messages_size + sizeof(timestamp), public_key) == 0) {
        printf("Signature verified.\n\n");
    } else {
        printf("Signature verification failed.\n\n");
    }

    return 0;
}
