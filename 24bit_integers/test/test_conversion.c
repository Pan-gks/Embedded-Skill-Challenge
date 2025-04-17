#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "converter.h"

void test_signed_3byte() {
    int32_t input_data = -1;
    uint8_t expected_data[] = { 0xFF, 0xFF, 0xFF };
    uint8_t converted_data[8] = {0};
    assert(conversion_XtoY_byte(&input_data, sizeof(input_data), converted_data, 3, true));
    assert(memcmp(converted_data, expected_data, 3) == 0);
}

void test_long_signed_5byte_max() {
    int64_t input_data = -1234567890LL;
    uint8_t expected_data[] = { 0xFF, 0xB6, 0x69, 0xFD, 0x2E }; 
    uint8_t converted_data[8] = {0};
    assert(conversion_XtoY_byte(&input_data, sizeof(input_data), converted_data, 5, true));
    assert(memcmp(converted_data, expected_data, 5) == 0);
}

void test_clamping_signed_overflow() {
    int32_t input_data = 9000000;
    uint8_t expected_data[] = { 0x7F, 0xFF, 0xFF };
    uint8_t converted_data[8] = {0};
    assert(conversion_XtoY_byte(&input_data, sizeof(input_data), converted_data, 3, true));
    assert(memcmp(converted_data, expected_data, 3) == 0);
}

void test_invalid_input_size() {
    uint8_t converted_data[8];
    int32_t input_data = 0;
    assert(!conversion_XtoY_byte(&input_data, 5, converted_data, 3, true));
}


int main(void) {

    test_signed_3byte();
    test_long_signed_5byte_max();
    test_clamping_signed_overflow();
    test_invalid_input_size();
    printf("All tests passed \n");

}