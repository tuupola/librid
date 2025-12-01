#ifndef _RID_BASIC_ID_H
#define _RID_BASIC_ID_H

#include <stdint.h>

/**
 * @brief Basic ID message structure per ASTM F3411-22a.
 */
typedef struct
__attribute__((__packed__)) rid_basic_id {
    uint8_t protocol_version: 4;
    uint8_t message_type : 4;
    uint8_t ua_type: 4;
    uint8_t id_type: 4;
    char uas_id[20];
    char reserved[3];
} rid_basic_id_t;

/**
 * @brief UAS ID type classification per ASTM F3411-22a.
 */
typedef enum rid_basic_id_type {
    RID_ID_TYPE_NONE,
    RID_ID_TYPE_SERIAL_NUMBER,
    RID_ID_TYPE_CAA_REGISTRATION_ID,
    RID_ID_TYPE_UTM_ASSIGNED_UUID,
    RID_ID_TYPE_SPECIFIC_SESSION_ID,
    RID_ID_TYPE_MAX = 15,
    /* 5-15: unused */
} rid_basic_id_type_t;

/**
 * @brief Unmanned aircraft type classification per ASTM F3411-22a.
 */
typedef enum rid_ua_type {
    RID_UA_TYPE_NONE,
    RID_UA_TYPE_AEROPLANE_OR_FIXED_WING,
    RID_UA_TYPE_HELICOPTER_OR_MULTIROTOR,
    RID_UA_TYPE_GYROPLANE,
    RID_UA_TYPE_HYBRID_LIFT,
    RID_UA_TYPE_ORNITHOPTER,
    RID_UA_TYPE_GLIDER,
    RID_UA_TYPE_KITE,
    RID_UA_TYPE_FREE_BALLOON,
    RID_UA_TYPE_CAPTIVE_BALLOON,
    RID_UA_TYPE_AIRSHIP,
    RID_UA_TYPE_FREE_FALL_PARACHUTE,
    RID_UA_TYPE_ROCKET,
    RID_UA_TYPE_TETHERED_POWERED_AIRCRAFT,
    RID_UA_TYPE_GROUND_OBSTACLE,
    RID_UA_TYPE_OTHER,
    RID_UA_TYPE_MAX = 15,
} rid_ua_type_t;

/**
 * @brief Initialize a Basic ID message structure.
 *
 * Sets protocol version to VERSION_2 and message type to
 * RID_MESSAGE_TYPE_BASIC_ID. All other fields are zeroed.
 *
 * @param message Pointer to the Basic ID message structure to initialize.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 */
rid_error_t rid_basic_id_init(rid_basic_id_t *message);

/**
 * @brief Set the ID type for a Basic ID message.
 *
 * @param message Pointer to the Basic ID message structure.
 * @param type The ID type to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if type exceeds RID_ID_TYPE_MAX.
 */
rid_error_t rid_set_basic_id_type(rid_basic_id_t *message, rid_basic_id_type_t type);

/**
 * @brief Get the ID type from a Basic ID message.
 *
 * @param message Pointer to the Basic ID message structure.
 *
 * @return The ID type value.
 */
rid_basic_id_type_t rid_get_basic_id_type(const rid_basic_id_t *message);

/**
 * @brief Set the UA (unmanned aircraft) type for a Basic ID message.
 *
 * @param message Pointer to the Basic ID message structure.
 * @param type The UA type to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message is NULL.
 * @retval RID_ERROR_OUT_OF_RANGE if type exceeds RID_UA_TYPE_MAX.
 */
rid_error_t rid_set_ua_type(rid_basic_id_t *message, rid_ua_type_t type);

/**
 * @brief Get the UA (unmanned aircraft) type from a Basic ID message.
 *
 * @param message Pointer to the Basic ID message structure.
 *
 * @return The UA type value.
 */
rid_ua_type_t rid_get_ua_type(const rid_basic_id_t *message);

/**
 * @brief Set the UAS ID for a Basic ID message.
 *
 * The UAS ID is a null-terminated string up to 20 characters.
 *
 * @param message Pointer to the Basic ID message structure.
 * @param uas_id The UAS ID string to set.
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message or uas_id is NULL.
 * @retval RID_ERROR_BUFFER_TOO_LARGE if uas_id exceeds 20 characters.
 */
rid_error_t rid_set_uas_id(rid_basic_id_t *message, const char *uas_id);

/**
 * @brief Get the UAS ID from a Basic ID message.
 *
 * Copies the UAS ID to the provided buffer as a null-terminated string.
 *
 * @param message Pointer to the Basic ID message structure.
 * @param buffer Buffer to store the UAS ID.
 * @param buffer_size Size of the buffer (must be at least 21 for full ID).
 *
 * @retval RID_SUCCESS on success.
 * @retval RID_ERROR_NULL_POINTER if message or buffer is NULL.
 * @retval RID_ERROR_BUFFER_TOO_SMALL if buffer_size is insufficient.
 */
rid_error_t rid_get_uas_id(const rid_basic_id_t *message, char *buffer, size_t buffer_size);

#endif