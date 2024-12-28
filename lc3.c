#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "core.h"
#include "instruction_set.h"

int main(int argc, const char* argv[]) {
    
    // load args

    if (argc < 2) {
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }

    for (int i = 1; i < argc; i++) {
        if (!read_image(argv[i])) {
            printf("Failed to load image: %s\n", argv[i]);
            exit(1);
        }
    }

    // exactly one cond flag should be set at any given time
    reg[R_COND] = FL_ZRO;
    

    // default PC starting position is 0x3000
    enum { PC_START = 0x3000 };
    reg[R_PC] = PC_START;

    int running = 1;
    while (running) {
        // fetch instruction
        uint16_t instr = mem_read(reg[R_PC]++);
        uint16_t op = instr >> 12;

        switch (op) {
            case OP_ADD:
                add(instr);
                break;
            case OP_AND:
                add(instr);
                break;
            case OP_NOT:
                not(instr);
                break;
            case OP_BR:
                branch(instr);
                break;
            case OP_JMP:
                break;
            case OP_JSR:
                break;
            case OP_LD:
                break;
            case OP_LDI:
                loadIndirect(instr);
                break;
            case OP_LDR:
                break;
            case OP_LEA:
                break;
            case OP_ST:
                break;
            case OP_STI:
                break;
            case OP_STR:
                break;
            case OP_TRAP:
                break;
            case OP_RES:
                break;
            case OP_RTI:
                break;
            default:
                break;
        }
    }































    

}
