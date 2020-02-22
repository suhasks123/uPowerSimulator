#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#include "uPowerSim.h"

/*
 * Add new instruction translation functions for adding
 * new instructions
 */

char* add(int instr_c, char *instr_v[])
{
    int32_t instr_hex;
    char a;
    int rt,ra,rb,i,j,l,b=0,k=6;
    char instr[] = "0111110000000000000001000010100";                   //The binary with registernumbers filled as 0 initially
    int reg[5];                                                         //Temporary storage of register numbers in binary

    for(i=1;i<instr_c;i++){

        char* temp = instr_v[i];

        //To extract register number
        if(temp[2]=='\0')                   
            l = 1;
        else 
            l = 2;
        b=0;                                                            //Finding register number in decimal
        for(j=l;j>=1;j--){

            a = instr_v[i][j];
            int a1 = a-48;
            b = b + a1*pow(10,l-j);

        //    printf("%d ",l);
        }
        //printf("%d ",b);
        if(b>31)
        {
            printf("Invalid register number.\n");                       //Corner Case
            return '\0';
        }
        for(j=4;j>=0;j--)
        {
            reg[j] = b%2;
            b/=2;
        }
       /* for(j=0;j<5;j++)
        {
            printf("%d", reg[j]);
        }*/

        for(j=0;j<5;j++)                                                //Making the changes in the binary
        {
            if(reg[j]==0)
                instr[k+j] = '0';
            else
                instr[k+j] = '1';
        }
        k+=5;
      //  printf("%s ", instr);
    }    

    return instr;
}

char* addi(int instr_c, char *instr_v[])
{
    int32_t instr_hex;
    char a;
    int rt,ra,i,j,l,b=0,k=6;
    char instr[] = "00111000000000000000000000000000";                  //The binary with register numbers filled as 0 initially
    int reg[5];                                                         //Temporary storage of register numbers in binary
    int imm[16];                                                        //Temporary storage of immediate value

    for(i=1;i<instr_c-1;i++){

        char* temp = instr_v[i];

        //To extract register number
        if(temp[2]=='\0')                   
            l = 1;
        else 
            l = 2;
        b=0;                                                            //Finding register number in decimal
        for(j=l;j>=1;j--){

            a = instr_v[i][j];
            int a1 = a-48;
            b = b + a1*pow(10,l-j);

        //    printf("%d ",l);
        }
        //printf("%d ",b);
        if(b>31)
        {
            printf("Invalid register number.\n");                       //Corner Case
            return '\0';
        }
        for(j=4;j>=0;j--)
        {
            reg[j] = b%2;
            b/=2;
        }
       /* for(j=0;j<5;j++)
        {
            printf("%d", reg[j]);
        }*/

        for(j=0;j<5;j++)                                                //Making the changes in the binary
        {
            if(reg[j]==0)
                instr[k+j] = '0';
            else
                instr[k+j] = '1';
        }
        k+=5;
    }

    //printf("%s ", instr);

    l = strlen(instr_v[3]);   
    b=0;

    for(i=l-1;i>=0;i--){                                              //Extracting the immediate value integer form the string array
        a = instr_v[3][i];
        int a1 = a-48;
        b = b + a1*pow(10,l-1-i);
    }
    for(i=15;i>=0;i--){                                               //Converting immediate to a 16-bit binary
        imm[i] = b%2;
        b/=2;
    }

    k = 16;
    for(j=0;j<16;j++)                                                //Making the changes in the binary
    {
        if(imm[j]==0)
            instr[k+j] = '0';
        else
            instr[k+j] = '1';
    }
    //printf("%s", instr);    

    return instr;
}

char* beq(int instr_c, char *instr_v[], int curr_addr)
{
    int32_t instr_hex;
    char* temp;
    char* instr[] = "01001101100010100000000000000000";                     //Binary with BD part filled with 0's
    int addr,i,j,k=0;
    int bd[14];
    struct symbol_table_text* ptr = sym_tab_text_head;
    while (ptr->next!=NULL)
    {
        temp = ptr->label;
        if(strcmp(temp, instr_v[3])==0)                         //Finding address of label to jump to
        {
            addr = temp->rel_add;
            break;
        }
        else
        {
            ptr = ptr->next;
        }
    }    
    if(ptr->next==NULL)                                         //Checking the last instruction
    {
        temp = ptr->label;
        if(strcmp(temp, instr_v[3])==0){
            addr = temp->rel_add;
        }
        else
        {
            printf("Invalid label\n");
            return '\0';
        }
    }
    int b = curr_addr - addr;                                   //The branch displacement
    k = 16;
    if(b>=0)                                                    //Branch displacement as a 14-bit binary
    {
        for(i=14;i>=0;i--)
        {   
            bd[i] = b%2;
            b/=2;
        }
        for(i=0;i<14;i++)
        {
            if(bd[i] == 0)
                instr[k+i] = '0';
            else
                instr[k+i] = '1';
        }
    }
    else                                                        //If Branch Displacement<0, calculate binary using 1;s complement of -b-1;
    {
        b = b*(-1);
        b-=1;
        for(i=14;i>=0;i--)
        {   
            bd[i] = b%2;
            b/=2;
        }
        for(i=0;i<14;i++)
        {
            if(bd[i] == 0)
                instr[k+i] = '1';                               //THe complements
            else
                instr[k+i] = '0';
        }
    }

    return instr;
}