#ifndef _UTILS
#define _UTILS

#include <stdint.h>
#include <stdio.h>
#include <sys/termios.h>

uint16_t sign_extend(uint16_t x, int bit_count);
uint16_t swap16(uint16_t x);

void disable_input_buffering();
void restore_input_buffering();
uint16_t check_key();
void handle_interrupt(int signal);

#endif
