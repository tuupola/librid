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

#ifndef RID_VERSION_H
#define RID_VERSION_H

/**
 * @file version.h
 * @brief Library version information.
 *
 * @see https://semver.org/
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define RID_VERSION_MAJOR 0
#define RID_VERSION_MINOR 2
#define RID_VERSION_PATCH 0
#define RID_VERSION_STRING "0.2.0-dev"

/**
 * @brief Get the library version as a string.
 *
 * @return Version string in "major.minor.patch" format.
 */
const char *rid_version_to_string(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RID_VERSION_H */
