#ifndef LIBC_CONVERT_FROM_STR_H
#define LIBC_CONVERT_FROM_STR_H

#include "../stdint.h"
#include <stdbool.h>

int8_t str_to_int8(const char *str);
int16_t str_to_int16(const char *str);
int32_t str_to_int32(const char *str);
int64_t str_to_int64(const char *str);

uint8_t str_to_uint8(const char *str);
uint16_t str_to_uint16(const char *str);
uint32_t str_to_uint32(const char *str);
uint64_t str_to_uint64(const char *str);

bool str_to_bool(const char *str);

// Unimplemented for now.
float str_to_float(const char *str);
double str_to_double(const char *str);

#endif
