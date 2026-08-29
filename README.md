# librid

An [ASTM F3411](https://store.astm.org/f3411-22a.html) and
[DIN EN 4709-002](https://stan-shop.org/en/catalog/item/74958) message encoding
and decoding library written in the C programming language.

The library provides struct definitions for all Remote ID messages. It also
provides accessor and mutator functions for all members of the structure. You
should not access the struct members directly. Instead use the provided
functions which will decode and encode the data to and from the correct wire
format.

The library targets embedded systems with limited features. You can use it
for example for building a Remote ID scanner or transmitter. While not limited
to these, there are known live implementations done with both
[Espressif ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/) and
[Nordic nRF Connect SDK (NCS)](https://www.nordicsemi.com/Products/Development-software/nRF-Connect-SDK).

## Important

This is a read-only mirror of the repository. Actual developing happens elsewhere.
I do monitor this repository though.

## Naming Conventions

Naming of modules and variables mirrors naming from the ASTM F3411 standard.

| Element   | Pattern                  | Example                       |
| --------- | ------------------------ | ----------------------------- |
| Functions | `rid_<module>_<action>`  | `rid_location_set_latitude()` |
| Types     | `rid_<module>_t`         | `rid_basic_id_t`              |
| Enums     | `RID_<CATEGORY>_<VALUE>` | `RID_ID_TYPE_SERIAL_NUMBER`   |
| Constants | `RID_<NAME>`             | `RID_TRACK_DIRECTION_MAX`     |

Functions generally follow the init, validate, get and set pattern.

| Function                        | Description              | Example                       |
| ------------------------------- | ------------------------ | ----------------------------- |
| `rid_<type>_init()`             | Initialize with defaults | `rid_location_init()`         |
| `rid_<type>_validate()`         | Validate structure       | `rid_location_validate()`     |
| `rid_<type>_set_<field>()`      | Mutator                  | `rid_location_set_latitude()` |
| `rid_<type>_get_<field>()`      | Accessor                 | `rid_location_get_latitude()` |
| `rid_<type>_<enum>_to_string()` | Enum to string           | `rid_height_type_to_string()` |
| `rid_<type>_to_json()`          | JSON serialization       | `rid_location_to_json()`      |

## Examples

See the [examples](https://github.com/tuupola/librid/tree/master/examples) directory for better usage examples.

## Differences from the Open Drone ID library.

This library output is byte compatible with the
[Open Drone ID library](https://github.com/opendroneid/opendroneid-core-c) which
is the reference implementation. There are a couple of behavior differences though.

### Clamp Instead of Reject

According to ASTM F3411-22, the ground speed in a Location message must be
clamped to a maximum of 254.25 m/s. The vertical speed must be clamped to either
-62 m/s or 62 m/s depending on direction.

_"Ground speed of flight. This value is provided in meters per second with a
minimum resolution of 0.25 m/s. Special Values: Invalid, No Value, or Unknown:
255 m/s, if speed is >= 254.25 m/s: 254.25 m/s"_

_"Vertical speed upward relative to the WGS-84 datum, meters per second. Special
Values: Invalid, No Value, or Unknown: 63 m/s, if speed is >= 62 m/s: 62 m/s,
if speed is <= -62 m/s: -62 m/s"_

Open Drone ID rejects any input value outside the valid bounds. Instead of
rejecting this library clamps the values.

### Reject ASCII control characters

ASTM F3411-22 specifies the Self ID as ASCII text, a string of ASCII characters.
It is [unclear](https://github.com/opendroneid/opendroneid-core-c/issues/111) if
ASCII control characters should be accepted.

This library only allows printable ASCII characters and NUL. It is possible
that this requirement will be relaxed in the future. Open Drone ID does not do
an ASCII character check and also allows bytes `> 127`.

## Build

```
$ mkdir build && cd build
$ cmake -DRID_BUILD_EXAMPLES=ON -DRID_BUILD_TESTS=ON ..
$ make
$ ctest --verbose
```

## Install

Build and install a shared library.

```
$ mkdir build && cd build
$ cmake -DCMAKE_INSTALL_PREFIX=/opt/librid -DBUILD_SHARED_LIBS=ON ..
$ make
$ sudo make install
```

# Uninstall

```
$ cd build
$ sudo make uninstall
```

# License

The MIT License (MIT). Please see [License File](https://github.com/tuupola/librid/blob/master/LICENSE) for more information.
