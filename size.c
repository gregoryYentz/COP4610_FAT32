#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void SIZE(struct INSTRUCTION* instr){
	if(instr->numTokens==2){
		DirEntry* temp = GetDirectoryContents(region.BPB_RootClus); //must be changed from rootcluster to currentClusterNum
		int i = 0;
		int found = 0;
		int foundDirectory = 0;
		while (!temp[i].END_OF_ARRAY){
			//if((strcmp(instr->tokens[1], temp[i].DIR_Name)==0)&&(temp[i].DIR_Attr == FILE)){		//do we return the size of directories?
			if(strcmp(instr->tokens[1], temp[i].DIR_Name)==0){
				printf("%u bytes\n", temp[i].DIR_FileSize);
				found = 1;
				break;
			}
		/*	if((strcmp(instr->tokens[1], temp[i].DIR_Name)==0)&&(temp[i].DIR_Attr != FILE)){
				foundDirectory = 1;
			}*/
			i++;
		}
		if(found==0){
			// if(foundDirectory==1){
			// 	printf("NOT A FILE\n");
			// }
			// else{
				printf("FILE DOESN'T EXIST\n");
			// }
		}
	}
	else{
		printf("INCORRECT ATTRIBUTES\n");
	}
}

