#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void CLOSE(struct INSTRUCTION* instr){
	if(instr->numTokens==2){
		if(isValidFile(instr->tokens[1])!=0){
			if(isFileOpen(isValidFile(instr->tokens[1]))==1){
				removeFileEntry(isValidFile(instr->tokens[1]));
				printf("%s CLOSED\n", instr->tokens[1]);
			}
			else{
				printf("FILE NOT OPEN\n");
			}
		}
		else{
			printf("INVALID FILE\n");
		}
	}
	else{
		printf("INCORRECT ATTRIBUTES\n");
	}
}