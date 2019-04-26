#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void CD(struct INSTRUCTION* instr){
	if(instr->numTokens==2){
		if(strcmp(instr->tokens[1], ".")==0){
			//do nothing
			printf("Already HERE\n");
		}
		else if(strcmp(instr->tokens[1], "..")==0){
			//go_to_cluster(previousCLuster(CURRENTCLUSTERNUM));
			if(CLUSTERNUMSTACKINDEX!=0){
				CURRENTCLUSTERNUM = CLUSTERNUMSTACK[CLUSTERNUMSTACKINDEX-1];
				CLUSTERNUMSTACKINDEX -= 1;
			}
		}
		else{
			if(isValidDirectory(instr->tokens[1])!=0){
				CURRENTCLUSTERNUM = isValidDirectory(instr->tokens[1]);
				
				CLUSTERNUMSTACK[CLUSTERNUMSTACKINDEX+1] = CURRENTCLUSTERNUM;
				CLUSTERNUMSTACKINDEX += 1;
			}
			else{
				printf("NOT A VALID DIRECTORY\n");
			}
		}
	}
	else if(instr->numTokens==1){
		//printLS(CURRENTCLUSTERNUM);
	}
	else{
		printf("INCORRECT ATTRIBUTES\n");
	}
}