#include "core.h"
#include "utils.h"
#include <stdint.h>
#include <stdio.h>

uint16_t memory[MEMORY_MAX];
uint16_t reg[R_COUNT];

void update_flags(uint16_t r) {
    if (reg[r] == 0) reg[R_COND] = FL_ZRO;
    else if (reg[r] >> 15) reg[R_COND] = FL_NEG;
    else reg[R_COND] = FL_POS;
}

void read_image_file(FILE *file) {
    uint16_t origin;
    fread(&origin, sizeof(origin), 1, file);
    origin = swap16(origin);

    uint16_t max_read = MEMORY_MAX - origin;
    uint16_t* p = memory + origin;
    size_t read = fread(p, sizeof(uint16_t), max_read, file);

    while (read-- > 0) {
        *p = swap16(*p);
        ++p;
    }
}

int read_image(const char *image_path) {
    FILE* file = fopen(image_path, "rb");
    if (!file) return 0;
    read_image_file(file);
    fclose(file);
    return 1;
}

void mem_write(uint16_t address, uint16_t value) {
    memory[address] = value;
}

uint16_t mem_read(uint16_t address) {
    if (address == MR_KBSR) {
        if (check_key()) {
            memory[MR_KBSR] = (1 << 15);
            memory[MR_KBDR] = getchar();
        } else memory[MR_KBSR] = 0;
    }
    return memory[address];
}
