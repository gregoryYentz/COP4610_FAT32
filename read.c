#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

//read FILENAME OFFSET SIZE

void READ(struct INSTRUCTION* instr){
	if(instr->numTokens==4){
		if(isValidFile(instr->tokens[1])!=0){
			if(isFileOpen(isValidFile(instr->tokens[1])) !=0){
				if(isFileOpen(isValidFile(instr->tokens[1]))!=2){
					if(atoi(instr->tokens[2]) + atoi(instr->tokens[3]) <= getFileSize(instr->tokens[1])){
						int readSize = atoi(instr->tokens[3]);
						char* readSTRING = calloc(readSize, sizeof(char));
						fseek(GetImageFile(), go_to_clus(isValidFile(instr->tokens[1]))+atoi(instr->tokens[2]), SEEK_SET);
						fgets(readSTRING, readSize+1, GetImageFile());
						//printf("FSEEK\n");
						printf("%s\n", readSTRING);
					}
					else{
						printf("OFFSET + SIZE > FILESIZE\n");
					}
				}
				else{
					printf("FILE READ NOT ALLOWED\n");
				}
			}
			else{
				printf("FILE NOT OPEN\n");
			}
		}
		else{
			printf("FILE DOES NOT EXIST\n");
		}
	}
	else{
		printf("read ERROR\n");
	}
}