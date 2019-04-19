#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void WRITE(struct INSTRUCTION* instr){
	if(instr->numTokens==5){
		//strips the quotes
		int size = (int)strlen(instr->tokens[4]);
		instr->tokens[4][size-1] = '\0';
		instr->tokens[4]=instr->tokens[4]+1;

		printf(">write %s %s %s %s\n", instr->tokens[1], instr->tokens[2], instr->tokens[3], instr->tokens[4]);
	}
	else{
		printf("write ERROR\n");
	}
}