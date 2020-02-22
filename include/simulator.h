#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

// Registers
int64_t R[32];
int64_t LR, CIA, NIA, SRR0;
int32_t CR;

// Binary instruction array
int32_t instr[100];

// Functions
void read_bin();