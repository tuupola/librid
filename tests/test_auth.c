#include <stdint.h>

#include "greatest.h"
#include "rid/message.h"
#include "rid/auth_page.h"
#include "rid/auth.h"

TEST
test_auth_init(void) {
    rid_auth_t auth;

    int status = rid_auth_init(NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_auth_init(&auth);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(1, rid_auth_get_page_count(&auth));
    ASSERT_EQ(RID_PROTOCOL_VERSION_2, auth.page_0.protocol_version);
    ASSERT_EQ(RID_MESSAGE_TYPE_AUTH, auth.page_0.message_type);
    ASSERT_EQ(0, auth.page_0.page_number);

    PASS();
}

TEST
test_auth_get_page_count(void) {
    rid_auth_t auth;

    ASSERT_EQ(0, rid_auth_get_page_count(NULL));

    rid_auth_init(&auth);
    ASSERT_EQ(1, rid_auth_get_page_count(&auth));

    PASS();
}

TEST
test_auth_set_and_get_type(void) {
    rid_auth_t auth;
    rid_auth_init(&auth);

    int status = rid_auth_set_type(&auth, RID_AUTH_TYPE_UAS_ID_SIGNATURE);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(RID_AUTH_TYPE_UAS_ID_SIGNATURE, rid_auth_get_type(&auth));

    status = rid_auth_set_type(&auth, RID_AUTH_TYPE_OPERATOR_ID_SIGNATURE);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(RID_AUTH_TYPE_OPERATOR_ID_SIGNATURE, rid_auth_get_type(&auth));

    PASS();
}

TEST
test_auth_set_type_null_pointer(void) {
    int status = rid_auth_set_type(NULL, RID_AUTH_TYPE_UAS_ID_SIGNATURE);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_auth_get_type_null_pointer(void) {
    ASSERT_EQ(RID_AUTH_TYPE_NONE, rid_auth_get_type(NULL));

    PASS();
}

TEST
test_auth_set_and_get_timestamp(void) {
    rid_auth_t auth;
    rid_auth_init(&auth);

    int status = rid_auth_set_timestamp(&auth, 0);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(0, rid_auth_get_timestamp(&auth));

    status = rid_auth_set_timestamp(&auth, 12345678);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(12345678, rid_auth_get_timestamp(&auth));

    PASS();
}

TEST
test_auth_set_timestamp_null_pointer(void) {
    int status = rid_auth_set_timestamp(NULL, 12345);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_auth_get_timestamp_null_pointer(void) {
    ASSERT_EQ(0, rid_auth_get_timestamp(NULL));

    PASS();
}

TEST
test_auth_set_and_get_unixtime(void) {
    rid_auth_t auth;
    rid_auth_init(&auth);

    /* 2019-01-01 00:00:00 UTC = epoch, should give 0 */
    int status = rid_auth_set_unixtime(&auth, 1546300800);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(0, rid_auth_get_timestamp(&auth));
    ASSERT_EQ(1546300800, rid_auth_get_unixtime(&auth));

    /* 2019-01-01 00:01:40 UTC = 100 seconds after epoch */
    status = rid_auth_set_unixtime(&auth, 1546300900);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(100, rid_auth_get_timestamp(&auth));
    ASSERT_EQ(1546300900, rid_auth_get_unixtime(&auth));

    PASS();
}

TEST
test_auth_set_unixtime_null_pointer(void) {
    int status = rid_auth_set_unixtime(NULL, 1546300800);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_auth_set_unixtime_before_epoch(void) {
    rid_auth_t auth;
    rid_auth_init(&auth);

    /* Before 2019-01-01 should fail */
    int status = rid_auth_set_unixtime(&auth, 1546300799);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_auth_get_unixtime_null_pointer(void) {
    ASSERT_EQ(0, rid_auth_get_unixtime(NULL));

    PASS();
}

TEST
test_auth_set_and_get_signature_short(void) {
    rid_auth_t auth;
    rid_auth_init(&auth);

    uint8_t signature[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
    uint8_t buffer[10];

    int status = rid_auth_set_signature(&auth, signature, 10);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(10, rid_auth_get_length(&auth));
    ASSERT_EQ(1, rid_auth_get_page_count(&auth));

    status = rid_auth_get_signature(&auth, buffer, 10);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_MEM_EQ(signature, buffer, 10);

    PASS();
}

TEST
test_auth_set_and_get_signature_full_page_0(void) {
    rid_auth_t auth;
    rid_auth_init(&auth);

    uint8_t signature[17] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11
    };
    uint8_t buffer[17];

    int status = rid_auth_set_signature(&auth, signature, 17);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(17, rid_auth_get_length(&auth));
    ASSERT_EQ(1, rid_auth_get_page_count(&auth));

    status = rid_auth_get_signature(&auth, buffer, 17);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_MEM_EQ(signature, buffer, 17);

    PASS();
}

TEST
test_auth_set_and_get_signature_two_pages(void) {
    rid_auth_t auth;
    rid_auth_init(&auth);
    rid_auth_set_type(&auth, RID_AUTH_TYPE_UAS_ID_SIGNATURE);

    uint8_t signature[40];
    for (size_t i = 0; i < 40; ++i) {
        signature[i] = (uint8_t)i;
    }
    uint8_t buffer[40];

    int status = rid_auth_set_signature(&auth, signature, 40);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(40, rid_auth_get_length(&auth));
    ASSERT_EQ(2, rid_auth_get_page_count(&auth));

    status = rid_auth_get_signature(&auth, buffer, 40);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_MEM_EQ(signature, buffer, 40);

    PASS();
}

TEST
test_auth_set_and_get_signature_max_size(void) {
    rid_auth_t auth;
    rid_auth_init(&auth);
    rid_auth_set_type(&auth, RID_AUTH_TYPE_SPECIFIC_METHOD);

    uint8_t signature[255];
    for (size_t i = 0; i < 255; ++i) {
        signature[i] = (uint8_t)(i & 0xFF);
    }
    uint8_t buffer[255];

    int status = rid_auth_set_signature(&auth, signature, 255);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(255, rid_auth_get_length(&auth));
    ASSERT_EQ(12, rid_auth_get_page_count(&auth));

    status = rid_auth_get_signature(&auth, buffer, 255);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_MEM_EQ(signature, buffer, 255);

    PASS();
}

TEST
test_auth_set_signature_null_pointer(void) {
    rid_auth_t auth;
    rid_auth_init(&auth);

    uint8_t signature[10] = {0};

    int status = rid_auth_set_signature(NULL, signature, 10);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_auth_set_signature(&auth, NULL, 10);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_auth_set_signature_too_large(void) {
    rid_auth_t auth;
    rid_auth_init(&auth);

    uint8_t signature[256];

    int status = rid_auth_set_signature(&auth, signature, 256);
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_LARGE, status);

    PASS();
}

TEST
test_auth_get_length_null_pointer(void) {
    ASSERT_EQ(0, rid_auth_get_length(NULL));

    PASS();
}

TEST
test_auth_get_signature_null_pointer(void) {
    rid_auth_t auth;
    rid_auth_init(&auth);

    uint8_t buffer[10];

    int status = rid_auth_get_signature(NULL, buffer, 10);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_auth_get_signature(&auth, NULL, 10);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_auth_get_signature_buffer_too_small(void) {
    rid_auth_t auth;
    rid_auth_init(&auth);

    uint8_t signature[20] = {0};
    uint8_t buffer[10];

    rid_auth_set_signature(&auth, signature, 20);

    int status = rid_auth_get_signature(&auth, buffer, 10);
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_SMALL, status);

    PASS();
}

TEST
test_auth_signature_preserves_type(void) {
    rid_auth_t auth;
    rid_auth_init(&auth);
    rid_auth_set_type(&auth, RID_AUTH_TYPE_OPERATOR_ID_SIGNATURE);

    uint8_t signature[40] = {0};
    rid_auth_set_signature(&auth, signature, 40);

    ASSERT_EQ(RID_AUTH_TYPE_OPERATOR_ID_SIGNATURE, rid_auth_get_type(&auth));
    ASSERT_EQ(RID_AUTH_TYPE_OPERATOR_ID_SIGNATURE, auth.page_x[0].auth_type);

    PASS();
}

SUITE(auth_suite) {
    RUN_TEST(test_auth_init);
    RUN_TEST(test_auth_get_page_count);
    RUN_TEST(test_auth_set_and_get_type);
    RUN_TEST(test_auth_set_type_null_pointer);
    RUN_TEST(test_auth_get_type_null_pointer);
    RUN_TEST(test_auth_set_and_get_timestamp);
    RUN_TEST(test_auth_set_timestamp_null_pointer);
    RUN_TEST(test_auth_get_timestamp_null_pointer);
    RUN_TEST(test_auth_set_and_get_unixtime);
    RUN_TEST(test_auth_set_unixtime_null_pointer);
    RUN_TEST(test_auth_set_unixtime_before_epoch);
    RUN_TEST(test_auth_get_unixtime_null_pointer);
    RUN_TEST(test_auth_set_and_get_signature_short);
    RUN_TEST(test_auth_set_and_get_signature_full_page_0);
    RUN_TEST(test_auth_set_and_get_signature_two_pages);
    RUN_TEST(test_auth_set_and_get_signature_max_size);
    RUN_TEST(test_auth_set_signature_null_pointer);
    RUN_TEST(test_auth_set_signature_too_large);
    RUN_TEST(test_auth_get_length_null_pointer);
    RUN_TEST(test_auth_get_signature_null_pointer);
    RUN_TEST(test_auth_get_signature_buffer_too_small);
    RUN_TEST(test_auth_signature_preserves_type);
}
