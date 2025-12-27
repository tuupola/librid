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
    ASSERT_EQ(1, auth.page_count);
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
}
