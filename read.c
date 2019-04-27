#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

//read FILENAME OFFSET SIZE


#define MAX_CLUS 65536

void READ(struct INSTRUCTION* instr){
	if(instr->numTokens==4){
		if(isValidFile(instr->tokens[1])!=0){
			if(isFileOpen(isValidFile(instr->tokens[1])) !=0){
				if(isFileOpen(isValidFile(instr->tokens[1]))!=2){
					if(atoi(instr->tokens[2]) + atoi(instr->tokens[3]) <= getFileSize(instr->tokens[1])){

						unsigned int offset = atoi(instr->tokens[2]) % (region.BPB_BytsPerSec*region.BPB_SecPerClus);
						unsigned int i_start = atoi(instr->tokens[2]) / (region.BPB_BytsPerSec*region.BPB_SecPerClus);
						int remaining = atoi(instr->tokens[3]);
						//printf("reamaining: %u\n", remaining);

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
							//printf("remainging: %d\n", remaining);
							if(j==0){	//first cluster looked at
								fseek(GetImageFile(), go_to_clus(c[j])+offset, SEEK_SET);
								if(bytespercluster>readSize){
									fgets(readSTRING, readSize, GetImageFile());
								}
								else{
									fgets(readSTRING, bytespercluster - offset, GetImageFile());
								}
								printf("%s", readSTRING);
								remaining -= (int)bytespercluster - (int)offset;
							}
							else{
								if(bytespercluster >= remaining){ //should be the last cluster being looked at
									fseek(GetImageFile(), go_to_clus(c[j]), SEEK_SET);
									fgets(readSTRING, remaining, GetImageFile());
									printf("%s", readSTRING);
									remaining -= remaining;
									//remaining should now equal 0, should trip the for() statement
								}
								else{	//all other middle clusters lookoed at
									fseek(GetImageFile(), go_to_clus(c[j]), SEEK_SET);
									fgets(readSTRING, bytespercluster, GetImageFile());
									printf("%s", readSTRING);
									remaining -= (int)bytespercluster;
								}
							}
						}




						/*for(j = i_start; j<i; j++){
							if(total==readSize){
								break;
							}
							if(j==i_start){
								fseek(GetImageFile(), go_to_clus(j)+offset, SEEK_SET);
								fgets(readSTRING, region.BPB_BytsPerSec*region.BPB_SecPerClus - offset, GetImageFile());
								printf("%s", readSTRING);
								total+=region.BPB_BytsPerSec*region.BPB_SecPerClus - offset;
								continue;
							}
							else if((readSize-total)<region.BPB_BytsPerSec*region.BPB_SecPerClus){
							    fseek(GetImageFile(), go_to_clus(c[j]), SEEK_SET);
							    fgets(readSTRING, region.BPB_BytsPerSec*region.BPB_SecPerClus - (readSize-total), GetImageFile());
								printf("%s", readSTRING);
								total += region.BPB_BytsPerSec*region.BPB_SecPerClus - (readSize-total);


							}
							else{
							    fseek(GetImageFile(), go_to_clus(c[j]), SEEK_SET);
							    fgets(readSTRING, region.BPB_BytsPerSec*region.BPB_SecPerClus, GetImageFile());
								printf("%s", readSTRING);
								total += region.BPB_BytsPerSec*region.BPB_SecPerClus;
							}
						}*/


						/*int readSize = atoi(instr->tokens[3]);
						char* readSTRING = calloc(readSize, sizeof(char));
						fseek(GetImageFile(), go_to_clus(isValidFile(instr->tokens[1]))+atoi(instr->tokens[2]), SEEK_SET);
						fgets(readSTRING, readSize+1, GetImageFile());
						//printf("FSEEK\n");
						printf("%s\n", readSTRING);*/
						printf("\n");
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