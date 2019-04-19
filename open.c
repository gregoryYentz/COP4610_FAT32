#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void OPEN(struct INSTRUCTION* instr){
	if(instr->numTokens==3){
		printf(">open %s %s\n", instr->tokens[1], instr->tokens[2]);
	}
	else{
		printf("open ERROR\n");
	}
}