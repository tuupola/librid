#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include <sodium.h>

#include "rid/auth.h"

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
    if (sodium_init() < 0) {
        return 1;
    }

    /* [full_example] */
    rid_auth_t auth;

    /* Generate Ed25519 keypair */
    uint8_t public_key[crypto_sign_PUBLICKEYBYTES];
    uint8_t secret_key[crypto_sign_SECRETKEYBYTES];
    crypto_sign_keypair(public_key, secret_key);

    /* Message to sign: UAS ID + unixtime */
    const char uas_id[] = "1ABCD2345EF678XYZ";
    uint32_t unixtime = (uint32_t)time(NULL);
    uint8_t message[sizeof(uas_id) - 1 + sizeof(unixtime)];
    memcpy(message, uas_id, sizeof(uas_id) - 1);
    memcpy(message + sizeof(uas_id) - 1, &unixtime, sizeof(unixtime));

    /* Create 64 byte detached Ed25519 signature */
    uint8_t signature[crypto_sign_BYTES];
    crypto_sign_detached(signature, NULL, message, sizeof(message), secret_key);

    rid_auth_init(&auth);
    rid_auth_set_type(&auth, RID_AUTH_TYPE_UAS_ID_SIGNATURE);
    rid_auth_set_unixtime(&auth, unixtime);
    rid_auth_set_signature(&auth, signature, sizeof(signature));

    /* Get the signature back for verifying*/
    uint8_t retrieved[crypto_sign_BYTES];
    rid_auth_get_signature(&auth, retrieved, sizeof(retrieved));

    if (crypto_sign_verify_detached(retrieved, message, sizeof(message), public_key) == 0) {
        printf("Signature verified.\n");
    } else {
        printf("Signature verification failed.\n");
    }
    /* [full_example] */

    printf("Page count: %d\n", rid_auth_get_page_count(&auth));
    printf("Length:     %d bytes\n", rid_auth_get_length(&auth));
    printf("Auth type:  %d\n", rid_auth_get_type(&auth));
    printf("Timestamp:  %u\n", rid_auth_get_timestamp(&auth));
    printf("\n");

    printf("Public key:\n");
    hexdump(public_key, sizeof(public_key));

    printf("Page 0:\n");
    hexdump(&auth.page_0, sizeof(auth.page_0));

    printf("Page 1:\n");
    hexdump(&auth.page_x[0], sizeof(auth.page_x[0]));

    printf("Page 2:\n");
    hexdump(&auth.page_x[1], sizeof(auth.page_x[1]));

    printf("Page 3:\n");
    hexdump(&auth.page_x[2], sizeof(auth.page_x[2]));

    printf("Retrieved signature:\n");
    hexdump(retrieved, sizeof(retrieved));

    return 0;
}
