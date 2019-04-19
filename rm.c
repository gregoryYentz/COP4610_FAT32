#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void RM(struct INSTRUCTION* instr){
	if(instr->numTokens==2){
		printf(">rm %s\n", instr->tokens[1]);
	}
	else{
		printf("rm ERROR\n");
	}
}