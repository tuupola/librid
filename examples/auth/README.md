# Auth Example

This example demonstrates Ed25519 signature creation and verification using the auth message type. Requires libsodium. Spec does not mandate the signature algorithm.

```
$ make run
```

## Output

Note: Public key and signature values will vary on each run due to random key generation.

```
Signature verified.
Page count: 4
Length:     64 bytes
Auth type:  1
Timestamp:  189014400

Public key:
7b cc 86 f8 50 b0 c1 12  c4 40 e0 2e 97 d5 7d dd
cd d1 36 c1 3e 74 82 e7  72 fa 7a 20 df d1 96 2c

Page 0:
22 10 03 40 80 21 44 0b  76 50 50 49 3c 2c da ee
4a ea 66 58 11 80 21 14  6d

Page 1:
22 11 50 a1 11 82 df ef  9b fa 54 ce 06 23 92 95
a6 4e 06 72 44 a1 fd 1c  81

Page 2:
22 12 a2 36 2c 1c ff ab  24 d9 07 1c 00 2a ab ef
85 79 81 96 b8 ef db 30  0c

Page 3:
22 13 07 00 00 00 00 00  00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00  00

Retrieved signature:
76 50 50 49 3c 2c da ee  4a ea 66 58 11 80 21 14
6d 50 a1 11 82 df ef 9b  fa 54 ce 06 23 92 95 a6
4e 06 72 44 a1 fd 1c 81  a2 36 2c 1c ff ab 24 d9
07 1c 00 2a ab ef 85 79  81 96 b8 ef db 30 0c 07
```
