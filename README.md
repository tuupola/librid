# Usage
## Build examples

```
$ mkdir build && cd build
$ cmake -DRID_BUILD_EXAMPLES=ON ..
$ make
```

## Build and run tests

```
$ mkdir build && cd build
$ cmake -DRID_BUILD_TESTS=ON ..
$ make
$ ctest
```

## Message header
If you have captured a Remote ID message you can find the message type and
protocol version.

```c
#include <stdio.h>
#include "rid/message.h"
#include "rid/basic_id.h"

/* Captured Basic ID message bytes */
uint8_t buffer[] = {
    0x02, 0x12, 0x44, 0x4a, 0x49, 0x2d, 0x50, 0x48,
    0x41, 0x4e, 0x54, 0x4f, 0x4d, 0x2d, 0x34, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00
};

rid_message_type_t type = rid_get_message_type(buffer);
rid_protocol_version_t version = rid_get_protocol_version(buffer);

printf("Message type: %d Protocol version: %d ", type, version);

if (type == RID_MESSAGE_TYPE_BASIC_ID) {
    rid_basic_id_t *basic_id = (rid_basic_id_t *)buffer;
    rid_ua_type_t ua_type = rid_get_ua_type(&message);
    printf("UA type: %d\n", ua_type);
}
```
There is also setter for both, but you generally do not need to use them.

## Basic ID message

To create a Basic ID message, create a `rid_basic_id_t` structure and initialize it:

```c
#include "rid/basic_id.h"
#include "rid/message.h"

rid_basic_id_t message;

/* Initialize the message */
rid_error_t status = rid_basic_id_init(&message);
if (status != RID_SUCCESS) {
    /* Handle error */
}

/* Configure the message */
rid_set_basic_id_type(&message, RID_ID_TYPE_SERIAL_NUMBER);
rid_set_ua_type(&message, RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR);
rid_set_uas_id(&message, "DJI-PHANTOM-4");

/* Message is now ready to transmit */
```

You can read the values for example from a captured message. See all possible values in [message.h](include/rid/message.h) and [basic_id.h](include/rid/basic_id.h) files.

```c
rid_message_type_t type = rid_get_message_type(&message);
rid_protocol_version_t protocol = rid_get_protocol_version(&message);

rid_basic_id_type_t id_type = rid_get_basic_id_type(&message);
rid_ua_type_t ua_type = rid_get_ua_type(&message);

char uas_id[21];
status = rid_get_uas_id(&message, uas_id, sizeof(uas_id));
if (status == RID_SUCCESS) {
    printf("UAS ID: %s\n", uas_id);
}
```

## Error handling

All setter functions return `rid_error_t`. See all return values in [message.h](include/rid/message.h) file.
