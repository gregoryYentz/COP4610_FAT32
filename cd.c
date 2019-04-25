#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void CD(struct INSTRUCTION* instr){
	if(instr->numTokens==2){
		printf(">cd %s\n", instr->tokens[1]);
	}
	else{
		printf("cd ERROR\n");
	}
}


DirEntry* temp = GetDirectory(current)

found = 0;
for(numDirEntries){
	if((strcmp(userINPUT, temp[i].DIR_Name)==0)&&(temp[i].DIR_Attr = DIR)){
		currentClusterNum = temp[i].DIR_StrClusNum;
		found = 1;
		break;
	}
}
if(found=0){
	//error
}