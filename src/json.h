/*
 *
 * MIT License
 *
 * Copyright (c) 2026 Mika Tuupola
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * -cut-
 *
 * This file is part of librid: https://github.com/tuupola/librid
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef RID_JSON_H
#define RID_JSON_H

#ifndef RID_DISABLE_JSON

#include <stddef.h>
#include <stdint.h>

typedef struct rid_json {
    char *buffer;
    size_t buffer_size;
    size_t position;
    uint8_t need_comma;
} rid_json_t;

void rid_json_start(rid_json_t *json, char *buffer, size_t buffer_size);
int rid_json_end(rid_json_t *json);
void rid_json_array_start(rid_json_t *json);
void rid_json_array_end(rid_json_t *json);
void rid_json_key(rid_json_t *json, const char *key);
void rid_json_uint(rid_json_t *json, unsigned value);
void rid_json_string(rid_json_t *json, const char *string);
void rid_json_null(rid_json_t *json);
void rid_json_raw(rid_json_t *json, const char *token, size_t length);

#endif /* RID_DISABLE_JSON */

#endif /* RID_JSON_H */
