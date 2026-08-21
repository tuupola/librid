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

#ifndef RID_DISABLE_JSON

#include <stdio.h>

#include "json.h"

static void rid_json_putc(rid_json_t *json, char c) {
    if (json->buffer != NULL && json->buffer_size > 0) {
        if (json->position + 1 < json->buffer_size) {
            json->buffer[json->position] = c;
            json->buffer[json->position + 1] = '\0';
        } else {
            json->buffer[json->buffer_size - 1] = '\0';
        }
    }
    ++json->position;
}

static void rid_json_puts(rid_json_t *json, const char *s, size_t length) {
    size_t i;

    for (i = 0; i < length; ++i) {
        rid_json_putc(json, s[i]);
    }
}

static void rid_json_escape(rid_json_t *json, const char *s) {
    static const char hex[] = "0123456789abcdef";
    const unsigned char *p;

    for (p = (const unsigned char *)s; *p != '\0'; ++p) {
        if (*p == '"' || *p == '\\') {
            rid_json_putc(json, '\\');
            rid_json_putc(json, (char)*p);
        } else if (*p < 0x20) {
            rid_json_putc(json, '\\');
            rid_json_putc(json, 'u');
            rid_json_putc(json, '0');
            rid_json_putc(json, '0');
            rid_json_putc(json, hex[*p >> 4]);
            rid_json_putc(json, hex[*p & 0x0FU]);
        } else {
            rid_json_putc(json, (char)*p);
        }
    }
}

void rid_json_start(rid_json_t *json, char *buffer, size_t buffer_size) {
    json->buffer = buffer;
    json->buffer_size = buffer_size;
    json->position = 0;
    json->need_comma = 0;
    if (buffer != NULL && buffer_size > 0) {
        buffer[0] = '\0';
    }
    rid_json_putc(json, '{');
}

int rid_json_end(rid_json_t *json) {
    rid_json_putc(json, '}');
    return (int)json->position;
}

void rid_json_array_start(rid_json_t *json) {
    if (json->need_comma) {
        rid_json_putc(json, ',');
    }
    rid_json_putc(json, '[');
    json->need_comma = 0;
}

void rid_json_array_end(rid_json_t *json) {
    rid_json_putc(json, ']');
    json->need_comma = 1;
}

void rid_json_key(rid_json_t *json, const char *key) {
    if (json->need_comma) {
        rid_json_putc(json, ',');
    }
    rid_json_putc(json, '"');
    rid_json_escape(json, key);
    rid_json_putc(json, '"');
    rid_json_putc(json, ':');
    json->need_comma = 0;
}

void rid_json_uint(rid_json_t *json, unsigned value) {
    char token[16];
    int length;

    length = snprintf(token, sizeof(token), "%u", value);
    if (length > 0) {
        rid_json_puts(json, token, (size_t)length);
    }
    json->need_comma = 1;
}

void rid_json_string(rid_json_t *json, const char *string) {
    rid_json_putc(json, '"');
    rid_json_escape(json, string);
    rid_json_putc(json, '"');
    json->need_comma = 1;
}

void rid_json_null(rid_json_t *json) {
    rid_json_puts(json, "null", 4);
    json->need_comma = 1;
}

void rid_json_raw(rid_json_t *json, const char *token, size_t length) {
    rid_json_puts(json, token, length);
    json->need_comma = 1;
}

#endif /* RID_DISABLE_JSON */
