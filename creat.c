#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void CREAT(struct INSTRUCTION* instr){
	if(instr->numTokens==2){
		printf(">creat %s\n", instr->tokens[1]);
	}
	else{
		printf("creat ERROR\n");
	}
}