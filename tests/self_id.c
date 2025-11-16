#include <string.h>

#include "greatest.h"
#include "rid/header.h"
#include "rid/self_id.h"

TEST
test_set_and_get_description_type(void) {
    rid_description_type_t types[] = {
        RID_DESCRIPTION_TYPE_TEXT,
        RID_DESCRIPTION_TYPE_EMERGENCY,
        RID_DESCRIPTION_TYPE_EXTENDED_STATUS
    };

    for (size_t i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
        rid_self_id_t message;

        memset(&message, 0, sizeof(message));
        rid_error_t status = rid_set_description_type(&message, types[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        rid_description_type_t result = rid_get_description_type(&message);

        ASSERT_EQ(types[i], result);
    }

    PASS();
}

TEST
test_set_and_get_description(void) {
    const char *test_descriptions[] = {
        "Kakotron:Survey",
        "12345678901234567890123",
        "Bearmetal photo shoot",
        "",
        "X"
    };

    for (size_t i = 0; i < sizeof(test_descriptions) / sizeof(test_descriptions[0]); i++) {
        rid_self_id_t message;
        rid_error_t status;

        memset(&message, 0, sizeof(message));

        status = rid_set_description(&message, test_descriptions[i]);
        ASSERT_EQ(RID_SUCCESS, status);

        char buffer[24];
        status = rid_get_description(&message, buffer, sizeof(buffer));
        ASSERT_EQ(RID_SUCCESS, status);

        ASSERT_STR_EQ(test_descriptions[i], buffer);
    }

    PASS();
}

TEST
test_set_description_must_be_ascii(void) {
    rid_self_id_t message;
    rid_error_t status;

    memset(&message, 0, sizeof(message));

    /* Test with non-ASCII character (UTF-8 encoded) */
    status = rid_set_description(&message, "TEST\xC3\xA4");
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    /* Test with character > 127 */
    status = rid_set_description(&message, "TEST\xFF");
    ASSERT_EQ(RID_ERROR_INVALID_CHARACTER, status);

    /* Test valid ASCII */
    status = rid_set_description(&message, "All your base are");
    ASSERT_EQ(RID_SUCCESS, status);

    PASS();
}

TEST
test_set_description_too_long(void) {
    rid_self_id_t message;
    rid_error_t status;

    memset(&message, 0, sizeof(message));

    /* Test with description > 23 characters */
    status = rid_set_description(&message, "All your base are belong to us...");
    ASSERT_EQ(RID_ERROR_BUFFER_TOO_LARGE, status);

    PASS();
}

SUITE(self_id_suite) {
    RUN_TEST(test_set_and_get_description_type);
    RUN_TEST(test_set_and_get_description);
    RUN_TEST(test_set_description_must_be_ascii);
    RUN_TEST(test_set_description_too_long);
}
