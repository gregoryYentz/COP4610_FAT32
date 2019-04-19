#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void SIZE(struct INSTRUCTION* instr){
	if(instr->numTokens==2){
		printf(">size %s\n", instr->tokens[1]);
	}
	else{
		printf("size ERROR\n");
	}
}