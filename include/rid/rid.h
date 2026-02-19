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

#ifndef RID_H
#define RID_H

/**
 * @file rid.h
 * @brief Convenience header to include all the other headers.
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "rid/auth.h"
#include "rid/auth_page.h"
#include "rid/basic_id.h"
#include "rid/location.h"
#include "rid/message.h"
#include "rid/message_pack.h"
#include "rid/operator_id.h"
#include "rid/self_id.h"
#include "rid/system.h"
#include "rid/transport.h"
#include "rid/version.h"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RID_H */
