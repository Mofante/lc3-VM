#include <stdio.h>
#include <stdint.h>

#define MEMORY_MAX (1 << 16)

uint16_t memory[MEMORY_MAX];

enum {
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC,
    R_COND,
    R_COUNT
};

uint16_t reg[R_COUNT];

// condition flags
enum {
    FL_POS = 1 << 0,
    FL_ZRO = 1 << 1,
    FL_NEG = 1 << 2,
};

void update_flags(uint16_t r);


void read_image_file(FILE* file);
int read_image(const char* image_path);
