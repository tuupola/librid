#include <string.h>

#include "greatest.h"
#include "rid/header.h"
#include "rid/operator_id.h"

TEST
test_set_and_get_operator_id_type(void) {
    rid_operator_id_type_t types[] = {
        RID_ID_TYPE_OPERATOR_ID
    };

    for (size_t i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
        rid_operator_id_t message;

        memset(&message, 0, sizeof(message));
        rid_error_t status = rid_set_operator_id_type(&message, types[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        rid_operator_id_type_t result = rid_get_operator_id_type(&message);

        ASSERT_EQ(types[i], result);
    }

    PASS();
}

TEST
test_set_and_get_operator_id(void) {
    const char *test_ids[] = {
        "ABC123",
        "12345678901234567890",
        "TEST-ID",
        "",
        "X"
    };

    for (size_t i = 0; i < sizeof(test_ids) / sizeof(test_ids[0]); i++) {
        rid_operator_id_t message;
        rid_error_t status;

        memset(&message, 0, sizeof(message));

        status = rid_set_operator_id(&message, test_ids[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        char buffer[21];
        status = rid_get_operator_id(&message, buffer, sizeof(buffer));
        ASSERT_EQ(RID_SUCCESS, status);

        ASSERT_STR_EQ(test_ids[i], buffer);
    }

    PASS();
}

TEST
test_set_operator_id_must_be_ascii(void) {
    rid_operator_id_t message;
    rid_error_t status;

    memset(&message, 0, sizeof(message));

    /* Test with non-ASCII character (UTF-8 encoded) */
    status = rid_set_operator_id(&message, "TEST\xC3\xA4");
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    /* Test with character > 127 */
    status = rid_set_operator_id(&message, "TEST\xFF");
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    /* Test valid ASCII */
    status = rid_set_operator_id(&message, "BRAWND0");
    ASSERT_EQ(RID_SUCCESS, status);

    PASS();
}

SUITE(operator_id_suite) {
    RUN_TEST(test_set_and_get_operator_id_type);
    RUN_TEST(test_set_and_get_operator_id);
    RUN_TEST(test_set_operator_id_must_be_ascii);
}
