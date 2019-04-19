#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void RMDIR(struct INSTRUCTION* instr){
	if(instr->numTokens==2){
		printf(">rmdir %s\n", instr->tokens[1]);
	}
	else{
		printf("rmdir ERROR\n");
	}
}