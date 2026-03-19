# MAVLink Example

```
$ make run
$ make MAVLINK_DIR=/path/to/c_library_v2 run
```

## Output

```
=== Remote ID to MAVLink =======================

Remote ID Basic ID (25 bytes):
02 12 31 41 42 43 44 32  33 34 35 45 46 36 37 38
58 59 5a 00 00 00 00 00  00

  ID type: RID_ID_TYPE_SERIAL_NUMBER
  UA type: RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR
  UAS ID:  1ABCD2345EF678XYZ

MAVLink OPEN_DRONE_ID_BASIC_ID:
  Message ID:     12900
  Payload length: 41 bytes

=== MAVLink to Remote ID =======================

Remote ID Basic ID (25 bytes):
02 12 31 41 42 43 44 32  33 34 35 45 46 36 37 38
58 59 5a 00 00 00 00 00  00

  ID type: RID_ID_TYPE_SERIAL_NUMBER
  UA type: RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR
  UAS ID:  1ABCD2345EF678XYZ
```
