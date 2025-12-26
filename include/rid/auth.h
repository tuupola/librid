#ifndef _RID_AUTH_H
#define _RID_AUTH_H

/**
 * @file auth.h
 * @brief Authentication message handling per ASTM F3411-22a.
 *
 * Authentication messages support multi-page transmission with up to 16 pages
 * (0-15). Page 0 has a different structure than pages 1-15.
 *
 * Example usage:
 * @snippet auth/auth.c full_example
 */

#include <stdint.h>
#include <stddef.h>

/** Timestamp epoch offset (2019-01-01 00:00:00 UTC as Unix timestamp) */
#define RID_AUTH_EPOCH_OFFSET 1546300800

/** Auth data size for page 0 */
#define RID_AUTH_PAGE0_DATA_SIZE 17

/** Auth data size for pages 1-15 */
#define RID_AUTH_PAGE_DATA_SIZE 23

/** Maximum number of authentication pages */
#define RID_AUTH_MAX_PAGES 16

/** Maximum page index (0-15) */
#define RID_AUTH_MAX_PAGE_INDEX 15

/**
 * @brief Authentication type classification per ASTM F3411-22a.
 */
typedef enum rid_auth_type {
    RID_AUTH_TYPE_NONE = 0,
    RID_AUTH_TYPE_UAS_ID_SIGNATURE = 1,
    RID_AUTH_TYPE_OPERATOR_ID_SIGNATURE = 2,
    RID_AUTH_TYPE_MESSAGE_SET_SIGNATURE = 3,
    RID_AUTH_TYPE_NETWORK_REMOTE_ID = 4,
    RID_AUTH_TYPE_SPECIFIC_METHOD = 5,
    /* 6-9: Reserved for ASTM spec */
    /* 0xA-0xF: Available for private use */
    RID_AUTH_TYPE_MAX = 0x0F,
} rid_auth_type_t;

/**
 * @brief Authentication message page 0 structure per ASTM F3411-22a.
 *
 * Page 0 contains header information including timestamp and total length.
 */
typedef struct
__attribute__((__packed__)) rid_auth {
    uint8_t protocol_version: 4;
    uint8_t message_type: 4;
    uint8_t page_number: 4;
    uint8_t auth_type: 4;
    uint8_t last_page_index;
    uint8_t length;
    uint32_t timestamp;
    uint8_t auth_data[17];
} rid_auth_t;

/**
 * @brief Authentication message pages 1-15 structure per ASTM F3411-22a.
 *
 * Pages 1-15 contain only auth type, page number, and authentication data.
 */
typedef struct
__attribute__((__packed__)) rid_auth_page {
    uint8_t protocol_version: 4;
    uint8_t message_type: 4;
    uint8_t page_number: 4;
    uint8_t auth_type: 4;
    uint8_t auth_data[23];
} rid_auth_page_t;

#endif
