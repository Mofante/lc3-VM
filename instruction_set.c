#include <stdint.h>

#include "utils.h"
#include "core.h"

void add(uint16_t instruction) {
    uint16_t dr = (instruction >> 9) & 0x7;   //make sure it is one of the GP registers
    uint16_t sr1 = (instruction >> 6) & 0x7;
    uint16_t imm_flag = (instruction >> 5) & 0x1;

    if (imm_flag) {
        uint16_t imm5 = sign_extend(instruction & 0x1F, 5);
        reg[dr] = reg[sr1] + imm5;
    } else {
        uint16_t sr2 = instruction & 0x7;
        reg[dr] = reg[sr1] + reg[sr2];
    }

    update_flags(dr);
}

void and(uint16_t instruction) {
    uint16_t dr = (instruction >> 9) & 0x7;
    uint16_t sr1 = (instruction >> 6) & 0x7;
    uint16_t imm_flag = (instruction >> 5) & 0x1;
    
    if (imm_flag) {
        uint16_t imm5 = sign_extend(instruction & 0x1F, 5);
        reg[dr] = reg[sr1] & imm5;
    } else {
        uint16_t sr2 = instruction & 0x7;
        reg[dr] = reg[sr1] & reg[sr2];
    }

    update_flags(dr);
}

void not(uint16_t instruction) {
    uint16_t dr = (instruction >> 9) & 0x7;
    uint16_t sr = (instruction >> 6) & 0x7;

    reg[dr] = ~sr;
    update_flags(dr);
}

void branch(uint16_t instruction) {
    uint16_t conds = (instruction >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instruction & 0x1FF, 9);

    if (conds & reg[R_COND]) reg[R_PC] += pc_offset;
}

void loadIndirect(uint16_t instruction) {
    uint16_t dr = (instruction >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instruction & 0x1FF, 9);
    
    reg[dr] = mem_read(mem_read(reg[R_PC] + pc_offset));
    update_flags(dr);
}

