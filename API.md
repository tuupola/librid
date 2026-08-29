# API Reference

## Header files

- [include/rid/auth.h](#file-includeridauthh)
- [include/rid/auth_page.h](#file-includeridauth_pageh)
- [include/rid/basic_id.h](#file-includeridbasic_idh)
- [include/rid/location.h](#file-includeridlocationh)
- [include/rid/message.h](#file-includeridmessageh)
- [include/rid/message_pack.h](#file-includeridmessage_packh)
- [include/rid/operator_id.h](#file-includeridoperator_idh)
- [include/rid/rid.h](#file-includeridridh)
- [include/rid/self_id.h](#file-includeridself_idh)
- [include/rid/system.h](#file-includeridsystemh)
- [include/rid/transport.h](#file-includeridtransporth)
- [include/rid/version.h](#file-includeridversionh)

## File include/rid/auth.h

_High-level authentication data API per ASTM F3411-22a._

Provides a container struct and functions for managing multi-page authentication data.

Example usage: 
````cpp
    rid_message_pack_t pack;
    rid_basic_id_t basic_id;
    rid_location_t location;
    rid_self_id_t self_id;
    rid_operator_id_t operator_id;
    rid_system_t system;
    rid_auth_t auth;

    rid_message_pack_init(&pack);
    rid_basic_id_init(&basic_id);
    rid_location_init(&location);
    rid_self_id_init(&self_id);
    rid_operator_id_init(&operator_id);
    rid_system_init(&system);
    rid_auth_init(&auth);

    rid_message_pack_add_message(&pack, &basic_id);
    rid_message_pack_add_message(&pack, &location);
    rid_message_pack_add_message(&pack, &self_id);
    rid_message_pack_add_message(&pack, &operator_id);
    rid_message_pack_add_message(&pack, &system);

    /* You must set timestamp manually */
    rid_auth_set_unixtime(&auth, (uint32_t)time(NULL));

    /* Sign and add the Auth message to the Message Pack */
    rid_auth_sign(&auth, &pack, sign_ed25519, (void *)secret_key);
    rid_message_pack_set_auth(&pack, &auth);
````

## Structures and Types

| Type | Name |
| ---: | :--- |
| typedef int(\* | [**rid\_auth\_sign\_cb\_t**](#typedef-rid_auth_sign_cb_t)  <br>_Callback function type for producing authentication signatures._ |
| struct | [**rid\_auth\_t**](#struct-rid_auth_t) <br>_Container for multi-page authentication data._ |
| typedef int(\* | [**rid\_auth\_verify\_cb\_t**](#typedef-rid_auth_verify_cb_t)  <br>_Callback function type for verifying authentication signatures._ |

## Functions

| Type | Name |
| ---: | :--- |
|  uint8\_t | [**rid\_auth\_get\_length**](#function-rid_auth_get_length) (const [**rid\_auth\_t**](#struct-rid_auth_t) \*auth) <br>_Get the total signature length in bytes._ |
|  uint8\_t | [**rid\_auth\_get\_page\_count**](#function-rid_auth_get_page_count) (const [**rid\_auth\_t**](#struct-rid_auth_t) \*auth) <br>_Get the number of pages used._ |
|  int | [**rid\_auth\_get\_signature**](#function-rid_auth_get_signature) (const [**rid\_auth\_t**](#struct-rid_auth_t) \*auth, uint8\_t \*buffer, size\_t buffer\_size) <br>_Get the signature data._ |
|  uint32\_t | [**rid\_auth\_get\_timestamp**](#function-rid_auth_get_timestamp) (const [**rid\_auth\_t**](#struct-rid_auth_t) \*auth) <br>_Get the timestamp._ |
|  [**rid\_auth\_type\_t**](#enum-rid_auth_type_t) | [**rid\_auth\_get\_type**](#function-rid_auth_get_type) (const [**rid\_auth\_t**](#struct-rid_auth_t) \*auth) <br>_Get the authentication type._ |
|  uint32\_t | [**rid\_auth\_get\_unixtime**](#function-rid_auth_get_unixtime) (const [**rid\_auth\_t**](#struct-rid_auth_t) \*auth) <br>_Get the timestamp as Unix time._ |
|  int | [**rid\_auth\_init**](#function-rid_auth_init) ([**rid\_auth\_t**](#struct-rid_auth_t) \*auth) <br>_Initialize an authentication data container._ |
|  int | [**rid\_auth\_set\_signature**](#function-rid_auth_set_signature) ([**rid\_auth\_t**](#struct-rid_auth_t) \*auth, const uint8\_t \*signature, size\_t size) <br>_Set the signature data._ |
|  int | [**rid\_auth\_set\_timestamp**](#function-rid_auth_set_timestamp) ([**rid\_auth\_t**](#struct-rid_auth_t) \*auth, uint32\_t timestamp) <br>_Set the timestamp._ |
|  int | [**rid\_auth\_set\_type**](#function-rid_auth_set_type) ([**rid\_auth\_t**](#struct-rid_auth_t) \*auth, [**rid\_auth\_type\_t**](#enum-rid_auth_type_t) type) <br>_Set the authentication type._ |
|  int | [**rid\_auth\_set\_unixtime**](#function-rid_auth_set_unixtime) ([**rid\_auth\_t**](#struct-rid_auth_t) \*auth, uint32\_t unixtime) <br>_Set the timestamp from Unix time._ |
|  int | [**rid\_auth\_sign**](#function-rid_auth_sign) ([**rid\_auth\_t**](#struct-rid_auth_t) \*auth, const void \*message, [**rid\_auth\_sign\_cb\_t**](#typedef-rid_auth_sign_cb_t) callback, void \*context) <br>_Create an authentication signature with a caller supplied callback._ |
|  int | [**rid\_auth\_to\_json**](#function-rid_auth_to_json) (const [**rid\_auth\_t**](#struct-rid_auth_t) \*auth, char \*buffer, size\_t buffer\_size, size\_t \*needed\_size) <br>_Format an Auth message as a JSON string._ |
|  int | [**rid\_auth\_validate**](#function-rid_auth_validate) (const [**rid\_auth\_t**](#struct-rid_auth_t) \*auth) <br>_Validate an Auth container structure._ |
|  int | [**rid\_auth\_verify**](#function-rid_auth_verify) (const [**rid\_auth\_t**](#struct-rid_auth_t) \*auth, const void \*message, [**rid\_auth\_verify\_cb\_t**](#typedef-rid_auth_verify_cb_t) callback, void \*context) <br>_Verify an authentication signature using a caller supplied callback._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**RID\_AUTH\_PAGE\_MAX\_SIGNATURE\_SIZE**](#define-rid_auth_page_max_signature_size)  255<br>_Max signature size in bytes._ |

## Structures and Types Documentation

### typedef `rid_auth_sign_cb_t`

_Callback function type for producing authentication signatures._
```c
typedef int(* rid_auth_sign_cb_t) (void *context, const uint8_t *input, size_t input_length, uint8_t *signature, size_t signature_size, size_t *signature_length);
```


Called by [**rid\_auth\_sign()**](#function-rid_auth_sign) to perform the actual signing of the payload.



**Parameters:**


* `context` Opaque context passed to the callback. 
* `input` Pointer to the payload to sign. 
* `input_length` Length of the payload in bytes. 
* `signature` Output buffer for the signature. 
* `signature_size` Size of the signature buffer in bytes. 
* `signature_length` Output: actual signature length written.


**Return value:**


* `0` on success. 
* `Non-zero` on signing failure.
### struct `rid_auth_t`

_Container for multi-page authentication data._

Holds page 0 and up to 15 additional pages.

Variables:

-  [**rid\_auth\_page\_0\_t**](#struct-rid_auth_page_0_t) page_0  

-  [**rid\_auth\_page\_x\_t**](#struct-rid_auth_page_x_t) page_x  

### typedef `rid_auth_verify_cb_t`

_Callback function type for verifying authentication signatures._
```c
typedef int(* rid_auth_verify_cb_t) (void *context, const uint8_t *input, size_t input_length, const uint8_t *signature, size_t signature_length);
```


Called by [**rid\_auth\_verify()**](#function-rid_auth_verify) to perform the actual verification of the signed payload.



**Parameters:**


* `context` Opaque context passed to the callback. 
* `input` Pointer to the signed payload data. 
* `input_length` Length of the signed payload in bytes. 
* `signature` Pointer to the signature data to verify against. 
* `signature_length` Length of the signature in bytes.


**Return value:**


* `0` on success. 
* `Non-zero` on verification failure.

## Functions Documentation

### function `rid_auth_get_length`

_Get the total signature length in bytes._
```c
uint8_t rid_auth_get_length (
    const rid_auth_t *auth
) 
```


**Parameters:**


* `auth` Pointer to the authentication data container.


**Returns:**

The total signature length in bytes, or 0 if auth is NULL.
### function `rid_auth_get_page_count`

_Get the number of pages used._
```c
uint8_t rid_auth_get_page_count (
    const rid_auth_t *auth
) 
```


**Parameters:**


* `auth` Pointer to the authentication data container.


**Returns:**

The page count (1-16), or 0 if auth is NULL.
### function `rid_auth_get_signature`

_Get the signature data._
```c
int rid_auth_get_signature (
    const rid_auth_t *auth,
    uint8_t *buffer,
    size_t buffer_size
) 
```


Retrieves signature data from page 0 and additional pages.



**Parameters:**


* `auth` Pointer to the authentication data container. 
* `buffer` Buffer to store the signature data. 
* `buffer_size` Size of the buffer (must be at least the signature length).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if auth or buffer is NULL. 
* `RID_ERROR_BUFFER_TOO_SMALL` if buffer\_size is less than signature length.
### function `rid_auth_get_timestamp`

_Get the timestamp._
```c
uint32_t rid_auth_get_timestamp (
    const rid_auth_t *auth
) 
```


**Parameters:**


* `auth` Pointer to the authentication data container.


**Returns:**

Seconds since 2019-01-01 00:00:00 UTC, or 0 if auth is NULL.
### function `rid_auth_get_type`

_Get the authentication type._
```c
rid_auth_type_t rid_auth_get_type (
    const rid_auth_t *auth
) 
```


**Parameters:**


* `auth` Pointer to the authentication data container.


**Returns:**

The authentication type, or RID\_AUTH\_TYPE\_NONE if auth is NULL.
### function `rid_auth_get_unixtime`

_Get the timestamp as Unix time._
```c
uint32_t rid_auth_get_unixtime (
    const rid_auth_t *auth
) 
```


Converts RID timestamp to Unix timestamp.



**Parameters:**


* `auth` Pointer to the authentication data container.


**Returns:**

Unix timestamp (seconds since 1970-01-01 00:00:00 UTC), or 0 if auth is NULL.
### function `rid_auth_init`

_Initialize an authentication data container._
```c
int rid_auth_init (
    rid_auth_t *auth
) 
```


Zeros the structure and initializes page0 with protocol version and message type. Sets page\_count to 1.



**Parameters:**


* `auth` Pointer to the authentication data container.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if auth is NULL.
### function `rid_auth_set_signature`

_Set the signature data._
```c
int rid_auth_set_signature (
    rid_auth_t *auth,
    const uint8_t *signature,
    size_t size
) 
```


Distributes signature data across page 0 and additional pages as needed. Page 0 holds up to 17 bytes, each additional page holds up to 23 bytes.



**Parameters:**


* `auth` Pointer to the authentication data container. 
* `signature` Pointer to the signature data. 
* `size` Size of the signature data (max 255 bytes).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if auth or signature is NULL. 
* `RID_ERROR_BUFFER_TOO_LARGE` if size exceeds 255 bytes.
### function `rid_auth_set_timestamp`

_Set the timestamp._
```c
int rid_auth_set_timestamp (
    rid_auth_t *auth,
    uint32_t timestamp
) 
```


**Parameters:**


* `auth` Pointer to the authentication data container. 
* `timestamp` Seconds since 2019-01-01 00:00:00 UTC.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if auth is NULL.
### function `rid_auth_set_type`

_Set the authentication type._
```c
int rid_auth_set_type (
    rid_auth_t *auth,
    rid_auth_type_t type
) 
```


**Parameters:**


* `auth` Pointer to the authentication data container. 
* `type` The authentication type to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if auth is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if type exceeds RID\_AUTH\_TYPE\_MAX.
### function `rid_auth_set_unixtime`

_Set the timestamp from Unix time._
```c
int rid_auth_set_unixtime (
    rid_auth_t *auth,
    uint32_t unixtime
) 
```


Converts Unix timestamp to RID timestamp (seconds since 2019-01-01).



**Parameters:**


* `auth` Pointer to the authentication data container. 
* `unixtime` Unix timestamp (seconds since 1970-01-01 00:00:00 UTC).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if auth is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if unixtime is before RID epoch (2019-01-01).
### function `rid_auth_sign`

_Create an authentication signature with a caller supplied callback._
```c
int rid_auth_sign (
    rid_auth_t *auth,
    const void *message,
    rid_auth_sign_cb_t callback,
    void *context
) 
```


Validates the auth container and the input message. Constructs the payload to be signed internally, invokes the sign callback, then stores the resulting signature in the auth container.

The caller must set the timestamp before calling this function. The auth type is set automatically to RID\_AUTH\_TYPE\_MESSAGE\_SET\_SIGNATURE.

Only `rid_message_pack_t` is currently supported.



**Parameters:**


* `auth` Pointer to the authentication data container. The signature produced by the callback is stored here. 
* `message` Pointer to a [**rid\_message\_pack\_t**](#struct-rid_message_pack_t) whose non-AUTH messages are to be signed.
* `callback` Callback function used to produce the signature. 
* `context` Opaque context passed to the callback.


**Return value:**


* `RID_SUCCESS` if signing succeeded. 
* `RID_ERROR_NULL_POINTER` if auth, message, or callback is NULL. 
* `RID_ERROR_NOT_IMPLEMENTED` if message is not a message pack. 
* `RID_ERROR_OUT_OF_RANGE` if the callback produced a zero-length signature. 
* `Validation` error codes from [**rid\_auth\_validate()**](#function-rid_auth_validate) or[**rid\_message\_pack\_validate()**](#function-rid_message_pack_validate).
* `Any` non-zero value returned by the callback on signing failure.
### function `rid_auth_to_json`

_Format an Auth message as a JSON string._
```c
int rid_auth_to_json (
    const rid_auth_t *auth,
    char *buffer,
    size_t buffer_size,
    size_t *needed_size
) 
```


**Parameters:**


* `auth` Pointer to the Auth container structure. 
* `buffer` Buffer to store the JSON string or NULL. 
* `buffer_size` Size of the buffer. 
* `needed_size` If non-NULL receives the required buffer size.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if `auth` is NULL or if both`buffer` and`needed_size` are NULL.
* `RID_ERROR_BUFFER_TOO_SMALL` if `buffer` is too small.
### function `rid_auth_validate`

_Validate an Auth container structure._
```c
int rid_auth_validate (
    const rid_auth_t *auth
) 
```


Checks that page\_0 fields contain valid values according to ASTM F3411-22a.



**Parameters:**


* `auth` Pointer to the Auth container structure to validate.


**Return value:**


* `RID_SUCCESS` if all fields are valid. 
* `RID_ERROR_NULL_POINTER` if auth is NULL. 
* `RID_ERROR_INVALID_PROTOCOL_VERSION` if protocol version is invalid. 
* `RID_ERROR_UNKNOWN_MESSAGE_TYPE` if message type is not AUTH. 
* `RID_ERROR_INVALID_PAGE_NUMBER` if page\_number is invalid. 
* `RID_ERROR_INVALID_LAST_PAGE_INDEX` if last\_page\_index exceeds maximum. 
* `RID_ERROR_NON_EMPTY_SIGNATURE` if auth type is NETWORK\_REMOTE\_ID but signature is not empty.
### function `rid_auth_verify`

_Verify an authentication signature using a caller supplied callback._
```c
int rid_auth_verify (
    const rid_auth_t *auth,
    const void *message,
    rid_auth_verify_cb_t callback,
    void *context
) 
```


Validates the auth container and the input message. Constructs the signed payload internally, extracts the signature and then invokes the verify callback with the payload and signature.

Only `rid_message_pack_t` is currently supported.

Only `RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE` is currently supported.



**Parameters:**


* `auth` Pointer to the authentication data container. 
* `message` Pointer to a [**rid\_message\_pack\_t**](#struct-rid_message_pack_t) whose non-AUTH messages were signed.
* `callback` Callback function used to verify the signature. 
* `context` Opaque context passed to the callback.


**Return value:**


* `RID_SUCCESS` if verification succeeded. 
* `RID_ERROR_NULL_POINTER` if auth, message, or callback is NULL. 
* `RID_ERROR_NOT_IMPLEMENTED` if message is not a message pack, or if auth type is not MESSAGE\_SET\_SIGNATURE. 
* `RID_ERROR_OUT_OF_RANGE` if the signature length is zero. 
* `Validation` error codes from [**rid\_auth\_validate()**](#function-rid_auth_validate) or[**rid\_message\_pack\_validate()**](#function-rid_message_pack_validate).
* `Any` non-zero value returned by the callback on verification failure.

## Macros Documentation

### define `RID_AUTH_PAGE_MAX_SIGNATURE_SIZE`

_Max signature size in bytes._
```c
#define RID_AUTH_PAGE_MAX_SIGNATURE_SIZE 255
```


## File include/rid/auth_page.h

_Authentication message handling per ASTM F3411-22a._

Authentication messages support multi-page transmission with up to 16 pages (0-15). Page 0 has a different structure than pages 1-15.



**Note:**

For typical use cases, you should use the higher-level API in [**auth.h**](#file-includeridauthh) instead which manages multi-page authentication data automatically.



**See also:** [**auth.h**](#file-includeridauthh)
Example usage:
````cpp
    rid_auth_page_0_t page_0;
    rid_auth_page_x_t page_1;
    rid_auth_page_x_t page_2;

    /* sample authentication data */
    const uint8_t page_0_data[] = {
        0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09,
        0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01,
        0x01
    };

    const uint8_t page_1_data[] = {
        0x05, 0x00, 0x03, 0x82, 0x01, 0x0f, 0x00, 0x30,
        0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01, 0x00,
        0xbb, 0x6a, 0x8c, 0x7e, 0x5f, 0x2a, 0x9b
    };

    const uint8_t page_2_data[] = {
        0xc5, 0x7b, 0x99, 0x3a, 0x1d, 0x03, 0x66, 0x81,
        0xf4, 0x9e, 0x2c, 0x87, 0xab, 0x4f, 0xe0, 0x12
    };

    /* page 0 example */
    rid_auth_page_0_init(&page_0);
    rid_auth_page_0_set_type(&page_0, RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE);
    rid_auth_page_0_set_last_page_index(&page_0, 2);
    rid_auth_page_0_set_length(&page_0, 56);
    rid_auth_page_0_set_timestamp(&page_0, 189302400);
    rid_auth_page_0_set_data(&page_0, page_0_data, sizeof(page_0_data));

    printf("Page 0:\n");
    hexdump(&page_0, sizeof(page_0));

    uint8_t data_buffer[RID_AUTH_PAGE_0_DATA_SIZE];
    rid_auth_page_0_get_data(&page_0, data_buffer, sizeof(data_buffer));

    printf("Auth type:       %d\n", rid_auth_page_0_get_type(&page_0));
    printf("Last page index: %d\n", rid_auth_page_0_get_last_page_index(&page_0));
    printf("Length:          %d\n", rid_auth_page_0_get_length(&page_0));
    printf("Timestamp:       %u\n", rid_auth_page_0_get_timestamp(&page_0));
    printf("\n");

    /* page 1 example */
    rid_auth_page_x_init(&page_1, 1);
    rid_auth_page_x_set_type(&page_1, RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE);
    rid_auth_page_x_set_data(&page_1, page_1_data, sizeof(page_1_data));

    printf("Page 1:\n");
    hexdump(&page_1, sizeof(page_1));

    printf("Auth type:   %d\n", rid_auth_page_x_get_type(&page_1));
    printf("Page number: %d\n", rid_auth_page_x_get_number(&page_1));
    printf("\n");

    /* page 2 example */
    rid_auth_page_x_init(&page_2, 2);
    rid_auth_page_x_set_type(&page_2, RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE);
    rid_auth_page_x_set_data(&page_2, page_2_data, sizeof(page_2_data));

    printf("Page 2:\n");
    hexdump(&page_2, sizeof(page_2));

    printf("Auth type:   %d\n", rid_auth_page_x_get_type(&page_2));
    printf("Page number: %d\n", rid_auth_page_x_get_number(&page_2));
````

## Structures and Types

| Type | Name |
| ---: | :--- |
| struct | [**rid\_auth\_page\_0\_t**](#struct-rid_auth_page_0_t) <br>_Authentication message page 0 structure per ASTM F3411-22a._ |
| struct | [**rid\_auth\_page\_x\_t**](#struct-rid_auth_page_x_t) <br>_Authentication message pages 1-15 structure per ASTM F3411-22a._ |
| enum  | [**rid\_auth\_type\_t**](#enum-rid_auth_type_t)  <br>_Authentication type classification per ASTM F3411-22a._ |

## Functions

| Type | Name |
| ---: | :--- |
|  int | [**rid\_auth\_page\_0\_get\_data**](#function-rid_auth_page_0_get_data) (const [**rid\_auth\_page\_0\_t**](#struct-rid_auth_page_0_t) \*message, uint8\_t \*buffer, size\_t buffer\_size) <br>_Get the authentication data from page 0._ |
|  uint8\_t | [**rid\_auth\_page\_0\_get\_last\_page\_index**](#function-rid_auth_page_0_get_last_page_index) (const [**rid\_auth\_page\_0\_t**](#struct-rid_auth_page_0_t) \*message) <br>_Get the last page index from page 0._ |
|  uint8\_t | [**rid\_auth\_page\_0\_get\_length**](#function-rid_auth_page_0_get_length) (const [**rid\_auth\_page\_0\_t**](#struct-rid_auth_page_0_t) \*message) <br>_Get the total authentication data length from page 0._ |
|  uint32\_t | [**rid\_auth\_page\_0\_get\_timestamp**](#function-rid_auth_page_0_get_timestamp) (const [**rid\_auth\_page\_0\_t**](#struct-rid_auth_page_0_t) \*message) <br>_Get the timestamp from page 0._ |
|  [**rid\_auth\_type\_t**](#enum-rid_auth_type_t) | [**rid\_auth\_page\_0\_get\_type**](#function-rid_auth_page_0_get_type) (const [**rid\_auth\_page\_0\_t**](#struct-rid_auth_page_0_t) \*message) <br>_Get the authentication type from page 0._ |
|  int | [**rid\_auth\_page\_0\_init**](#function-rid_auth_page_0_init) ([**rid\_auth\_page\_0\_t**](#struct-rid_auth_page_0_t) \*message) <br>_Initialize an Authentication message page 0 structure._ |
|  int | [**rid\_auth\_page\_0\_set\_data**](#function-rid_auth_page_0_set_data) ([**rid\_auth\_page\_0\_t**](#struct-rid_auth_page_0_t) \*message, const uint8\_t \*data, size\_t size) <br>_Set the authentication data for page 0._ |
|  int | [**rid\_auth\_page\_0\_set\_last\_page\_index**](#function-rid_auth_page_0_set_last_page_index) ([**rid\_auth\_page\_0\_t**](#struct-rid_auth_page_0_t) \*message, uint8\_t index) <br>_Set the last page index for page 0._ |
|  int | [**rid\_auth\_page\_0\_set\_length**](#function-rid_auth_page_0_set_length) ([**rid\_auth\_page\_0\_t**](#struct-rid_auth_page_0_t) \*message, uint8\_t length) <br>_Set the total authentication data length for page 0._ |
|  int | [**rid\_auth\_page\_0\_set\_timestamp**](#function-rid_auth_page_0_set_timestamp) ([**rid\_auth\_page\_0\_t**](#struct-rid_auth_page_0_t) \*message, uint32\_t timestamp) <br>_Set the timestamp for page 0._ |
|  int | [**rid\_auth\_page\_0\_set\_type**](#function-rid_auth_page_0_set_type) ([**rid\_auth\_page\_0\_t**](#struct-rid_auth_page_0_t) \*message, [**rid\_auth\_type\_t**](#enum-rid_auth_type_t) type) <br>_Set the authentication type for page 0._ |
|  int | [**rid\_auth\_page\_to\_json**](#function-rid_auth_page_to_json) (const void \*message, char \*buffer, size\_t buffer\_size, size\_t \*needed\_size) <br>_Format a single AUTH page message as a JSON string._ |
|  int | [**rid\_auth\_page\_x\_get\_data**](#function-rid_auth_page_x_get_data) (const [**rid\_auth\_page\_x\_t**](#struct-rid_auth_page_x_t) \*message, uint8\_t \*buffer, size\_t buffer\_size) <br>_Get the authentication data from pages 1-15._ |
|  uint8\_t | [**rid\_auth\_page\_x\_get\_number**](#function-rid_auth_page_x_get_number) (const [**rid\_auth\_page\_x\_t**](#struct-rid_auth_page_x_t) \*message) <br>_Get the page number from pages 1-15._ |
|  [**rid\_auth\_type\_t**](#enum-rid_auth_type_t) | [**rid\_auth\_page\_x\_get\_type**](#function-rid_auth_page_x_get_type) (const [**rid\_auth\_page\_x\_t**](#struct-rid_auth_page_x_t) \*message) <br>_Get the authentication type from pages 1-15._ |
|  int | [**rid\_auth\_page\_x\_init**](#function-rid_auth_page_x_init) ([**rid\_auth\_page\_x\_t**](#struct-rid_auth_page_x_t) \*message, uint8\_t page\_number) <br>_Initialize an Authentication message page 1-15 structure._ |
|  int | [**rid\_auth\_page\_x\_set\_data**](#function-rid_auth_page_x_set_data) ([**rid\_auth\_page\_x\_t**](#struct-rid_auth_page_x_t) \*message, const uint8\_t \*data, size\_t size) <br>_Set the authentication data for pages 1-15._ |
|  int | [**rid\_auth\_page\_x\_set\_number**](#function-rid_auth_page_x_set_number) ([**rid\_auth\_page\_x\_t**](#struct-rid_auth_page_x_t) \*message, uint8\_t page\_number) <br>_Set the page number for pages 1-15._ |
|  int | [**rid\_auth\_page\_x\_set\_type**](#function-rid_auth_page_x_set_type) ([**rid\_auth\_page\_x\_t**](#struct-rid_auth_page_x_t) \*message, [**rid\_auth\_type\_t**](#enum-rid_auth_type_t) type) <br>_Set the authentication type for pages 1-15._ |
|  const char \* | [**rid\_auth\_type\_to\_string**](#function-rid_auth_type_to_string) ([**rid\_auth\_type\_t**](#enum-rid_auth_type_t) type) <br>_Convert authentication type to string representation._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**RID\_AUTH\_EPOCH\_OFFSET**](#define-rid_auth_epoch_offset)  1546300800<br>_Timestamp epoch offset (2019-01-01 00:00:00 UTC)._ |
| define  | [**RID\_AUTH\_MAX\_PAGES**](#define-rid_auth_max_pages)  16<br>_Maximum number of authentication pages._ |
| define  | [**RID\_AUTH\_MAX\_PAGE\_INDEX**](#define-rid_auth_max_page_index)  15<br>_Maximum page index (0-15)._ |
| define  | [**RID\_AUTH\_PAGE\_0\_DATA\_SIZE**](#define-rid_auth_page_0_data_size)  17<br>_Auth data size for page 0._ |
| define  | [**RID\_AUTH\_PAGE\_DATA\_SIZE**](#define-rid_auth_page_data_size)  23<br>_Auth data size for pages 1-15._ |

## Structures and Types Documentation

### struct `rid_auth_page_0_t`

_Authentication message page 0 structure per ASTM F3411-22a._

Page 0 contains header information including timestamp and total length.

Variables:

-  uint8\_t auth_data  

-  uint8\_t auth_type  

-  uint8\_t last_page_index  

-  uint8\_t length  

-  uint8\_t message_type  

-  uint8\_t page_number  

-  uint8\_t protocol_version  

-  uint32\_t timestamp  

### struct `rid_auth_page_x_t`

_Authentication message pages 1-15 structure per ASTM F3411-22a._

Pages 1-15 contain only auth type, page number, and authentication data.

Variables:

-  uint8\_t auth_data  

-  uint8\_t auth_type  

-  uint8\_t message_type  

-  uint8\_t page_number  

-  uint8\_t protocol_version  

### enum `rid_auth_type_t`

_Authentication type classification per ASTM F3411-22a._
```c
enum rid_auth_type_t {
    RID_AUTH_TYPE_NONE = 0,
    RID_AUTH_TYPE_UAS_ID_SIGNATURE = 1,
    RID_AUTH_TYPE_OPERATOR_ID_SIGNATURE = 2,
    RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE = 3,
    RID_AUTH_TYPE_NETWORK_REMOTE_ID = 4,
    RID_AUTH_TYPE_SPECIFIC_METHOD = 5,
    RID_AUTH_TYPE_MAX = 0x0F
};
```


## Functions Documentation

### function `rid_auth_page_0_get_data`

_Get the authentication data from page 0._
```c
int rid_auth_page_0_get_data (
    const rid_auth_page_0_t *message,
    uint8_t *buffer,
    size_t buffer_size
) 
```


**Parameters:**


* `message` Pointer to the Authentication message structure. 
* `buffer` Buffer to store the authentication data. 
* `buffer_size` Size of the buffer (must be at least 17).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message or buffer is NULL. 
* `RID_ERROR_BUFFER_TOO_SMALL` if buffer\_size &lt; 17.
### function `rid_auth_page_0_get_last_page_index`

_Get the last page index from page 0._
```c
uint8_t rid_auth_page_0_get_last_page_index (
    const rid_auth_page_0_t *message
) 
```


**Parameters:**


* `message` Pointer to the Authentication message structure.


**Returns:**

The last page index, or 0 if message is NULL.
### function `rid_auth_page_0_get_length`

_Get the total authentication data length from page 0._
```c
uint8_t rid_auth_page_0_get_length (
    const rid_auth_page_0_t *message
) 
```


**Parameters:**


* `message` Pointer to the Authentication message structure.


**Returns:**

The total length, or 0 if message is NULL.
### function `rid_auth_page_0_get_timestamp`

_Get the timestamp from page 0._
```c
uint32_t rid_auth_page_0_get_timestamp (
    const rid_auth_page_0_t *message
) 
```


**Parameters:**


* `message` Pointer to the Authentication message structure.


**Returns:**

Seconds since 2019-01-01 00:00:00 UTC, or 0 if message is NULL.
### function `rid_auth_page_0_get_type`

_Get the authentication type from page 0._
```c
rid_auth_type_t rid_auth_page_0_get_type (
    const rid_auth_page_0_t *message
) 
```


**Parameters:**


* `message` Pointer to the Authentication message structure.


**Returns:**

The authentication type, or RID\_AUTH\_TYPE\_NONE if message is NULL.
### function `rid_auth_page_0_init`

_Initialize an Authentication message page 0 structure._
```c
int rid_auth_page_0_init (
    rid_auth_page_0_t *message
) 
```


Sets protocol version to RID\_PROTOCOL\_VERSION\_2, message type to RID\_MESSAGE\_TYPE\_AUTH, and page number to 0. All other fields are zeroed.



**Parameters:**


* `message` Pointer to the Authentication message structure to initialize.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL.
### function `rid_auth_page_0_set_data`

_Set the authentication data for page 0._
```c
int rid_auth_page_0_set_data (
    rid_auth_page_0_t *message,
    const uint8_t *data,
    size_t size
) 
```


**Parameters:**


* `message` Pointer to the Authentication message structure. 
* `data` Pointer to the authentication data. 
* `size` Size of the data (max 17 bytes).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message or data is NULL. 
* `RID_ERROR_BUFFER_TOO_LARGE` if size &gt; 17.
### function `rid_auth_page_0_set_last_page_index`

_Set the last page index for page 0._
```c
int rid_auth_page_0_set_last_page_index (
    rid_auth_page_0_t *message,
    uint8_t index
) 
```


**Parameters:**


* `message` Pointer to the Authentication message structure. 
* `index` The last page index (0-15).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if index &gt; 15.
### function `rid_auth_page_0_set_length`

_Set the total authentication data length for page 0._
```c
int rid_auth_page_0_set_length (
    rid_auth_page_0_t *message,
    uint8_t length
) 
```


**Parameters:**


* `message` Pointer to the Authentication message structure. 
* `length` The total length of authentication data across all pages.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL.
### function `rid_auth_page_0_set_timestamp`

_Set the timestamp for page 0._
```c
int rid_auth_page_0_set_timestamp (
    rid_auth_page_0_t *message,
    uint32_t timestamp
) 
```


Timestamp is seconds since 2019-01-01 00:00:00 UTC.



**Parameters:**


* `message` Pointer to the Authentication message structure. 
* `timestamp` Seconds since 2019-01-01 00:00:00 UTC.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL.
### function `rid_auth_page_0_set_type`

_Set the authentication type for page 0._
```c
int rid_auth_page_0_set_type (
    rid_auth_page_0_t *message,
    rid_auth_type_t type
) 
```


**Parameters:**


* `message` Pointer to the Authentication message structure. 
* `type` The authentication type to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if type exceeds RID\_AUTH\_TYPE\_MAX.
### function `rid_auth_page_to_json`

_Format a single AUTH page message as a JSON string._
```c
int rid_auth_page_to_json (
    const void *message,
    char *buffer,
    size_t buffer_size,
    size_t *needed_size
) 
```


Handles both page 0 ([**rid\_auth\_page\_0\_t**](#struct-rid_auth_page_0_t)) and pages 1-15 ([**rid\_auth\_page\_x\_t**](#struct-rid_auth_page_x_t)) automatically based on the page\_number field.



**Parameters:**


* `message` Pointer to an AUTH page structure. 
* `buffer` Buffer to store the JSON string or NULL. 
* `buffer_size` Size of the buffer. 
* `needed_size` If non-NULL receives the required buffer size.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if `message` is NULL or if both`buffer` and`needed_size` are NULL.
* `RID_ERROR_BUFFER_TOO_SMALL` if `buffer` is too small.
### function `rid_auth_page_x_get_data`

_Get the authentication data from pages 1-15._
```c
int rid_auth_page_x_get_data (
    const rid_auth_page_x_t *message,
    uint8_t *buffer,
    size_t buffer_size
) 
```


**Parameters:**


* `message` Pointer to the Authentication page structure. 
* `buffer` Buffer to store the authentication data. 
* `buffer_size` Size of the buffer (must be at least 23).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message or buffer is NULL. 
* `RID_ERROR_BUFFER_TOO_SMALL` if buffer\_size &lt; 23.
### function `rid_auth_page_x_get_number`

_Get the page number from pages 1-15._
```c
uint8_t rid_auth_page_x_get_number (
    const rid_auth_page_x_t *message
) 
```


**Parameters:**


* `message` Pointer to the Authentication page structure.


**Returns:**

The page number, or 0 if message is NULL.
### function `rid_auth_page_x_get_type`

_Get the authentication type from pages 1-15._
```c
rid_auth_type_t rid_auth_page_x_get_type (
    const rid_auth_page_x_t *message
) 
```


**Parameters:**


* `message` Pointer to the Authentication page structure.


**Returns:**

The authentication type, or RID\_AUTH\_TYPE\_NONE if message is NULL.
### function `rid_auth_page_x_init`

_Initialize an Authentication message page 1-15 structure._
```c
int rid_auth_page_x_init (
    rid_auth_page_x_t *message,
    uint8_t page_number
) 
```


Sets protocol version to RID\_PROTOCOL\_VERSION\_2, message type to RID\_MESSAGE\_TYPE\_AUTH, and page number to specified value.



**Parameters:**


* `message` Pointer to the Authentication page structure to initialize. 
* `page_number` Page number (1-15).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if page\_number is 0 or &gt; 15.
### function `rid_auth_page_x_set_data`

_Set the authentication data for pages 1-15._
```c
int rid_auth_page_x_set_data (
    rid_auth_page_x_t *message,
    const uint8_t *data,
    size_t size
) 
```


**Parameters:**


* `message` Pointer to the Authentication page structure. 
* `data` Pointer to the authentication data. 
* `size` Size of the data (max 23 bytes).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message or data is NULL. 
* `RID_ERROR_BUFFER_TOO_LARGE` if size &gt; 23.
### function `rid_auth_page_x_set_number`

_Set the page number for pages 1-15._
```c
int rid_auth_page_x_set_number (
    rid_auth_page_x_t *message,
    uint8_t page_number
) 
```


**Parameters:**


* `message` Pointer to the Authentication page structure. 
* `page_number` The page number (1-15).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if page\_number is 0 or &gt; 15.
### function `rid_auth_page_x_set_type`

_Set the authentication type for pages 1-15._
```c
int rid_auth_page_x_set_type (
    rid_auth_page_x_t *message,
    rid_auth_type_t type
) 
```


**Parameters:**


* `message` Pointer to the Authentication page structure. 
* `type` The authentication type to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if type exceeds RID\_AUTH\_TYPE\_MAX.
### function `rid_auth_type_to_string`

_Convert authentication type to string representation._
```c
const char * rid_auth_type_to_string (
    rid_auth_type_t type
) 
```


**Parameters:**


* `type` The authentication type to convert.


**Returns:**

String representation of the authentication type. Returns "UNKNOWN" for invalid values.

## Macros Documentation

### define `RID_AUTH_EPOCH_OFFSET`

_Timestamp epoch offset (2019-01-01 00:00:00 UTC)._
```c
#define RID_AUTH_EPOCH_OFFSET 1546300800
```

### define `RID_AUTH_MAX_PAGES`

_Maximum number of authentication pages._
```c
#define RID_AUTH_MAX_PAGES 16
```

### define `RID_AUTH_MAX_PAGE_INDEX`

_Maximum page index (0-15)._
```c
#define RID_AUTH_MAX_PAGE_INDEX 15
```

### define `RID_AUTH_PAGE_0_DATA_SIZE`

_Auth data size for page 0._
```c
#define RID_AUTH_PAGE_0_DATA_SIZE 17
```

### define `RID_AUTH_PAGE_DATA_SIZE`

_Auth data size for pages 1-15._
```c
#define RID_AUTH_PAGE_DATA_SIZE 23
```


## File include/rid/basic_id.h

_Basic ID message handling per ASTM F3411-22a._

Example usage: 
````cpp
rid_basic_id_t basic_id;

rid_basic_id_init(&basic_id);
rid_basic_id_set_type(&basic_id, RID_ID_TYPE_SERIAL_NUMBER);
rid_basic_id_set_ua_type(&basic_id, RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR);
rid_basic_id_set_uas_id(&basic_id, "1ABCD2345EF678XYZ", strlen("1ABCD2345EF678XYZ"));

hexdump(&basic_id, sizeof(basic_id));

char uas_id[RID_UAS_ID_SIZE + 1];
rid_basic_id_get_uas_id(&basic_id, uas_id, sizeof(uas_id));
rid_ua_type_t ua_type = rid_basic_id_get_ua_type(&basic_id);
rid_basic_id_type_t id_type = rid_basic_id_get_type(&basic_id);

printf("UAS ID:  %s\n", uas_id);
printf("UA type: %d\n", ua_type);
printf("ID type: %d\n", id_type);
````

## Structures and Types

| Type | Name |
| ---: | :--- |
| struct | [**rid\_basic\_id\_t**](#struct-rid_basic_id_t) <br>_Basic ID message structure per ASTM F3411-22a._ |
| enum  | [**rid\_basic\_id\_type\_t**](#enum-rid_basic_id_type_t)  <br>_Basic ID type classification per ASTM F3411-22a._ |
| enum  | [**rid\_ua\_type\_t**](#enum-rid_ua_type_t)  <br>_Unmanned Aircraft type classification per ASTM F3411-22a._ |

## Functions

| Type | Name |
| ---: | :--- |
|  [**rid\_basic\_id\_type\_t**](#enum-rid_basic_id_type_t) | [**rid\_basic\_id\_get\_type**](#function-rid_basic_id_get_type) (const [**rid\_basic\_id\_t**](#struct-rid_basic_id_t) \*message) <br>_Get the ID type from a Basic ID message._ |
|  [**rid\_ua\_type\_t**](#enum-rid_ua_type_t) | [**rid\_basic\_id\_get\_ua\_type**](#function-rid_basic_id_get_ua_type) (const [**rid\_basic\_id\_t**](#struct-rid_basic_id_t) \*message) <br>_Get the Unmanned Aircraft type from a Basic ID message._ |
|  int | [**rid\_basic\_id\_get\_uas\_id**](#function-rid_basic_id_get_uas_id) (const [**rid\_basic\_id\_t**](#struct-rid_basic_id_t) \*message, void \*buffer, size\_t buffer\_size) <br>_Get the Unmanned Aircraft System ID from a Basic ID message._ |
|  int | [**rid\_basic\_id\_init**](#function-rid_basic_id_init) ([**rid\_basic\_id\_t**](#struct-rid_basic_id_t) \*message) <br>_Initialize a Basic ID message structure._ |
|  int | [**rid\_basic\_id\_set\_type**](#function-rid_basic_id_set_type) ([**rid\_basic\_id\_t**](#struct-rid_basic_id_t) \*message, [**rid\_basic\_id\_type\_t**](#enum-rid_basic_id_type_t) type) <br>_Set the ID type for a Basic ID message._ |
|  int | [**rid\_basic\_id\_set\_ua\_type**](#function-rid_basic_id_set_ua_type) ([**rid\_basic\_id\_t**](#struct-rid_basic_id_t) \*message, [**rid\_ua\_type\_t**](#enum-rid_ua_type_t) type) <br>_Set the Unmanned Aircraft type for a Basic ID message._ |
|  int | [**rid\_basic\_id\_set\_uas\_id**](#function-rid_basic_id_set_uas_id) ([**rid\_basic\_id\_t**](#struct-rid_basic_id_t) \*message, const void \*uas\_id, size\_t uas\_id\_size) <br>_Set the Unmanned Aircraft System ID for a Basic ID message._ |
|  int | [**rid\_basic\_id\_to\_json**](#function-rid_basic_id_to_json) (const [**rid\_basic\_id\_t**](#struct-rid_basic_id_t) \*message, char \*buffer, size\_t buffer\_size, size\_t \*needed\_size) <br>_Format a Basic ID message as a JSON string._ |
|  const char \* | [**rid\_basic\_id\_type\_to\_string**](#function-rid_basic_id_type_to_string) ([**rid\_basic\_id\_type\_t**](#enum-rid_basic_id_type_t) type) <br>_Convert ID type to string representation._ |
|  int | [**rid\_basic\_id\_validate**](#function-rid_basic_id_validate) (const [**rid\_basic\_id\_t**](#struct-rid_basic_id_t) \*message) <br>_Validate a Basic ID message structure._ |
|  const char \* | [**rid\_ua\_type\_to\_string**](#function-rid_ua_type_to_string) ([**rid\_ua\_type\_t**](#enum-rid_ua_type_t) type) <br>_Convert Unmanned Aircraft type to string representation._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**RID\_UAS\_ID\_SIZE**](#define-rid_uas_id_size)  20<br>_UAS ID field size in bytes per ASTM F3411-22a._ |
| define  | [**RID\_UAS\_ID\_UUID\_SIZE**](#define-rid_uas_id_uuid_size)  16<br>_RFC4122 UUID size in bytes._ |

## Structures and Types Documentation

### struct `rid_basic_id_t`

_Basic ID message structure per ASTM F3411-22a._

Variables:

-  uint8\_t id_type  

-  uint8\_t message_type  

-  uint8\_t protocol_version  

-  char reserved  

-  uint8\_t ua_type  

-  char uas_id  

### enum `rid_basic_id_type_t`

_Basic ID type classification per ASTM F3411-22a._
```c
enum rid_basic_id_type_t {
    RID_ID_TYPE_NONE = 0,
    RID_ID_TYPE_SERIAL_NUMBER = 1,
    RID_ID_TYPE_CAA_REGISTRATION_ID = 2,
    RID_ID_TYPE_UTM_ASSIGNED_UUID = 3,
    RID_ID_TYPE_SPECIFIC_SESSION_ID = 4,
    RID_ID_TYPE_MAX = 15
};
```

### enum `rid_ua_type_t`

_Unmanned Aircraft type classification per ASTM F3411-22a._
```c
enum rid_ua_type_t {
    RID_UA_TYPE_NONE = 0,
    RID_UA_TYPE_AEROPLANE_OR_FIXED_WING = 1,
    RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR = 2,
    RID_UA_TYPE_GYROPLANE = 3,
    RID_UA_TYPE_HYBRID_LIFT = 4,
    RID_UA_TYPE_ORNITHOPTER = 5,
    RID_UA_TYPE_GLIDER = 6,
    RID_UA_TYPE_KITE = 7,
    RID_UA_TYPE_FREE_BALLOON = 8,
    RID_UA_TYPE_CAPTIVE_BALLOON = 9,
    RID_UA_TYPE_AIRSHIP = 10,
    RID_UA_TYPE_FREE_FALL_PARACHUTE = 11,
    RID_UA_TYPE_ROCKET = 12,
    RID_UA_TYPE_TETHERED_POWERED_AIRCRAFT = 13,
    RID_UA_TYPE_GROUND_OBSTACLE = 14,
    RID_UA_TYPE_OTHER = 15,
    RID_UA_TYPE_MAX = 15
};
```


## Functions Documentation

### function `rid_basic_id_get_type`

_Get the ID type from a Basic ID message._
```c
rid_basic_id_type_t rid_basic_id_get_type (
    const rid_basic_id_t *message
) 
```


**Parameters:**


* `message` Pointer to the Basic ID message structure.


**Returns:**

The ID type or RID\_ID\_TYPE\_NONE if message is NULL.
### function `rid_basic_id_get_ua_type`

_Get the Unmanned Aircraft type from a Basic ID message._
```c
rid_ua_type_t rid_basic_id_get_ua_type (
    const rid_basic_id_t *message
) 
```


**Parameters:**


* `message` Pointer to the Basic ID message structure.


**Returns:**

The UA type or RID\_UA\_TYPE\_NONE if message is NULL.
### function `rid_basic_id_get_uas_id`

_Get the Unmanned Aircraft System ID from a Basic ID message._
```c
int rid_basic_id_get_uas_id (
    const rid_basic_id_t *message,
    void *buffer,
    size_t buffer_size
) 
```


Copies RID\_UAS\_ID\_SIZE bytes to the provided buffer. String callers should pass a buffer of RID\_UAS\_ID\_SIZE + 1 to get a null-terminated C string.



**Parameters:**


* `message` Pointer to the Basic ID message structure. 
* `buffer` Buffer to store the UAS ID. 
* `buffer_size` Size of the buffer. Must be at least RID\_UAS\_ID\_SIZE.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message or buffer is NULL. 
* `RID_ERROR_BUFFER_TOO_SMALL` if buffer\_size is insufficient.
### function `rid_basic_id_init`

_Initialize a Basic ID message structure._
```c
int rid_basic_id_init (
    rid_basic_id_t *message
) 
```


Sets protocol version to RID\_PROTOCOL\_VERSION\_2 and message type to RID\_MESSAGE\_TYPE\_BASIC\_ID. All other fields are zeroed.



**Parameters:**


* `message` Pointer to the Basic ID message structure to initialize.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL.
### function `rid_basic_id_set_type`

_Set the ID type for a Basic ID message._
```c
int rid_basic_id_set_type (
    rid_basic_id_t *message,
    rid_basic_id_type_t type
) 
```


**Parameters:**


* `message` Pointer to the Basic ID message structure. 
* `type` The ID type to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if type exceeds RID\_ID\_TYPE\_MAX.
### function `rid_basic_id_set_ua_type`

_Set the Unmanned Aircraft type for a Basic ID message._
```c
int rid_basic_id_set_ua_type (
    rid_basic_id_t *message,
    rid_ua_type_t type
) 
```


**Parameters:**


* `message` Pointer to the Basic ID message structure. 
* `type` The UA type to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if type exceeds RID\_UA\_TYPE\_MAX.
### function `rid_basic_id_set_uas_id`

_Set the Unmanned Aircraft System ID for a Basic ID message._
```c
int rid_basic_id_set_uas_id (
    rid_basic_id_t *message,
    const void *uas_id,
    size_t uas_id_size
) 
```


Copies uas\_id\_size bytes and zero-pads the remainder.



**Parameters:**


* `message` Pointer to the Basic ID message structure. 
* `uas_id` The UAS ID bytes to set. 
* `uas_id_size` Number of bytes in the uas\_id.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message or uas\_id is NULL. 
* `RID_ERROR_BUFFER_TOO_LARGE` if uas\_id\_size exceeds RID\_UAS\_ID\_SIZE.
### function `rid_basic_id_to_json`

_Format a Basic ID message as a JSON string._
```c
int rid_basic_id_to_json (
    const rid_basic_id_t *message,
    char *buffer,
    size_t buffer_size,
    size_t *needed_size
) 
```


**Parameters:**


* `message` Pointer to the Basic ID message structure. 
* `buffer` Buffer to store the JSON string or NULL. 
* `buffer_size` Size of the buffer. 
* `needed_size` Receives the required buffer size. Can be NULL.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL or if both buffer and needed\_size are NULL. 
* `RID_ERROR_BUFFER_TOO_SMALL` if buffer is too small.
### function `rid_basic_id_type_to_string`

_Convert ID type to string representation._
```c
const char * rid_basic_id_type_to_string (
    rid_basic_id_type_t type
) 
```


**Parameters:**


* `type` The ID type to convert.


**Returns:**

String representation of the ID type. Returns "UNKNOWN" for invalid values.
### function `rid_basic_id_validate`

_Validate a Basic ID message structure._
```c
int rid_basic_id_validate (
    const rid_basic_id_t *message
) 
```


Checks that all fields contain valid encoded values according to ASTM F3411-22a. Reserved values are considered valid.



**Parameters:**


* `message` Pointer to the Basic ID message structure to validate.


**Return value:**


* `RID_SUCCESS` if all fields are valid. 
* `RID_ERROR_NULL_POINTER` if message is NULL. 
* `RID_ERROR_INVALID_PROTOCOL_VERSION` if protocol version is invalid. 
* `RID_ERROR_UNKNOWN_MESSAGE_TYPE` if message type is not BASIC\_ID. 
* `RID_ERROR_INVALID_CAA_REGISTRATION_ID` if Registration ID contains invalid characters. 
* `RID_ERROR_INVALID_SERIAL_NUMBER` if Serial Number contains invalid characters. 
* `RID_ERROR_INVALID_UUID_VERSION` if UTM UUID version is not 1-5. 
* `RID_ERROR_INVALID_UUID_VARIANT` if UTM UUID variant is not RFC4122. 
* `RID_ERROR_INVALID_UUID_PADDING` if UTM UUID padding bytes are non-zero.
### function `rid_ua_type_to_string`

_Convert Unmanned Aircraft type to string representation._
```c
const char * rid_ua_type_to_string (
    rid_ua_type_t type
) 
```


**Parameters:**


* `type` The UA type to convert.


**Returns:**

String representation of the UA type. Returns "UNKNOWN" for invalid values.

## Macros Documentation

### define `RID_UAS_ID_SIZE`

_UAS ID field size in bytes per ASTM F3411-22a._
```c
#define RID_UAS_ID_SIZE 20
```

### define `RID_UAS_ID_UUID_SIZE`

_RFC4122 UUID size in bytes._
```c
#define RID_UAS_ID_UUID_SIZE 16
```


## File include/rid/location.h

_Location message handling per ASTM F3411-22a._

Example usage: 
````cpp
    rid_location_t location;

    rid_location_init(&location);
    rid_location_set_operational_status(&location, RID_OPERATIONAL_STATUS_AIRBORNE);
    rid_location_set_height_type(&location, RID_HEIGHT_TYPE_ABOVE_TAKEOFF);
    rid_location_set_latitude(&location, 62.683472);
    rid_location_set_longitude(&location, 21.974944);
    rid_location_set_geodetic_altitude(&location, 120.5f);
    rid_location_set_height(&location, 50.0f);
    rid_location_set_speed(&location, 15.5f);
    rid_location_set_vertical_speed(&location, 2.0f);
    rid_location_set_track_direction(&location, 45);
    rid_location_set_timestamp(&location, 12345);
    rid_location_set_horizontal_accuracy(&location, RID_HORIZONTAL_ACCURACY_10M);
    rid_location_set_vertical_accuracy(&location, RID_VERTICAL_ACCURACY_10M);
    rid_location_set_speed_accuracy(&location, RID_SPEED_ACCURACY_1MS);
    rid_location_set_timestamp_accuracy(&location, RID_TIMESTAMP_ACCURACY_0_1S);
    rid_location_set_pressure_altitude(&location, 101.3f);
    rid_location_set_baro_altitude_accuracy(&location, RID_VERTICAL_ACCURACY_3M);

    hexdump(&location, sizeof(location));

    rid_height_type_t height_type = rid_location_get_height_type(&location);
    rid_operational_status_t status = rid_location_get_operational_status(&location);
    uint16_t direction = rid_location_get_track_direction(&location);
    float speed = rid_location_get_speed(&location);
    float vspeed = rid_location_get_vertical_speed(&location);
    double latitude = rid_location_get_latitude(&location);
    double longitude = rid_location_get_longitude(&location);
    float pressure_alt = rid_location_get_pressure_altitude(&location);
    float geodetic_alt = rid_location_get_geodetic_altitude(&location);
    float height = rid_location_get_height(&location);
    rid_horizontal_accuracy_t h_accuracy = rid_location_get_horizontal_accuracy(&location);
    rid_vertical_accuracy_t v_accuracy = rid_location_get_vertical_accuracy(&location);
    rid_speed_accuracy_t s_accuracy = rid_location_get_speed_accuracy(&location);
    rid_vertical_accuracy_t baro_accuracy = rid_location_get_baro_altitude_accuracy(&location);
    uint16_t timestamp = rid_location_get_timestamp(&location);
    rid_timestamp_accuracy_t ts_accuracy = rid_location_get_timestamp_accuracy(&location);

    printf("Height Type:         %s\n", rid_height_type_to_string(height_type));
    printf("Status:              %s\n", rid_operational_status_to_string(status));
    printf("Direction:           %u deg\n", direction);
    printf("Speed:               %.1f m/s\n", (double)speed);
    printf("Vertical Speed:      %.1f m/s\n", (double)vspeed);
    printf("Latitude:            %.6f\n", latitude);
    printf("Longitude:           %.6f\n", longitude);
    printf("Pressure Alt:        %.1f m\n", (double)pressure_alt);
    printf("Geodetic Alt:        %.1f m\n", (double)geodetic_alt);
    printf("Height:              %.1f m\n", (double)height);
    printf("Horizontal Accuracy: %s\n", rid_horizontal_accuracy_to_string(h_accuracy));
    printf("Vertical Accuracy:   %s\n", rid_vertical_accuracy_to_string(v_accuracy));
    printf("Speed Accuracy:      %s\n", rid_speed_accuracy_to_string(s_accuracy));
    printf("Baro Accuracy:       %s\n", rid_vertical_accuracy_to_string(baro_accuracy));
    printf("Timestamp:           %u ds\n", timestamp);
    printf("Timestamp Accuracy:  %s\n", rid_timestamp_accuracy_to_string(ts_accuracy));
````

## Structures and Types

| Type | Name |
| ---: | :--- |
| enum  | [**rid\_ew\_direction\_t**](#enum-rid_ew_direction_t)  <br>_East/West direction flag per ASTM F3411-22a._ |
| enum  | [**rid\_height\_type\_t**](#enum-rid_height_type_t)  <br>_Height reference type per ASTM F3411-22a._ |
| enum  | [**rid\_horizontal\_accuracy\_t**](#enum-rid_horizontal_accuracy_t)  <br>_Horizontal accuracy per ASTM F3411-22a._ |
| struct | [**rid\_location\_t**](#struct-rid_location_t) <br>_Location message structure per ASTM F3411-22a._ |
| enum  | [**rid\_operational\_status\_t**](#enum-rid_operational_status_t)  <br>_Operational status per ASTM F3411-22a._ |
| enum  | [**rid\_speed\_accuracy\_t**](#enum-rid_speed_accuracy_t)  <br>_Speed accuracy per ASTM F3411-22a._ |
| enum  | [**rid\_timestamp\_accuracy\_t**](#enum-rid_timestamp_accuracy_t)  <br>_Timestamp accuracy per ASTM F3411-22a._ |
| enum  | [**rid\_vertical\_accuracy\_t**](#enum-rid_vertical_accuracy_t)  <br>_Vertical accuracy per ASTM F3411-22a._ |

## Functions

| Type | Name |
| ---: | :--- |
|  const char \* | [**rid\_height\_type\_to\_string**](#function-rid_height_type_to_string) ([**rid\_height\_type\_t**](#enum-rid_height_type_t) type) <br>_Convert height type to string representation._ |
|  const char \* | [**rid\_horizontal\_accuracy\_to\_string**](#function-rid_horizontal_accuracy_to_string) ([**rid\_horizontal\_accuracy\_t**](#enum-rid_horizontal_accuracy_t) accuracy) <br>_Convert horizontal accuracy to string representation._ |
|  [**rid\_vertical\_accuracy\_t**](#enum-rid_vertical_accuracy_t) | [**rid\_location\_get\_baro\_altitude\_accuracy**](#function-rid_location_get_baro_altitude_accuracy) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the barometric altitude accuracy from a Location message._ |
|  float | [**rid\_location\_get\_geodetic\_altitude**](#function-rid_location_get_geodetic_altitude) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the geodetic altitude from a Location message._ |
|  float | [**rid\_location\_get\_height**](#function-rid_location_get_height) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the height from a Location message._ |
|  [**rid\_height\_type\_t**](#enum-rid_height_type_t) | [**rid\_location\_get\_height\_type**](#function-rid_location_get_height_type) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the height reference type from a Location message._ |
|  [**rid\_horizontal\_accuracy\_t**](#enum-rid_horizontal_accuracy_t) | [**rid\_location\_get\_horizontal\_accuracy**](#function-rid_location_get_horizontal_accuracy) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the horizontal position accuracy from a Location message._ |
|  double | [**rid\_location\_get\_latitude**](#function-rid_location_get_latitude) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the latitude from a Location message._ |
|  double | [**rid\_location\_get\_longitude**](#function-rid_location_get_longitude) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the longitude from a Location message._ |
|  [**rid\_operational\_status\_t**](#enum-rid_operational_status_t) | [**rid\_location\_get\_operational\_status**](#function-rid_location_get_operational_status) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the operational status from a Location message._ |
|  float | [**rid\_location\_get\_pressure\_altitude**](#function-rid_location_get_pressure_altitude) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the pressure altitude from a Location message._ |
|  float | [**rid\_location\_get\_speed**](#function-rid_location_get_speed) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the ground speed from a Location message._ |
|  [**rid\_speed\_accuracy\_t**](#enum-rid_speed_accuracy_t) | [**rid\_location\_get\_speed\_accuracy**](#function-rid_location_get_speed_accuracy) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the speed accuracy from a Location message._ |
|  uint16\_t | [**rid\_location\_get\_timestamp**](#function-rid_location_get_timestamp) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the timestamp from a Location message._ |
|  [**rid\_timestamp\_accuracy\_t**](#enum-rid_timestamp_accuracy_t) | [**rid\_location\_get\_timestamp\_accuracy**](#function-rid_location_get_timestamp_accuracy) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the timestamp accuracy from a Location message._ |
|  uint16\_t | [**rid\_location\_get\_track\_direction**](#function-rid_location_get_track_direction) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the track direction from a Location message._ |
|  [**rid\_vertical\_accuracy\_t**](#enum-rid_vertical_accuracy_t) | [**rid\_location\_get\_vertical\_accuracy**](#function-rid_location_get_vertical_accuracy) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the vertical position accuracy from a Location message._ |
|  float | [**rid\_location\_get\_vertical\_speed**](#function-rid_location_get_vertical_speed) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Get the vertical speed from a Location message._ |
|  int | [**rid\_location\_init**](#function-rid_location_init) ([**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Initialize a Location message structure._ |
|  int | [**rid\_location\_set\_baro\_altitude\_accuracy**](#function-rid_location_set_baro_altitude_accuracy) ([**rid\_location\_t**](#struct-rid_location_t) \*location, [**rid\_vertical\_accuracy\_t**](#enum-rid_vertical_accuracy_t) accuracy) <br>_Set the barometric altitude accuracy for a Location message._ |
|  int | [**rid\_location\_set\_geodetic\_altitude**](#function-rid_location_set_geodetic_altitude) ([**rid\_location\_t**](#struct-rid_location_t) \*location, float altitude\_m) <br>_Set the geodetic altitude for a Location message._ |
|  int | [**rid\_location\_set\_height**](#function-rid_location_set_height) ([**rid\_location\_t**](#struct-rid_location_t) \*location, float height\_m) <br>_Set the height for a Location message._ |
|  int | [**rid\_location\_set\_height\_type**](#function-rid_location_set_height_type) ([**rid\_location\_t**](#struct-rid_location_t) \*location, [**rid\_height\_type\_t**](#enum-rid_height_type_t) type) <br>_Set the height reference type for a Location message._ |
|  int | [**rid\_location\_set\_horizontal\_accuracy**](#function-rid_location_set_horizontal_accuracy) ([**rid\_location\_t**](#struct-rid_location_t) \*location, [**rid\_horizontal\_accuracy\_t**](#enum-rid_horizontal_accuracy_t) accuracy) <br>_Set the horizontal position accuracy for a Location message._ |
|  int | [**rid\_location\_set\_latitude**](#function-rid_location_set_latitude) ([**rid\_location\_t**](#struct-rid_location_t) \*location, double degrees) <br>_Set the latitude for a Location message._ |
|  int | [**rid\_location\_set\_longitude**](#function-rid_location_set_longitude) ([**rid\_location\_t**](#struct-rid_location_t) \*location, double degrees) <br>_Set the longitude for a Location message._ |
|  int | [**rid\_location\_set\_operational\_status**](#function-rid_location_set_operational_status) ([**rid\_location\_t**](#struct-rid_location_t) \*location, [**rid\_operational\_status\_t**](#enum-rid_operational_status_t) status) <br>_Set the operational status for a Location message._ |
|  int | [**rid\_location\_set\_pressure\_altitude**](#function-rid_location_set_pressure_altitude) ([**rid\_location\_t**](#struct-rid_location_t) \*location, float altitude\_m) <br>_Set the pressure altitude for a Location message._ |
|  int | [**rid\_location\_set\_speed**](#function-rid_location_set_speed) ([**rid\_location\_t**](#struct-rid_location_t) \*location, float speed\_ms) <br>_Set the ground speed for a Location message._ |
|  int | [**rid\_location\_set\_speed\_accuracy**](#function-rid_location_set_speed_accuracy) ([**rid\_location\_t**](#struct-rid_location_t) \*location, [**rid\_speed\_accuracy\_t**](#enum-rid_speed_accuracy_t) accuracy) <br>_Set the speed accuracy for a Location message._ |
|  int | [**rid\_location\_set\_timestamp**](#function-rid_location_set_timestamp) ([**rid\_location\_t**](#struct-rid_location_t) \*location, uint16\_t deciseconds) <br>_Set the timestamp for a Location message._ |
|  int | [**rid\_location\_set\_timestamp\_accuracy**](#function-rid_location_set_timestamp_accuracy) ([**rid\_location\_t**](#struct-rid_location_t) \*location, [**rid\_timestamp\_accuracy\_t**](#enum-rid_timestamp_accuracy_t) accuracy) <br>_Set the timestamp accuracy for a Location message._ |
|  int | [**rid\_location\_set\_track\_direction**](#function-rid_location_set_track_direction) ([**rid\_location\_t**](#struct-rid_location_t) \*location, uint16\_t degrees) <br>_Set the track direction for a Location message._ |
|  int | [**rid\_location\_set\_unixtime**](#function-rid_location_set_unixtime) ([**rid\_location\_t**](#struct-rid_location_t) \*location, uint32\_t unixtime) <br>_Set the timestamp from Unix time for a Location message._ |
|  int | [**rid\_location\_set\_vertical\_accuracy**](#function-rid_location_set_vertical_accuracy) ([**rid\_location\_t**](#struct-rid_location_t) \*location, [**rid\_vertical\_accuracy\_t**](#enum-rid_vertical_accuracy_t) accuracy) <br>_Set the vertical position accuracy for a Location message._ |
|  int | [**rid\_location\_set\_vertical\_speed**](#function-rid_location_set_vertical_speed) ([**rid\_location\_t**](#struct-rid_location_t) \*location, float speed\_ms) <br>_Set the vertical speed for a Location message._ |
|  int | [**rid\_location\_to\_json**](#function-rid_location_to_json) (const [**rid\_location\_t**](#struct-rid_location_t) \*location, char \*buffer, size\_t buffer\_size, size\_t \*needed\_size) <br>_Format a Location message as a JSON string._ |
|  int | [**rid\_location\_validate**](#function-rid_location_validate) (const [**rid\_location\_t**](#struct-rid_location_t) \*location) <br>_Validate a Location message structure._ |
|  const char \* | [**rid\_operational\_status\_to\_string**](#function-rid_operational_status_to_string) ([**rid\_operational\_status\_t**](#enum-rid_operational_status_t) status) <br>_Convert operational status to string representation._ |
|  const char \* | [**rid\_speed\_accuracy\_to\_string**](#function-rid_speed_accuracy_to_string) ([**rid\_speed\_accuracy\_t**](#enum-rid_speed_accuracy_t) accuracy) <br>_Convert speed accuracy to string representation._ |
|  const char \* | [**rid\_timestamp\_accuracy\_to\_string**](#function-rid_timestamp_accuracy_to_string) ([**rid\_timestamp\_accuracy\_t**](#enum-rid_timestamp_accuracy_t) accuracy) <br>_Convert timestamp accuracy to string representation._ |
|  const char \* | [**rid\_vertical\_accuracy\_to\_string**](#function-rid_vertical_accuracy_to_string) ([**rid\_vertical\_accuracy\_t**](#enum-rid_vertical_accuracy_t) accuracy) <br>_Convert vertical accuracy to string representation._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**RID\_GEODETIC\_ALTITUDE\_INVALID**](#define-rid_geodetic_altitude_invalid)  FLT\_MAX<br>_Value indicating invalid geodetic altitude._ |
| define  | [**RID\_GEODETIC\_ALTITUDE\_INVALID\_ENCODED**](#define-rid_geodetic_altitude_invalid_encoded)  0<br>_Encoded value for invalid geodetic altitude._ |
| define  | [**RID\_HEIGHT\_INVALID**](#define-rid_height_invalid)  FLT\_MAX<br>_Value indicating invalid height._ |
| define  | [**RID\_HEIGHT\_INVALID\_ENCODED**](#define-rid_height_invalid_encoded)  0<br>_Encoded value for invalid height._ |
| define  | [**RID\_LATITUDE\_INVALID**](#define-rid_latitude_invalid)  DBL\_MAX<br>_Value indicating invalid latitude._ |
| define  | [**RID\_LONGITUDE\_INVALID**](#define-rid_longitude_invalid)  DBL\_MAX<br>_Value indicating invalid longitude._ |
| define  | [**RID\_PRESSURE\_ALTITUDE\_INVALID**](#define-rid_pressure_altitude_invalid)  FLT\_MAX<br>_Value indicating invalid pressure altitude._ |
| define  | [**RID\_PRESSURE\_ALTITUDE\_INVALID\_ENCODED**](#define-rid_pressure_altitude_invalid_encoded)  0<br>_Encoded value for invalid pressure altitude._ |
| define  | [**RID\_SPEED\_INVALID**](#define-rid_speed_invalid)  FLT\_MAX<br>_Value indicating invalid speed._ |
| define  | [**RID\_SPEED\_INVALID\_ENCODED**](#define-rid_speed_invalid_encoded)  255<br>_Encoded value for invalid speed._ |
| define  | [**RID\_TIMESTAMP\_INVALID**](#define-rid_timestamp_invalid)  0xFFFF<br>_Value indicating invalid timestamp._ |
| define  | [**RID\_TIMESTAMP\_MAX**](#define-rid_timestamp_max)  36000<br>_Maximum valid timestamp in deciseconds (1 hour)._ |
| define  | [**RID\_TRACK\_DIRECTION\_MAX**](#define-rid_track_direction_max)  359<br>_Maximum valid track direction in degrees._ |
| define  | [**RID\_TRACK\_DIRECTION\_UNKNOWN**](#define-rid_track_direction_unknown)  361<br>_Value indicating unknown track direction._ |
| define  | [**RID\_TRACK\_DIRECTION\_UNKNOWN\_ENCODED**](#define-rid_track_direction_unknown_encoded)  181<br>_Encoded value for unknown track direction._ |
| define  | [**RID\_VERTICAL\_SPEED\_INVALID**](#define-rid_vertical_speed_invalid)  FLT\_MAX<br>_Value indicating invalid vertical speed._ |
| define  | [**RID\_VERTICAL\_SPEED\_INVALID\_ENCODED**](#define-rid_vertical_speed_invalid_encoded)  126<br>_Encoded value for invalid vertical speed._ |

## Structures and Types Documentation

### enum `rid_ew_direction_t`

_East/West direction flag per ASTM F3411-22a._
```c
enum rid_ew_direction_t {
    RID_EW_DIRECTION_EAST = 0,
    RID_EW_DIRECTION_WEST = 1
};
```

### enum `rid_height_type_t`

_Height reference type per ASTM F3411-22a._
```c
enum rid_height_type_t {
    RID_HEIGHT_TYPE_ABOVE_TAKEOFF = 0,
    RID_HEIGHT_TYPE_AGL = 1
};
```

### enum `rid_horizontal_accuracy_t`

_Horizontal accuracy per ASTM F3411-22a._
```c
enum rid_horizontal_accuracy_t {
    RID_HORIZONTAL_ACCURACY_UNKNOWN = 0,
    RID_HORIZONTAL_ACCURACY_18520M = 1,
    RID_HORIZONTAL_ACCURACY_7408M = 2,
    RID_HORIZONTAL_ACCURACY_3704M = 3,
    RID_HORIZONTAL_ACCURACY_1852M = 4,
    RID_HORIZONTAL_ACCURACY_926M = 5,
    RID_HORIZONTAL_ACCURACY_555M = 6,
    RID_HORIZONTAL_ACCURACY_185M = 7,
    RID_HORIZONTAL_ACCURACY_93M = 8,
    RID_HORIZONTAL_ACCURACY_30M = 9,
    RID_HORIZONTAL_ACCURACY_10M = 10,
    RID_HORIZONTAL_ACCURACY_3M = 11,
    RID_HORIZONTAL_ACCURACY_1M = 12,
    RID_HORIZONTAL_ACCURACY_MAX = 15
};
```

### struct `rid_location_t`

_Location message structure per ASTM F3411-22a._

Variables:

-  uint8\_t baro_altitude_accuracy  

-  uint8\_t ew_direction  

-  uint16\_t geodetic_altitude  

-  uint16\_t height  

-  uint8\_t height_type  

-  uint8\_t horizontal_accuracy  

-  int32\_t latitude  

-  int32\_t longitude  

-  uint8\_t message_type  

-  uint8\_t operational_status  

-  uint16\_t pressure_altitude  

-  uint8\_t protocol_version  

-  uint8\_t reserved_1  

-  uint8\_t reserved_2  

-  uint8\_t reserved_3  

-  uint8\_t speed  

-  uint8\_t speed_accuracy  

-  uint8\_t speed_multiplier  

-  uint16\_t timestamp  

-  uint8\_t timestamp_accuracy  

-  uint8\_t track_direction  

-  uint8\_t vertical_accuracy  

-  int8\_t vertical_speed  

### enum `rid_operational_status_t`

_Operational status per ASTM F3411-22a._
```c
enum rid_operational_status_t {
    RID_OPERATIONAL_STATUS_UNDECLARED = 0,
    RID_OPERATIONAL_STATUS_GROUND = 1,
    RID_OPERATIONAL_STATUS_AIRBORNE = 2,
    RID_OPERATIONAL_STATUS_EMERGENCY = 3,
    RID_OPERATIONAL_STATUS_REMOTE_ID_SYSTEM_FAILURE = 4,
    RID_OPERATIONAL_STATUS_MAX = 15
};
```

### enum `rid_speed_accuracy_t`

_Speed accuracy per ASTM F3411-22a._
```c
enum rid_speed_accuracy_t {
    RID_SPEED_ACCURACY_UNKNOWN = 0,
    RID_SPEED_ACCURACY_10MS = 1,
    RID_SPEED_ACCURACY_3MS = 2,
    RID_SPEED_ACCURACY_1MS = 3,
    RID_SPEED_ACCURACY_03MS = 4,
    RID_SPEED_ACCURACY_MAX = 15
};
```

### enum `rid_timestamp_accuracy_t`

_Timestamp accuracy per ASTM F3411-22a._
```c
enum rid_timestamp_accuracy_t {
    RID_TIMESTAMP_ACCURACY_UNKNOWN = 0,
    RID_TIMESTAMP_ACCURACY_0_1S = 1,
    RID_TIMESTAMP_ACCURACY_0_2S = 2,
    RID_TIMESTAMP_ACCURACY_0_3S = 3,
    RID_TIMESTAMP_ACCURACY_0_4S = 4,
    RID_TIMESTAMP_ACCURACY_0_5S = 5,
    RID_TIMESTAMP_ACCURACY_0_6S = 6,
    RID_TIMESTAMP_ACCURACY_0_7S = 7,
    RID_TIMESTAMP_ACCURACY_0_8S = 8,
    RID_TIMESTAMP_ACCURACY_0_9S = 9,
    RID_TIMESTAMP_ACCURACY_1_0S = 10,
    RID_TIMESTAMP_ACCURACY_1_1S = 11,
    RID_TIMESTAMP_ACCURACY_1_2S = 12,
    RID_TIMESTAMP_ACCURACY_1_3S = 13,
    RID_TIMESTAMP_ACCURACY_1_4S = 14,
    RID_TIMESTAMP_ACCURACY_1_5S = 15
};
```

### enum `rid_vertical_accuracy_t`

_Vertical accuracy per ASTM F3411-22a._
```c
enum rid_vertical_accuracy_t {
    RID_VERTICAL_ACCURACY_UNKNOWN = 0,
    RID_VERTICAL_ACCURACY_150M = 1,
    RID_VERTICAL_ACCURACY_45M = 2,
    RID_VERTICAL_ACCURACY_25M = 3,
    RID_VERTICAL_ACCURACY_10M = 4,
    RID_VERTICAL_ACCURACY_3M = 5,
    RID_VERTICAL_ACCURACY_1M = 6,
    RID_VERTICAL_ACCURACY_MAX = 15
};
```


## Functions Documentation

### function `rid_height_type_to_string`

_Convert height type to string representation._
```c
const char * rid_height_type_to_string (
    rid_height_type_t type
) 
```


**Parameters:**


* `type` The height type to convert.


**Returns:**

String representation of the height type. Returns "UNKNOWN" for invalid values.
### function `rid_horizontal_accuracy_to_string`

_Convert horizontal accuracy to string representation._
```c
const char * rid_horizontal_accuracy_to_string (
    rid_horizontal_accuracy_t accuracy
) 
```


**Parameters:**


* `accuracy` The horizontal accuracy to convert.


**Returns:**

String representation of the horizontal accuracy. Returns "UNKNOWN" for invalid values.
### function `rid_location_get_baro_altitude_accuracy`

_Get the barometric altitude accuracy from a Location message._
```c
rid_vertical_accuracy_t rid_location_get_baro_altitude_accuracy (
    const rid_location_t *location
) 
```


**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

The barometric altitude accuracy or RID\_VERTICAL\_ACCURACY\_UNKNOWN if location is NULL.
### function `rid_location_get_geodetic_altitude`

_Get the geodetic altitude from a Location message._
```c
float rid_location_get_geodetic_altitude (
    const rid_location_t *location
) 
```


This is the GNSS height above or below the WGS-84 reference ellipsoid. In layman's terms, this is the height you get from you GPS.



**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

Geodetic altitude in meters or RID\_GEODETIC\_ALTITUDE\_INVALID if location is NULL.
### function `rid_location_get_height`

_Get the height from a Location message._
```c
float rid_location_get_height (
    const rid_location_t *location
) 
```


This is an altitude relative to a local reference point which is either the takeoff location or above ground level. The reference point is set separately with [**rid\_location\_set\_height\_type()**](#function-rid_location_set_height_type) function.



**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

Height in meters or RID\_HEIGHT\_INVALID if location is NULL.
### function `rid_location_get_height_type`

_Get the height reference type from a Location message._
```c
rid_height_type_t rid_location_get_height_type (
    const rid_location_t *location
) 
```


**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

The height reference type or RID\_HEIGHT\_TYPE\_ABOVE\_TAKEOFF if location is NULL.
### function `rid_location_get_horizontal_accuracy`

_Get the horizontal position accuracy from a Location message._
```c
rid_horizontal_accuracy_t rid_location_get_horizontal_accuracy (
    const rid_location_t *location
) 
```


**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

The horizontal accuracy or RID\_HORIZONTAL\_ACCURACY\_UNKNOWN if location is NULL.
### function `rid_location_get_latitude`

_Get the latitude from a Location message._
```c
double rid_location_get_latitude (
    const rid_location_t *location
) 
```


Returns RID\_LATITUDE\_INVALID when both latitude and longitude are zero.



**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

Latitude in degrees or RID\_LATITUDE\_INVALID if location is NULL or if both encoded latitude and longitude are 0.
### function `rid_location_get_longitude`

_Get the longitude from a Location message._
```c
double rid_location_get_longitude (
    const rid_location_t *location
) 
```


Returns RID\_LONGITUDE\_INVALID when both latitude and longitude are zero.



**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

Longitude in degrees or RID\_LONGITUDE\_INVALID if location is NULL or if both encoded latitude and longitude are 0.
### function `rid_location_get_operational_status`

_Get the operational status from a Location message._
```c
rid_operational_status_t rid_location_get_operational_status (
    const rid_location_t *location
) 
```


**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

The operational status or RID\_OPERATIONAL\_STATUS\_UNDECLARED if location is NULL.
### function `rid_location_get_pressure_altitude`

_Get the pressure altitude from a Location message._
```c
float rid_location_get_pressure_altitude (
    const rid_location_t *location
) 
```


This is the uncorrected barometric altitude referenced to the standard atmosphere (29.92 inHg / 1013.25 mb). It is not corrected for the local altimeter setting. It is used as common reference for algorithms computing altitude differences between aircraft.



**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

Pressure altitude in meters or RID\_PRESSURE\_ALTITUDE\_INVALID if location is NULL.
### function `rid_location_get_speed`

_Get the ground speed from a Location message._
```c
float rid_location_get_speed (
    const rid_location_t *location
) 
```


**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

Speed in meters per second or RID\_SPEED\_INVALID if location is NULL.
### function `rid_location_get_speed_accuracy`

_Get the speed accuracy from a Location message._
```c
rid_speed_accuracy_t rid_location_get_speed_accuracy (
    const rid_location_t *location
) 
```


**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

The speed accuracy or RID\_SPEED\_ACCURACY\_UNKNOWN if location is NULL.
### function `rid_location_get_timestamp`

_Get the timestamp from a Location message._
```c
uint16_t rid_location_get_timestamp (
    const rid_location_t *location
) 
```


**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

Time in deciseconds since the hour or RID\_TIMESTAMP\_INVALID if location is NULL.
### function `rid_location_get_timestamp_accuracy`

_Get the timestamp accuracy from a Location message._
```c
rid_timestamp_accuracy_t rid_location_get_timestamp_accuracy (
    const rid_location_t *location
) 
```


**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

The timestamp accuracy or RID\_TIMESTAMP\_ACCURACY\_UNKNOWN if location is NULL.
### function `rid_location_get_track_direction`

_Get the track direction from a Location message._
```c
uint16_t rid_location_get_track_direction (
    const rid_location_t *location
) 
```


**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

Track direction in degrees (0-359) or RID\_TRACK\_DIRECTION\_UNKNOWN, including when location is NULL.
### function `rid_location_get_vertical_accuracy`

_Get the vertical position accuracy from a Location message._
```c
rid_vertical_accuracy_t rid_location_get_vertical_accuracy (
    const rid_location_t *location
) 
```


**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

The vertical accuracy or RID\_VERTICAL\_ACCURACY\_UNKNOWN if location is NULL.
### function `rid_location_get_vertical_speed`

_Get the vertical speed from a Location message._
```c
float rid_location_get_vertical_speed (
    const rid_location_t *location
) 
```


**Parameters:**


* `location` Pointer to the Location message structure.


**Returns:**

Vertical speed in meters per second or RID\_VERTICAL\_SPEED\_INVALID if location is NULL.
### function `rid_location_init`

_Initialize a Location message structure._
```c
int rid_location_init (
    rid_location_t *location
) 
```


Sets protocol version to RID\_PROTOCOL\_VERSION\_2 and message type to RID\_MESSAGE\_TYPE\_LOCATION. All other fields are set to invalid markers.



**Parameters:**


* `location` Pointer to the Location message structure to initialize.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL.
### function `rid_location_set_baro_altitude_accuracy`

_Set the barometric altitude accuracy for a Location message._
```c
int rid_location_set_baro_altitude_accuracy (
    rid_location_t *location,
    rid_vertical_accuracy_t accuracy
) 
```


**Parameters:**


* `location` Pointer to the Location message structure. 
* `accuracy` The barometric altitude accuracy to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL.
### function `rid_location_set_geodetic_altitude`

_Set the geodetic altitude for a Location message._
```c
int rid_location_set_geodetic_altitude (
    rid_location_t *location,
    float altitude_m
) 
```


Encodes the value per ASTM F3411-22a Table 7 with 0.5 m resolution. Pass RID\_GEODETIC\_ALTITUDE\_INVALID to mark the altitude as unknown.

This is the GNSS height above or below the WGS-84 reference ellipsoid. In layman's terms, this is the height you get from you GPS.



**Parameters:**


* `location` Pointer to the Location message structure. 
* `altitude_m` Geodetic altitude in meters (-1000 to 31767), or RID\_GEODETIC\_ALTITUDE\_INVALID for unknown.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if altitude\_m is outside the valid range.
### function `rid_location_set_height`

_Set the height for a Location message._
```c
int rid_location_set_height (
    rid_location_t *location,
    float height_m
) 
```


This is an altitude relative to a local reference point which is either the takeoff location or above ground level. The reference point is set separately with [**rid\_location\_set\_height\_type()**](#function-rid_location_set_height_type) function.

Encodes the value per ASTM F3411-22a Table 7 with 0.5 m resolution. Pass RID\_HEIGHT\_INVALID to mark the height as unknown.



**Parameters:**


* `location` Pointer to the Location message structure. 
* `height_m` Height in meters (-1000 to 31767), or RID\_HEIGHT\_INVALID for unknown.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if height\_m is outside the valid range.
### function `rid_location_set_height_type`

_Set the height reference type for a Location message._
```c
int rid_location_set_height_type (
    rid_location_t *location,
    rid_height_type_t type
) 
```


**Parameters:**


* `location` Pointer to the Location message structure. 
* `type` The height reference type to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL.
### function `rid_location_set_horizontal_accuracy`

_Set the horizontal position accuracy for a Location message._
```c
int rid_location_set_horizontal_accuracy (
    rid_location_t *location,
    rid_horizontal_accuracy_t accuracy
) 
```


**Parameters:**


* `location` Pointer to the Location message structure. 
* `accuracy` The horizontal accuracy to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL.
### function `rid_location_set_latitude`

_Set the latitude for a Location message._
```c
int rid_location_set_latitude (
    rid_location_t *location,
    double degrees
) 
```


Encodes the value per ASTM F3411-22a Table 7 with 10^-7 degree resolution. Pass RID\_LATITUDE\_INVALID to mark the latitude as unknown.



**Parameters:**


* `location` Pointer to the Location message structure. 
* `degrees` Latitude in degrees (-90 to 90) or RID\_LATITUDE\_INVALID for unknown.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if degrees is outside the valid range.
### function `rid_location_set_longitude`

_Set the longitude for a Location message._
```c
int rid_location_set_longitude (
    rid_location_t *location,
    double degrees
) 
```


Encodes the value per ASTM F3411-22a Table 7 with 10^-7 degree resolution. Pass RID\_LONGITUDE\_INVALID to mark the longitude as unknown.



**Parameters:**


* `location` Pointer to the Location message structure. 
* `degrees` Longitude in degrees (-180 to 180) or RID\_LONGITUDE\_INVALID for unknown.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if degrees is outside the valid range.
### function `rid_location_set_operational_status`

_Set the operational status for a Location message._
```c
int rid_location_set_operational_status (
    rid_location_t *location,
    rid_operational_status_t status
) 
```


**Parameters:**


* `location` Pointer to the Location message structure. 
* `status` The operational status to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL.
### function `rid_location_set_pressure_altitude`

_Set the pressure altitude for a Location message._
```c
int rid_location_set_pressure_altitude (
    rid_location_t *location,
    float altitude_m
) 
```


Encodes the value per ASTM F3411-22a Table 7 with 0.5 m resolution. Pass RID\_PRESSURE\_ALTITUDE\_INVALID to mark the altitude as unknown.

This is the uncorrected barometric altitude referenced to the standard atmosphere (29.92 inHg / 1013.25 mb). It is not corrected for the local altimeter setting. It is used as common reference for algorithms computing altitude differences between aircraft.



**Parameters:**


* `location` Pointer to the Location message structure. 
* `altitude_m` Pressure altitude in meters (-1000 to 31767) or RID\_PRESSURE\_ALTITUDE\_INVALID for unknown.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if altitude\_m is outside the valid range.
### function `rid_location_set_speed`

_Set the ground speed for a Location message._
```c
int rid_location_set_speed (
    rid_location_t *location,
    float speed_ms
) 
```


Values above 254.25 m/s are clamped to 254.25 m/s.



**Parameters:**


* `location` Pointer to the Location message structure. 
* `speed_ms` Speed in meters per second (0 to 254.25).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if speed\_ms is negative.
### function `rid_location_set_speed_accuracy`

_Set the speed accuracy for a Location message._
```c
int rid_location_set_speed_accuracy (
    rid_location_t *location,
    rid_speed_accuracy_t accuracy
) 
```


**Parameters:**


* `location` Pointer to the Location message structure. 
* `accuracy` The speed accuracy to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL.
### function `rid_location_set_timestamp`

_Set the timestamp for a Location message._
```c
int rid_location_set_timestamp (
    rid_location_t *location,
    uint16_t deciseconds
) 
```


**Parameters:**


* `location` Pointer to the Location message structure. 
* `deciseconds` Time in deciseconds since the hour.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL.
### function `rid_location_set_timestamp_accuracy`

_Set the timestamp accuracy for a Location message._
```c
int rid_location_set_timestamp_accuracy (
    rid_location_t *location,
    rid_timestamp_accuracy_t accuracy
) 
```


**Parameters:**


* `location` Pointer to the Location message structure. 
* `accuracy` The timestamp accuracy to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL.
### function `rid_location_set_track_direction`

_Set the track direction for a Location message._
```c
int rid_location_set_track_direction (
    rid_location_t *location,
    uint16_t degrees
) 
```


**Parameters:**


* `location` Pointer to the Location message structure. 
* `degrees` Track direction in degrees (0-359) or RID\_TRACK\_DIRECTION\_UNKNOWN.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL.
### function `rid_location_set_unixtime`

_Set the timestamp from Unix time for a Location message._
```c
int rid_location_set_unixtime (
    rid_location_t *location,
    uint32_t unixtime
) 
```


Converts Unix timestamp to deciseconds since the hour.



**Parameters:**


* `location` Pointer to the Location message structure. 
* `unixtime` Unix timestamp (seconds since epoch).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL.
### function `rid_location_set_vertical_accuracy`

_Set the vertical position accuracy for a Location message._
```c
int rid_location_set_vertical_accuracy (
    rid_location_t *location,
    rid_vertical_accuracy_t accuracy
) 
```


**Parameters:**


* `location` Pointer to the Location message structure. 
* `accuracy` The vertical accuracy to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL.
### function `rid_location_set_vertical_speed`

_Set the vertical speed for a Location message._
```c
int rid_location_set_vertical_speed (
    rid_location_t *location,
    float speed_ms
) 
```


Values outside -62 to 62 m/s range are clamped to the nearest limit.



**Parameters:**


* `location` Pointer to the Location message structure. 
* `speed_ms` Vertical speed in meters per second (-62 to 62).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if location is NULL.
### function `rid_location_to_json`

_Format a Location message as a JSON string._
```c
int rid_location_to_json (
    const rid_location_t *location,
    char *buffer,
    size_t buffer_size,
    size_t *needed_size
) 
```


**Parameters:**


* `location` Pointer to the Location message structure. 
* `buffer` Buffer to store the JSON string or NULL. 
* `buffer_size` Size of the buffer. 
* `needed_size` If non-NULL receives the required buffer size.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if `location` is NULL or if both`buffer` and`needed_size` are NULL.
* `RID_ERROR_BUFFER_TOO_SMALL` if `buffer` is too small.
### function `rid_location_validate`

_Validate a Location message structure._
```c
int rid_location_validate (
    const rid_location_t *location
) 
```


Checks that all fields contain valid encoded values according to ASTM F3411-22a. This validates the raw encoded values, not decoded physical values.



**Parameters:**


* `location` Pointer to the Location message structure to validate.


**Return value:**


* `RID_SUCCESS` if all fields are valid. 
* `RID_ERROR_NULL_POINTER` if location is NULL. 
* `RID_ERROR_INVALID_PROTOCOL_VERSION` if protocol version is invalid. 
* `RID_ERROR_UNKNOWN_MESSAGE_TYPE` if message type is not LOCATION. 
* `RID_ERROR_INVALID_LATITUDE` if latitude is out of range. 
* `RID_ERROR_INVALID_LONGITUDE` if longitude is out of range. 
* `RID_ERROR_INVALID_TRACK_DIRECTION` if track direction is out of range. 
* `RID_ERROR_INVALID_TIMESTAMP` if timestamp is out of range.
### function `rid_operational_status_to_string`

_Convert operational status to string representation._
```c
const char * rid_operational_status_to_string (
    rid_operational_status_t status
) 
```


**Parameters:**


* `status` The operational status to convert.


**Returns:**

String representation of the operational status. Returns "UNKNOWN" for invalid values.
### function `rid_speed_accuracy_to_string`

_Convert speed accuracy to string representation._
```c
const char * rid_speed_accuracy_to_string (
    rid_speed_accuracy_t accuracy
) 
```


**Parameters:**


* `accuracy` The speed accuracy to convert.


**Returns:**

String representation of the speed accuracy. Returns "UNKNOWN" for invalid values.
### function `rid_timestamp_accuracy_to_string`

_Convert timestamp accuracy to string representation._
```c
const char * rid_timestamp_accuracy_to_string (
    rid_timestamp_accuracy_t accuracy
) 
```


**Parameters:**


* `accuracy` The timestamp accuracy to convert.


**Returns:**

String representation of the timestamp accuracy. Returns "UNKNOWN" for invalid values.
### function `rid_vertical_accuracy_to_string`

_Convert vertical accuracy to string representation._
```c
const char * rid_vertical_accuracy_to_string (
    rid_vertical_accuracy_t accuracy
) 
```


**Parameters:**


* `accuracy` The vertical accuracy to convert.


**Returns:**

String representation of the vertical accuracy. Returns "UNKNOWN" for invalid values.

## Macros Documentation

### define `RID_GEODETIC_ALTITUDE_INVALID`

_Value indicating invalid geodetic altitude._
```c
#define RID_GEODETIC_ALTITUDE_INVALID FLT_MAX
```

### define `RID_GEODETIC_ALTITUDE_INVALID_ENCODED`

_Encoded value for invalid geodetic altitude._
```c
#define RID_GEODETIC_ALTITUDE_INVALID_ENCODED 0
```

### define `RID_HEIGHT_INVALID`

_Value indicating invalid height._
```c
#define RID_HEIGHT_INVALID FLT_MAX
```

### define `RID_HEIGHT_INVALID_ENCODED`

_Encoded value for invalid height._
```c
#define RID_HEIGHT_INVALID_ENCODED 0
```

### define `RID_LATITUDE_INVALID`

_Value indicating invalid latitude._
```c
#define RID_LATITUDE_INVALID DBL_MAX
```

### define `RID_LONGITUDE_INVALID`

_Value indicating invalid longitude._
```c
#define RID_LONGITUDE_INVALID DBL_MAX
```

### define `RID_PRESSURE_ALTITUDE_INVALID`

_Value indicating invalid pressure altitude._
```c
#define RID_PRESSURE_ALTITUDE_INVALID FLT_MAX
```

### define `RID_PRESSURE_ALTITUDE_INVALID_ENCODED`

_Encoded value for invalid pressure altitude._
```c
#define RID_PRESSURE_ALTITUDE_INVALID_ENCODED 0
```

### define `RID_SPEED_INVALID`

_Value indicating invalid speed._
```c
#define RID_SPEED_INVALID FLT_MAX
```

### define `RID_SPEED_INVALID_ENCODED`

_Encoded value for invalid speed._
```c
#define RID_SPEED_INVALID_ENCODED 255
```

### define `RID_TIMESTAMP_INVALID`

_Value indicating invalid timestamp._
```c
#define RID_TIMESTAMP_INVALID 0xFFFF
```

### define `RID_TIMESTAMP_MAX`

_Maximum valid timestamp in deciseconds (1 hour)._
```c
#define RID_TIMESTAMP_MAX 36000
```

### define `RID_TRACK_DIRECTION_MAX`

_Maximum valid track direction in degrees._
```c
#define RID_TRACK_DIRECTION_MAX 359
```

### define `RID_TRACK_DIRECTION_UNKNOWN`

_Value indicating unknown track direction._
```c
#define RID_TRACK_DIRECTION_UNKNOWN 361
```

### define `RID_TRACK_DIRECTION_UNKNOWN_ENCODED`

_Encoded value for unknown track direction._
```c
#define RID_TRACK_DIRECTION_UNKNOWN_ENCODED 181
```

### define `RID_VERTICAL_SPEED_INVALID`

_Value indicating invalid vertical speed._
```c
#define RID_VERTICAL_SPEED_INVALID FLT_MAX
```

### define `RID_VERTICAL_SPEED_INVALID_ENCODED`

_Encoded value for invalid vertical speed._
```c
#define RID_VERTICAL_SPEED_INVALID_ENCODED 126
```


## File include/rid/message.h

_Message header handling per ASTM F3411-22a._

Example usage: 
````cpp
    uint8_t buffer[] = {
        0xe3, 0xd2, 0x27, 0xcf, 0xfd, 0x7f, 0x00, 0x00,
        0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00
    };

    const rid_message_t *message = (const rid_message_t *)buffer;

    rid_protocol_version_t version = rid_message_get_protocol_version(message);
    rid_message_type_t type = rid_message_get_type(message);

    printf("Protocol version: %u\n", version);
    printf("Message type:     %u\n", type);
````

## Structures and Types

| Type | Name |
| ---: | :--- |
| enum  | [**rid\_error\_t**](#enum-rid_error_t)  <br> |
| struct | [**rid\_message\_t**](#struct-rid_message_t) <br>_Generic message structure for any Remote ID message._ |
| enum  | [**rid\_message\_type\_t**](#enum-rid_message_type_t)  <br> |
| enum  | [**rid\_protocol\_version\_t**](#enum-rid_protocol_version_t)  <br> |

## Functions

| Type | Name |
| ---: | :--- |
|  const char \* | [**rid\_error\_to\_string**](#function-rid_error_to_string) ([**rid\_error\_t**](#enum-rid_error_t) error) <br>_Convert error code to string representation._ |
|  [**rid\_protocol\_version\_t**](#enum-rid_protocol_version_t) | [**rid\_message\_get\_protocol\_version**](#function-rid_message_get_protocol_version) (const void \*message) <br>_Get the protocol version from a generic message structure._ |
|  [**rid\_message\_type\_t**](#enum-rid_message_type_t) | [**rid\_message\_get\_type**](#function-rid_message_get_type) (const void \*message) <br>_Get the message type from a generic message structure._ |
|  int | [**rid\_message\_to\_json**](#function-rid_message_to_json) (const void \*message, char \*buffer, size\_t buffer\_size, size\_t \*needed\_size) <br>_Format any Remote ID message as a JSON string._ |
|  const char \* | [**rid\_message\_type\_to\_string**](#function-rid_message_type_to_string) ([**rid\_message\_type\_t**](#enum-rid_message_type_t) type) <br>_Convert message type to string representation._ |
|  int | [**rid\_message\_validate**](#function-rid_message_validate) (const void \*message) <br>_Validate any Remote ID message._ |
|  const char \* | [**rid\_protocol\_version\_to\_string**](#function-rid_protocol_version_to_string) ([**rid\_protocol\_version\_t**](#enum-rid_protocol_version_t) version) <br>_Convert protocol version to string representation._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**RID\_MESSAGE\_SIZE**](#define-rid_message_size)  25<br>_Size of a single message in bytes._ |

## Structures and Types Documentation

### enum `rid_error_t`

```c
enum rid_error_t {
    RID_SUCCESS = 0,
    RID_ERROR_NULL_POINTER = -1,
    RID_ERROR_BUFFER_TOO_SMALL = -2,
    RID_ERROR_BUFFER_TOO_LARGE = -3,
    RID_ERROR_INVALID_CHARACTER = -4,
    RID_ERROR_OUT_OF_RANGE = -5,
    RID_ERROR_UNKNOWN_MESSAGE_TYPE = -6,
    RID_ERROR_INVALID_LATITUDE = -7,
    RID_ERROR_INVALID_LONGITUDE = -8,
    RID_ERROR_INVALID_TRACK_DIRECTION = -9,
    RID_ERROR_INVALID_TIMESTAMP = -10,
    RID_ERROR_INVALID_PROTOCOL_VERSION = -11,
    RID_ERROR_INVALID_MESSAGE_COUNT = -12,
    RID_ERROR_INVALID_MESSAGE_SIZE = -13,
    RID_ERROR_INVALID_LAST_PAGE_INDEX = -14,
    RID_ERROR_INVALID_PAGE_NUMBER = -15,
    RID_ERROR_NON_EMPTY_SIGNATURE = -16,
    RID_ERROR_INVALID_UUID_VERSION = -17,
    RID_ERROR_INVALID_UUID_VARIANT = -18,
    RID_ERROR_INVALID_UUID_PADDING = -19,
    RID_ERROR_INVALID_SERIAL_NUMBER = -20,
    RID_ERROR_INVALID_CAA_REGISTRATION_ID = -21,
    RID_ERROR_NOT_FOUND = -22,
    RID_ERROR_INVALID_MESSAGE_TYPE = -23,
    RID_ERROR_NOT_IMPLEMENTED = -24
};
```

### struct `rid_message_t`

_Generic message structure for any Remote ID message._

All messages are 25 bytes with a common header. Cast to specific message type after checking message\_type field.

Variables:

-  uint8\_t body  

-  uint8\_t message_type  

-  uint8\_t protocol_version  

### enum `rid_message_type_t`

```c
enum rid_message_type_t {
    RID_MESSAGE_TYPE_BASIC_ID = 0x00,
    RID_MESSAGE_TYPE_LOCATION = 0x01,
    RID_MESSAGE_TYPE_AUTH = 0x02,
    RID_MESSAGE_TYPE_SELF_ID = 0x03,
    RID_MESSAGE_TYPE_SYSTEM = 0x04,
    RID_MESSAGE_TYPE_OPERATOR_ID = 0x05,
    RID_MESSAGE_TYPE_MESSAGE_PACK = 0x0F
};
```

### enum `rid_protocol_version_t`

```c
enum rid_protocol_version_t {
    RID_PROTOCOL_VERSION_0 = 0x00,
    RID_PROTOCOL_VERSION_1 = 0x01,
    RID_PROTOCOL_VERSION_2 = 0x02,
    RID_PROTOCOL_PRIVATE_USE = 0x0F
};
```


## Functions Documentation

### function `rid_error_to_string`

_Convert error code to string representation._
```c
const char * rid_error_to_string (
    rid_error_t error
) 
```


**Parameters:**


* `error` The error code to convert.


**Returns:**

String representation of the error code. Returns "UNKNOWN" for invalid values.
### function `rid_message_get_protocol_version`

_Get the protocol version from a generic message structure._
```c
rid_protocol_version_t rid_message_get_protocol_version (
    const void *message
) 
```


**Parameters:**


* `message` Pointer to the message structure.


**Returns:**

The protocol version or RID\_PROTOCOL\_VERSION\_0 if message is NULL.
### function `rid_message_get_type`

_Get the message type from a generic message structure._
```c
rid_message_type_t rid_message_get_type (
    const void *message
) 
```


**Parameters:**


* `message` Pointer to the message structure.


**Returns:**

The message type or RID\_MESSAGE\_TYPE\_BASIC\_ID if message is NULL.
### function `rid_message_to_json`

_Format any Remote ID message as a JSON string._
```c
int rid_message_to_json (
    const void *message,
    char *buffer,
    size_t buffer_size,
    size_t *needed_size
) 
```


Determines the message type and calls the appropriate type-specific \*\_to\_json() function.



**Parameters:**


* `message` Pointer to any Remote ID message structure. 
* `buffer` Buffer to store the JSON string or NULL. 
* `buffer_size` Size of the buffer. 
* `needed_size` If non-NULL receives the required buffer size.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if `message` is NULL or if both`buffer` and`needed_size` are NULL.
* `RID_ERROR_BUFFER_TOO_SMALL` if `buffer` is too small.
### function `rid_message_type_to_string`

_Convert message type to string representation._
```c
const char * rid_message_type_to_string (
    rid_message_type_t type
) 
```


**Parameters:**


* `type` The message type to convert.


**Returns:**

String representation of the message type. Returns "UNKNOWN" for invalid values.
### function `rid_message_validate`

_Validate any Remote ID message._
```c
int rid_message_validate (
    const void *message
) 
```


Dispatches to the appropriate type-specific validation function based on the message type field.



**Parameters:**


* `message` Pointer to the message structure to validate.


**Return value:**


* `RID_SUCCESS` if validation passes. 
* `RID_ERROR_NULL_POINTER` if message is NULL. 
* `RID_ERROR_UNKNOWN_MESSAGE_TYPE` if message type is not recognized. 
* `Other` error codes from type-specific validators.
### function `rid_protocol_version_to_string`

_Convert protocol version to string representation._
```c
const char * rid_protocol_version_to_string (
    rid_protocol_version_t version
) 
```


**Parameters:**


* `version` The protocol version to convert.


**Returns:**

String representation of the protocol version. Returns "UNKNOWN" for invalid values.

## Macros Documentation

### define `RID_MESSAGE_SIZE`

_Size of a single message in bytes._
```c
#define RID_MESSAGE_SIZE 25
```


## File include/rid/message_pack.h

_Message pack handling per ASTM F3411-22a._

Example usage: 
````cpp
    rid_message_pack_t pack;
    rid_basic_id_t basic_id_1;
    rid_basic_id_t basic_id_2;
    rid_location_t location;
    rid_self_id_t self_id;
    rid_operator_id_t operator_id;
    rid_system_t system;

    rid_message_pack_init(&pack);

    rid_basic_id_init(&basic_id_1);
    rid_basic_id_init(&basic_id_2);
    rid_location_init(&location);
    rid_self_id_init(&self_id);
    rid_operator_id_init(&operator_id);
    rid_system_init(&system);

    rid_message_pack_add_message(&pack, &basic_id_1);
    rid_message_pack_add_message(&pack, &basic_id_2);
    rid_message_pack_add_message(&pack, &location);
    rid_message_pack_add_message(&pack, &self_id);
    rid_message_pack_add_message(&pack, &operator_id);
    rid_message_pack_add_message(&pack, &system);

    printf("%s:\n", rid_message_type_to_string(rid_message_get_type(&pack)));
    hexdump(&pack, rid_message_pack_size(&pack));

    uint8_t count = rid_message_pack_message_count(&pack);

    for (uint8_t i = 0; i < count; i++) {
        const rid_message_t *message = rid_message_pack_get_message_at(&pack, i);
        if (message) {
            printf("%s:\n", rid_message_type_to_string(rid_message_get_type(message)));
            hexdump(&message, sizeof(rid_message_t));
        }
    }
````

## Structures and Types

| Type | Name |
| ---: | :--- |
| struct | [**rid\_message\_pack\_t**](#struct-rid_message_pack_t) <br>_Message Pack structure per ASTM F3411-22a._ |

## Functions

| Type | Name |
| ---: | :--- |
|  int | [**rid\_message\_pack\_add\_message**](#function-rid_message_pack_add_message) ([**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack, const void \*message) <br>_Add a message to a Message Pack._ |
|  int | [**rid\_message\_pack\_copy\_message\_at**](#function-rid_message_pack_copy_message_at) (const [**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack, uint8\_t index, void \*message) <br>_Copy a message at the specified index out of a Message Pack._ |
|  int | [**rid\_message\_pack\_delete\_message\_at**](#function-rid_message_pack_delete_message_at) ([**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack, uint8\_t index) <br>_Delete a message at the specified index._ |
|  int | [**rid\_message\_pack\_find\_message\_index\_by\_type**](#function-rid_message_pack_find_message_index_by_type) (const [**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack, [**rid\_message\_type\_t**](#enum-rid_message_type_t) type, uint8\_t start\_index, uint8\_t \*index) <br>_Find the index of the first message of the specified type starting at an index._ |
|  int | [**rid\_message\_pack\_get\_auth**](#function-rid_message_pack_get_auth) (const [**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack, [**rid\_auth\_t**](#struct-rid_auth_t) \*auth) <br>_Get Auth message from a Message Pack._ |
|  const void \* | [**rid\_message\_pack\_get\_message\_at**](#function-rid_message_pack_get_message_at) (const [**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack, uint8\_t index) <br>_Get a pointer to a message at the specified index._ |
|  int | [**rid\_message\_pack\_get\_message\_type\_at**](#function-rid_message_pack_get_message_type_at) (const [**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack, uint8\_t index, [**rid\_message\_type\_t**](#enum-rid_message_type_t) \*type) <br>_Get the message type at the specified index._ |
|  const void \* | [**rid\_message\_pack\_get\_messages**](#function-rid_message_pack_get_messages) (const [**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack) <br>_Get a pointer to the messages array in a Message Pack._ |
|  int | [**rid\_message\_pack\_init**](#function-rid_message_pack_init) ([**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack) <br>_Initialize a Message Pack structure._ |
|  uint8\_t | [**rid\_message\_pack\_message\_count**](#function-rid_message_pack_message_count) (const [**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack) <br>_Get the message count from a Message Pack._ |
|  size\_t | [**rid\_message\_pack\_messages\_size**](#function-rid_message_pack_messages_size) (const [**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack) <br>_Get the combined size of messages in a Message Pack in bytes._ |
|  int | [**rid\_message\_pack\_set\_auth**](#function-rid_message_pack_set_auth) ([**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack, const [**rid\_auth\_t**](#struct-rid_auth_t) \*auth) <br>_Set Auth message in a Message Pack._ |
|  int | [**rid\_message\_pack\_set\_message\_at**](#function-rid_message_pack_set_message_at) ([**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack, uint8\_t index, const void \*message) <br>_Replace a message at the specified index._ |
|  size\_t | [**rid\_message\_pack\_size**](#function-rid_message_pack_size) (const [**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack) <br>_Get the size of a Message Pack in bytes._ |
|  int | [**rid\_message\_pack\_sort**](#function-rid_message_pack_sort) ([**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack) <br>_Sort messages in a Message Pack by message type._ |
|  int | [**rid\_message\_pack\_to\_json**](#function-rid_message_pack_to_json) (const [**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack, char \*buffer, size\_t buffer\_size, size\_t \*needed\_size) <br>_Format a Message Pack as a JSON string._ |
|  int | [**rid\_message\_pack\_validate**](#function-rid_message_pack_validate) (const [**rid\_message\_pack\_t**](#struct-rid_message_pack_t) \*pack) <br>_Validate a Message Pack structure._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**RID\_MESSAGE\_PACK\_HEADER\_SIZE**](#define-rid_message_pack_header_size)  3<br>_Header size of a Message Pack in bytes._ |
| define  | [**RID\_MESSAGE\_PACK\_MAX\_MESSAGES**](#define-rid_message_pack_max_messages)  9<br>_Maximum number of messages in a Message Pack._ |
| define  | [**RID\_MESSAGE\_PACK\_MAX\_SIZE**](#define-rid_message_pack_max_size)  228<br>_Maximum size of a Message Pack in bytes (header + 9 messages)._ |
| define  | [**RID\_MESSAGE\_PACK\_MIN\_SIZE**](#define-rid_message_pack_min_size)  28<br>_Minimum size of a Message Pack in bytes (header + 1 message)._ |

## Structures and Types Documentation

### struct `rid_message_pack_t`

_Message Pack structure per ASTM F3411-22a._

Contains up to 9 concatenated messages of 25 bytes each.

Variables:

-  uint8\_t message_count  

-  uint8\_t message_size  

-  uint8\_t message_type  

-  uint8\_t messages  

-  uint8\_t protocol_version  


## Functions Documentation

### function `rid_message_pack_add_message`

_Add a message to a Message Pack._
```c
int rid_message_pack_add_message (
    rid_message_pack_t *pack,
    const void *message
) 
```


**Parameters:**


* `pack` Pointer to the Message Pack structure. 
* `message` Pointer to the message to add.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if pack or message is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if pack already contains RID\_MESSAGE\_PACK\_MAX\_MESSAGES.
### function `rid_message_pack_copy_message_at`

_Copy a message at the specified index out of a Message Pack._
```c
int rid_message_pack_copy_message_at (
    const rid_message_pack_t *pack,
    uint8_t index,
    void *message
) 
```


Copies RID\_MESSAGE\_SIZE bytes from the Message Pack at the given index into the caller provided buffer. The destination must point to a struct matching the message type at the index.



**Parameters:**


* `pack` Pointer to the Message Pack structure. 
* `index` Index of the message to copy. 
* `message` Pointer to the destination buffer.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if pack or message is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if index is out of range.
### function `rid_message_pack_delete_message_at`

_Delete a message at the specified index._
```c
int rid_message_pack_delete_message_at (
    rid_message_pack_t *pack,
    uint8_t index
) 
```


Messages after the deleted one are shifted down to fill the gap.



**Parameters:**


* `pack` Pointer to the Message Pack structure. 
* `index` Index of the message to delete (0-based).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if pack is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if index is out of range.
### function `rid_message_pack_find_message_index_by_type`

_Find the index of the first message of the specified type starting at an index._
```c
int rid_message_pack_find_message_index_by_type (
    const rid_message_pack_t *pack,
    rid_message_type_t type,
    uint8_t start_index,
    uint8_t *index
) 
```


**Parameters:**


* `pack` Pointer to the Message Pack structure. 
* `type` The message type to search for. 
* `start_index` Index to start the search from. 
* `index` Pointer to store the index of the first found message.


**Return value:**


* `RID_SUCCESS` on success, \*index holds the matching index. 
* `RID_ERROR_NULL_POINTER` if pack or index is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if start\_index is past the last message. 
* `RID_ERROR_NOT_FOUND` if no message of the given type is found.
### function `rid_message_pack_get_auth`

_Get Auth message from a Message Pack._
```c
int rid_message_pack_get_auth (
    const rid_message_pack_t *pack,
    rid_auth_t *auth
) 
```


Searches the Message Pack for an Auth message and reconstructs it into the provided auth structure. Supports multi-page Auth messages.



**Parameters:**


* `pack` Pointer to the Message Pack structure. 
* `auth` Pointer to the Auth structure to populate.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if pack or auth is NULL. 
* `RID_ERROR_NOT_FOUND` if no Auth message is found in the pack.
### function `rid_message_pack_get_message_at`

_Get a pointer to a message at the specified index._
```c
const void * rid_message_pack_get_message_at (
    const rid_message_pack_t *pack,
    uint8_t index
) 
```


**Parameters:**


* `pack` Pointer to the Message Pack structure. 
* `index` Index of the message.


**Returns:**

Pointer to the message, or NULL if pack is NULL or index is out of range.
### function `rid_message_pack_get_message_type_at`

_Get the message type at the specified index._
```c
int rid_message_pack_get_message_type_at (
    const rid_message_pack_t *pack,
    uint8_t index,
    rid_message_type_t *type
) 
```


**Parameters:**


* `pack` Pointer to the Message Pack structure. 
* `index` Index of the message. 
* `type` Pointer to store the message type.


**Return value:**


* `RID_SUCCESS` on success, \*type holds the message type. 
* `RID_ERROR_NULL_POINTER` if pack or type is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if index is out of range.
### function `rid_message_pack_get_messages`

_Get a pointer to the messages array in a Message Pack._
```c
const void * rid_message_pack_get_messages (
    const rid_message_pack_t *pack
) 
```


**Parameters:**


* `pack` Pointer to the Message Pack structure.


**Returns:**

Pointer to the messages array, or NULL if pack is NULL.
### function `rid_message_pack_init`

_Initialize a Message Pack structure._
```c
int rid_message_pack_init (
    rid_message_pack_t *pack
) 
```


Sets protocol version to RID\_PROTOCOL\_VERSION\_2 and message type to RID\_MESSAGE\_TYPE\_MESSAGE\_PACK. The message\_size is set to RID\_MESSAGE\_SIZE. All other fields are zeroed.



**Parameters:**


* `pack` Pointer to the Message Pack structure to initialize.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if pack is NULL.
### function `rid_message_pack_message_count`

_Get the message count from a Message Pack._
```c
uint8_t rid_message_pack_message_count (
    const rid_message_pack_t *pack
) 
```


**Parameters:**


* `pack` Pointer to the Message Pack structure.


**Returns:**

The message count, or 0 if pack is NULL.
### function `rid_message_pack_messages_size`

_Get the combined size of messages in a Message Pack in bytes._
```c
size_t rid_message_pack_messages_size (
    const rid_message_pack_t *pack
) 
```


**Parameters:**


* `pack` Pointer to the Message Pack structure.


**Returns:**

The combined messages size in bytes or 0 if pack is NULL.
### function `rid_message_pack_set_auth`

_Set Auth message in a Message Pack._
```c
int rid_message_pack_set_auth (
    rid_message_pack_t *pack,
    const rid_auth_t *auth
) 
```


Deletes any existing Auth messages from the pack and adds the new Auth message. Supports multi-page Auth messages.



**Parameters:**


* `pack` Pointer to the Message Pack structure. 
* `auth` Pointer to the Auth message to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if pack or auth is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if pack cannot accommodate the Auth message.
### function `rid_message_pack_set_message_at`

_Replace a message at the specified index._
```c
int rid_message_pack_set_message_at (
    rid_message_pack_t *pack,
    uint8_t index,
    const void *message
) 
```


**Parameters:**


* `pack` Pointer to the Message Pack structure. 
* `index` Index of the message to set. 
* `message` Pointer to the new message.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if pack or message is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if index is out of range.
### function `rid_message_pack_size`

_Get the size of a Message Pack in bytes._
```c
size_t rid_message_pack_size (
    const rid_message_pack_t *pack
) 
```


**Parameters:**


* `pack` Pointer to the Message Pack structure.


**Returns:**

The size in bytes or 0 if pack is NULL.
### function `rid_message_pack_sort`

_Sort messages in a Message Pack by message type._
```c
int rid_message_pack_sort (
    rid_message_pack_t *pack
) 
```


Messages are sorted in ascending order by the message type. The sort preserves the relative order of messages with the same type.



**Parameters:**


* `pack` Pointer to the Message Pack structure.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if pack is NULL.
### function `rid_message_pack_to_json`

_Format a Message Pack as a JSON string._
```c
int rid_message_pack_to_json (
    const rid_message_pack_t *pack,
    char *buffer,
    size_t buffer_size,
    size_t *needed_size
) 
```


**Parameters:**


* `pack` Pointer to the Message Pack structure. 
* `buffer` Buffer to store the JSON string or NULL. 
* `buffer_size` Size of the buffer. 
* `needed_size` If non-NULL receives the required buffer size.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if `pack` is NULL or if both`buffer` and`needed_size` are NULL.
* `RID_ERROR_BUFFER_TOO_SMALL` if `buffer` is too small.
### function `rid_message_pack_validate`

_Validate a Message Pack structure._
```c
int rid_message_pack_validate (
    const rid_message_pack_t *pack
) 
```


Checks that all fields contain valid values according to ASTM F3411-22a.



**Parameters:**


* `pack` Pointer to the Message Pack structure to validate.


**Return value:**


* `RID_SUCCESS` if all fields are valid. 
* `RID_ERROR_NULL_POINTER` if pack is NULL. 
* `RID_ERROR_INVALID_PROTOCOL_VERSION` if protocol version is invalid. 
* `RID_ERROR_UNKNOWN_MESSAGE_TYPE` if message type is not MESSAGE\_PACK. 
* `RID_ERROR_INVALID_MESSAGE_SIZE` if message\_size is not 25. 
* `RID_ERROR_INVALID_MESSAGE_COUNT` if message\_count exceeds maximum.

## Macros Documentation

### define `RID_MESSAGE_PACK_HEADER_SIZE`

_Header size of a Message Pack in bytes._
```c
#define RID_MESSAGE_PACK_HEADER_SIZE 3
```

### define `RID_MESSAGE_PACK_MAX_MESSAGES`

_Maximum number of messages in a Message Pack._
```c
#define RID_MESSAGE_PACK_MAX_MESSAGES 9
```

### define `RID_MESSAGE_PACK_MAX_SIZE`

_Maximum size of a Message Pack in bytes (header + 9 messages)._
```c
#define RID_MESSAGE_PACK_MAX_SIZE 228
```

### define `RID_MESSAGE_PACK_MIN_SIZE`

_Minimum size of a Message Pack in bytes (header + 1 message)._
```c
#define RID_MESSAGE_PACK_MIN_SIZE 28
```


## File include/rid/operator_id.h

_Operator ID message handling per ASTM F3411-22a._

Example usage: 
````cpp
    rid_operator_id_t operator_id;

    rid_operator_id_init(&operator_id);
    rid_operator_id_set_type(&operator_id, RID_ID_TYPE_OPERATOR_ID);
    rid_operator_id_set(&operator_id, "FIN87astrdge12k8");

    hexdump(&operator_id, sizeof(operator_id));

    char id[RID_OPERATOR_ID_SIZE + 1];
    rid_operator_id_get(&operator_id, id, sizeof(id));
    rid_operator_id_type_t id_type = rid_operator_id_get_type(&operator_id);

    printf("Operator ID: %s\n", id);
    printf("ID type:     %d\n", id_type);
````

## Structures and Types

| Type | Name |
| ---: | :--- |
| struct | [**rid\_operator\_id\_t**](#struct-rid_operator_id_t) <br>_Operator ID message structure per ASTM F3411-22a._ |
| enum  | [**rid\_operator\_id\_type\_t**](#enum-rid_operator_id_type_t)  <br>_Operator ID type classification per ASTM F3411-22a._ |

## Functions

| Type | Name |
| ---: | :--- |
|  int | [**rid\_operator\_id\_get**](#function-rid_operator_id_get) (const [**rid\_operator\_id\_t**](#struct-rid_operator_id_t) \*message, char \*buffer, size\_t buffer\_size) <br>_Get the Operator ID from an Operator ID message._ |
|  [**rid\_operator\_id\_type\_t**](#enum-rid_operator_id_type_t) | [**rid\_operator\_id\_get\_type**](#function-rid_operator_id_get_type) (const [**rid\_operator\_id\_t**](#struct-rid_operator_id_t) \*message) <br>_Get the ID type from an Operator ID message._ |
|  int | [**rid\_operator\_id\_init**](#function-rid_operator_id_init) ([**rid\_operator\_id\_t**](#struct-rid_operator_id_t) \*message) <br>_Initialize an Operator ID message with default values._ |
|  int | [**rid\_operator\_id\_set**](#function-rid_operator_id_set) ([**rid\_operator\_id\_t**](#struct-rid_operator_id_t) \*message, const char \*uas\_id) <br>_Set the Operator ID for an Operator ID message._ |
|  int | [**rid\_operator\_id\_set\_type**](#function-rid_operator_id_set_type) ([**rid\_operator\_id\_t**](#struct-rid_operator_id_t) \*message, [**rid\_operator\_id\_type\_t**](#enum-rid_operator_id_type_t) type) <br>_Set the ID type for an Operator ID message._ |
|  int | [**rid\_operator\_id\_to\_json**](#function-rid_operator_id_to_json) (const [**rid\_operator\_id\_t**](#struct-rid_operator_id_t) \*message, char \*buffer, size\_t buffer\_size, size\_t \*needed\_size) <br>_Format an Operator ID message as a JSON string._ |
|  const char \* | [**rid\_operator\_id\_type\_to\_string**](#function-rid_operator_id_type_to_string) ([**rid\_operator\_id\_type\_t**](#enum-rid_operator_id_type_t) type) <br>_Convert operator ID type to string representation._ |
|  int | [**rid\_operator\_id\_validate**](#function-rid_operator_id_validate) (const [**rid\_operator\_id\_t**](#struct-rid_operator_id_t) \*message) <br>_Validate an Operator ID message structure._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**RID\_OPERATOR\_ID\_SIZE**](#define-rid_operator_id_size)  20<br>_Operator ID field size in bytes per ASTM F3411-22a._ |

## Structures and Types Documentation

### struct `rid_operator_id_t`

_Operator ID message structure per ASTM F3411-22a._

Variables:

-  uint8\_t id_type  

-  uint8\_t message_type  

-  char operator_id  

-  uint8\_t protocol_version  

-  char reserved  

### enum `rid_operator_id_type_t`

_Operator ID type classification per ASTM F3411-22a._
```c
enum rid_operator_id_type_t {
    RID_ID_TYPE_OPERATOR_ID = 0
};
```


## Functions Documentation

### function `rid_operator_id_get`

_Get the Operator ID from an Operator ID message._
```c
int rid_operator_id_get (
    const rid_operator_id_t *message,
    char *buffer,
    size_t buffer_size
) 
```


Copies the Operator ID to the provided buffer as a null-terminated string.



**Parameters:**


* `message` Pointer to the Operator ID message structure. 
* `buffer` Buffer to store the Operator ID. 
* `buffer_size` Size of the buffer (must be at least RID\_OPERATOR\_ID\_SIZE + 1).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message or buffer is NULL. 
* `RID_ERROR_BUFFER_TOO_SMALL` if buffer\_size is insufficient.
### function `rid_operator_id_get_type`

_Get the ID type from an Operator ID message._
```c
rid_operator_id_type_t rid_operator_id_get_type (
    const rid_operator_id_t *message
) 
```


**Parameters:**


* `message` Pointer to the Operator ID message structure.


**Returns:**

The ID type or RID\_ID\_TYPE\_OPERATOR\_ID if message is NULL.
### function `rid_operator_id_init`

_Initialize an Operator ID message with default values._
```c
int rid_operator_id_init (
    rid_operator_id_t *message
) 
```


Sets protocol version to 2 and message type to OPERATOR\_ID. All other fields are set to zero.



**Parameters:**


* `message` Pointer to the Operator ID message structure.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL.
### function `rid_operator_id_set`

_Set the Operator ID for an Operator ID message._
```c
int rid_operator_id_set (
    rid_operator_id_t *message,
    const char *uas_id
) 
```


The Operator ID is a null-terminated string up to RID\_OPERATOR\_ID\_SIZE characters.



**Parameters:**


* `message` Pointer to the Operator ID message structure. 
* `uas_id` The Operator ID string to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message or uas\_id is NULL. 
* `RID_ERROR_BUFFER_TOO_LARGE` if uas\_id exceeds RID\_OPERATOR\_ID\_SIZE characters.
### function `rid_operator_id_set_type`

_Set the ID type for an Operator ID message._
```c
int rid_operator_id_set_type (
    rid_operator_id_t *message,
    rid_operator_id_type_t type
) 
```


**Parameters:**


* `message` Pointer to the Operator ID message structure. 
* `type` The ID type to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL.
### function `rid_operator_id_to_json`

_Format an Operator ID message as a JSON string._
```c
int rid_operator_id_to_json (
    const rid_operator_id_t *message,
    char *buffer,
    size_t buffer_size,
    size_t *needed_size
) 
```


**Parameters:**


* `message` Pointer to the Operator ID message structure. 
* `buffer` Buffer to store the JSON string or NULL. 
* `buffer_size` Size of the buffer. 
* `needed_size` If non-NULL receives the required buffer size.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if `message` is NULL or if both`buffer` and`needed_size` are NULL.
* `RID_ERROR_BUFFER_TOO_SMALL` if `buffer` is too small.
### function `rid_operator_id_type_to_string`

_Convert operator ID type to string representation._
```c
const char * rid_operator_id_type_to_string (
    rid_operator_id_type_t type
) 
```


**Parameters:**


* `type` The operator ID type to convert.


**Returns:**

String representation of the operator ID type. Returns "UNKNOWN" for invalid values.
### function `rid_operator_id_validate`

_Validate an Operator ID message structure._
```c
int rid_operator_id_validate (
    const rid_operator_id_t *message
) 
```


Checks that all fields contain valid encoded values according to ASTM F3411-22a.



**Parameters:**


* `message` Pointer to the Operator ID message structure to validate.


**Return value:**


* `RID_SUCCESS` if all fields are valid. 
* `RID_ERROR_NULL_POINTER` if message is NULL. 
* `RID_ERROR_INVALID_PROTOCOL_VERSION` if protocol version is invalid. 
* `RID_ERROR_UNKNOWN_MESSAGE_TYPE` if message type is not OPERATOR\_ID. 
* `RID_ERROR_INVALID_CHARACTER` if operator ID contains non-ASCII characters.

## Macros Documentation

### define `RID_OPERATOR_ID_SIZE`

_Operator ID field size in bytes per ASTM F3411-22a._
```c
#define RID_OPERATOR_ID_SIZE 20
```


## File include/rid/rid.h

_Convenience header to include all the other headers._









## File include/rid/self_id.h

_Self ID message handling per ASTM F3411-22a._

Example usage: 
````cpp
    rid_self_id_t self_id;

    rid_self_id_init(&self_id);
    rid_self_id_set_description_type(&self_id, RID_DESCRIPTION_TYPE_TEXT);
    rid_self_id_set_description(&self_id, "Drone delivery test");

    hexdump(&self_id, sizeof(self_id));

    char description[RID_DESCRIPTION_SIZE + 1];
    rid_self_id_get_description(&self_id, description, sizeof(description));
    rid_description_type_t desc_type = rid_self_id_get_description_type(&self_id);

    printf("Description: %s\n", description);
    printf("Type:        %d\n", desc_type);
````

## Structures and Types

| Type | Name |
| ---: | :--- |
| enum  | [**rid\_description\_type\_t**](#enum-rid_description_type_t)  <br>_Description type classification per ASTM F3411-22a._ |
| struct | [**rid\_self\_id\_t**](#struct-rid_self_id_t) <br>_Self ID message structure per ASTM F3411-22a._ |

## Functions

| Type | Name |
| ---: | :--- |
|  const char \* | [**rid\_description\_type\_to\_string**](#function-rid_description_type_to_string) ([**rid\_description\_type\_t**](#enum-rid_description_type_t) type) <br>_Convert description type to string representation._ |
|  int | [**rid\_self\_id\_get\_description**](#function-rid_self_id_get_description) (const [**rid\_self\_id\_t**](#struct-rid_self_id_t) \*message, char \*buffer, size\_t buffer\_size) <br>_Get the description from a Self ID message._ |
|  [**rid\_description\_type\_t**](#enum-rid_description_type_t) | [**rid\_self\_id\_get\_description\_type**](#function-rid_self_id_get_description_type) (const [**rid\_self\_id\_t**](#struct-rid_self_id_t) \*message) <br>_Get the description type from a Self ID message._ |
|  int | [**rid\_self\_id\_init**](#function-rid_self_id_init) ([**rid\_self\_id\_t**](#struct-rid_self_id_t) \*message) <br>_Initialize a Self ID message with default values._ |
|  int | [**rid\_self\_id\_set\_description**](#function-rid_self_id_set_description) ([**rid\_self\_id\_t**](#struct-rid_self_id_t) \*message, const char \*description) <br>_Set the description for a Self ID message._ |
|  int | [**rid\_self\_id\_set\_description\_type**](#function-rid_self_id_set_description_type) ([**rid\_self\_id\_t**](#struct-rid_self_id_t) \*message, [**rid\_description\_type\_t**](#enum-rid_description_type_t) type) <br>_Set the description type for a Self ID message._ |
|  int | [**rid\_self\_id\_to\_json**](#function-rid_self_id_to_json) (const [**rid\_self\_id\_t**](#struct-rid_self_id_t) \*message, char \*buffer, size\_t buffer\_size, size\_t \*needed\_size) <br>_Format a Self ID message as a JSON string._ |
|  int | [**rid\_self\_id\_validate**](#function-rid_self_id_validate) (const [**rid\_self\_id\_t**](#struct-rid_self_id_t) \*message) <br>_Validate a Self ID message structure._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**RID\_DESCRIPTION\_SIZE**](#define-rid_description_size)  23<br>_Self ID description field size in bytes per ASTM F3411-22a._ |

## Structures and Types Documentation

### enum `rid_description_type_t`

_Description type classification per ASTM F3411-22a._
```c
enum rid_description_type_t {
    RID_DESCRIPTION_TYPE_TEXT = 0,
    RID_DESCRIPTION_TYPE_EMERGENCY = 1,
    RID_DESCRIPTION_TYPE_EXTENDED_STATUS = 2
};
```

### struct `rid_self_id_t`

_Self ID message structure per ASTM F3411-22a._

Variables:

-  char description  

-  uint8\_t description_type  

-  uint8\_t message_type  

-  uint8\_t protocol_version  


## Functions Documentation

### function `rid_description_type_to_string`

_Convert description type to string representation._
```c
const char * rid_description_type_to_string (
    rid_description_type_t type
) 
```


**Parameters:**


* `type` The description type to convert.


**Returns:**

String representation of the description type. Returns "UNKNOWN" for invalid values.
### function `rid_self_id_get_description`

_Get the description from a Self ID message._
```c
int rid_self_id_get_description (
    const rid_self_id_t *message,
    char *buffer,
    size_t buffer_size
) 
```


Copies the description to the provided buffer as a null-terminated string.



**Parameters:**


* `message` Pointer to the Self ID message structure. 
* `buffer` Buffer to store the description. 
* `buffer_size` Size of the buffer (must be at least RID\_DESCRIPTION\_SIZE + 1).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message or buffer is NULL. 
* `RID_ERROR_BUFFER_TOO_SMALL` if buffer\_size is insufficient.
### function `rid_self_id_get_description_type`

_Get the description type from a Self ID message._
```c
rid_description_type_t rid_self_id_get_description_type (
    const rid_self_id_t *message
) 
```


**Parameters:**


* `message` Pointer to the Self ID message structure.


**Returns:**

The description type or RID\_DESCRIPTION\_TYPE\_TEXT if message is NULL.
### function `rid_self_id_init`

_Initialize a Self ID message with default values._
```c
int rid_self_id_init (
    rid_self_id_t *message
) 
```


Sets protocol version to 2 and message type to SELF\_ID. All other fields are set to zero.



**Parameters:**


* `message` Pointer to the Self ID message structure.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL.
### function `rid_self_id_set_description`

_Set the description for a Self ID message._
```c
int rid_self_id_set_description (
    rid_self_id_t *message,
    const char *description
) 
```


The description is a null-terminated string up to RID\_DESCRIPTION\_SIZE characters.



**Parameters:**


* `message` Pointer to the Self ID message structure. 
* `description` The description string to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message or description is NULL. 
* `RID_ERROR_BUFFER_TOO_LARGE` if description exceeds RID\_DESCRIPTION\_SIZE characters. 
* `RID_ERROR_INVALID_CHARACTER` if description contains non-ASCII or control characters.
### function `rid_self_id_set_description_type`

_Set the description type for a Self ID message._
```c
int rid_self_id_set_description_type (
    rid_self_id_t *message,
    rid_description_type_t type
) 
```


**Parameters:**


* `message` Pointer to the Self ID message structure. 
* `type` The description type to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if message is NULL.
### function `rid_self_id_to_json`

_Format a Self ID message as a JSON string._
```c
int rid_self_id_to_json (
    const rid_self_id_t *message,
    char *buffer,
    size_t buffer_size,
    size_t *needed_size
) 
```


**Parameters:**


* `message` Pointer to the Self ID message structure. 
* `buffer` Buffer to store the JSON string or NULL. 
* `buffer_size` Size of the buffer. 
* `needed_size` If non-NULL receives the required buffer size.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if `message` is NULL or if both`buffer` and`needed_size` are NULL.
* `RID_ERROR_BUFFER_TOO_SMALL` if `buffer` is too small.
### function `rid_self_id_validate`

_Validate a Self ID message structure._
```c
int rid_self_id_validate (
    const rid_self_id_t *message
) 
```


Checks that all fields contain valid encoded values according to ASTM F3411-22a.



**Parameters:**


* `message` Pointer to the Self ID message structure to validate.


**Return value:**


* `RID_SUCCESS` if all fields are valid. 
* `RID_ERROR_NULL_POINTER` if message is NULL. 
* `RID_ERROR_INVALID_PROTOCOL_VERSION` if protocol version is invalid. 
* `RID_ERROR_UNKNOWN_MESSAGE_TYPE` if message type is not SELF\_ID. 
* `RID_ERROR_INVALID_CHARACTER` if description contains non-ASCII or control characters.

## Macros Documentation

### define `RID_DESCRIPTION_SIZE`

_Self ID description field size in bytes per ASTM F3411-22a._
```c
#define RID_DESCRIPTION_SIZE 23
```


## File include/rid/system.h

_System message handling per ASTM F3411-22a._

Example usage: 
````cpp
    rid_system_t system;

    rid_system_init(&system);

    rid_system_set_operator_location_type(&system, RID_OPERATOR_LOCATION_TYPE_TAKEOFF);
    rid_system_set_classification_type(&system, RID_CLASSIFICATION_TYPE_EUROPEAN_UNION);
    rid_system_set_ua_classification_category(&system, RID_UA_CLASSIFICATION_CATEGORY_OPEN);
    rid_system_set_ua_classification_class(&system, RID_UA_CLASSIFICATION_CLASS_1);

    rid_system_set_operator_latitude(&system, 60.2870324);
    rid_system_set_operator_longitude(&system, 24.5397187);
    rid_system_set_operator_altitude(&system, 50.0f);

    rid_system_set_area_count(&system, 1);
    rid_system_set_area_radius(&system, 100);
    rid_system_set_area_ceiling(&system, 120.0f);
    rid_system_set_area_floor(&system, 0.0f);

    rid_system_set_timestamp(&system, 3600);

    hexdump(&system, sizeof(system));

    printf("Protocol version:   %u\n", rid_message_get_protocol_version(&system));
    printf("Message type:       %u\n", rid_message_get_type(&system));
    printf("Operator loc type:  %u\n", rid_system_get_operator_location_type(&system));
    printf("Classification:     %u\n", rid_system_get_classification_type(&system));
    printf("Operator latitude:  %.6f\n", rid_system_get_operator_latitude(&system));
    printf("Operator longitude: %.6f\n", rid_system_get_operator_longitude(&system));
    printf("Area count:         %u\n", rid_system_get_area_count(&system));
    printf("Area radius:        %u m\n", rid_system_get_area_radius(&system));
    printf("Area ceiling:       %.1f m\n", (double)rid_system_get_area_ceiling(&system));
    printf("Area floor:         %.1f m\n", (double)rid_system_get_area_floor(&system));
    printf("UA class:           %u\n", rid_system_get_ua_classification_class(&system));
    printf("UA category:        %u\n", rid_system_get_ua_classification_category(&system));
    printf("Operator altitude:  %.1f m\n", (double)rid_system_get_operator_altitude(&system));
    printf("Timestamp:          %u\n", rid_system_get_timestamp(&system));
    printf("Unixtime:           %u\n", rid_system_get_unixtime(&system));
````

## Structures and Types

| Type | Name |
| ---: | :--- |
| enum  | [**rid\_classification\_type\_t**](#enum-rid_classification_type_t)  <br>_Classification type per ASTM F3411-22a._ |
| enum  | [**rid\_operator\_location\_type\_t**](#enum-rid_operator_location_type_t)  <br>_Operator location type per ASTM F3411-22a._ |
| struct | [**rid\_system\_t**](#struct-rid_system_t) <br>_System message structure per ASTM F3411-22a._ |
| enum  | [**rid\_ua\_classification\_category\_t**](#enum-rid_ua_classification_category_t)  <br>_UA classification category per ASTM F3411-22a._ |
| enum  | [**rid\_ua\_classification\_class\_t**](#enum-rid_ua_classification_class_t)  <br>_UA classification class per ASTM F3411-22a._ |

## Functions

| Type | Name |
| ---: | :--- |
|  const char \* | [**rid\_classification\_type\_to\_string**](#function-rid_classification_type_to_string) ([**rid\_classification\_type\_t**](#enum-rid_classification_type_t) type) <br>_Convert classification type to string representation._ |
|  const char \* | [**rid\_operator\_location\_type\_to\_string**](#function-rid_operator_location_type_to_string) ([**rid\_operator\_location\_type\_t**](#enum-rid_operator_location_type_t) type) <br>_Convert operator location type to string representation._ |
|  float | [**rid\_system\_get\_area\_ceiling**](#function-rid_system_get_area_ceiling) (const [**rid\_system\_t**](#struct-rid_system_t) \*system) <br>_Get the area ceiling from a System message._ |
|  uint16\_t | [**rid\_system\_get\_area\_count**](#function-rid_system_get_area_count) (const [**rid\_system\_t**](#struct-rid_system_t) \*system) <br>_Get the area count from a System message._ |
|  float | [**rid\_system\_get\_area\_floor**](#function-rid_system_get_area_floor) (const [**rid\_system\_t**](#struct-rid_system_t) \*system) <br>_Get the area floor from a System message._ |
|  uint16\_t | [**rid\_system\_get\_area\_radius**](#function-rid_system_get_area_radius) (const [**rid\_system\_t**](#struct-rid_system_t) \*system) <br>_Get the area radius from a System message._ |
|  [**rid\_classification\_type\_t**](#enum-rid_classification_type_t) | [**rid\_system\_get\_classification\_type**](#function-rid_system_get_classification_type) (const [**rid\_system\_t**](#struct-rid_system_t) \*system) <br>_Get the classification type from a System message._ |
|  float | [**rid\_system\_get\_operator\_altitude**](#function-rid_system_get_operator_altitude) (const [**rid\_system\_t**](#struct-rid_system_t) \*system) <br>_Get the operator altitude from a System message._ |
|  double | [**rid\_system\_get\_operator\_latitude**](#function-rid_system_get_operator_latitude) (const [**rid\_system\_t**](#struct-rid_system_t) \*system) <br>_Get the operator latitude from a System message._ |
|  [**rid\_operator\_location\_type\_t**](#enum-rid_operator_location_type_t) | [**rid\_system\_get\_operator\_location\_type**](#function-rid_system_get_operator_location_type) (const [**rid\_system\_t**](#struct-rid_system_t) \*system) <br>_Get the operator location type from a System message._ |
|  double | [**rid\_system\_get\_operator\_longitude**](#function-rid_system_get_operator_longitude) (const [**rid\_system\_t**](#struct-rid_system_t) \*system) <br>_Get the operator longitude from a System message._ |
|  uint32\_t | [**rid\_system\_get\_timestamp**](#function-rid_system_get_timestamp) (const [**rid\_system\_t**](#struct-rid_system_t) \*system) <br>_Get the timestamp from a System message._ |
|  [**rid\_ua\_classification\_category\_t**](#enum-rid_ua_classification_category_t) | [**rid\_system\_get\_ua\_classification\_category**](#function-rid_system_get_ua_classification_category) (const [**rid\_system\_t**](#struct-rid_system_t) \*system) <br>_Get the UA classification category from a System message._ |
|  [**rid\_ua\_classification\_class\_t**](#enum-rid_ua_classification_class_t) | [**rid\_system\_get\_ua\_classification\_class**](#function-rid_system_get_ua_classification_class) (const [**rid\_system\_t**](#struct-rid_system_t) \*system) <br>_Get the UA classification class from a System message._ |
|  uint32\_t | [**rid\_system\_get\_unixtime**](#function-rid_system_get_unixtime) (const [**rid\_system\_t**](#struct-rid_system_t) \*system) <br>_Get the timestamp as Unix timestamp._ |
|  int | [**rid\_system\_init**](#function-rid_system_init) ([**rid\_system\_t**](#struct-rid_system_t) \*system) <br>_Initialize a System message with default values._ |
|  int | [**rid\_system\_set\_area\_ceiling**](#function-rid_system_set_area_ceiling) ([**rid\_system\_t**](#struct-rid_system_t) \*system, float altitude) <br>_Set the area ceiling for a System message._ |
|  int | [**rid\_system\_set\_area\_count**](#function-rid_system_set_area_count) ([**rid\_system\_t**](#struct-rid_system_t) \*system, uint16\_t count) <br>_Set the area count for a System message._ |
|  int | [**rid\_system\_set\_area\_floor**](#function-rid_system_set_area_floor) ([**rid\_system\_t**](#struct-rid_system_t) \*system, float altitude) <br>_Set the area floor for a System message._ |
|  int | [**rid\_system\_set\_area\_radius**](#function-rid_system_set_area_radius) ([**rid\_system\_t**](#struct-rid_system_t) \*system, uint16\_t meters) <br>_Set the area radius for a System message._ |
|  int | [**rid\_system\_set\_classification\_type**](#function-rid_system_set_classification_type) ([**rid\_system\_t**](#struct-rid_system_t) \*system, [**rid\_classification\_type\_t**](#enum-rid_classification_type_t) type) <br>_Set the classification type for a System message._ |
|  int | [**rid\_system\_set\_operator\_altitude**](#function-rid_system_set_operator_altitude) ([**rid\_system\_t**](#struct-rid_system_t) \*system, float altitude) <br>_Set the operator altitude for a System message._ |
|  int | [**rid\_system\_set\_operator\_latitude**](#function-rid_system_set_operator_latitude) ([**rid\_system\_t**](#struct-rid_system_t) \*system, double degrees) <br>_Set the operator latitude for a System message._ |
|  int | [**rid\_system\_set\_operator\_location\_type**](#function-rid_system_set_operator_location_type) ([**rid\_system\_t**](#struct-rid_system_t) \*system, [**rid\_operator\_location\_type\_t**](#enum-rid_operator_location_type_t) type) <br>_Set the operator location type for a System message._ |
|  int | [**rid\_system\_set\_operator\_longitude**](#function-rid_system_set_operator_longitude) ([**rid\_system\_t**](#struct-rid_system_t) \*system, double degrees) <br>_Set the operator longitude for a System message._ |
|  int | [**rid\_system\_set\_timestamp**](#function-rid_system_set_timestamp) ([**rid\_system\_t**](#struct-rid_system_t) \*system, uint32\_t timestamp) <br>_Set the timestamp for a System message._ |
|  int | [**rid\_system\_set\_ua\_classification\_category**](#function-rid_system_set_ua_classification_category) ([**rid\_system\_t**](#struct-rid_system_t) \*system, [**rid\_ua\_classification\_category\_t**](#enum-rid_ua_classification_category_t) category) <br>_Set the UA classification category for a System message._ |
|  int | [**rid\_system\_set\_ua\_classification\_class**](#function-rid_system_set_ua_classification_class) ([**rid\_system\_t**](#struct-rid_system_t) \*system, [**rid\_ua\_classification\_class\_t**](#enum-rid_ua_classification_class_t) class) <br>_Set the UA classification class for a System message._ |
|  int | [**rid\_system\_set\_unixtime**](#function-rid_system_set_unixtime) ([**rid\_system\_t**](#struct-rid_system_t) \*system, uint32\_t unixtime) <br>_Set the timestamp for a System message from Unix timestamp._ |
|  int | [**rid\_system\_to\_json**](#function-rid_system_to_json) (const [**rid\_system\_t**](#struct-rid_system_t) \*system, char \*buffer, size\_t buffer\_size, size\_t \*needed\_size) <br>_Format a System message as a JSON string._ |
|  int | [**rid\_system\_validate**](#function-rid_system_validate) (const [**rid\_system\_t**](#struct-rid_system_t) \*system) <br>_Validate a System message structure._ |
|  const char \* | [**rid\_ua\_classification\_category\_to\_string**](#function-rid_ua_classification_category_to_string) ([**rid\_ua\_classification\_category\_t**](#enum-rid_ua_classification_category_t) category) <br>_Convert UA classification category to string representation._ |
|  const char \* | [**rid\_ua\_classification\_class\_to\_string**](#function-rid_ua_classification_class_to_string) ([**rid\_ua\_classification\_class\_t**](#enum-rid_ua_classification_class_t) class) <br>_Convert UA classification class to string representation._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**RID\_AREA\_CEILING\_INVALID**](#define-rid_area_ceiling_invalid)  -1000.0f<br>_Value indicating invalid area ceiling altitude._ |
| define  | [**RID\_AREA\_CEILING\_INVALID\_ENCODED**](#define-rid_area_ceiling_invalid_encoded)  0<br>_Encoded value for invalid area ceiling altitude._ |
| define  | [**RID\_AREA\_CEILING\_MAX**](#define-rid_area_ceiling_max)  31767.0f<br>_Maximum area ceiling altitude in meters._ |
| define  | [**RID\_AREA\_CEILING\_MIN**](#define-rid_area_ceiling_min)  -1000.0f<br>_Minimum area ceiling altitude in meters._ |
| define  | [**RID\_AREA\_COUNT\_MAX**](#define-rid_area_count_max)  UINT16\_MAX<br>_Maximum area count value._ |
| define  | [**RID\_AREA\_FLOOR\_INVALID**](#define-rid_area_floor_invalid)  -1000.0f<br>_Value indicating invalid area floor altitude._ |
| define  | [**RID\_AREA\_FLOOR\_INVALID\_ENCODED**](#define-rid_area_floor_invalid_encoded)  0<br>_Encoded value for invalid area floor altitude._ |
| define  | [**RID\_AREA\_FLOOR\_MAX**](#define-rid_area_floor_max)  31767.0f<br>_Maximum area floor altitude in meters._ |
| define  | [**RID\_AREA\_FLOOR\_MIN**](#define-rid_area_floor_min)  -1000.0f<br>_Minimum area floor altitude in meters._ |
| define  | [**RID\_AREA\_RADIUS\_MAX**](#define-rid_area_radius_max)  2550<br>_Maximum area radius in meters._ |
| define  | [**RID\_OPERATOR\_ALTITUDE\_INVALID**](#define-rid_operator_altitude_invalid)  -1000.0f<br>_Value indicating invalid operator altitude._ |
| define  | [**RID\_OPERATOR\_ALTITUDE\_INVALID\_ENCODED**](#define-rid_operator_altitude_invalid_encoded)  0<br>_Encoded value for invalid operator altitude._ |
| define  | [**RID\_OPERATOR\_LATITUDE\_INVALID**](#define-rid_operator_latitude_invalid)  DBL\_MAX<br>_Value indicating invalid operator latitude._ |
| define  | [**RID\_OPERATOR\_LONGITUDE\_INVALID**](#define-rid_operator_longitude_invalid)  DBL\_MAX<br>_Value indicating invalid operator longitude._ |
| define  | [**RID\_SYSTEM\_TIMESTAMP\_EPOCH**](#define-rid_system_timestamp_epoch)  1546300800<br>_Timestamp epoch (2019-01-01 00:00:00 UTC as Unix timestamp)._ |

## Structures and Types Documentation

### enum `rid_classification_type_t`

_Classification type per ASTM F3411-22a._
```c
enum rid_classification_type_t {
    RID_CLASSIFICATION_TYPE_UNDECLARED = 0,
    RID_CLASSIFICATION_TYPE_EUROPEAN_UNION = 1,
    RID_CLASSIFICATION_TYPE_MAX = 7
};
```

### enum `rid_operator_location_type_t`

_Operator location type per ASTM F3411-22a._
```c
enum rid_operator_location_type_t {
    RID_OPERATOR_LOCATION_TYPE_TAKEOFF = 0,
    RID_OPERATOR_LOCATION_TYPE_DYNAMIC = 1,
    RID_OPERATOR_LOCATION_TYPE_FIXED = 2,
    RID_OPERATOR_LOCATION_TYPE_MAX = 3
};
```

### struct `rid_system_t`

_System message structure per ASTM F3411-22a._

Variables:

-  uint16\_t area_ceiling  

-  uint16\_t area_count  

-  uint16\_t area_floor  

-  uint8\_t area_radius  

-  uint8\_t classification_type  

-  uint8\_t message_type  

-  uint16\_t operator_altitude  

-  int32\_t operator_latitude  

-  uint8\_t operator_location_type  

-  int32\_t operator_longitude  

-  uint8\_t protocol_version  

-  uint8\_t reserved_1  

-  uint8\_t reserved_2  

-  uint32\_t timestamp  

-  uint8\_t ua_classification_category  

-  uint8\_t ua_classification_class  

### enum `rid_ua_classification_category_t`

_UA classification category per ASTM F3411-22a._
```c
enum rid_ua_classification_category_t {
    RID_UA_CLASSIFICATION_CATEGORY_UNDEFINED = 0,
    RID_UA_CLASSIFICATION_CATEGORY_OPEN = 1,
    RID_UA_CLASSIFICATION_CATEGORY_SPECIFIC = 2,
    RID_UA_CLASSIFICATION_CATEGORY_CERTIFIED = 3,
    RID_UA_CLASSIFICATION_CATEGORY_MAX = 15
};
```

### enum `rid_ua_classification_class_t`

_UA classification class per ASTM F3411-22a._
```c
enum rid_ua_classification_class_t {
    RID_UA_CLASSIFICATION_CLASS_UNDEFINED = 0,
    RID_UA_CLASSIFICATION_CLASS_0 = 1,
    RID_UA_CLASSIFICATION_CLASS_1 = 2,
    RID_UA_CLASSIFICATION_CLASS_2 = 3,
    RID_UA_CLASSIFICATION_CLASS_3 = 4,
    RID_UA_CLASSIFICATION_CLASS_4 = 5,
    RID_UA_CLASSIFICATION_CLASS_5 = 6,
    RID_UA_CLASSIFICATION_CLASS_6 = 7,
    RID_UA_CLASSIFICATION_CLASS_MAX = 15
};
```


## Functions Documentation

### function `rid_classification_type_to_string`

_Convert classification type to string representation._
```c
const char * rid_classification_type_to_string (
    rid_classification_type_t type
) 
```


**Parameters:**


* `type` The classification type to convert.


**Returns:**

String representation of the classification type. Returns "UNKNOWN" for invalid values.
### function `rid_operator_location_type_to_string`

_Convert operator location type to string representation._
```c
const char * rid_operator_location_type_to_string (
    rid_operator_location_type_t type
) 
```


**Parameters:**


* `type` The operator location type to convert.


**Returns:**

String representation of the operator location type. Returns "UNKNOWN" for invalid values.
### function `rid_system_get_area_ceiling`

_Get the area ceiling from a System message._
```c
float rid_system_get_area_ceiling (
    const rid_system_t *system
) 
```


**Parameters:**


* `system` Pointer to the System message structure.


**Returns:**

The ceiling altitude in meters or RID\_AREA\_CEILING\_INVALID when uknnown, including when system is NULL.
### function `rid_system_get_area_count`

_Get the area count from a System message._
```c
uint16_t rid_system_get_area_count (
    const rid_system_t *system
) 
```


**Parameters:**


* `system` Pointer to the System message structure.


**Returns:**

The number of aircraft in the area or 0 if system is NULL.
### function `rid_system_get_area_floor`

_Get the area floor from a System message._
```c
float rid_system_get_area_floor (
    const rid_system_t *system
) 
```


**Parameters:**


* `system` Pointer to the System message structure.


**Returns:**

The floor altitude in meters or RID\_AREA\_FLOOR\_INVALID when unknown, including when system is NULL.
### function `rid_system_get_area_radius`

_Get the area radius from a System message._
```c
uint16_t rid_system_get_area_radius (
    const rid_system_t *system
) 
```


**Parameters:**


* `system` Pointer to the System message structure.


**Returns:**

The radius in meters or 0 if system is NULL.
### function `rid_system_get_classification_type`

_Get the classification type from a System message._
```c
rid_classification_type_t rid_system_get_classification_type (
    const rid_system_t *system
) 
```


**Parameters:**


* `system` Pointer to the System message structure.


**Returns:**

The classification type or RID\_CLASSIFICATION\_TYPE\_UNDECLARED if system is NULL.
### function `rid_system_get_operator_altitude`

_Get the operator altitude from a System message._
```c
float rid_system_get_operator_altitude (
    const rid_system_t *system
) 
```


Decodes altitude from encoded uint16\_t value per ASTM F3411-22a.



**Parameters:**


* `system` Pointer to the System message structure.


**Returns:**

Altitude in meters or RID\_OPERATOR\_ALTITUDE\_INVALID when uknown, including when system is NULL.
### function `rid_system_get_operator_latitude`

_Get the operator latitude from a System message._
```c
double rid_system_get_operator_latitude (
    const rid_system_t *system
) 
```


Decodes latitude from encoded int32\_t value per ASTM F3411-22a.



**Parameters:**


* `system` Pointer to the System message structure.


**Returns:**

Latitude in degrees or RID\_OPERATOR\_LATITUDE\_INVALID if system is NULL or if both encoded latitude and longitude are 0.
### function `rid_system_get_operator_location_type`

_Get the operator location type from a System message._
```c
rid_operator_location_type_t rid_system_get_operator_location_type (
    const rid_system_t *system
) 
```


**Parameters:**


* `system` Pointer to the System message structure.


**Returns:**

The operator location type or RID\_OPERATOR\_LOCATION\_TYPE\_TAKEOFF if system is NULL.
### function `rid_system_get_operator_longitude`

_Get the operator longitude from a System message._
```c
double rid_system_get_operator_longitude (
    const rid_system_t *system
) 
```


Decodes longitude from encoded int32\_t value per ASTM F3411-22a.



**Parameters:**


* `system` Pointer to the System message structure.


**Returns:**

Longitude in degrees or RID\_OPERATOR\_LONGITUDE\_INVALID if system is NULL or if both encoded latitude and longitude are 0.
### function `rid_system_get_timestamp`

_Get the timestamp from a System message._
```c
uint32_t rid_system_get_timestamp (
    const rid_system_t *system
) 
```


**Parameters:**


* `system` Pointer to the System message structure.


**Returns:**

Seconds since RID epoch (2019-01-01 00:00:00 UTC) or 0 if system is NULL.
### function `rid_system_get_ua_classification_category`

_Get the UA classification category from a System message._
```c
rid_ua_classification_category_t rid_system_get_ua_classification_category (
    const rid_system_t *system
) 
```


**Parameters:**


* `system` Pointer to the System message structure.


**Returns:**

The UA classification category or RID\_UA\_CLASSIFICATION\_CATEGORY\_UNDEFINED if system is NULL.
### function `rid_system_get_ua_classification_class`

_Get the UA classification class from a System message._
```c
rid_ua_classification_class_t rid_system_get_ua_classification_class (
    const rid_system_t *system
) 
```


**Parameters:**


* `system` Pointer to the System message structure.


**Returns:**

The UA classification class or RID\_UA\_CLASSIFICATION\_CLASS\_UNDEFINED if system is NULL.
### function `rid_system_get_unixtime`

_Get the timestamp as Unix timestamp._
```c
uint32_t rid_system_get_unixtime (
    const rid_system_t *system
) 
```


Get RID timestamp as Unix timestamp.



**Parameters:**


* `system` Pointer to the System message structure.


**Returns:**

Unix timestamp (seconds since 1970-01-01 00:00:00 UTC) or 0 if system is NULL.
### function `rid_system_init`

_Initialize a System message with default values._
```c
int rid_system_init (
    rid_system_t *system
) 
```


Sets protocol version to 2 and message type to SYSTEM. All other fields are set to zero.



**Parameters:**


* `system` Pointer to the System message structure.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if system is NULL.
### function `rid_system_set_area_ceiling`

_Set the area ceiling for a System message._
```c
int rid_system_set_area_ceiling (
    rid_system_t *system,
    float altitude
) 
```


**Parameters:**


* `system` Pointer to the System message structure. 
* `altitude` The ceiling altitude in meters (-1000 to 31767). Use RID\_AREA\_CEILING\_INVALID for invalid/unknown.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if system is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if altitude is outside valid range.
### function `rid_system_set_area_count`

_Set the area count for a System message._
```c
int rid_system_set_area_count (
    rid_system_t *system,
    uint16_t count
) 
```


**Parameters:**


* `system` Pointer to the System message structure. 
* `count` The number of aircraft in the area.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if system is NULL.
### function `rid_system_set_area_floor`

_Set the area floor for a System message._
```c
int rid_system_set_area_floor (
    rid_system_t *system,
    float altitude
) 
```


**Parameters:**


* `system` Pointer to the System message structure. 
* `altitude` The floor altitude in meters (-1000 to 31767). Use RID\_AREA\_FLOOR\_INVALID for invalid/unknown.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if system is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if altitude is outside valid range.
### function `rid_system_set_area_radius`

_Set the area radius for a System message._
```c
int rid_system_set_area_radius (
    rid_system_t *system,
    uint16_t meters
) 
```


**Parameters:**


* `system` Pointer to the System message structure. 
* `meters` The radius in meters (0 to 2550, 10m resolution).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if system is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if meters exceeds 2550.
### function `rid_system_set_classification_type`

_Set the classification type for a System message._
```c
int rid_system_set_classification_type (
    rid_system_t *system,
    rid_classification_type_t type
) 
```


**Parameters:**


* `system` Pointer to the System message structure. 
* `type` The classification type to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if system is NULL.
### function `rid_system_set_operator_altitude`

_Set the operator altitude for a System message._
```c
int rid_system_set_operator_altitude (
    rid_system_t *system,
    float altitude
) 
```


Encodes altitude in meters per ASTM F3411-22a ((value + 1000) / 0.5).



**Parameters:**


* `system` Pointer to the System message structure. 
* `altitude` Altitude in meters (-1000.0 to 31767.0). Use RID\_OPERATOR\_ALTITUDE\_INVALID for invalid/unknown.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if system is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if altitude is outside valid range.
### function `rid_system_set_operator_latitude`

_Set the operator latitude for a System message._
```c
int rid_system_set_operator_latitude (
    rid_system_t *system,
    double degrees
) 
```


Encodes latitude in degrees per ASTM F3411-22a (value \* 10^7).



**Parameters:**


* `system` Pointer to the System message structure. 
* `degrees` Latitude in degrees (-90.0 to +90.0). Use RID\_OPERATOR\_LATITUDE\_INVALID to indicate invalid/unknown.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if system is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if degrees is outside valid range.
### function `rid_system_set_operator_location_type`

_Set the operator location type for a System message._
```c
int rid_system_set_operator_location_type (
    rid_system_t *system,
    rid_operator_location_type_t type
) 
```


**Parameters:**


* `system` Pointer to the System message structure. 
* `type` The operator location type to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if system is NULL.
### function `rid_system_set_operator_longitude`

_Set the operator longitude for a System message._
```c
int rid_system_set_operator_longitude (
    rid_system_t *system,
    double degrees
) 
```


Encodes longitude in degrees per ASTM F3411-22a (value \* 10^7).



**Parameters:**


* `system` Pointer to the System message structure. 
* `degrees` Longitude in degrees (-180.0 to +180.0). Use RID\_OPERATOR\_LONGITUDE\_INVALID to indicate invalid/unknown.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if system is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if degrees is outside valid range.
### function `rid_system_set_timestamp`

_Set the timestamp for a System message._
```c
int rid_system_set_timestamp (
    rid_system_t *system,
    uint32_t timestamp
) 
```


**Parameters:**


* `system` Pointer to the System message structure. 
* `timestamp` Seconds since RID epoch (2019-01-01 00:00:00 UTC).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if system is NULL.
### function `rid_system_set_ua_classification_category`

_Set the UA classification category for a System message._
```c
int rid_system_set_ua_classification_category (
    rid_system_t *system,
    rid_ua_classification_category_t category
) 
```


**Parameters:**


* `system` Pointer to the System message structure. 
* `category` The UA classification category to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if system is NULL.
### function `rid_system_set_ua_classification_class`

_Set the UA classification class for a System message._
```c
int rid_system_set_ua_classification_class (
    rid_system_t *system,
    rid_ua_classification_class_t class
) 
```


**Parameters:**


* `system` Pointer to the System message structure. 
* `class` The UA classification class to set.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if system is NULL. 
* `RID_ERROR_OUT_OF_RANGE` if classification\_class exceeds RID\_UA\_CLASSIFICATION\_CLASS\_MAX.
### function `rid_system_set_unixtime`

_Set the timestamp for a System message from Unix timestamp._
```c
int rid_system_set_unixtime (
    rid_system_t *system,
    uint32_t unixtime
) 
```


Converts Unix timestamp to RID epoch and stores.



**Parameters:**


* `system` Pointer to the System message structure. 
* `unixtime` Unix timestamp (seconds since 1970-01-01 00:00:00 UTC).


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if system is NULL.
### function `rid_system_to_json`

_Format a System message as a JSON string._
```c
int rid_system_to_json (
    const rid_system_t *system,
    char *buffer,
    size_t buffer_size,
    size_t *needed_size
) 
```


**Parameters:**


* `system` Pointer to the System message structure. 
* `buffer` Buffer to store the JSON string or NULL. 
* `buffer_size` Size of the buffer. 
* `needed_size` If non-NULL receives the required buffer size.


**Return value:**


* `RID_SUCCESS` on success. 
* `RID_ERROR_NULL_POINTER` if `system` is NULL or if both`buffer` and`needed_size` are NULL.
* `RID_ERROR_BUFFER_TOO_SMALL` if `buffer` is too small.
### function `rid_system_validate`

_Validate a System message structure._
```c
int rid_system_validate (
    const rid_system_t *system
) 
```


Checks that all fields contain valid encoded values according to ASTM F3411-22a.



**Parameters:**


* `system` Pointer to the System message structure to validate.


**Return value:**


* `RID_SUCCESS` if all fields are valid. 
* `RID_ERROR_NULL_POINTER` if system is NULL. 
* `RID_ERROR_INVALID_PROTOCOL_VERSION` if protocol version is invalid. 
* `RID_ERROR_UNKNOWN_MESSAGE_TYPE` if message type is not SYSTEM. 
* `RID_ERROR_INVALID_LATITUDE` if operator latitude is out of range. 
* `RID_ERROR_INVALID_LONGITUDE` if operator longitude is out of range.
### function `rid_ua_classification_category_to_string`

_Convert UA classification category to string representation._
```c
const char * rid_ua_classification_category_to_string (
    rid_ua_classification_category_t category
) 
```


**Parameters:**


* `category` The UA classification category to convert.


**Returns:**

String representation of the UA classification category. Returns "UNKNOWN" for invalid values.
### function `rid_ua_classification_class_to_string`

_Convert UA classification class to string representation._
```c
const char * rid_ua_classification_class_to_string (
    rid_ua_classification_class_t class
) 
```


**Parameters:**


* `class` The UA classification class to convert.


**Returns:**

String representation of the UA classification class. Returns "UNKNOWN" for invalid values.

## Macros Documentation

### define `RID_AREA_CEILING_INVALID`

_Value indicating invalid area ceiling altitude._
```c
#define RID_AREA_CEILING_INVALID -1000.0f
```

### define `RID_AREA_CEILING_INVALID_ENCODED`

_Encoded value for invalid area ceiling altitude._
```c
#define RID_AREA_CEILING_INVALID_ENCODED 0
```

### define `RID_AREA_CEILING_MAX`

_Maximum area ceiling altitude in meters._
```c
#define RID_AREA_CEILING_MAX 31767.0f
```

### define `RID_AREA_CEILING_MIN`

_Minimum area ceiling altitude in meters._
```c
#define RID_AREA_CEILING_MIN -1000.0f
```

### define `RID_AREA_COUNT_MAX`

_Maximum area count value._
```c
#define RID_AREA_COUNT_MAX UINT16_MAX
```

### define `RID_AREA_FLOOR_INVALID`

_Value indicating invalid area floor altitude._
```c
#define RID_AREA_FLOOR_INVALID -1000.0f
```

### define `RID_AREA_FLOOR_INVALID_ENCODED`

_Encoded value for invalid area floor altitude._
```c
#define RID_AREA_FLOOR_INVALID_ENCODED 0
```

### define `RID_AREA_FLOOR_MAX`

_Maximum area floor altitude in meters._
```c
#define RID_AREA_FLOOR_MAX 31767.0f
```

### define `RID_AREA_FLOOR_MIN`

_Minimum area floor altitude in meters._
```c
#define RID_AREA_FLOOR_MIN -1000.0f
```

### define `RID_AREA_RADIUS_MAX`

_Maximum area radius in meters._
```c
#define RID_AREA_RADIUS_MAX 2550
```

### define `RID_OPERATOR_ALTITUDE_INVALID`

_Value indicating invalid operator altitude._
```c
#define RID_OPERATOR_ALTITUDE_INVALID -1000.0f
```

### define `RID_OPERATOR_ALTITUDE_INVALID_ENCODED`

_Encoded value for invalid operator altitude._
```c
#define RID_OPERATOR_ALTITUDE_INVALID_ENCODED 0
```

### define `RID_OPERATOR_LATITUDE_INVALID`

_Value indicating invalid operator latitude._
```c
#define RID_OPERATOR_LATITUDE_INVALID DBL_MAX
```

### define `RID_OPERATOR_LONGITUDE_INVALID`

_Value indicating invalid operator longitude._
```c
#define RID_OPERATOR_LONGITUDE_INVALID DBL_MAX
```

### define `RID_SYSTEM_TIMESTAMP_EPOCH`

_Timestamp epoch (2019-01-01 00:00:00 UTC as Unix timestamp)._
```c
#define RID_SYSTEM_TIMESTAMP_EPOCH 1546300800
```


## File include/rid/transport.h

_Remote ID transport method definitions._



## Structures and Types

| Type | Name |
| ---: | :--- |
| enum  | [**rid\_transport\_t**](#enum-rid_transport_t)  <br>_Transport methods for broadcasting Remote ID messages._ |

## Functions

| Type | Name |
| ---: | :--- |
|  const char \* | [**rid\_transport\_to\_string**](#function-rid_transport_to_string) ([**rid\_transport\_t**](#enum-rid_transport_t) transport) <br>_Convert transport type to string representation._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**RID\_TRANSPORT\_BLUETOOTH\_APP\_CODE**](#define-rid_transport_bluetooth_app_code)  0x0D<br> |
| define  | [**RID\_TRANSPORT\_BLUETOOTH\_LEGACY\_MAX\_PAYLOAD**](#define-rid_transport_bluetooth_legacy_max_payload)  25<br> |
| define  | [**RID\_TRANSPORT\_BLUETOOTH\_LONG\_RANGE\_MAX\_PAYLOAD**](#define-rid_transport_bluetooth_long_range_max_payload)  255<br> |
| define  | [**RID\_TRANSPORT\_BLUETOOTH\_OUI**](#define-rid_transport_bluetooth_oui)  0xFFFA<br> |
| define  | [**RID\_TRANSPORT\_TIME\_UNIT\_US**](#define-rid_transport_time_unit_us)  1024<br>_Time Unit in microseconds per ASTM F3411-22a._ |
| define  | [**RID\_TRANSPORT\_WIFI\_BEACON\_MAX\_PAYLOAD**](#define-rid_transport_wifi_beacon_max_payload)  250<br> |
| define  | [**RID\_TRANSPORT\_WIFI\_BEACON\_OUI**](#define-rid_transport_wifi_beacon_oui)  0xFA0BBC<br> |
| define  | [**RID\_TRANSPORT\_WIFI\_BEACON\_VENDOR\_TYPE**](#define-rid_transport_wifi_beacon_vendor_type)  0x0D<br> |
| define  | [**RID\_TRANSPORT\_WIFI\_NAN\_CHANNEL\_2G**](#define-rid_transport_wifi_nan_channel_2g)  6<br> |
| define  | [**RID\_TRANSPORT\_WIFI\_NAN\_CHANNEL\_5G**](#define-rid_transport_wifi_nan_channel_5g)  149<br> |
| define  | [**RID\_TRANSPORT\_WIFI\_NAN\_CLUSTER\_ID**](#define-rid_transport_wifi_nan_cluster_id)  0x506F9A0100FFULL<br> |
| define  | [**RID\_TRANSPORT\_WIFI\_NAN\_MAX\_PAYLOAD**](#define-rid_transport_wifi_nan_max_payload)  255<br> |
| define  | [**RID\_TRANSPORT\_WIFI\_NAN\_OUI**](#define-rid_transport_wifi_nan_oui)  0x506F9A<br> |

## Structures and Types Documentation

### enum `rid_transport_t`

_Transport methods for broadcasting Remote ID messages._
```c
enum rid_transport_t {
    RID_TRANSPORT_BLUETOOTH_LEGACY = 0,
    RID_TRANSPORT_BLUETOOTH_LONG_RANGE = 1,
    RID_TRANSPORT_WIFI_NAN = 2,
    RID_TRANSPORT_WIFI_BEACON = 3,
    RID_TRANSPORT_MAX = 3
};
```


Defined in ASTM F3411-22a Section 5.4

## Functions Documentation

### function `rid_transport_to_string`

_Convert transport type to string representation._
```c
const char * rid_transport_to_string (
    rid_transport_t transport
) 
```


**Parameters:**


* `transport` The transport type to convert.


**Returns:**

String representation of the transport type. Returns "UNKNOWN" for invalid values.

## Macros Documentation

### define `RID_TRANSPORT_BLUETOOTH_APP_CODE`

```c
#define RID_TRANSPORT_BLUETOOTH_APP_CODE 0x0D
```

### define `RID_TRANSPORT_BLUETOOTH_LEGACY_MAX_PAYLOAD`

```c
#define RID_TRANSPORT_BLUETOOTH_LEGACY_MAX_PAYLOAD 25
```

### define `RID_TRANSPORT_BLUETOOTH_LONG_RANGE_MAX_PAYLOAD`

```c
#define RID_TRANSPORT_BLUETOOTH_LONG_RANGE_MAX_PAYLOAD 255
```

### define `RID_TRANSPORT_BLUETOOTH_OUI`

```c
#define RID_TRANSPORT_BLUETOOTH_OUI 0xFFFA
```

### define `RID_TRANSPORT_TIME_UNIT_US`

_Time Unit in microseconds per ASTM F3411-22a._
```c
#define RID_TRANSPORT_TIME_UNIT_US 1024
```

### define `RID_TRANSPORT_WIFI_BEACON_MAX_PAYLOAD`

```c
#define RID_TRANSPORT_WIFI_BEACON_MAX_PAYLOAD 250
```

### define `RID_TRANSPORT_WIFI_BEACON_OUI`

```c
#define RID_TRANSPORT_WIFI_BEACON_OUI 0xFA0BBC
```

### define `RID_TRANSPORT_WIFI_BEACON_VENDOR_TYPE`

```c
#define RID_TRANSPORT_WIFI_BEACON_VENDOR_TYPE 0x0D
```

### define `RID_TRANSPORT_WIFI_NAN_CHANNEL_2G`

```c
#define RID_TRANSPORT_WIFI_NAN_CHANNEL_2G 6
```

### define `RID_TRANSPORT_WIFI_NAN_CHANNEL_5G`

```c
#define RID_TRANSPORT_WIFI_NAN_CHANNEL_5G 149
```

### define `RID_TRANSPORT_WIFI_NAN_CLUSTER_ID`

```c
#define RID_TRANSPORT_WIFI_NAN_CLUSTER_ID 0x506F9A0100FFULL
```

### define `RID_TRANSPORT_WIFI_NAN_MAX_PAYLOAD`

```c
#define RID_TRANSPORT_WIFI_NAN_MAX_PAYLOAD 255
```

### define `RID_TRANSPORT_WIFI_NAN_OUI`

```c
#define RID_TRANSPORT_WIFI_NAN_OUI 0x506F9A
```


## File include/rid/version.h

_Library version information._

**See also:** [https://semver.org/](https://semver.org/)


## Functions

| Type | Name |
| ---: | :--- |
|  const char \* | [**rid\_version\_to\_string**](#function-rid_version_to_string) (void) <br>_Get the library version as a string._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**RID\_VERSION\_MAJOR**](#define-rid_version_major)  0<br> |
| define  | [**RID\_VERSION\_MINOR**](#define-rid_version_minor)  6<br> |
| define  | [**RID\_VERSION\_PATCH**](#define-rid_version_patch)  0<br> |
| define  | [**RID\_VERSION\_STRING**](#define-rid_version_string)  "0.6.0-dev"<br> |


## Functions Documentation

### function `rid_version_to_string`

_Get the library version as a string._
```c
const char * rid_version_to_string (
    void
) 
```


**Returns:**

Version string in "major.minor.patch" format.

## Macros Documentation

### define `RID_VERSION_MAJOR`

```c
#define RID_VERSION_MAJOR 0
```

### define `RID_VERSION_MINOR`

```c
#define RID_VERSION_MINOR 6
```

### define `RID_VERSION_PATCH`

```c
#define RID_VERSION_PATCH 0
```

### define `RID_VERSION_STRING`

```c
#define RID_VERSION_STRING "0.6.0-dev"
```


