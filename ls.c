#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void LS(struct INSTRUCTION* instr){
	if(instr->numTokens==2){
		printf(">ls %s\n", instr->tokens[1]);
	}
	else{
		printf("ls ERROR\n");
	}
}