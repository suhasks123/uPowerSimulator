#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

#include "uPowerSim.h"

int i;

char temp[33]; // stores the binary encoding of the instructions

//function to compute the 5 bit representations of register numbers
char* register_translator(char* t)  
{
    if(strcmp(t,"R1")==0)
        return "00001";
    else if(strcmp(t,"R2")==0)
        return "00010";
    else if(strcmp(t,"R3")==0)
        return "00011";
    else if(strcmp(t,"R4")==0)
        return "00100";
    else if(strcmp(t,"R5")==0)
        return "00101";
    else if(strcmp(t,"R6")==0)
        return "00110";
    else if(strcmp(t,"R7")==0)
        return "00111";
    else if(strcmp(t,"R8")==0)
        return "01000";
    else if(strcmp(t,"R9")==0)
        return "01001";
    else if(strcmp(t,"R10")==0)
        return "01010";
    else if(strcmp(t,"R11")==0)
        return "01011";
    else if(strcmp(t,"R12")==0)
        return "01100";
    else if(strcmp(t,"R13")==0)
        return "01101";            
    else if(strcmp(t,"R14")==0)
        return "01110";
    else if(strcmp(t,"R15")==0)
        return "01111";
    else if(strcmp(t,"R16")==0)
        return "10000";
    else if(strcmp(t,"R17")==0)
        return "10001";
    else if(strcmp(t,"R18")==0)
        return "10010";
    else if(strcmp(t,"R19")==0)
        return "10011";
    else if(strcmp(t,"R20")==0)
        return "10100";
    else if(strcmp(t,"R21")==0)
        return "10101";
    else if(strcmp(t,"R22")==0)
        return "10110";
    else if(strcmp(t,"R23")==0)
        return "10111";
    else if(strcmp(t,"R24")==0)
        return "11000";
    else if(strcmp(t,"R25")==0)
        return "11001";
    else if(strcmp(t,"R26")==0)
        return "11010";
    else if(strcmp(t,"R27")==0)
        return "11011";
    else if(strcmp(t,"R28")==0)
        return "11100";
    else if(strcmp(t,"R29")==0)
        return "11101";
    else if(strcmp(t,"R30")==0)
        return "11110";
    else if(strcmp(t,"R31")==0)
        return "11111";
}

/*utility function for binary encoding
  of the registers in the instruction */
void src_trgts_reg_translate_for_x_format(char* instr_v[])  
{
    char* temp1=register_translator(instr_v[1]);
    for(i=6;i<=10;i++)
        temp[i]=temp1[i-6];
    temp1=register_translator(instr_v[2]);
    for(i=11;i<=15;i++)
        temp[i]=temp1[i-11];
    
    if(strcmp(instr_v[0],"extsw")!=0)
    {
        temp1=register_translator(instr_v[3]);
        for(i=16;i<=20;i++)
            temp[i]=temp1[i-16];
    }

    else
    {
        for(i=16;i<=20;i++)
            temp[i]='0';
    }   
}

// and instruction
// X format
int32_t and(int instr_c, char *instr_v[])  
{
    int32_t instr_hex;

    // PO  011111
    temp[0]='0';
    for(i=1;i<=5;i++)
    {
        temp[i]='1';
    }

    // XO  0000011100
    for(i=21;i<=25;i++)
    {
        temp[i]='0';
    }
    for(i=26;i<=28;i++)
    {
        temp[i]='1';
    }
    temp[29]='0';
    temp[30]='0';

    // Rc
    temp[31]='0';

    // RS RA RB
    src_trgts_reg_translate_for_x_format(instr_v);

    temp[32]='\0';    
    //sscanf(temp,"%d",&instr_hex);
    return instr_hex;
}

// nand instruction
// X format
int32_t nand(int instr_c, char *instr_v[])
{
    int32_t instr_hex;
    
    // PO 011111
   temp[0]='0';
   for(i=1;i<=5;i++)
   {
       temp[i]='1';
   }

    // XO   0111011100
    temp[21]='0';
    for(i=22;i<=24;i++)
    {
        temp[i]='1';
    }
    temp[25]='0';
    for(i=26;i<=28;i++)
    {
        temp[i]='1';
    }
    temp[29]='0';
    temp[30]='0';

    // Rc
    temp[31]='0';

    // RS RA RB
    src_trgts_reg_translate_for_x_format(instr_v);

    temp[32]='\0';    
    //sscanf(temp,"%d",&instr_hex);
    return instr_hex;
}

// or instruction
// X format
int32_t or(int instr_c, char *instr_v[])
{
    int32_t instr_hex;
    
    // PO 011111
    temp[0]='0';
    for(i=1;i<=5;i++)
    {
        temp[i]='1';
    }

    // XO 0110111100
    temp[21]='0';
    temp[22]='1';
    temp[23]='1';
    temp[24]='0';
    for(i=25;i<=28;i++)
    {
        temp[i]='1';
    }
    temp[29]='0';
    temp[30]='0';

    // Rc
    temp[31]='0';

    // RS RA RB
     src_trgts_reg_translate_for_x_format(instr_v);

    temp[32]='\0'; 
    //sscanf(temp,"%d",&instr_hex);
    return instr_hex;
}

// xor instruction
// X format
int32_t xor(int instr_c, char *instr_v[])
{
    int32_t instr_hex;
    
    // PO 011111
    temp[0]='0';
    for(i=1;i<=5;i++)
    {
        temp[i]='1';
    }

    // XO 0100111100
    temp[21]='0';
    temp[22]='1';
    temp[23]='0';
    temp[24]='0';
    for(i=25;i<=28;i++)
    {
        temp[i]='1';
    }
    temp[29]='0';
    temp[30]='0';

    // Rc
    temp[31]='0';

    // RS RA RB
    src_trgts_reg_translate_for_x_format(instr_v);

    temp[32]='\0'; 
    //sscanf(temp,"%d",&instr_hex);
    return instr_hex;
}

// extsw instruction
// X format
int32_t extsw(int instr_c, char *instr_v[])
{
    int32_t instr_hex;
    
    // PO 011111
    temp[0]='0';
    for(i=1;i<=5;i++)
    {
        temp[i]='1';
    }

    // XO 1111011010
    for(i=21;i<=24;i++)
    {
        temp[i]='1';
    }
    temp[25]='0';
    temp[26]='1';
    temp[27]='1';
    temp[28]='0';
    temp[29]='1';
    temp[30]='0';

    // Rc
    temp[31]='0';

    // RS RA RB
    src_trgts_reg_translate_for_x_format(instr_v);

    temp[32]='\0'; 
    //sscanf(temp,"%d",&instr_hex);
    return instr_hex;
}

// sld instruction
// X format
int32_t sld(int instr_c, char *instr_v[])
{
    int32_t instr_hex;
    
    // PO 011111
    temp[0]='0';
    for(i=1;i<=5;i++)
    {
        temp[i]='1';
    }

    // XO 0000011011
    for(i=21;i<=25;i++)
    {
        temp[i]='0';
    }
    temp[26]='1';
    temp[27]='1';
    temp[28]='0';
    temp[29]='1';
    temp[30]='1';

    // Rc
    temp[31]='0';

    // RS RA RB
    src_trgts_reg_translate_for_x_format(instr_v);

    temp[32]='\0'; 
    //sscanf(temp,"%d",&instr_hex);
    return instr_hex;
}

// srd instruction
// X format
int32_t srd(int instr_c, char *instr_v[])
{
    int32_t instr_hex;
    
    // PO 011111
    temp[0]='0';
    for(i=1;i<=5;i++)
    {
        temp[i]='1';
    }

    // XO 1000011011
    temp[21]='1';
    for(i=22;i<=25;i++)
    {
        temp[i]='0';
    }
    temp[26]='1';
    temp[27]='1';
    temp[28]='0';
    temp[29]='1';
    temp[30]='1';

    // Rc
    temp[31]='0';

    // RS RA RB
    src_trgts_reg_translate_for_x_format(instr_v);

    temp[32]='\0'; 
    //sscanf(temp,"%d",&instr_hex);
    return instr_hex;
}

// srad instruction
// X format
int32_t srad(int instr_c, char *instr_v[])
{
    int32_t instr_hex;
    
    // PO 011111
    temp[0]='0';
    for(i=1;i<=5;i++)
    {
        temp[i]='1';
    }

    // XO 1100011010
    temp[21]='1';
    temp[22]='1';
    for(i=23;i<=25;i++)
    {
        temp[i]='0';
    }
    temp[26]='1';
    temp[27]='1';
    temp[28]='0';
    temp[29]='1';
    temp[30]='0';

    // Rc
    temp[31]='0';

    // RS RA RB
    src_trgts_reg_translate_for_x_format(instr_v);

    temp[32]='\0'; 
    //sscanf(temp,"%d",&instr_hex);
    return instr_hex;
}
