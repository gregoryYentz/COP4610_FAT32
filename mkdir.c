#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void MKDIR(struct INSTRUCTION* instr){
	if(instr->numTokens==2){
		printf(">mkdir %s\n", instr->tokens[1]);
	}
	else{
		printf("mkdir ERROR\n");
	}
}