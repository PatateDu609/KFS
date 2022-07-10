#ifndef LIBC_CONVERT_TO_STR_H
#define LIBC_CONVERT_TO_STR_H

#include "../stdint.h"
#include <stddef.h>
#include <stdbool.h>

// Todo: make this functions work without buffers (use malloc when it will be implemented)

char *int8_to_str(int8_t value, char *buffer, size_t size);
char *int16_to_str(int16_t value, char *buffer, size_t size);
char *int32_to_str(int32_t value, char *buffer, size_t size);
char *int64_to_str(int64_t value, char *buffer, size_t size);

char *uint8_to_str(uint8_t value, char *buffer, size_t size);
char *uint16_to_str(uint16_t value, char *buffer, size_t size);
char *uint32_to_str(uint32_t value, char *buffer, size_t size);
char *uint64_to_str(uint64_t value, char *buffer, size_t size);

char *bool_to_str(bool b); // No buffer, returns a static string.

// Unimplemented functions for now.
char *float_to_str(float value, char *buffer, size_t size);
char *double_to_str(double value, char *buffer, size_t size);

#endif
