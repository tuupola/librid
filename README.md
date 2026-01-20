# [WIP] librid

An ASTM F3411 message encoding and decoding library written in C programming language.

The library provides struct definitions for all Remote ID messages. It also provides getter and setter functions for all members of the structure. You should not access the struct members directly. Instead use the provided functions which will decode and encode the data to and from the correct wire format.

## Important

This is a read only mirror of the repository. Actual developing happens elsewhere. I do monitor the bug reports, feature requests and any discussion here though.


# Message types
## Basic ID (0x00)
Provides UAS identification (serial number, registration ID, or UUID) and characterizes the aircraft type.

```c
rid_basic_id_t basic_id;

rid_basic_id_init(&basic_id);
rid_basic_id_set_type(&basic_id, RID_ID_TYPE_SERIAL_NUMBER);
rid_basic_id_set_ua_type(&basic_id, RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR);
rid_basic_id_set_uas_id(&basic_id, "1ABCD2345EF678XYZ");
```

See [examples/basic_id/](examples/basic_id/) for full example.

## Location (0x01)
Contains current position, altitude, speed, direction, and timestamp of the UA.

```c
rid_location_t location;

rid_location_init(&location);
rid_location_set_latitude(&location, 60.1699);
rid_location_set_longitude(&location, 24.9384);
rid_location_set_geodetic_altitude(&location, 120.5f);
rid_location_set_speed(&location, 15.5f);
```

See [examples/location/](examples/location/) for full example.

## Auth (0x02)
Provides authentication data for verifying the identity of the UA sending the message.

```c
rid_auth_t auth;

rid_auth_init(&auth);
rid_auth_set_type(&auth, RID_AUTH_TYPE_UAS_ID_SIGNATURE);
rid_auth_set_unixtime(&auth, (uint32_t)time(NULL));
rid_auth_set_signature(&auth, signature, sizeof(signature));
```

See [examples/auth/](examples/auth/) for full example.

## Self ID (0x03)
Allows operators to declare their identity or describe the purpose of a flight.

```c
rid_self_id_t self_id;

rid_self_id_init(&self_id);
rid_self_id_set_description_type(&self_id, RID_DESCRIPTION_TYPE_TEXT);
rid_self_id_set_description(&self_id, "Drone delivery test");
```

See [examples/self_id/](examples/self_id/) for full example.

## System (0x04)
Contains remote pilot location, operating area details, and group aircraft information.

```c
rid_system_t system;

rid_system_init(&system);
rid_system_set_operator_location_type(&system, RID_OPERATOR_LOCATION_TYPE_TAKEOFF);
rid_system_set_operator_latitude(&system, 60.2870324);
rid_system_set_operator_longitude(&system, 24.5397187);
rid_system_set_operator_altitude(&system, 50.0f);
```

See [examples/system/](examples/system/) for full example.

## Operator ID (0x05)
Provides CAA-issued registration or license ID for the remote pilot or operator.

```c
rid_operator_id_t operator_id;

rid_operator_id_init(&operator_id);
rid_operator_id_set_type(&operator_id, RID_ID_TYPE_OPERATOR_ID);
rid_operator_id_set(&operator_id, "FIN87astrdge12k8");
```

See [examples/operator_id/](examples/operator_id/) for full example.

## Message Pack (0x0F)
Combines multiple message types into a single payload for transmission.

```c
rid_message_pack_t pack;
rid_basic_id_t basic_id;
rid_location_t location;

rid_message_pack_init(&pack);
rid_message_pack_add_message(&pack, &basic_id);
rid_message_pack_add_message(&pack, &location);
```

See [examples/message_pack/](examples/message_pack/) for full example.

# Build examples

```
$ mkdir build && cd build
$ cmake -DRID_BUILD_EXAMPLES=ON ..
$ make
```

# Build and run tests

```
$ mkdir build && cd build
$ cmake -DRID_BUILD_TESTS=ON ..
$ make
$ ctest
```

# License

The MIT License (MIT). Please see [License File](LICENSE) for more information.