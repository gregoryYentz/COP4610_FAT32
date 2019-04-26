#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void printLS(unsigned int clusterNUM){
	DirEntry* temp = GetDirectoryContents(clusterNUM); //directory_entry.c
	unsigned int i = 0;
	while (!temp[i].END_OF_ARRAY) {
		char tempBuff[12];
		memset(tempBuff, '\0', 12);
		strcpy(tempBuff, temp[i].DIR_Name);
		printf("1: %x\n2: %x\n", temp[i].DIR_Name[0], temp[i].DIR_Name[1]);
		//ToStandardFormat(tempBuff);
		printf("%s\n", tempBuff);
		printf("ATTR: %d\n", temp[i].DIR_Attr);
		i++;
	}
}

void LS(struct INSTRUCTION* instr){
	if(instr->numTokens==2){
		if(strcmp(instr->tokens[1], ".")==0){
			printLS(CURRENTCLUSTERNUM);
			//printLS(region.BPB_RootClus);
		}
		else if(strcmp(instr->tokens[1], "..")==0){
			//printLS(getPreviousCluster(CURRENTCLUSTERNUM);
		}
		else{
			if(isValidDirectory(instr->tokens[1])!=0){
				printLS(isValidDirectory(instr->tokens[1]));
			}
			else{
				printf("NOT A VALID DIRECTORY\n");
			}
		}
	}
	else if(instr->numTokens==1){
		printLS(CURRENTCLUSTERNUM);
	}
	else{
		printf("INCORRECT ATTRIBUTES\n");
	}
}
