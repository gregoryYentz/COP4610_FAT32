#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void SIZE(struct INSTRUCTION* instr){
	if(instr->numTokens==2){
		if(isValidFile(instr->tokens[1])!=0){
			DirEntry* temp = GetDirectoryContents(CURRENTCLUSTERNUM); //must be changed from rootcluster to currentClusterNum
			int i=0;
			while(!temp[i].END_OF_ARRAY){
				if(strcmp(temp[i].DIR_Name, instr->tokens[1])==0){
					printf("%u bytes\n", temp[i].DIR_FileSize);
					break;
				}
				i++;
			}
		}
		else{
			printf("FILE DOESN'T EXIST\n");
		}
	}
	else{
		printf("INCORRECT ATTRIBUTES\n");
	}
}

