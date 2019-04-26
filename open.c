#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void OPEN(struct INSTRUCTION* instr){
	if(instr->numTokens==3){
		if(isValidFile(instr->tokens[1])!=0){
			if((strcmp(instr->tokens[2], "r")==0)||(strcmp(instr->tokens[2], "w")==0)||(strcmp(instr->tokens[2], "rw")==0)||(strcmp(instr->tokens[2], "wr")==0)){
				if(isFileOpen(isValidFile(instr->tokens[1]))==0){
					if((strcmp(instr->tokens[2], "w")==0)||(strcmp(instr->tokens[2], "rw")==0)||(strcmp(instr->tokens[2], "wr")==0)){
						if(isReadOnly(instr->tokens[1])==0){
							addFileEntry(isValidFile(instr->tokens[1]), instr->tokens[2]);
						}
						else{
							printf("%s IS READ ONLY\n", instr->tokens[1]);
						}
					}
					else{
						addFileEntry(isValidFile(instr->tokens[1]), instr->tokens[2]);
					}
				}
				else{
					printf("%s ALREADY OPEN\n", instr->tokens[1]);
				}

			}
			else{
				printf("INVALID MODE\n");

			}
		}
		else{
			printf("NOT A VALID FILENAME\n");
		}
	}
	else{
		printf("INCORRECT ATTRIBUTES\n");
	}
}



