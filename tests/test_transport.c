#include "greatest.h"
#include "rid/transport.h"

TEST
test_transport_to_string(void)
{
    ASSERT_STR_EQ("RID_TRANSPORT_BLUETOOTH_LEGACY", rid_transport_to_string(RID_TRANSPORT_BLUETOOTH_LEGACY));
    ASSERT_STR_EQ("RID_TRANSPORT_BLUETOOTH_LONG_RANGE", rid_transport_to_string(RID_TRANSPORT_BLUETOOTH_LONG_RANGE));
    ASSERT_STR_EQ("RID_TRANSPORT_WIFI_NAN", rid_transport_to_string(RID_TRANSPORT_WIFI_NAN));
    ASSERT_STR_EQ("RID_TRANSPORT_WIFI_BEACON", rid_transport_to_string(RID_TRANSPORT_WIFI_BEACON));
    ASSERT_STR_EQ("UNKNOWN", rid_transport_to_string((rid_transport_t)99));
    PASS();
}

SUITE(transport_suite)
{
    RUN_TEST(test_transport_to_string);
}
