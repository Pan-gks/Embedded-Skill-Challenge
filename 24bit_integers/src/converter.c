/*
 * File: converter.c
 * Description: Implementation of Y-byte integer conversion with clamping given any size ,for X input data in native format(1,2,4,8). 
 *
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "converter.h"

bool conversion_XtoY_byte(void *native_data,size_t native_data_size,uint8_t database_data[8],uint8_t database_data_size,bool signedness){
    if (database_data_size == 0 || database_data_size > 8){
        return false;
    }

    uint64_t tmp_val; // temporary variable to store native data 

    if(signedness == true){
        switch (native_data_size)
        {
        case 1:
            tmp_val = (int8_t)*(uint8_t *)native_data; // type cast void * native data to 1 byte value and then to signed 1 byte integer and 
            break;                                     // coping to the temporary variable
        case 2:
            tmp_val = (int16_t)*(uint16_t *)native_data;
            break;
        case 4:
            tmp_val = (int32_t)*(uint32_t *)native_data;
            break;
        case 8:
            tmp_val = (int64_t)*(uint64_t *)native_data;
            break;
        default:
            return false;
            break;
        }
    }
    else{
        switch (native_data_size)
        {
        case 1:
            tmp_val = *(uint8_t *)native_data;
            break;
        case 2:
            tmp_val = *(uint16_t *)native_data;
            break;
        case 4:
            tmp_val = *(uint32_t *)native_data;
            break;
        case 8:
            tmp_val = *(uint64_t *)native_data;
            break;
        default:
            return false;
            break;
        }
    }

    // Clamp to fit output size
    if (signedness) {
        int64_t max = (1LL << (database_data_size * 8 - 1)) - 1;
        int64_t min = -(1LL << (database_data_size * 8 - 1));
        if (tmp_val > max) tmp_val = max;
        if (tmp_val < min) tmp_val = min;
    } else {
        uint64_t max = (1ULL << (database_data_size * 8)) - 1;
        if (tmp_val > max) tmp_val = max;
    }    

    for(int i=0; i<database_data_size; i++){
        database_data[database_data_size - i -1] = (tmp_val >> (i * 8)) & 0xFF; // Big-endian output to database
    }

    return true;

}