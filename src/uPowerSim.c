#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#include "uPowerSim.h"

int main(int argc, char *argv[])
{
	parse_command(argv);
	read_asm();
	pass_1_text();
	pass_1_data();
	sym_table_to_files();
	pass_2();
	return 0;
}

void parse_command(char *argv[])
{
	cmd->command = argv[1];
	cmd->path = argv[2];
	// More statements to be added
	// for options
	return;
}

void read_asm()
{
	asm_file = fopen(cmd->path, "r");
	if(asm_file == NULL)
	{
		perror("Unable to open file");
		exit(EXIT_FAILURE);
	}

	char buffer[100];
	int i = 0;

	while(fgets(buffer, 100, asm_file))
	{
		//f_lines[i] = (struct line *)malloc(sizeof(struct line));
		strcpy(f_lines[i]->asm_line, buffer);
		i++;
	}

	n_lines = i;
	return;
}

void pass_1_text()
{
	int flag = 0, i;
	for(i=0;i<n_lines;i++)
	{
		if(strcmp(f_lines[i]->asm_line, ".text") == 0)
		{
			flag = 1;
			f_lines[i]->type = 'D';
			continue;
		}

		if((f_lines[i]->asm_line[0] == '.') &&
	        (strcmp(f_lines[i]->asm_line, ".text") != 0))
		{
			flag = 0;
			f_lines[i]->type = 'D';
			continue;
		}

		// If the line is under .text and is not blank or newline
		if(flag == 1 && f_lines[i]->asm_line[0] != '\0' &&
	        f_lines[i]->asm_line[0] != '\n')
		{
			// Check for label
			if(f_lines[i]->asm_line[strlen(f_lines[i]->asm_line)-1]==':')
			{
				f_lines[i]->type = 'L';
				struct symbol_table_text *s_temp;
				s_temp = (struct symbol_table_text *)malloc(sizeof(struct symbol_table_text));
				
				// Create a string with the label name without ':'
				char lname[sizeof(f_lines[i]->asm_line)];
				strcpy(lname, f_lines[i]->asm_line);
				lname[strlen(lname)-1] = '\0';
				
				// Add data to the symbol table entry and connect it to the table
				s_temp->label = lname;
				s_temp->rel_add = n_instr;
				s_temp->next = sym_tab_text_head;
				sym_tab_text_head = s_temp;
				continue;
			}

			// Ignore Comments
			if(f_lines[i]->asm_line[0] == '#')
			{
				f_lines[i]->type = 'C';
				continue;
			}
			i_lines[n_instr]->asm_line = f_lines[i]->asm_line;
			// n_instr is the number of instructions actually written to the binary
			n_instr++;
		}
	}
}

/*
 * In the case of this assembler, the data is declared in the
 * following format:
 * .data
 * <label-name>:
 * <assembler-directive> <data>
 * 
 * For example,
 * .data
 * numbers:	text_sym  = fopen("text.sym", "r");

 * .word 1, 2, 3, 4, 5, 6
 */

void pass_1_data()
{
	int flag = 0, i;
	char *token;
	char *data_type, *data;
	for(i=0;i<n_lines;i++)
	{
		if(strcmp(f_lines[i]->asm_line, ".data") == 0)
		{
			flag = 1;
			f_lines[i]->type = 'D';
			continue;
		}

		if((f_lines[i]->asm_line[0] == '.') &&
	        (strcmp(f_lines[i]->asm_line, ".data") != 0))
		{
			flag = 0;
			f_lines[i]->type = 'D';
			continue;
		}

		// If the line is under .data and is not blank or newline
		if(flag == 1 && f_lines[i]->asm_line[0] != '\0' &&
	        f_lines[i]->asm_line[0] != '\n')
		{
			// Check for label
			if(f_lines[i]->asm_line[strlen(f_lines[i]->asm_line)-1] == ':')
			{
				f_lines[i]->type = 'L';
				struct symbol_table_data *s_temp;
				s_temp = (struct symbol_table_data *)malloc(sizeof(struct symbol_table_data));
				
				// Create a string with the label name without ':'
				char lname[sizeof(f_lines[i]->asm_line)];
				strcpy(lname, f_lines[i]->asm_line);
				lname[strlen(lname)-1] = '\0';

				// Move on to the next line
				i++;

				//Tokenization
				token = strtok(f_lines[i], " ");
				data_type = token;
				token = strtok(NULL, " ");
				data = token;
				
				// Add data to the symbol table entry and connect it to the table
				s_temp->label = lname;
				s_temp->type = data_type;
				s_temp->data = data;
				s_temp->next = sym_tab_data_head;
				sym_tab_data_head = s_temp;
				continue;
			}

			// Ignore Comments
			if(f_lines[i]->asm_line[0] == '#')
			{
				f_lines[i]->type = 'C';
				continue;
			}
		}
	}
}


void pass_2()
{
	int i;
	int32_t instr_hex;
	bin_file = fopen("upower.bin", "w");
	for (i = 0;i < n_instr;i++)
	{
		instr_hex = translate_instr(i_lines[i],i);
		fprintf(bin_file, "%x\n", instr_hex);
	}
}

/*
 * This function is called for every text instructon.
 * Every instruction is first parsed using strtok.
 * Then the specialized functions in instr_translator.c are
 * called depending on the instruction.
 */
int32_t translate_instr(char *instr, int cia);
{
	int i = 0, instr_c = 0;
	char* instr_hex;
	char *token;
	char instr_v[10][100];
	
	//Tokenization
	token = strtok(instr, ", ");
	while (token != NULL)
	{
		instr_v[i] = token;
		instr_c++;
		token = strtok(NULL, ", ");
	}

	//Add new 'if' condition for adding a new instruction 
	if (strcmp(instr_v[0], "add") == 0)
		instr_hex = add(instr_c, instr_v);
	if (strcmp(instr_v[0], "addi") == 0)
		instr_hex = addi(instr_c, instr_v);	
	if (strcmp(instr_v[0], "beq") == 0)
		instr_hex = beq(instr_c, instr_v, cia);
	return instr_hex;

	
}

int parse_line(char *line)
{
	int size = 64;
    char **args = malloc(size * sizeof(char*));
    char* token = strtok(line, " ,");
    int i=0;
    while(token != NULL)
    {
        args[i] = token;
        token = strtok(NULL, " ,");
        i++;
    }
    args[i]=NULL;
	int instruction_binary;
	instruction_binary = translate_instruction(args);
}

int translate_instruction(char *args[])
{
	check_instruction_type(args[0]);
}

char check_instruction_type(char *inst)
{
	if(inst[0] == '.')
		return 'D';
	else if(inst[0] == '#')
		return 'C';
	else if(inst[(sizeof(*inst)-1)]==':')
		return 'L';
	else
		return 'I';

}

void sym_table_to_files()
{
	struct symbol_table_text *s_temp_text;
	s_temp_text = sym_tab_text_head;
	text_sym  = fopen("text.sym", "w");
	while (s_temp != NULL)
	{
		fprintf(text_sym, "%s#%d", s_temp_text->label, s_temp_text->rel_add);
		s_temp_text = s_temp_text->next;
	}

	struct symbol_table_data *s_temp_data;
	s_temp_data = sym_tab_data_head;
	data_sym  = fopen("data.sym", "w");
	while (s_temp != NULL)
	{
		fprintf(data_sym, "%s#%s#%s", s_temp_data->label, s_temp_data->type, s_temp_data->data);
		s_temp_data = s_temp_data->next;
	}

	return;
}