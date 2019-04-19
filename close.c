#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void CLOSE(struct INSTRUCTION* instr){
	if(instr->numTokens==2){
		printf(">close %s\n", instr->tokens[1]);
	}
	else{
		printf("close ERROR\n");
	}
}