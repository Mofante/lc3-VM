#include <stdint.h>
#include "utils.h"

uint16_t sign_extend(uint16_t x, int bit_count) {
    if ((x >> (bit_count - 1)) & 1) {  // if number is negative
        x |= (0xFFFF << bit_count);    // fill most significant bits with 1s 
    }

    return x;
}

