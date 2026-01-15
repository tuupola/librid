/*

MIT License

Copyright (c) 2026 Mika Tuupola

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

/**
 * @file transport.h
 * @brief Remote ID transport method definitions
 */

#ifndef RID_TRANSPORT_H
#define RID_TRANSPORT_H

#ifdef __cplusplus
extern "C" {
#endif

/** @name Transport Payload Sizes
 *
 *  Maximum payload sizes in bytes for each transport method.
 *  @{
 */
#define RID_TRANSPORT_BLUETOOTH_LEGACY_MAX_PAYLOAD      25
#define RID_TRANSPORT_BLUETOOTH_LONG_RANGE_MAX_PAYLOAD  255
#define RID_TRANSPORT_WIFI_NAN_MAX_PAYLOAD              255
#define RID_TRANSPORT_WIFI_BEACON_MAX_PAYLOAD           250
/** @} */

/** @brief Time Unit in microseconds per ASTM F3411-22a. */
#define RID_TRANSPORT_TIME_UNIT_US  1024

/** @name Transport OUI Values
 *
 *  Organizationally Unique Identifiers for each transport.
 *  @{
 */
#define RID_TRANSPORT_BLUETOOTH_OUI         0xFFFA
#define RID_TRANSPORT_WIFI_NAN_OUI          0x506F9A
#define RID_TRANSPORT_WIFI_BEACON_OUI       0xFA0BBC
/** @} */

/** @name Bluetooth Constants
 *  @{
 */
#define RID_TRANSPORT_BLUETOOTH_APP_CODE    0x0D
/** @} */

/** @name Wi-Fi NAN Constants
 *  @{
 */
#define RID_TRANSPORT_WIFI_NAN_CLUSTER_ID   0x506F9A0100FFULL
#define RID_TRANSPORT_WIFI_NAN_CHANNEL_2G   6
#define RID_TRANSPORT_WIFI_NAN_CHANNEL_5G   149
/** @} */

/** @name Wi-Fi Beacon Constants
 *  @{
 */
#define RID_TRANSPORT_WIFI_BEACON_VENDOR_TYPE   0x0D
/** @} */

/**
 * @brief Transport methods for broadcasting Remote ID messages
 *
 * Defined in ASTM F3411-22a Section 5.4
 */
typedef enum rid_transport {
    RID_TRANSPORT_BLUETOOTH_LEGACY = 0,
    RID_TRANSPORT_BLUETOOTH_LONG_RANGE = 1,
    RID_TRANSPORT_WIFI_NAN = 2,
    RID_TRANSPORT_WIFI_BEACON = 3,
    RID_TRANSPORT_MAX = 3,
} rid_transport_t;

/**
 * @brief Convert transport type to string representation.
 *
 * @param transport The transport type to convert.
 *
 * @return String representation of the transport type.
 *         Returns "UNKNOWN" for invalid values.
 */
const char *rid_transport_to_string(rid_transport_t transport);

#ifdef __cplusplus
}
#endif

#endif /* RID_TRANSPORT_H */
