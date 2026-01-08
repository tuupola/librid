# [WIP] librid

An ASTM F3411 message generating and parsing library written in c programming language.

The library povides struct definitions for all remote id messages. It also provides getter and setter functions for all members of the structure. You should not access the struct members directly. Instead use the provided functions which will decode and encode the data to the correct format.

# Message types
## Basic ID (0x00)
Provides UAS identification (serial number, registration ID, or UUID) and characterizes the aircraft type.

## Location (0x01)
Contains current position, altitude, speed, direction, and timestamp of the UA.

## Auth (0x02)
Provides authentication data for verifying the identity of the UA sending the message.

## Self ID (0x03)
Allows operators to declare their identity or describe the purpose of a flight.

## System (0x04)
Contains remote pilot location, operating area details, and group aircraft information.

## Operator ID (0x05)
Provides CAA-issued registration or license ID for the remote pilot or operator.

## Message Pack (0x0F)
Combines multiple message types into a single payload for transmission.

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

## License

The MIT License (MIT). Please see [License File](LICENSE) for more information.