#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "core.h"
#include "opcodes.h"

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

void jump(uint16_t instruction) {
   uint16_t br = (instruction >> 6) & 0x7;
   reg[R_PC] = reg[br];
}

void jumpToSubroutine(uint16_t instruction) {
    uint16_t flag = (instruction >> 11) & 1;

    reg[R_R7] = reg[R_PC];      // save return address

    if (flag) {
        uint16_t pc_offset = sign_extend(instruction & 0x7FF, 11);
        reg[R_PC] += pc_offset;
    } else {
        uint16_t br = (instruction >> 6) & 0x7;
        reg[R_PC] = reg[br];
    }
}

void load(uint16_t instruction) {
    uint16_t dr = (instruction >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instruction & 0x1FF, 9);

    reg[dr] = mem_read(reg[R_PC] + pc_offset);
    update_flags(dr);
}

void loadIndirect(uint16_t instruction) {
    uint16_t dr = (instruction >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instruction & 0x1FF, 9);
    
    reg[dr] = mem_read(mem_read(reg[R_PC] + pc_offset));
    update_flags(dr);
}

void loadRegister(uint16_t instruction) {
    uint16_t dr = (instruction >> 9) & 0x7;
    uint16_t br = (instruction >> 6) & 0x7;
    uint16_t br_offset = sign_extend(instruction & 0x3F, 6);

    reg[dr] = mem_read(reg[br] + br_offset);
    update_flags(dr);
}

void loadEffectiveAddress(uint16_t instruction) {
    uint16_t dr = (instruction >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instruction & 0x1FF, 9);

    reg[dr] = reg[R_PC] + pc_offset;
    update_flags(dr);
}

void store(uint16_t instruction) {
    uint16_t sr = (instruction >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instruction & 0x1FF, 9);

    mem_write(reg[R_PC] + pc_offset, reg[sr]);
}


void storeIndirect(uint16_t instruction) {
    uint16_t sr = (instruction >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instruction & 0x1FF, 9);
    
    mem_write(mem_read(reg[R_PC] + pc_offset), reg[sr]);
}

void storeRegister(uint16_t instruction) {
    uint16_t sr = (instruction >> 9) & 0x7;
    uint16_t br = (instruction >> 6) & 0x7;
    uint16_t br_offset = sign_extend(instruction & 0x3F, 6);

    mem_write(reg[br] + br_offset, reg[sr]);
}

void trapPuts() {
    uint16_t* c = memory + reg[R_R0];

    while (*c) {
        putc((char)*c, stdout);
        ++c;
    }

    fflush(stdout);
}

void trapGetC() {
    char c = getchar();

    reg[R_R0] = (uint16_t)c;
    update_flags(R_R0);
}

void trapOut() {
    putchar((char)reg[R_R0]);
    fflush(stdout);
}

void trapIn() {
    printf("Enter a character: ");
    char c = getchar();
    putchar(c);
    fflush(stdout);

    reg[R_R0] = (uint16_t)c;
    update_flags(R_R0);
}

void trapPutSP() {
    uint16_t* c = memory + reg[R_R0];

    while (*c) {
        char c1 = (*c) & 0xFF;
        putchar(c1);
        char c2 = (*c) >> 8;
        if (c2) putchar(c2);
        ++c;
    }
    fflush(stdout);
}

void trapHalt() {
    printf("HALT\n");
    exit(0);
}

void trap(uint16_t instruction) {
    reg[R_R7] = reg[R_PC];
    
    switch (instruction & 0xFF) {
        case TRAP_GETC:
            trapGetC();
            break;
        case TRAP_OUT:
            trapOut();
            break;
        case TRAP_PUTS:
            trapPuts();
            break;
        case TRAP_IN:
            trapIn();
            break;
        case TRAP_PUTSP:
            trapPutSP();
            break;
        case TRAP_HALT:
            trapHalt();
            break;
    }
}










