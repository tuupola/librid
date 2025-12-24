# Parse a Remote ID System Message

This example shows how to parse a Remote ID System message from raw bytes.

```
$ make run
gcc -Wall -Wextra -std=c99 -I../../include -o parse_system_message parse_system_message.c ../../src/message.c ../../src/system.c
./parse_system_message
Hex dump:
42 04 34 12 ef 23 c3 76  a0 0e 01 00 0a c0 08 d0
07 12 34 08 61 42 21 0d  00

System message (25 bytes):
  Protocol version:   2
  Message type:       4
  Operator loc type:  0
  Classification:     1
  Operator latitude:  60.287032
  Operator longitude: 24.539719
  Area count:         1
  Area radius:        100 m
  Area ceiling:       120.0 m
  Area floor:         0.0 m
  UA class:           2
  UA category:        1
  Operator altitude:  50.0 m
  Timestamp:          220283489
```
