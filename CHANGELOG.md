# Changelog

All notable changes to this project will be documented in this file, in reverse chronological order by release.

## [0.4.0](https://github.com/tuupola/librid/compare/0.3.0...master) - unreleased

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
