#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void CD(struct INSTRUCTION* instr){
	if(instr->numTokens==2){
		printf(">cd %s\n", instr->tokens[1]);
	}
	else{
		printf("cd ERROR\n");
	}
}