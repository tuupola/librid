#ifndef _RID_LOCATION_H
#define _RID_LOCATION_H

#include <stdint.h>
#include <float.h>

#include "rid/header.h"

#define RID_TRACK_DIRECTION_MAX 359
#define RID_TRACK_DIRECTION_UNKNOWN 361
#define RID_TRACK_DIRECTION_UNKNOWN_ENCODED 181

#define RID_SPEED_INVALID FLT_MAX
#define RID_SPEED_INVALID_ENCODED 255

#define RID_VERTICAL_SPEED_INVALID 63
#define RID_VERTICAL_SPEED_INVALID_ENCODED 126

#define RID_HEIGHT_INVALID FLT_MAX
#define RID_HEIGHT_INVALID_ENCODED 0

#define RID_PRESSURE_ALTITUDE_INVALID FLT_MAX
#define RID_PRESSURE_ALTITUDE_INVALID_ENCODED 0

#define RID_GEODETIC_ALTITUDE_INVALID FLT_MAX
#define RID_GEODETIC_ALTITUDE_INVALID_ENCODED 0

#define RID_TIMESTAMP_INVALID 0xFFFF
#define RID_TIMESTAMP_MAX 36000

/**
 * @brief East/West direction flag per ASTM F3411-22a.
 */
typedef enum rid_ew_direction {
    RID_EW_DIRECTION_EAST,
    RID_EW_DIRECTION_WEST,
} rid_ew_direction_t;

/**
 * @brief Height reference type per ASTM F3411-22a.
 */
typedef enum rid_height_type {
    RID_HEIGHT_TYPE_ABOVE_TAKEOFF,
    RID_HEIGHT_TYPE_AGL,
} rid_height_type_t;

/**
 * @brief Operational status per ASTM F3411-22a.
 */
typedef enum rid_operational_status {
    RID_OPERATIONAL_STATUS_UNDECLARED,
    RID_OPERATIONAL_STATUS_GROUND,
    RID_OPERATIONAL_STATUS_AIRBORNE,
    RID_OPERATIONAL_STATUS_EMERGENCY,
    RID_OPERATIONAL_STATUS_REMOTE_ID_SYSTEM_FAILURE,
    RID_OPERATIONAL_STATUS_RESERVED_5,
    RID_OPERATIONAL_STATUS_RESERVED_6,
    RID_OPERATIONAL_STATUS_RESERVED_7,
    RID_OPERATIONAL_STATUS_RESERVED_8,
    RID_OPERATIONAL_STATUS_RESERVED_9,
    RID_OPERATIONAL_STATUS_RESERVED_10,
    RID_OPERATIONAL_STATUS_RESERVED_11,
    RID_OPERATIONAL_STATUS_RESERVED_12,
    RID_OPERATIONAL_STATUS_RESERVED_13,
    RID_OPERATIONAL_STATUS_RESERVED_14,
    RID_OPERATIONAL_STATUS_RESERVED_15,
} rid_operational_status_t;

/**
 * @brief Horizontal accuracy per ASTM F3411-22a.
 */
typedef enum rid_horizontal_accuracy {
    RID_HORIZONTAL_ACCURACY_UNKNOWN,
    RID_HORIZONTAL_ACCURACY_18520M,
    RID_HORIZONTAL_ACCURACY_7408M,
    RID_HORIZONTAL_ACCURACY_3704M,
    RID_HORIZONTAL_ACCURACY_1852M,
    RID_HORIZONTAL_ACCURACY_926M,
    RID_HORIZONTAL_ACCURACY_555M,
    RID_HORIZONTAL_ACCURACY_185M,
    RID_HORIZONTAL_ACCURACY_93M,
    RID_HORIZONTAL_ACCURACY_30M,
    RID_HORIZONTAL_ACCURACY_10M,
    RID_HORIZONTAL_ACCURACY_3M,
    RID_HORIZONTAL_ACCURACY_1M,
    RID_HORIZONTAL_ACCURACY_RESERVED_13,
    RID_HORIZONTAL_ACCURACY_RESERVED_14,
    RID_HORIZONTAL_ACCURACY_RESERVED_15,
} rid_horizontal_accuracy_t;

/**
 * @brief Vertical accuracy per ASTM F3411-22a.
 */
typedef enum rid_vertical_accuracy {
    RID_VERTICAL_ACCURACY_UNKNOWN,
    RID_VERTICAL_ACCURACY_150M,
    RID_VERTICAL_ACCURACY_45M,
    RID_VERTICAL_ACCURACY_25M,
    RID_VERTICAL_ACCURACY_10M,
    RID_VERTICAL_ACCURACY_3M,
    RID_VERTICAL_ACCURACY_1M,
    RID_VERTICAL_ACCURACY_RESERVED_7,
    RID_VERTICAL_ACCURACY_RESERVED_8,
    RID_VERTICAL_ACCURACY_RESERVED_9,
    RID_VERTICAL_ACCURACY_RESERVED_10,
    RID_VERTICAL_ACCURACY_RESERVED_11,
    RID_VERTICAL_ACCURACY_RESERVED_12,
    RID_VERTICAL_ACCURACY_RESERVED_13,
    RID_VERTICAL_ACCURACY_RESERVED_14,
    RID_VERTICAL_ACCURACY_RESERVED_15,
} rid_vertical_accuracy_t;

/**
 * @brief Speed accuracy per ASTM F3411-22a.
 */
typedef enum rid_speed_accuracy {
    RID_SPEED_ACCURACY_UNKNOWN,
    RID_SPEED_ACCURACY_10MS,
    RID_SPEED_ACCURACY_3MS,
    RID_SPEED_ACCURACY_1MS,
    RID_SPEED_ACCURACY_03MS,
    RID_SPEED_ACCURACY_RESERVED_5,
    RID_SPEED_ACCURACY_RESERVED_6,
    RID_SPEED_ACCURACY_RESERVED_7,
    RID_SPEED_ACCURACY_RESERVED_8,
    RID_SPEED_ACCURACY_RESERVED_9,
    RID_SPEED_ACCURACY_RESERVED_10,
    RID_SPEED_ACCURACY_RESERVED_11,
    RID_SPEED_ACCURACY_RESERVED_12,
    RID_SPEED_ACCURACY_RESERVED_13,
    RID_SPEED_ACCURACY_RESERVED_14,
    RID_SPEED_ACCURACY_RESERVED_15,
} rid_speed_accuracy_t;

/**
 * @brief Timestamp accuracy per ASTM F3411-22a.
 */
typedef enum rid_timestamp_accuracy {
    RID_TIMESTAMP_ACCURACY_UNKNOWN,
    RID_TIMESTAMP_ACCURACY_0_1S,
    RID_TIMESTAMP_ACCURACY_0_2S,
    RID_TIMESTAMP_ACCURACY_0_3S,
    RID_TIMESTAMP_ACCURACY_0_4S,
    RID_TIMESTAMP_ACCURACY_0_5S,
    RID_TIMESTAMP_ACCURACY_0_6S,
    RID_TIMESTAMP_ACCURACY_0_7S,
    RID_TIMESTAMP_ACCURACY_0_8S,
    RID_TIMESTAMP_ACCURACY_0_9S,
    RID_TIMESTAMP_ACCURACY_1_0S,
    RID_TIMESTAMP_ACCURACY_1_1S,
    RID_TIMESTAMP_ACCURACY_1_2S,
    RID_TIMESTAMP_ACCURACY_1_3S,
    RID_TIMESTAMP_ACCURACY_1_4S,
    RID_TIMESTAMP_ACCURACY_1_5S,
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
rid_error_t rid_location_init(rid_location_t *location);

/**
 * @brief Set the height reference type for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param type The height reference type to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_height_type(rid_location_t *location, rid_height_type_t type);

/**
 * @brief Get the height reference type from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return The height reference type.
 */
rid_height_type_t rid_get_height_type(const rid_location_t *location);

/**
 * @brief Set the operational status for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param status The operational status to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_operational_status(rid_location_t *location, rid_operational_status_t status);

/**
 * @brief Get the operational status from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return The operational status.
 */
rid_operational_status_t rid_get_operational_status(const rid_location_t *location);

/**
 * @brief Set the track direction for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param degrees Track direction in degrees (0-359, or RID_TRACK_DIRECTION_UNKNOWN).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_track_direction(rid_location_t *location, uint16_t degrees);

/**
 * @brief Get the track direction from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Track direction in degrees (0-359, or RID_TRACK_DIRECTION_UNKNOWN).
 */
uint16_t rid_get_track_direction(const rid_location_t *location);

/**
 * @brief Set the ground speed for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param speed_ms Speed in meters per second.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_speed(rid_location_t *location, float speed_ms);

/**
 * @brief Get the ground speed from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Speed in meters per second.
 */
float rid_get_speed(const rid_location_t *location);

/**
 * @brief Set the vertical speed for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param speed_ms Vertical speed in meters per second.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_vertical_speed(rid_location_t *location, float speed_ms);

/**
 * @brief Get the vertical speed from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Vertical speed in meters per second.
 */
float rid_get_vertical_speed(const rid_location_t *location);

/**
 * @brief Set the latitude for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param degrees Latitude in degrees.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_latitude(rid_location_t *location, double degrees);

/**
 * @brief Get the latitude from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Latitude in degrees.
 */
double rid_get_latitude(const rid_location_t *location);

/**
 * @brief Set the longitude for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param degrees Longitude in degrees.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_longitude(rid_location_t *location, double degrees);

/**
 * @brief Get the longitude from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Longitude in degrees.
 */
double rid_get_longitude(const rid_location_t *location);

/**
 * @brief Set the pressure altitude for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param altitude_m Pressure altitude in meters.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_pressure_altitude(rid_location_t *location, float altitude_m);

/**
 * @brief Get the pressure altitude from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Pressure altitude in meters.
 */
float rid_get_pressure_altitude(const rid_location_t *location);

/**
 * @brief Set the geodetic altitude for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param altitude_m Geodetic altitude in meters.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_geodetic_altitude(rid_location_t *location, float altitude_m);

/**
 * @brief Get the geodetic altitude from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Geodetic altitude in meters.
 */
float rid_get_geodetic_altitude(const rid_location_t *location);

/**
 * @brief Set the height for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param height_m Height in meters.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_height(rid_location_t *location, float height_m);

/**
 * @brief Get the height from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Height in meters.
 */
float rid_get_height(const rid_location_t *location);

/**
 * @brief Set the horizontal position accuracy for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param accuracy The horizontal accuracy to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_horizontal_accuracy(rid_location_t *location, rid_horizontal_accuracy_t accuracy);

/**
 * @brief Get the horizontal position accuracy from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return The horizontal accuracy.
 */
rid_horizontal_accuracy_t rid_get_horizontal_accuracy(const rid_location_t *location);

/**
 * @brief Set the vertical position accuracy for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param accuracy The vertical accuracy to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_vertical_accuracy(rid_location_t *location, rid_vertical_accuracy_t accuracy);

/**
 * @brief Get the vertical position accuracy from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return The vertical accuracy.
 */
rid_vertical_accuracy_t rid_get_vertical_accuracy(const rid_location_t *location);

/**
 * @brief Set the speed accuracy for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param accuracy The speed accuracy to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_speed_accuracy(rid_location_t *location, rid_speed_accuracy_t accuracy);

/**
 * @brief Get the speed accuracy from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return The speed accuracy.
 */
rid_speed_accuracy_t rid_get_speed_accuracy(const rid_location_t *location);

/**
 * @brief Set the barometric altitude accuracy for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param accuracy The barometric altitude accuracy to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_baro_altitude_accuracy(rid_location_t *location, rid_vertical_accuracy_t accuracy);

/**
 * @brief Get the barometric altitude accuracy from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return The barometric altitude accuracy.
 */
rid_vertical_accuracy_t rid_get_baro_altitude_accuracy(const rid_location_t *location);

/**
 * @brief Set the timestamp for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param deciseconds Time in deciseconds since the hour.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_timestamp(rid_location_t *location, uint16_t deciseconds);

/**
 * @brief Get the timestamp from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return Time in deciseconds since the hour.
 */
uint16_t rid_get_timestamp(const rid_location_t *location);

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
rid_error_t rid_set_timestamp_from_unixtime(rid_location_t *location, uint32_t unixtime);

/**
 * @brief Set the timestamp accuracy for a Location message.
 *
 * @param location Pointer to the Location message structure.
 * @param accuracy The timestamp accuracy to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if location is NULL.
 */
rid_error_t rid_set_timestamp_accuracy(rid_location_t *location, rid_timestamp_accuracy_t accuracy);

/**
 * @brief Get the timestamp accuracy from a Location message.
 *
 * @param location Pointer to the Location message structure.
 *
 * @return The timestamp accuracy.
 */
rid_timestamp_accuracy_t rid_get_timestamp_accuracy(const rid_location_t *location);

#endif