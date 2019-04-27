#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void WRITE(struct INSTRUCTION* instr){
	if(instr->numTokens==5){
		//strips the quotes
		int size = (int)strlen(instr->tokens[4]);
		instr->tokens[4][size-1] = '\0';
		instr->tokens[4]=instr->tokens[4]+1;

		printf(">write %s %s %s %s\n", instr->tokens[1], instr->tokens[2], instr->tokens[3], instr->tokens[4]);
		if(isValidFile(instr->tokens[1])!=0){
			if(isFileOpen(isValidFile(instr->tokens[1])) !=0){
				if(isFileOpen(isValidFile(instr->tokens[1]))!=1){
					if(atoi(instr->tokens[2]) + atoi(instr->tokens[3]) <= getFileSize(instr->tokens[1])){

						unsigned int offset = atoi(instr->tokens[2]) % (region.BPB_BytsPerSec*region.BPB_SecPerClus);
						unsigned int i_start = atoi(instr->tokens[2]) / (region.BPB_BytsPerSec*region.BPB_SecPerClus);
						int remaining = atoi(instr->tokens[3]);

						instr->tokens[4][remaining] = '\0';	//sets the string length to the size

						unsigned int bytespercluster = region.BPB_BytsPerSec*region.BPB_SecPerClus;
						

						int c[MAX_CLUS];                 // max possible clusters for entire image file
						int i = 1, j, n_cluster;
						int total = 0;

						c[0] = isValidFile(instr->tokens[1]);
						n_cluster = get_next_clus(isValidFile(instr->tokens[1]));
						while(n_cluster < 0x0FFFFFF8){
							c[i] = n_cluster;
							n_cluster = get_next_clus(n_cluster);
							i++;
						}

						//i = total number of clusters for file
						//i_start = i value of cluster to start at
						//offset = btye offset from first cluster fseeked to
						//remaining = number of bytes left to fgets

						int readSize = atoi(instr->tokens[3])+1;
						char* readSTRING = calloc(readSize, sizeof(char));

						for(j = i_start; j<i && remaining>0; j++){
							if(j==0){	//first cluster looked at
								fseek(GetImageFile(), go_to_clus(c[j])+offset, SEEK_SET);
								if(bytespercluster>readSize){
									char* temp = instr->tokens[4];
									temp[readSize] = '\0';
									fputs(temp, GetImageFile());
								}
								else{
									char* temp = instr->tokens[4];
									temp[bytespercluster - offset] = '\0';
									fputs(temp, GetImageFile());
								}

								instr->tokens[4]+=(int)bytespercluster - (int)offset;
								remaining -= (int)bytespercluster - (int)offset;
							}
							else{
								if(bytespercluster >= remaining){ //should be the last cluster being looked at
									char* temp = instr->tokens[4];
									temp[remaining] = '\0';
									fseek(GetImageFile(), go_to_clus(c[j]), SEEK_SET);
									fputs(temp, GetImageFile());
									instr->tokens[4]+=remaining;
									remaining -= remaining;
									//remaining should now equal 0, should trip the for() statement
								}
								else{	//all other middle clusters lookoed at
									char* temp = instr->tokens[4];
									temp[bytespercluster] = '\0';
									fseek(GetImageFile(), go_to_clus(c[j]), SEEK_SET);
									fputs(temp, GetImageFile());
									instr->tokens[4]+=(int)bytespercluster;
									remaining -= (int)bytespercluster;
								}
							}
						}

						printf("\n");
					}
					else{
						printf("OFFSET + SIZE > FILESIZE\n");
					}
				}
				else{
					printf("FILE WRITE NOT ALLOWED\n");
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
		printf("write ERROR\n");
	}
}