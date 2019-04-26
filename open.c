#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>



void OPEN(struct INSTRUCTION* instr){
	if(instr->numTokens==3){
		if(isValidDirectory(instr->tokens[1])!=0){
			//printLS(isValidDirectory(instr->tokens[1]));
			if(strcmp(instr->tokens[2], "r")==0){
				printf("OPENING %s R\n", instr->tokens[1]);
			}
			else if(strcmp(instr->tokens[2], "w")==0){
				printf("OPENING %s W\n", instr->tokens[1]);
			}
			else if(strcmp(instr->tokens[2], "rw")==0){
				printf("OPENING %s RW\n", instr->tokens[1]);
			}
			else if(strcmp(instr->tokens[2], "wr")==0){
				printf("OPENING %s WR\n", instr->tokens[1]);
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



