#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void printLS(unsigned int clusterNUM){
	DirEntry* temp = GetDirectoryContents(clusterNUM);
 unsigned int i = 0;
  while (!temp[i].END_OF_ARRAY) {
    char tempBuff[32];
    memset(tempBuff, '\0', 32);
    strcpy(tempBuff, temp[i++].DIR_Name);
    //ToStandardFormat(tempBuff);
    printf("%s\n", tempBuff);
  }	
}

void LS(struct INSTRUCTION* instr){
	if(instr->numTokens==2){
		printf(">ls %s\n", instr->tokens[1]);
	}
	else{
		//printf("ls ERROR\n");
		//for testing
		printLS(region.BPB_RootClus);

	}
}