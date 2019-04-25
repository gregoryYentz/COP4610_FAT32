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


DirEntry* temp = GetDirectory(current)

found = 0;
for(numDirEntries){
	if((strcmp(userINPUT, temp[i].DIR_Name)==0)&&(temp[i].DIR_Attr = FILE)){
		print(temp[i].DIR_FileSize)
		found = 1;
		break;
	}
}
if(found==0){
	//error message
}