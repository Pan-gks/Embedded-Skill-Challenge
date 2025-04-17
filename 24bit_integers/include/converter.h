/*
 * File: CONVERTER.h
 * 
 */

#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Converts X-byte native data to Y-byte format.
 * @param native_data Input data (as void*; supports 1/2/4/8-byte integers).
 * @param native_data_size Size of native_data (1, 2, 4, or 8).
 * @param database_data Output buffer.
 * @param database_data_size Size of output in bytes.
 * @param signedness Treat input as signed (true) or unsigned (false).
 * @return True on success, false if input size is invalid.
 */
bool conversion_XtoY_byte(void *native_data,size_t native_data_size,uint8_t database_data[8],uint8_t database_data_size,bool signedness);

#ifdef __cplusplus
}
#endif

#endif // CONVERTER_H