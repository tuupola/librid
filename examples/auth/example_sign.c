#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include <sodium.h>

#include "rid/auth.h"
#include "rid/basic_id.h"
#include "rid/location.h"
#include "rid/message.h"
#include "rid/message_pack.h"
#include "rid/operator_id.h"
#include "rid/self_id.h"
#include "rid/system.h"

#include "keys.h"

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

static void hexstring(const void *data, size_t size) {
    const uint8_t *p = data;
    while (size--) {
        printf("%02x", *p++);
    }
    printf("\n");
}

/* Callback wrapper for libsodium */
static int sign_ed25519(
    void *context,
    const uint8_t *input,
    size_t input_length,
    uint8_t *signature,
    size_t signature_size,
    size_t *signature_length
) {
    (void)signature_size;
    const uint8_t *key = (const uint8_t *)context;
    unsigned long long sig_len = 0;
    int rc = crypto_sign_detached(signature, &sig_len, input, input_length, key);
    if (0 == rc) {
        *signature_length = (size_t)sig_len;
    }
    return rc;
}

int main(void) {
    if (sodium_init() < 0) {
        return 1;
    }

    /* [full_example] */
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;
    rid_location_t location;
    rid_self_id_t self_id;
    rid_operator_id_t operator_id;
    rid_system_t system;
    rid_auth_t auth;

    rid_message_pack_init(&pack);
    rid_basic_id_init(&basic_id);
    rid_location_init(&location);
    rid_self_id_init(&self_id);
    rid_operator_id_init(&operator_id);
    rid_system_init(&system);
    rid_auth_init(&auth);

    rid_message_pack_add_message(&pack, &basic_id);
    rid_message_pack_add_message(&pack, &location);
    rid_message_pack_add_message(&pack, &self_id);
    rid_message_pack_add_message(&pack, &operator_id);
    rid_message_pack_add_message(&pack, &system);

    /* You must set timestamp manually */
    rid_auth_set_unixtime(&auth, (uint32_t)time(NULL));

    /* Sign and add the Auth message to the Message Pack */
    rid_auth_sign(&auth, &pack, sign_ed25519, (void *)secret_key);
    rid_message_pack_set_auth(&pack, &auth);
    /* [full_example] */

    uint8_t signature[crypto_sign_BYTES];
    rid_auth_get_signature(&auth, signature, sizeof(signature));

    printf("Auth type:  %d\n", rid_auth_get_type(&auth));
    printf("Timestamp:  %u\n", rid_auth_get_timestamp(&auth));
    printf("Length:     %d bytes\n\n", rid_auth_get_length(&auth));
    printf("Page count: %d\n", rid_auth_get_page_count(&auth));

    printf("Signature:\n");
    hexdump(signature, sizeof(signature));
    hexstring(signature, sizeof(signature));

    printf("\nAuth pages:\n");
    uint8_t page_count = rid_auth_get_page_count(&auth);
    for (uint8_t i = 0; i < page_count; i++) {
        printf("Page %d:\n", i);
        if (i == 0) {
            hexdump(&auth.page_0, sizeof(auth.page_0));
        } else {
            hexdump(&auth.page_x[i - 1], sizeof(auth.page_x[0]));
        }
    }

    printf("Message pack:\n");
    hexdump(&pack, rid_message_pack_get_size(&pack));

    printf("Verify with:\n");
    printf("$ ./example_verify ");
    hexstring(&pack, rid_message_pack_get_size(&pack));
    printf("\n");

    return 0;
}
