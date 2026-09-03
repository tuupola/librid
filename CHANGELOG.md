# Changelog

All notable changes to this project will be documented in this file, in reverse
chronological order by release.

## [0.6.0-dev](https://github.com/tuupola/librid/compare/0.5.0...master) - unreleased

### Changed

- `rid_basic_id_set_uas_id()` now takes a `void *` buffer and length instead of a C string. ([#75](https://github.com/tuupola/librid/commit/f4d832c))
- `rid_basic_id_get_uas_id()` now takes a `void *` buffer and copies `RID_UAS_ID_SIZE` bytes. ([#81](https://github.com/tuupola/librid/commit/ede5f75))
- `rid_self_id_set_description()` and `rid_self_id_validate()` now reject ASCII control characters. ([#82](https://github.com/tuupola/librid/commit/xxxxxx))
- `rid_operator_id_set()` and `rid_operator_id_validate()` now reject ASCII control characters. ([#85](https://github.com/tuupola/librid/commit/xxxxxx))

### Fixed

- `rid_auth_set_signature()` now clears any lingering data if new signature is shorter than the previous. ([#83](https://github.com/tuupola/librid/commit/xxxxxx))
- `rid_auth_set_signature()` now accepts NULL if signature length is 0. ([#84](https://github.com/tuupola/librid/commit/xxxxxx))

## [0.5.0](https://github.com/tuupola/librid/compare/0.4.0...0.5.0) - 2026-08-24

This release is mostly about JSON output correctness. Invalid and missing values
are either rendered as `null` or `0`. The latitude and longitude values are
rendered with seven decimals and all floats with two decimals. Any binary data
is rendered as a hex string.

### Added

- Reduce flash usage by adding `RID_DISABLE_JSON` compile time flag and hex and uuid json helpers. ([#72](https://github.com/tuupola/librid/commit/e422c7e), [#73](https://github.com/tuupola/librid/commit/ed59935))

### Changed

- Invalid and missing values are now rendered as `null` in JSON output ([#44](https://github.com/tuupola/librid/commit/2e4a834), [#49](https://github.com/tuupola/librid/commit/bed97d5), [#50](https://github.com/tuupola/librid/commit/3304c51), [#52](https://github.com/tuupola/librid/commit/215f57e), [#55](https://github.com/tuupola/librid/commit/e44910c), [#58](https://github.com/tuupola/librid/commit/c998d07), [#62](https://github.com/tuupola/librid/commit/973f8a3), [#63](https://github.com/tuupola/librid/commit/b3630ac))
- Value of `RID_VERTICAL_SPEED_INVALID` sentinel is now `FLT_MAX`. ([#45](https://github.com/tuupola/librid/commit/a7b23aa))
- All getters now return `RID_XXX_INVALID` sentinel for missing and invalid values. ([#46](https://github.com/tuupola/librid/commit/99b79c4), [#47](https://github.com/tuupola/librid/commit/c6b7765), [#48](https://github.com/tuupola/librid/commit/9456b0a), [#54](https://github.com/tuupola/librid/commit/f7d48f6))
- Location timestamp is now initialised as `RID_TIMESTAMP_INVALID`. ([#51](https://github.com/tuupola/librid/commit/5773340))
- Latitude and longitude precision in JSON output is now seven decimals instead of six. ([#53](https://github.com/tuupola/librid/commit/ddf5545))
- All setters now accept `RID_XXX_INVALID` sentinel as input for missing and invalid values. ([#56](https://github.com/tuupola/librid/commit/a94b8aa), [#61](https://github.com/tuupola/librid/commit/4e6b7e6))
- All floats are now rendered with two decimals in JSON output. ([#57](https://github.com/tuupola/librid/commit/168e4e9))
- All `rid_*_to_json()` functions now take an optional `needed_size` parameter which receives the required buffer size. The function return value is now only an error code. ([#67](https://github.com/tuupola/librid/commit/21591d9), [#68](https://github.com/tuupola/librid/commit/8bbe610))
- All getter functions now return either `RID_X_INVALID`, `RID_X_UNKNOWN` or `0` when the input message is `NULL`. ([#69](https://github.com/tuupola/librid/commit/896f6bf))
- Binary session id is now rendered as hex in JSON. ([#70](https://github.com/tuupola/librid/commit/0952f44))

### Fixed

- Setting system unixtime before `RID_SYSTEM_TIMESTAMP_EPOCH` reported success but produced garbage timestamp. ([#59](https://github.com/tuupola/librid/commit/2b7732f))

## [0.4.0](https://github.com/tuupola/librid/compare/0.3.0...0.4.0) - 2026-06-17

### Added

- `rid_message_pack_messages_size()` function to get combined size of messages in a Message Pack. ([#25](https://github.com/tuupola/librid/commit/c9c7224), [#36](https://github.com/tuupola/librid/commit/da20dd4))
- `rid_message_pack_get_messages()` function to get pointer to messages in a Message Pack. ([#26](https://github.com/tuupola/librid/commit/d7612e4))
- `rid_message_pack_get_auth()` function to get the Auth message from a Message Pack. ([#28](https://github.com/tuupola/librid/commit/7ff02eb))
- `rid_message_pack_set_auth()` function to set the Auth message in a Message Pack. ([#29](https://github.com/tuupola/librid/commit/616616c))
- `rid_auth_sign()` and `rid_auth_verify()` functions to sign and verify a message. ([#31](https://github.com/tuupola/librid/commit/142efaf))
- `rid_message_pack_sort()` function to sort messages in a Message Pack by type. ([#32](https://github.com/tuupola/librid/commit/95127a3))
- `rid_message_pack_copy_message_at()` function to copy a message from a Message Pack. ([#38](https://github.com/tuupola/librid/commit/b4af9ce))
- `rid_message_pack_find_message_index_by_type()` function to find the index of the first message of a given type. ([#39](https://github.com/tuupola/librid/commit/e680884))
- `rid_message_pack_get_message_type_at()` function to get the message type at a given index. ([#42](https://github.com/tuupola/librid/commit/a4550a2))

### Changed

- `rid_message_pack_add_message()` now also handles Auth messages. ([#27](https://github.com/tuupola/librid/commit/1d2c51c))
- JSON output now includes the assembled Auth message. ([#30](https://github.com/tuupola/librid/commit/81ac214))
- `rid_message_pack_get_size()` renamed to `rid_message_pack_size()`. ([#36](https://github.com/tuupola/librid/commit/da20dd4))
- `rid_message_pack_get_message_count()` renamed to `rid_message_pack_message_count()`. ([#36](https://github.com/tuupola/librid/commit/da20dd4))
- `rid_message_pack_replace_message_at()` renamed to `rid_message_pack_set_message_at()`. ([#37](https://github.com/tuupola/librid/commit/1401f87))

### Fixed

- CMake name collisions when using `FetchContent`. ([#33](https://github.com/tuupola/librid/commit/4b82155))
- JSON output when Message Pack contains only Auth messages. ([#34](https://github.com/tuupola/librid/commit/7390392))

## [0.3.0](https://github.com/tuupola/librid/compare/0.2.0...0.3.0) - 2024-04-20

### Added

- `rid_message_pack_get_size()` function to get Message Pack size in bytes. ([#21](https://github.com/tuupola/librid/commit/06bf138))
- CMake now creates `compile_commands.json` file by default. ([#16](https://github.com/tuupola/librid/commit/3322e4d))
- MAVlink encode/decode roundtrip to examples. ([#15](https://github.com/tuupola/librid/commit/9f0d7f5))
- `RID_ID_TYPE_UTM_ASSIGNED_UUID` ID type is now parsed to human readable format. ([#20](https://github.com/tuupola/librid/commit/5b9005a))

### Removed

- `rid_message_pack_set_message_count()` function from public API. Message count is set automatically. ([#17](https://github.com/tuupola/librid/commit/7b694cc))

### Changed

- `RID_ERROR_INVALID_SERIAL_NUMBER` error is now returned when Basic ID serial number validation fails. ([#19](https://github.com/tuupola/librid/commit/ce37c91))
- `RID_ERROR_INVALID_CAA_REGISTRATION_ID` error is now returned when Basic ID CAA registration validation fails. ([#22](https://github.com/tuupola/librid/commit/2b26214))

## [0.2.0](https://github.com/tuupola/librid/compare/0.1.0...0.2.0) - 2026-03-11

### Added

- `rid_system_get_unixtime()` function to get system timestamp as Unix timestamp. ([#9](https://github.com/tuupola/librid/commit/b5db54c))

### Removed

- `rid_ew_direction_to_string()` function from public API. EW direction flag is internal to the implementation. ([#8](https://github.com/tuupola/librid/commit/34a3701))

## 0.1.0 - 2026-01-27

Initial release.
