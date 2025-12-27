#include <stdint.h>
#include <string.h>

#include "greatest.h"
#include "rid/message.h"
#include "rid/auth_page.h"
#include "rid/auth.h"

TEST
test_auth_data_init(void) {
    rid_auth_data_t auth;

    int status = rid_auth_data_init(NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_auth_data_init(&auth);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(1, auth.page_count);
    ASSERT_EQ(RID_PROTOCOL_VERSION_2, auth.page_0.protocol_version);
    ASSERT_EQ(RID_MESSAGE_TYPE_AUTH, auth.page_0.message_type);
    ASSERT_EQ(0, auth.page_0.page_number);

    PASS();
}

TEST
test_auth_data_set_null_pointer(void) {
    rid_auth_data_t auth;
    uint8_t data[17] = {0};

    int status = rid_auth_data_set(NULL, RID_AUTH_TYPE_NONE, 0, data, sizeof(data));
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_auth_data_set(&auth, RID_AUTH_TYPE_NONE, 0, NULL, 17);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_auth_data_set_too_large(void) {
    rid_auth_data_t auth;
    uint8_t data[256] = {0};

    int status = rid_auth_data_set(&auth, RID_AUTH_TYPE_NONE, 0, data, sizeof(data));
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_LARGE, status);

    PASS();
}

TEST
test_auth_data_set_single_page(void) {
    rid_auth_data_t auth;
    uint8_t data[17] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
        0x11
    };
    uint32_t timestamp = 12345678;

    int status = rid_auth_data_set(&auth, RID_AUTH_TYPE_UAS_ID_SIGNATURE,
                                   timestamp, data, sizeof(data));
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(1, rid_auth_data_get_page_count(&auth));
    ASSERT_EQ(RID_AUTH_TYPE_UAS_ID_SIGNATURE, rid_auth_page_0_get_type(&auth.page_0));
    ASSERT_EQ(timestamp, rid_auth_page_0_get_timestamp(&auth.page_0));
    ASSERT_EQ(17, rid_auth_page_0_get_length(&auth.page_0));
    ASSERT_EQ(0, rid_auth_page_0_get_last_page_index(&auth.page_0));

    PASS();
}

TEST
test_auth_data_set_two_pages(void) {
    rid_auth_data_t auth;
    uint8_t data[40] = {0};

    for (size_t i = 0; i < sizeof(data); ++i) {
        data[i] = (uint8_t)i;
    }

    int status = rid_auth_data_set(&auth, RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE,
                                   0, data, sizeof(data));
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(2, rid_auth_data_get_page_count(&auth));
    ASSERT_EQ(40, rid_auth_page_0_get_length(&auth.page_0));
    ASSERT_EQ(1, rid_auth_page_0_get_last_page_index(&auth.page_0));

    ASSERT_EQ(RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE, rid_auth_page_x_get_type(&auth.page_x[0]));
    ASSERT_EQ(1, rid_auth_page_x_get_number(&auth.page_x[0]));

    PASS();
}

TEST
test_auth_data_set_multiple_pages(void) {
    rid_auth_data_t auth;
    uint8_t data[100] = {0};

    for (size_t i = 0; i < sizeof(data); ++i) {
        data[i] = (uint8_t)(i & 0xFF);
    }

    int status = rid_auth_data_set(&auth, RID_AUTH_TYPE_NETWORK_REMOTE_ID,
                                   0, data, sizeof(data));
    ASSERT_EQ(RID_SUCCESS, status);

    /* 17 + 23 + 23 + 23 + 14 = 100, so 5 pages */
    ASSERT_EQ(5, rid_auth_data_get_page_count(&auth));
    ASSERT_EQ(100, rid_auth_page_0_get_length(&auth.page_0));
    ASSERT_EQ(4, rid_auth_page_0_get_last_page_index(&auth.page_0));

    for (uint8_t i = 0; i < 4; ++i) {
        ASSERT_EQ(i + 1, rid_auth_page_x_get_number(&auth.page_x[i]));
        ASSERT_EQ(RID_AUTH_TYPE_NETWORK_REMOTE_ID, rid_auth_page_x_get_type(&auth.page_x[i]));
    }

    PASS();
}

TEST
test_auth_data_set_max_size(void) {
    rid_auth_data_t auth;
    uint8_t data[255];

    /* Electrolytes, its what plants crave */
    for (size_t i = 0; i < sizeof(data); ++i) {
        data[i] = (uint8_t)(i & 0xFF);
    }

    int status = rid_auth_data_set(&auth, RID_AUTH_TYPE_SPECIFIC_METHOD,
                                   0, data, sizeof(data));
    ASSERT_EQ(RID_SUCCESS, status);

    /* 17 + 10*23 + 8 = 255, so 12 pages */
    ASSERT_EQ(12, rid_auth_data_get_page_count(&auth));
    ASSERT_EQ(255, rid_auth_page_0_get_length(&auth.page_0));
    ASSERT_EQ(11, rid_auth_page_0_get_last_page_index(&auth.page_0));

    PASS();
}

TEST
test_auth_data_get(void) {
    rid_auth_data_t auth;
    uint8_t input[64];
    uint8_t output[64];
    size_t output_size = 0;

    for (size_t i = 0; i < sizeof(input); ++i) {
        input[i] = (uint8_t)(i * 3);
    }

    int status = rid_auth_data_set(&auth, RID_AUTH_TYPE_UAS_ID_SIGNATURE,
                                   98765, input, sizeof(input));
    ASSERT_EQ(RID_SUCCESS, status);

    status = rid_auth_data_get(&auth, output, sizeof(output), &output_size);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(64, output_size);
    ASSERT_MEM_EQ(input, output, sizeof(input));

    PASS();
}

TEST
test_auth_data_get_null_pointer(void) {
    rid_auth_data_t auth;
    uint8_t buffer[64];
    size_t size;

    rid_auth_data_init(&auth);

    int status = rid_auth_data_get(NULL, buffer, sizeof(buffer), &size);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_auth_data_get(&auth, NULL, 64, &size);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_auth_data_get_buffer_too_small(void) {
    rid_auth_data_t auth;
    uint8_t input[64] = {0};
    uint8_t output[32];
    size_t size;

    rid_auth_data_set(&auth, RID_AUTH_TYPE_NONE, 0, input, sizeof(input));

    int status = rid_auth_data_get(&auth, output, sizeof(output), &size);
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_SMALL, status);

    PASS();
}

TEST
test_auth_data_get_page_count(void) {
    rid_auth_data_t auth;
    uint8_t data[50] = {0};

    ASSERT_EQ(0, rid_auth_data_get_page_count(NULL));

    rid_auth_data_init(&auth);
    ASSERT_EQ(1, rid_auth_data_get_page_count(&auth));

    rid_auth_data_set(&auth, RID_AUTH_TYPE_NONE, 0, data, 17);
    ASSERT_EQ(1, rid_auth_data_get_page_count(&auth));

    rid_auth_data_set(&auth, RID_AUTH_TYPE_NONE, 0, data, 18);
    ASSERT_EQ(2, rid_auth_data_get_page_count(&auth));

    rid_auth_data_set(&auth, RID_AUTH_TYPE_NONE, 0, data, 40);
    ASSERT_EQ(2, rid_auth_data_get_page_count(&auth));

    rid_auth_data_set(&auth, RID_AUTH_TYPE_NONE, 0, data, 41);
    ASSERT_EQ(3, rid_auth_data_get_page_count(&auth));

    PASS();
}

TEST
test_auth_data_roundtrip_single_page(void) {
    rid_auth_data_t auth;
    const char *input = "Welcome to CostCo";
    uint8_t output[32];
    size_t size;

    int status = rid_auth_data_set(&auth, RID_AUTH_TYPE_OPERATOR_ID_SIGNATURE,
                                   500, (const uint8_t *)input, strlen(input));
    ASSERT_EQ(RID_SUCCESS, status);

    status = rid_auth_data_get(&auth, output, sizeof(output), &size);
    ASSERT_EQ(RID_SUCCESS, status);
    ASSERT_EQ(strlen(input), size);
    ASSERT_MEM_EQ(input, output, size);

    PASS();
}

SUITE(auth_suite) {
    RUN_TEST(test_auth_data_init);
    RUN_TEST(test_auth_data_set_null_pointer);
    RUN_TEST(test_auth_data_set_too_large);
    RUN_TEST(test_auth_data_set_single_page);
    RUN_TEST(test_auth_data_set_two_pages);
    RUN_TEST(test_auth_data_set_multiple_pages);
    RUN_TEST(test_auth_data_set_max_size);
    RUN_TEST(test_auth_data_get);
    RUN_TEST(test_auth_data_get_null_pointer);
    RUN_TEST(test_auth_data_get_buffer_too_small);
    RUN_TEST(test_auth_data_get_page_count);
    RUN_TEST(test_auth_data_roundtrip_single_page);
}
