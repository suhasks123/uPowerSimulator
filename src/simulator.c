#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#include "uPowerSim.h"
#include "simulator.h"

void read_bin()
{
    int i = 0;
    char buffer[100];
    while(fgets(buffer, 100, asm_file))
	{
	    sscanf(buffer, "%x", &instr[i]);
        i++;
	}
}