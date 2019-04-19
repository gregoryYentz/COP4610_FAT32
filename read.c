#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void READ(struct INSTRUCTION* instr){
	if(instr->numTokens==4){
		printf(">read %s %s %s\n", instr->tokens[1], instr->tokens[2], instr->tokens[3]);
	}
	else{
		printf("read ERROR\n");
	}
}