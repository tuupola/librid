#ifndef _RID_SYSTEM_H
#define _RID_SYSTEM_H

#include <stdint.h>
#include <stddef.h>
#include <float.h>

#include "rid/header.h"

/**
 * @brief System message structure per ASTM F3411-22a.
 */
typedef struct
__attribute__((__packed__)) rid_system {
    uint8_t protocol_version: 4;
    uint8_t message_type : 4;

    uint8_t operator_location_type: 2;
    uint8_t classification_type: 3;
    uint8_t reserved_1: 3;

    int32_t operator_latitude;
    int32_t operator_longitude;

    uint16_t area_count;
    uint8_t area_radius;
    uint16_t area_ceiling;
    uint16_t area_floor;

    uint8_t ua_classification_class: 4;
    uint8_t ua_classification_category: 4;

    uint16_t operator_altitude;
    uint32_t timestamp;

    uint8_t reserved_2;
} rid_system_t;

#define RID_OPERATOR_ALTITUDE_INVALID FLT_MAX
#define RID_OPERATOR_ALTITUDE_INVALID_ENCODED 0

/**
 * @brief Operator location type per ASTM F3411-22a.
 */
typedef enum rid_operator_location_type {
    RID_OPERATOR_LOCATION_TYPE_TAKEOFF,
    RID_OPERATOR_LOCATION_TYPE_DYNAMIC,
    RID_OPERATOR_LOCATION_TYPE_FIXED,
    RID_OPERATOR_LOCATION_TYPE_MAX = 3,
} rid_operator_location_type_t;

/**
 * @brief Classification type per ASTM F3411-22a.
 */
typedef enum rid_classification_type {
    RID_CLASSIFICATION_TYPE_UNDECLARED,
    RID_CLASSIFICATION_TYPE_EUROPEAN_UNION,
    RID_CLASSIFICATION_TYPE_MAX = 7,
    /* 2-7: reserved */
} rid_classification_type_t;

/**
 * @brief UA classification category per ASTM F3411-22a.
 */
typedef enum rid_ua_classification_category {
    RID_UA_CLASSIFICATION_CATEGORY_UNDEFINED,
    RID_UA_CLASSIFICATION_CATEGORY_OPEN,
    RID_UA_CLASSIFICATION_CATEGORY_SPECIFIC,
    RID_UA_CLASSIFICATION_CATEGORY_CERTIFIED,
    RID_UA_CLASSIFICATION_CATEGORY_MAX = 15,
    /* 4-15: reserved */
} rid_ua_classification_category_t;

/**
 * @brief UA classification class per ASTM F3411-22a.
 */
typedef enum rid_ua_classification_class {
    RID_UA_CLASSIFICATION_CLASS_UNDEFINED,
    RID_UA_CLASSIFICATION_CLASS_0,
    RID_UA_CLASSIFICATION_CLASS_1,
    RID_UA_CLASSIFICATION_CLASS_2,
    RID_UA_CLASSIFICATION_CLASS_3,
    RID_UA_CLASSIFICATION_CLASS_4,
    RID_UA_CLASSIFICATION_CLASS_5,
    RID_UA_CLASSIFICATION_CLASS_6,
    RID_UA_CLASSIFICATION_CLASS_MAX = 15,
    /* 8-15: reserved */
} rid_ua_classification_class_t;

/**
 * @brief Set the operator location type for a System message.
 *
 * @param system Pointer to the System message structure.
 * @param type The operator location type to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if system is NULL.
 */
rid_error_t rid_set_operator_location_type(rid_system_t *system, rid_operator_location_type_t type);

/**
 * @brief Get the operator location type from a System message.
 *
 * @param system Pointer to the System message structure.
 *
 * @return The operator location type value.
 */
rid_operator_location_type_t rid_get_operator_location_type(const rid_system_t *system);

/**
 * @brief Set the classification type for a System message.
 *
 * @param system Pointer to the System message structure.
 * @param type The classification type to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if system is NULL.
 */
rid_error_t rid_set_classification_type(rid_system_t *system, rid_classification_type_t type);

/**
 * @brief Get the classification type from a System message.
 *
 * @param system Pointer to the System message structure.
 *
 * @return The classification type value.
 */
rid_classification_type_t rid_get_classification_type(const rid_system_t *system);

/**
 * @brief Set the UA classification category for a System message.
 *
 * @param system Pointer to the System message structure.
 * @param category The UA classification category to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if system is NULL.
 */
rid_error_t rid_set_ua_classification_category(rid_system_t *system, rid_ua_classification_category_t category);

/**
 * @brief Get the UA classification category from a System message.
 *
 * @param system Pointer to the System message structure.
 *
 * @return The UA classification category value.
 */
rid_ua_classification_category_t rid_get_ua_classification_category(const rid_system_t *system);

/**
 * @brief Set the UA classification class for a System message.
 *
 * @param system Pointer to the System message structure.
 * @param class The UA classification class to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if system is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if classification_class exceeds RID_UA_CLASSIFICATION_CLASS_MAX.
 */
rid_error_t rid_set_ua_classification_class(rid_system_t *system, rid_ua_classification_class_t class);

/**
 * @brief Get the UA classification class from a System message.
 *
 * @param system Pointer to the System message structure.
 *
 * @return The UA classification class value.
 */
rid_ua_classification_class_t rid_get_ua_classification_class(const rid_system_t *system);

/**
 * @brief Set the operator latitude for a System message.
 *
 * Encodes latitude in degrees per ASTM F3411-22a (value * 10^7).
 *
 * @param system Pointer to the System message structure.
 * @param degrees Latitude in degrees (-90.0 to +90.0). Use 0.0 for invalid/unknown.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if system is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if degrees is outside valid range.
 */
rid_error_t rid_set_operator_latitude(rid_system_t *system, double degrees);

/**
 * @brief Get the operator latitude from a System message.
 *
 * Decodes latitude from encoded int32_t value per ASTM F3411-22a.
 *
 * @param system Pointer to the System message structure.
 *
 * @return Latitude in degrees. 0.0 indicates invalid/unknown.
 */
double rid_get_operator_latitude(const rid_system_t *system);

/**
 * @brief Set the operator longitude for a System message.
 *
 * Encodes longitude in degrees per ASTM F3411-22a (value * 10^7).
 *
 * @param system Pointer to the System message structure.
 * @param degrees Longitude in degrees (-180.0 to +180.0). Use 0.0 for invalid/unknown.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if system is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if degrees is outside valid range.
 */
rid_error_t rid_set_operator_longitude(rid_system_t *system, double degrees);

/**
 * @brief Get the operator longitude from a System message.
 *
 * Decodes longitude from encoded int32_t value per ASTM F3411-22a.
 *
 * @param system Pointer to the System message structure.
 *
 * @return Longitude in degrees. 0.0 indicates invalid/unknown.
 */
double rid_get_operator_longitude(const rid_system_t *system);

/**
 * @brief Set the operator altitude for a System message.
 *
 * Encodes altitude in meters per ASTM F3411-22a ((value + 1000) / 0.5).
 *
 * @param system Pointer to the System message structure.
 * @param altitude Altitude in meters (-1000.0 to 31767.0). Use RID_OPERATOR_ALTITUDE_INVALID for invalid/unknown.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if system is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if altitude is outside valid range.
 */
rid_error_t rid_set_operator_altitude(rid_system_t *system, float altitude);

/**
 * @brief Get the operator altitude from a System message.
 *
 * Decodes altitude from encoded uint16_t value per ASTM F3411-22a.
 *
 * @param system Pointer to the System message structure.
 *
 * @return Altitude in meters. -1000.0 indicates invalid/unknown.
 */
float rid_get_operator_altitude(const rid_system_t *system);

/**
 * @brief Initialize a System message with default values.
 *
 * Sets protocol version to 2 and message type to SYSTEM.
 * All other fields are set to zero.
 *
 * @param system Pointer to the System message structure.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if system is NULL.
 */
rid_error_t rid_system_init(rid_system_t *system);

#endif
