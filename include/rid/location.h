/*

MIT License

Copyright (c) 2025-2026 Mika Tuupola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-cut-

This file is part of librid: https://github.com/tuupola/librid

SPDX-License-Identifier: MIT

*/

#ifndef RID_LOCATION_H
#define RID_LOCATION_H

/**
 * @file location.h
 * @brief Location message handling per ASTM F3411-22a.
 *
 * Example usage:
 * @snippet location/example_location.c full_example
 */

#include <stdint.h>
#include <float.h>

#include "rid/message.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @brief Maximum valid track direction in degrees. */
#define RID_TRACK_DIRECTION_MAX 359
/** @brief Value indicating unknown track direction. */
#define RID_TRACK_DIRECTION_UNKNOWN 361
/** @brief Encoded value for unknown track direction. */
#define RID_TRACK_DIRECTION_UNKNOWN_ENCODED 181

/** @brief Value indicating invalid speed. */
#define RID_SPEED_INVALID FLT_MAX
/** @brief Encoded value for invalid speed. */
#define RID_SPEED_INVALID_ENCODED 255

/** @brief Value indicating invalid vertical speed. */
#define RID_VERTICAL_SPEED_INVALID 63
/** @brief Encoded value for invalid vertical speed. */
#define RID_VERTICAL_SPEED_INVALID_ENCODED 126

/** @brief Value indicating invalid height. */
#define RID_HEIGHT_INVALID FLT_MAX
/** @brief Encoded value for invalid height. */
#define RID_HEIGHT_INVALID_ENCODED 0

/** @brief Value indicating invalid pressure altitude. */
#define RID_PRESSURE_ALTITUDE_INVALID FLT_MAX
/** @brief Encoded value for invalid pressure altitude. */
#define RID_PRESSURE_ALTITUDE_INVALID_ENCODED 0

/** @brief Value indicating invalid geodetic altitude. */
#define RID_GEODETIC_ALTITUDE_INVALID FLT_MAX
/** @brief Encoded value for invalid geodetic altitude. */
#define RID_GEODETIC_ALTITUDE_INVALID_ENCODED 0

/** @brief Value indicating invalid timestamp. */
#define RID_TIMESTAMP_INVALID 0xFFFF
/** @brief Maximum valid timestamp in deciseconds (1 hour). */
#define RID_TIMESTAMP_MAX 36000

/**
 * @brief East/West direction flag per ASTM F3411-22a.
 */
typedef enum rid_ew_direction {
    RID_EW_DIRECTION_EAST = 0,
    RID_EW_DIRECTION_WEST = 1,
} rid_ew_direction_t;

/**
 * @brief Height reference type per ASTM F3411-22a.
 */
typedef enum rid_height_type {
    RID_HEIGHT_TYPE_ABOVE_TAKEOFF = 0,
    RID_HEIGHT_TYPE_AGL = 1,
} rid_height_type_t;

/**
 * @brief Operational status per ASTM F3411-22a.
 */
typedef enum rid_operational_status {
    RID_OPERATIONAL_STATUS_UNDECLARED = 0,
    RID_OPERATIONAL_STATUS_GROUND = 1,
    RID_OPERATIONAL_STATUS_AIRBORNE = 2,
    RID_OPERATIONAL_STATUS_EMERGENCY = 3,
    RID_OPERATIONAL_STATUS_REMOTE_ID_SYSTEM_FAILURE = 4,
    RID_OPERATIONAL_STATUS_RESERVED_5 = 5,
    RID_OPERATIONAL_STATUS_RESERVED_6 = 6,
    RID_OPERATIONAL_STATUS_RESERVED_7 = 7,
    RID_OPERATIONAL_STATUS_RESERVED_8 = 8,
    RID_OPERATIONAL_STATUS_RESERVED_9 = 9,
    RID_OPERATIONAL_STATUS_RESERVED_10 = 10,
    RID_OPERATIONAL_STATUS_RESERVED_11 = 11,
    RID_OPERATIONAL_STATUS_RESERVED_12 = 12,
    RID_OPERATIONAL_STATUS_RESERVED_13 = 13,
    RID_OPERATIONAL_STATUS_RESERVED_14 = 14,
    RID_OPERATIONAL_STATUS_RESERVED_15 = 15,
} rid_operational_status_t;

/**
 * @brief Horizontal accuracy per ASTM F3411-22a.
 */
typedef enum rid_horizontal_accuracy {
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
    RID_HORIZONTAL_ACCURACY_RESERVED_13 = 13,
    RID_HORIZONTAL_ACCURACY_RESERVED_14 = 14,
    RID_HORIZONTAL_ACCURACY_RESERVED_15 = 15,
} rid_horizontal_accuracy_t;

/**
 * @brief Vertical accuracy per ASTM F3411-22a.
 */
typedef enum rid_vertical_accuracy {
    RID_VERTICAL_ACCURACY_UNKNOWN = 0,
    RID_VERTICAL_ACCURACY_150M = 1,
    RID_VERTICAL_ACCURACY_45M = 2,
    RID_VERTICAL_ACCURACY_25M = 3,
    RID_VERTICAL_ACCURACY_10M = 4,
    RID_VERTICAL_ACCURACY_3M = 5,
    RID_VERTICAL_ACCURACY_1M = 6,
    RID_VERTICAL_ACCURACY_RESERVED_7 = 7,
    RID_VERTICAL_ACCURACY_RESERVED_8 = 8,
    RID_VERTICAL_ACCURACY_RESERVED_9 = 9,
    RID_VERTICAL_ACCURACY_RESERVED_10 = 10,
    RID_VERTICAL_ACCURACY_RESERVED_11 = 11,
    RID_VERTICAL_ACCURACY_RESERVED_12 = 12,
    RID_VERTICAL_ACCURACY_RESERVED_13 = 13,
    RID_VERTICAL_ACCURACY_RESERVED_14 = 14,
    RID_VERTICAL_ACCURACY_RESERVED_15 = 15,
} rid_vertical_accuracy_t;

/**
 * @brief Speed accuracy per ASTM F3411-22a.
 */
typedef enum rid_speed_accuracy {
    RID_SPEED_ACCURACY_UNKNOWN = 0,
    RID_SPEED_ACCURACY_10MS = 1,
    RID_SPEED_ACCURACY_3MS = 2,
    RID_SPEED_ACCURACY_1MS = 3,
    RID_SPEED_ACCURACY_03MS = 4,
    RID_SPEED_ACCURACY_RESERVED_5 = 5,
    RID_SPEED_ACCURACY_RESERVED_6 = 6,
    RID_SPEED_ACCURACY_RESERVED_7 = 7,
    RID_SPEED_ACCURACY_RESERVED_8 = 8,
    RID_SPEED_ACCURACY_RESERVED_9 = 9,
    RID_SPEED_ACCURACY_RESERVED_10 = 10,
    RID_SPEED_ACCURACY_RESERVED_11 = 11,
    RID_SPEED_ACCURACY_RESERVED_12 = 12,
    RID_SPEED_ACCURACY_RESERVED_13 = 13,
    RID_SPEED_ACCURACY_RESERVED_14 = 14,
    RID_SPEED_ACCURACY_RESERVED_15 = 15,
} rid_speed_accuracy_t;

/**
 * @brief Timestamp accuracy per ASTM F3411-22a.
 */
typedef enum rid_timestamp_accuracy {
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
    RID_TIMESTAMP_ACCURACY_1_5S = 15,
} rid_timestamp_accuracy_t;

/**
 * @brief Location message structure per ASTM F3411-22a.
 */
typedef struct
__attribute__((__packed__)) rid_location {
    uint8_t protocol_version: 4;
    uint8_t message_type : 4;

    uint8_t speed_multiplier: 1;
    uint8_t ew_direction: 1;
    uint8_t height_type: 1;
    uint8_t reserved_1: 1;
    uint8_t operational_status: 4;

    uint8_t track_direction;
    uint8_t speed;
    int8_t vertical_speed;

    int32_t latitude;
    int32_t longitude;
    uint16_t pressure_altitude;
    uint16_t geodetic_altitude;
    uint16_t height;

    uint8_t horizontal_accuracy: 4;
    uint8_t vertical_accuracy: 4;

    uint8_t speed_accuracy: 4;
    uint8_t baro_altitude_accuracy: 4;

    uint16_t timestamp;

    uint8_t timestamp_accuracy: 4;
    uint8_t reserved_2: 4;
    uint8_t reserved_3;
} rid_location_t;

/**
 * @brief Initialize a Location message structure.
 *
 * Sets protocol version to RID_PROTOCOL_VERSION_2 and message type to
 * RID_MESSAGE_TYPE_LOCATION. All other fields are set to invalid markers.
 *
 * @param location Pointer to the Location message structure to initialize.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_init(rid_location_t *location);

/**
 * @brief Validate a Location message structure.
 *
 * Checks that all fields contain valid encoded values according to
 * ASTM F3411-22a. This validates the raw encoded values, not decoded
 * physical values.
 *
 * @param location Pointer to the Location message structure to validate.
 *
 * @retval RID_SUCCESS if all fields are valid.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 * @retval RID_ERROR_INVALID_PROTOCOL_VERSION if protocol version is invalid.
 * @retval RID_ERROR_WRONG_MESSAGE_TYPE if message type is not LOCATION.
 * @retval RID_ERROR_INVALID_LATITUDE if latitude is out of range.
 * @retval RID_ERROR_INVALID_LONGITUDE if longitude is out of range.
 * @retval RID_ERROR_INVALID_TRACK_DIRECTION if track direction is out of range.
 * @retval RID_ERROR_INVALID_TIMESTAMP if timestamp is out of range.
 */
int rid_location_validate(const rid_location_t *location);

/**
 * @brief Set the height reference type for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param type The height reference type to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_height_type(rid_location_t *location, rid_height_type_t type);

/**
 * @brief Get the height reference type from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return The height reference type.
 */
rid_height_type_t rid_location_get_height_type(const rid_location_t *location);

/**
 * @brief Set the operational status for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param status The operational status to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_operational_status(rid_location_t *location, rid_operational_status_t status);

/**
 * @brief Get the operational status from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return The operational status.
 */
rid_operational_status_t rid_location_get_operational_status(const rid_location_t *location);

/**
 * @brief Set the track direction for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param degrees Track direction in degrees (0-359, or RID_TRACK_DIRECTION_UNKNOWN).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_track_direction(rid_location_t *location, uint16_t degrees);

/**
 * @brief Get the track direction from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Track direction in degrees (0-359, or RID_TRACK_DIRECTION_UNKNOWN).
 */
uint16_t rid_location_get_track_direction(const rid_location_t *location);

/**
 * @brief Set the ground speed for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param speed_ms Speed in meters per second.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_speed(rid_location_t *location, float speed_ms);

/**
 * @brief Get the ground speed from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Speed in meters per second.
 */
float rid_location_get_speed(const rid_location_t *location);

/**
 * @brief Set the vertical speed for a Location message.
 *
 * Values outside -62 to 62 m/s range are clamped to the nearest limit.
 *
 * @param location Pointer to the Location message structure.
 * @param speed_ms Vertical speed in meters per second (-62 to 62).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_vertical_speed(rid_location_t *location, float speed_ms);

/**
 * @brief Get the vertical speed from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Vertical speed in meters per second.
 */
float rid_location_get_vertical_speed(const rid_location_t *location);

/**
 * @brief Set the latitude for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param degrees Latitude in degrees.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_latitude(rid_location_t *location, double degrees);

/**
 * @brief Get the latitude from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Latitude in degrees.
 */
double rid_location_get_latitude(const rid_location_t *location);

/**
 * @brief Set the longitude for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param degrees Longitude in degrees.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_longitude(rid_location_t *location, double degrees);

/**
 * @brief Get the longitude from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Longitude in degrees.
 */
double rid_location_get_longitude(const rid_location_t *location);

/**
 * @brief Set the pressure altitude for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param altitude_m Pressure altitude in meters.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_pressure_altitude(rid_location_t *location, float altitude_m);

/**
 * @brief Get the pressure altitude from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Pressure altitude in meters.
 */
float rid_location_get_pressure_altitude(const rid_location_t *location);

/**
 * @brief Set the geodetic altitude for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param altitude_m Geodetic altitude in meters.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_geodetic_altitude(rid_location_t *location, float altitude_m);

/**
 * @brief Get the geodetic altitude from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Geodetic altitude in meters.
 */
float rid_location_get_geodetic_altitude(const rid_location_t *location);

/**
 * @brief Set the height for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param height_m Height in meters.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_height(rid_location_t *location, float height_m);

/**
 * @brief Get the height from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Height in meters.
 */
float rid_location_get_height(const rid_location_t *location);

/**
 * @brief Set the horizontal position accuracy for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param accuracy The horizontal accuracy to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_horizontal_accuracy(rid_location_t *location, rid_horizontal_accuracy_t accuracy);

/**
 * @brief Get the horizontal position accuracy from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return The horizontal accuracy.
 */
rid_horizontal_accuracy_t rid_location_get_horizontal_accuracy(const rid_location_t *location);

/**
 * @brief Set the vertical position accuracy for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param accuracy The vertical accuracy to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_vertical_accuracy(rid_location_t *location, rid_vertical_accuracy_t accuracy);

/**
 * @brief Get the vertical position accuracy from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return The vertical accuracy.
 */
rid_vertical_accuracy_t rid_location_get_vertical_accuracy(const rid_location_t *location);

/**
 * @brief Set the speed accuracy for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param accuracy The speed accuracy to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_speed_accuracy(rid_location_t *location, rid_speed_accuracy_t accuracy);

/**
 * @brief Get the speed accuracy from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return The speed accuracy.
 */
rid_speed_accuracy_t rid_location_get_speed_accuracy(const rid_location_t *location);

/**
 * @brief Set the barometric altitude accuracy for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param accuracy The barometric altitude accuracy to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_baro_altitude_accuracy(rid_location_t *location, rid_vertical_accuracy_t accuracy);

/**
 * @brief Get the barometric altitude accuracy from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return The barometric altitude accuracy.
 */
rid_vertical_accuracy_t rid_location_get_baro_altitude_accuracy(const rid_location_t *location);

/**
 * @brief Set the timestamp for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param deciseconds Time in deciseconds since the hour.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_timestamp(rid_location_t *location, uint16_t deciseconds);

/**
 * @brief Get the timestamp from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Time in deciseconds since the hour.
 */
uint16_t rid_location_get_timestamp(const rid_location_t *location);

/**
 * @brief Set the timestamp from Unix time for a Location message.
 *
 * Converts Unix timestamp to deciseconds since the hour.
 *
 * @param location Pointer to the Location message structure.
 * @param unixtime Unix timestamp (seconds since epoch).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_unixtime(rid_location_t *location, uint32_t unixtime);

/**
 * @brief Set the timestamp accuracy for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param accuracy The timestamp accuracy to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
int rid_location_set_timestamp_accuracy(rid_location_t *location, rid_timestamp_accuracy_t accuracy);

/**
 * @brief Get the timestamp accuracy from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return The timestamp accuracy.
 */
rid_timestamp_accuracy_t rid_location_get_timestamp_accuracy(const rid_location_t *location);

/**
 * @brief Convert EW direction to string representation.
 *
 * @param direction The EW direction to convert.
 *
 * @return String representation of the EW direction.
 *         Returns "UNKNOWN" for invalid values.
 */
const char *rid_ew_direction_to_string(rid_ew_direction_t direction);

/**
 * @brief Convert height type to string representation.
 *
 * @param type The height type to convert.
 *
 * @return String representation of the height type.
 *         Returns "UNKNOWN" for invalid values.
 */
const char *rid_height_type_to_string(rid_height_type_t type);

/**
 * @brief Convert operational status to string representation.
 *
 * @param status The operational status to convert.
 *
 * @return String representation of the operational status.
 *         Returns "UNKNOWN" for invalid values.
 */
const char *rid_operational_status_to_string(rid_operational_status_t status);

/**
 * @brief Convert horizontal accuracy to string representation.
 *
 * @param accuracy The horizontal accuracy to convert.
 *
 * @return String representation of the horizontal accuracy.
 *         Returns "UNKNOWN" for invalid values.
 */
const char *rid_horizontal_accuracy_to_string(rid_horizontal_accuracy_t accuracy);

/**
 * @brief Convert vertical accuracy to string representation.
 *
 * @param accuracy The vertical accuracy to convert.
 *
 * @return String representation of the vertical accuracy.
 *         Returns "UNKNOWN" for invalid values.
 */
const char *rid_vertical_accuracy_to_string(rid_vertical_accuracy_t accuracy);

/**
 * @brief Convert speed accuracy to string representation.
 *
 * @param accuracy The speed accuracy to convert.
 *
 * @return String representation of the speed accuracy.
 *         Returns "UNKNOWN" for invalid values.
 */
const char *rid_speed_accuracy_to_string(rid_speed_accuracy_t accuracy);

/**
 * @brief Convert timestamp accuracy to string representation.
 *
 * @param accuracy The timestamp accuracy to convert.
 *
 * @return String representation of the timestamp accuracy.
 *         Returns "UNKNOWN" for invalid values.
 */
const char *rid_timestamp_accuracy_to_string(rid_timestamp_accuracy_t accuracy);

/**
 * @brief Format a Location message as a JSON string.
 *
 * @param location Pointer to the Location message structure.
 * @param buffer Buffer to store the JSON string.
 * @param buffer_size Size of the buffer.
 *
 * @return Number of characters written (excluding null terminator),
 *         or negative value on error.
 */
int rid_location_to_json(const rid_location_t *location, char *buffer, size_t buffer_size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif