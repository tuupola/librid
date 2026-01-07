#include <stdint.h>
#include <string.h>

#include "greatest.h"
#include "rid/message.h"
#include "rid/auth_page.h"

TEST
test_auth_init(void) {
    rid_auth_page_0_t message;

    int status = rid_auth_page_0_init(NULL);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_auth_page_0_init(&message);
    ASSERT_EQ(RID_SUCCESS, status);

    ASSERT_EQ(RID_PROTOCOL_VERSION_2, message.protocol_version);
    ASSERT_EQ(RID_MESSAGE_TYPE_AUTH, message.message_type);
    ASSERT_EQ(0, message.page_number);
    ASSERT_EQ(RID_AUTH_TYPE_NONE, message.auth_type);
    ASSERT_EQ(0, message.last_page_index);
    ASSERT_EQ(0, message.length);
    ASSERT_EQ(0, message.timestamp);

    for (size_t i = 0; i < RID_AUTH_PAGE_0_DATA_SIZE; ++i) {
        ASSERT_EQ(0, message.auth_data[i]);
    }

    PASS();
}

TEST
test_auth_page_init(void) {
    rid_auth_page_x_t message;

    int status = rid_auth_page_x_init(NULL, 1);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    /* Page 0 is invalid for rid_auth_page_x_t */
    status = rid_auth_page_x_init(&message, 0);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    /* Page 16 is out of range */
    status = rid_auth_page_x_init(&message, 16);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    /* Valid pages 1-15 */
    for (uint8_t page = 1; page <= 15; ++page) {
        status = rid_auth_page_x_init(&message, page);
        ASSERT_EQ(RID_SUCCESS, status);
        ASSERT_EQ(RID_PROTOCOL_VERSION_2, message.protocol_version);
        ASSERT_EQ(RID_MESSAGE_TYPE_AUTH, message.message_type);
        ASSERT_EQ(page, message.page_number);
    }

    PASS();
}

TEST
test_set_and_get_auth_type(void) {
    rid_auth_type_t types[] = {
        RID_AUTH_TYPE_NONE,
        RID_AUTH_TYPE_UAS_ID_SIGNATURE,
        RID_AUTH_TYPE_OPERATOR_ID_SIGNATURE,
        RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE,
        RID_AUTH_TYPE_NETWORK_REMOTE_ID,
        RID_AUTH_TYPE_SPECIFIC_METHOD
    };

    for (size_t i = 0; i < sizeof(types) / sizeof(types[0]); ++i) {
        rid_auth_page_0_t message;
        rid_auth_page_0_init(&message);

        int status = rid_auth_page_0_set_type(&message, types[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        rid_auth_type_t result = rid_auth_page_0_get_type(&message);
        ASSERT_EQ(types[i], result);
    }

    PASS();
}

TEST
test_set_and_get_auth_type_null_pointer(void) {
    int status = rid_auth_page_0_set_type(NULL, RID_AUTH_TYPE_UAS_ID_SIGNATURE);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    rid_auth_type_t type = rid_auth_page_0_get_type(NULL);
    ASSERT_EQ(RID_AUTH_TYPE_NONE, type);

    PASS();
}

TEST
test_set_auth_type_out_of_range(void) {
    rid_auth_page_0_t message;
    rid_auth_page_0_init(&message);

    int status = rid_auth_page_0_set_type(&message, RID_AUTH_TYPE_MAX + 1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_auth_page_0_set_type(&message, UINT8_MAX);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_and_get_auth_last_page_index(void) {
    rid_auth_page_0_t message;
    rid_auth_page_0_init(&message);

    for (uint8_t index = 0; index <= RID_AUTH_MAX_PAGE_INDEX; ++index) {
        int status = rid_auth_page_0_set_last_page_index(&message, index);
        ASSERT_EQ(RID_SUCCESS, status);

        uint8_t result = rid_auth_page_0_get_last_page_index(&message);
        ASSERT_EQ(index, result);
    }

    PASS();
}

TEST
test_set_and_get_auth_last_page_index_null_pointer(void) {
    int status = rid_auth_page_0_set_last_page_index(NULL, 5);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    uint8_t index = rid_auth_page_0_get_last_page_index(NULL);
    ASSERT_EQ(0, index);

    PASS();
}

TEST
test_set_auth_last_page_index_out_of_range(void) {
    rid_auth_page_0_t message;
    rid_auth_page_0_init(&message);

    int status = rid_auth_page_0_set_last_page_index(&message, 16);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    status = rid_auth_page_0_set_last_page_index(&message, UINT8_MAX);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_get_auth_last_page_index_reserved_bits(void) {
    rid_auth_page_0_t message;
    rid_auth_page_0_init(&message);

    /* Simulate external data with garbage in reserved bits [7..4] */
    message.last_page_index = 0xF5;

    uint8_t result = rid_auth_page_0_get_last_page_index(&message);
    ASSERT_EQ(5, result);

    message.last_page_index = 0xAF;
    result = rid_auth_page_0_get_last_page_index(&message);
    ASSERT_EQ(15, result);

    message.last_page_index = 0x80;
    result = rid_auth_page_0_get_last_page_index(&message);
    ASSERT_EQ(0, result);

    PASS();
}

TEST
test_set_and_get_auth_length(void) {
    rid_auth_page_0_t message;
    rid_auth_page_0_init(&message);

    uint8_t test_lengths[] = {0, 17, 40, 109, 255};

    for (size_t i = 0; i < sizeof(test_lengths) / sizeof(test_lengths[0]); ++i) {
        int status = rid_auth_page_0_set_length(&message, test_lengths[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        uint8_t result = rid_auth_page_0_get_length(&message);
        ASSERT_EQ(test_lengths[i], result);
    }

    PASS();
}

TEST
test_set_and_get_auth_length_null_pointer(void) {
    int status = rid_auth_page_0_set_length(NULL, 42);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    uint8_t length = rid_auth_page_0_get_length(NULL);
    ASSERT_EQ(0, length);

    PASS();
}

TEST
test_set_and_get_auth_timestamp(void) {
    rid_auth_page_0_t message;
    rid_auth_page_0_init(&message);

    uint32_t test_timestamps[] = {0, 1, 86400, 31536000, UINT32_MAX};

    for (size_t i = 0; i < sizeof(test_timestamps) / sizeof(test_timestamps[0]); ++i) {
        int status = rid_auth_page_0_set_timestamp(&message, test_timestamps[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        uint32_t result = rid_auth_page_0_get_timestamp(&message);
        ASSERT_EQ(test_timestamps[i], result);
    }

    PASS();
}

TEST
test_set_and_get_auth_timestamp_null_pointer(void) {
    int status = rid_auth_page_0_set_timestamp(NULL, 12345);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    uint32_t timestamp = rid_auth_page_0_get_timestamp(NULL);
    ASSERT_EQ(0, timestamp);

    PASS();
}

TEST
test_set_and_get_auth_data(void) {
    rid_auth_page_0_t message;
    rid_auth_page_0_init(&message);

    uint8_t test_data[RID_AUTH_PAGE_0_DATA_SIZE] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
        0x11
    };

    int status = rid_auth_page_0_set_data(&message, test_data, sizeof(test_data));
    ASSERT_EQ(RID_SUCCESS, status);

    uint8_t buffer[RID_AUTH_PAGE_0_DATA_SIZE];
    status = rid_auth_page_0_get_data(&message, buffer, sizeof(buffer));
    ASSERT_EQ(RID_SUCCESS, status);

    ASSERT_MEM_EQ(test_data, buffer, RID_AUTH_PAGE_0_DATA_SIZE);

    PASS();
}

TEST
test_set_auth_data_partial(void) {
    rid_auth_page_0_t message;
    rid_auth_page_0_init(&message);

    uint8_t test_data[] = {0xDE, 0xAD, 0xBE, 0xEF};

    int status = rid_auth_page_0_set_data(&message, test_data, sizeof(test_data));
    ASSERT_EQ(RID_SUCCESS, status);

    uint8_t buffer[RID_AUTH_PAGE_0_DATA_SIZE];
    status = rid_auth_page_0_get_data(&message, buffer, sizeof(buffer));
    ASSERT_EQ(RID_SUCCESS, status);

    ASSERT_MEM_EQ(test_data, buffer, sizeof(test_data));

    /* Remaining bytes should be zero */
    for (size_t i = sizeof(test_data); i < RID_AUTH_PAGE_0_DATA_SIZE; ++i) {
        ASSERT_EQ(0, buffer[i]);
    }

    PASS();
}

TEST
test_set_and_get_auth_data_null_pointer(void) {
    rid_auth_page_0_t message;
    rid_auth_page_0_init(&message);
    uint8_t data[4] = {0};
    uint8_t buffer[RID_AUTH_PAGE_0_DATA_SIZE];

    int status = rid_auth_page_0_set_data(NULL, data, sizeof(data));
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_auth_page_0_set_data(&message, NULL, 4);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_auth_page_0_get_data(NULL, buffer, sizeof(buffer));
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_auth_page_0_get_data(&message, NULL, RID_AUTH_PAGE_0_DATA_SIZE);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_auth_data_too_large(void) {
    rid_auth_page_0_t message;
    rid_auth_page_0_init(&message);
    uint8_t data[RID_AUTH_PAGE_0_DATA_SIZE + 1] = {0};

    int status = rid_auth_page_0_set_data(&message, data, sizeof(data));
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_LARGE, status);

    PASS();
}

TEST
test_get_auth_data_buffer_too_small(void) {
    rid_auth_page_0_t message;
    rid_auth_page_0_init(&message);
    uint8_t buffer[RID_AUTH_PAGE_0_DATA_SIZE - 1];

    int status = rid_auth_page_0_get_data(&message, buffer, sizeof(buffer));
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_SMALL, status);

    PASS();
}

TEST
test_set_and_get_auth_page_type(void) {
    rid_auth_page_x_t message;
    rid_auth_page_x_init(&message, 1);

    rid_auth_type_t types[] = {
        RID_AUTH_TYPE_NONE,
        RID_AUTH_TYPE_UAS_ID_SIGNATURE,
        RID_AUTH_TYPE_OPERATOR_ID_SIGNATURE,
        RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE
    };

    for (size_t i = 0; i < sizeof(types) / sizeof(types[0]); ++i) {
        int status = rid_auth_page_x_set_type(&message, types[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        rid_auth_type_t result = rid_auth_page_x_get_type(&message);
        ASSERT_EQ(types[i], result);
    }

    PASS();
}

TEST
test_set_and_get_auth_page_type_null_pointer(void) {
    int status = rid_auth_page_x_set_type(NULL, RID_AUTH_TYPE_UAS_ID_SIGNATURE);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    rid_auth_type_t type = rid_auth_page_x_get_type(NULL);
    ASSERT_EQ(RID_AUTH_TYPE_NONE, type);

    PASS();
}

TEST
test_set_auth_page_type_out_of_range(void) {
    rid_auth_page_x_t message;
    rid_auth_page_x_init(&message, 1);

    int status = rid_auth_page_x_set_type(&message, RID_AUTH_TYPE_MAX + 1);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_and_get_auth_page_number(void) {
    rid_auth_page_x_t message;
    rid_auth_page_x_init(&message, 1);

    for (uint8_t page = 1; page <= RID_AUTH_MAX_PAGE_INDEX; ++page) {
        int status = rid_auth_page_x_set_number(&message, page);
        ASSERT_EQ(RID_SUCCESS, status);

        uint8_t result = rid_auth_page_x_get_number(&message);
        ASSERT_EQ(page, result);
    }

    PASS();
}

TEST
test_set_and_get_auth_page_number_null_pointer(void) {
    int status = rid_auth_page_x_set_number(NULL, 5);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    uint8_t page = rid_auth_page_x_get_number(NULL);
    ASSERT_EQ(0, page);

    PASS();
}

TEST
test_set_auth_page_number_out_of_range(void) {
    rid_auth_page_x_t message;
    rid_auth_page_x_init(&message, 1);

    /* Page 0 is invalid */
    int status = rid_auth_page_x_set_number(&message, 0);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    /* Page 16 is out of range */
    status = rid_auth_page_x_set_number(&message, 16);
    ASSERT_EQ(RID_ERROR_OUT_OF_RANGE, status);

    PASS();
}

TEST
test_set_and_get_auth_page_data(void) {
    rid_auth_page_x_t message;
    rid_auth_page_x_init(&message, 1);

    uint8_t test_data[RID_AUTH_PAGE_DATA_SIZE] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17
    };

    int status = rid_auth_page_x_set_data(&message, test_data, sizeof(test_data));
    ASSERT_EQ(RID_SUCCESS, status);

    uint8_t buffer[RID_AUTH_PAGE_DATA_SIZE];
    status = rid_auth_page_x_get_data(&message, buffer, sizeof(buffer));
    ASSERT_EQ(RID_SUCCESS, status);

    ASSERT_MEM_EQ(test_data, buffer, RID_AUTH_PAGE_DATA_SIZE);

    PASS();
}

TEST
test_set_and_get_auth_page_data_null_pointer(void) {
    rid_auth_page_x_t message;
    rid_auth_page_x_init(&message, 1);
    uint8_t data[4] = {0};
    uint8_t buffer[RID_AUTH_PAGE_DATA_SIZE];

    int status = rid_auth_page_x_set_data(NULL, data, sizeof(data));
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_auth_page_x_set_data(&message, NULL, 4);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_auth_page_x_get_data(NULL, buffer, sizeof(buffer));
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    status = rid_auth_page_x_get_data(&message, NULL, RID_AUTH_PAGE_DATA_SIZE);
    ASSERT_EQ(RID_ERROR_NULL_POINTER, status);

    PASS();
}

TEST
test_set_auth_page_data_too_large(void) {
    rid_auth_page_x_t message;
    rid_auth_page_x_init(&message, 1);
    uint8_t data[RID_AUTH_PAGE_DATA_SIZE + 1] = {0};

    int status = rid_auth_page_x_set_data(&message, data, sizeof(data));
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_LARGE, status);

    PASS();
}

TEST
test_get_auth_page_data_buffer_too_small(void) {
    rid_auth_page_x_t message;
    rid_auth_page_x_init(&message, 1);
    uint8_t buffer[RID_AUTH_PAGE_DATA_SIZE - 1];

    int status = rid_auth_page_x_get_data(&message, buffer, sizeof(buffer));
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_SMALL, status);

    PASS();
}

TEST
test_auth_type_to_string(void) {
    ASSERT_STR_EQ("RID_AUTH_TYPE_NONE", rid_auth_type_to_string(RID_AUTH_TYPE_NONE));
    ASSERT_STR_EQ("RID_AUTH_TYPE_UAS_ID_SIGNATURE", rid_auth_type_to_string(RID_AUTH_TYPE_UAS_ID_SIGNATURE));
    ASSERT_STR_EQ("RID_AUTH_TYPE_OPERATOR_ID_SIGNATURE", rid_auth_type_to_string(RID_AUTH_TYPE_OPERATOR_ID_SIGNATURE));
    ASSERT_STR_EQ("RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE", rid_auth_type_to_string(RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE));
    ASSERT_STR_EQ("RID_AUTH_TYPE_NETWORK_REMOTE_ID", rid_auth_type_to_string(RID_AUTH_TYPE_NETWORK_REMOTE_ID));
    ASSERT_STR_EQ("RID_AUTH_TYPE_SPECIFIC_METHOD", rid_auth_type_to_string(RID_AUTH_TYPE_SPECIFIC_METHOD));
    ASSERT_STR_EQ("UNKNOWN", rid_auth_type_to_string((rid_auth_type_t)99));
    PASS();
}

SUITE(auth_page_suite) {
    RUN_TEST(test_auth_init);
    RUN_TEST(test_auth_page_init);

    RUN_TEST(test_set_and_get_auth_type);
    RUN_TEST(test_set_and_get_auth_type_null_pointer);
    RUN_TEST(test_set_auth_type_out_of_range);

    RUN_TEST(test_set_and_get_auth_last_page_index);
    RUN_TEST(test_set_and_get_auth_last_page_index_null_pointer);
    RUN_TEST(test_set_auth_last_page_index_out_of_range);
    RUN_TEST(test_get_auth_last_page_index_reserved_bits);

    RUN_TEST(test_set_and_get_auth_length);
    RUN_TEST(test_set_and_get_auth_length_null_pointer);

    RUN_TEST(test_set_and_get_auth_timestamp);
    RUN_TEST(test_set_and_get_auth_timestamp_null_pointer);

    RUN_TEST(test_set_and_get_auth_data);
    RUN_TEST(test_set_auth_data_partial);
    RUN_TEST(test_set_and_get_auth_data_null_pointer);
    RUN_TEST(test_set_auth_data_too_large);
    RUN_TEST(test_get_auth_data_buffer_too_small);

    RUN_TEST(test_set_and_get_auth_page_type);
    RUN_TEST(test_set_and_get_auth_page_type_null_pointer);
    RUN_TEST(test_set_auth_page_type_out_of_range);

    RUN_TEST(test_set_and_get_auth_page_number);
    RUN_TEST(test_set_and_get_auth_page_number_null_pointer);
    RUN_TEST(test_set_auth_page_number_out_of_range);

    RUN_TEST(test_set_and_get_auth_page_data);
    RUN_TEST(test_set_and_get_auth_page_data_null_pointer);
    RUN_TEST(test_set_auth_page_data_too_large);
    RUN_TEST(test_get_auth_page_data_buffer_too_small);

    RUN_TEST(test_auth_type_to_string);
}
