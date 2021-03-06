typedef struct DirectoryEntry {
	char DIR_Name[12];
	unsigned char DIR_Attr;	
	unsigned int DIR_FstClusHI;
	unsigned int DIR_FstClusLO;
	unsigned int DIR_FileSize;
	unsigned int DIR_EntryByteAddress;
	unsigned char END_OF_ARRAY;
} DirEntry;

unsigned int isValidDirectory(char* dirName);
unsigned int isValidFile(char* dirName);
unsigned int isReadOnly(char* fileName);


DirEntry* GetDirectoryContents(unsigned int clusterNum){
	FILE* imgFILE = GetImageFile();		//parser.c
	static DirEntry returnEntrys[2048];
	unsigned int tempcurrentClusterNum = clusterNum;
	unsigned char data[32]; //data being read in 32 byte chunks from data region
	unsigned int INDEX = 0;

	do{
		unsigned int sector = go_to_clus(tempcurrentClusterNum);	//parser.c
		unsigned int nextByte = 0;
		do{
			fseek(imgFILE, sector+nextByte, SEEK_SET);
			fread(data, sizeof(char), 32, imgFILE);

			if (data[0] == 0x00 || (unsigned char)data[0] == 0xE5) {
				nextByte += 32;
				continue;
			}
			else{
				if (data[11] & 0x0F){
					nextByte+=32;
					continue;
				}
				else{
					int i;
					for(i=0; i<11; i++){
						if(data[i]!=' '){
							returnEntrys[INDEX].DIR_Name[i] = data[i];
						}
						else{
							returnEntrys[INDEX].DIR_Name[i] = '\0';
							break;
						}
					}
					returnEntrys[INDEX].DIR_Name[11] = '\0';
					returnEntrys[INDEX].DIR_Attr = data[11];
					returnEntrys[INDEX].DIR_EntryByteAddress = sector + nextByte ;
					//for DIR_FstClus
					unsigned char temp[4];
					
					//returnEntrys[0].DIR_FstClusHI = hex_to_int(temp, 2); //parser.c
					temp[0] = data[26];
					temp[1] = data[27];
					temp[2] = data[20];
					temp[3] = data[21];
					int w;
					returnEntrys[INDEX].DIR_FstClusLO = hex_to_int(temp, 4); //parser.c
					returnEntrys[INDEX].DIR_FileSize = hex_to_int(data+28, 4); //parser.c
					returnEntrys[INDEX].END_OF_ARRAY = 0;

					INDEX++;
					nextByte+=32;
				}
			}
		}while(data[0] != 0x00 && nextByte < region.BPB_BytsPerSec*region.BPB_SecPerClus);
		tempcurrentClusterNum = get_next_clus(tempcurrentClusterNum); //parser.c
		//printf("next_cluster_index: %u\n", tempcurrentClusterNum);
	}while(tempcurrentClusterNum<0x0FFFFFF8);
	returnEntrys[INDEX].END_OF_ARRAY = 1;
	return returnEntrys;
}

unsigned int isValidDirectory(char* dirName){
	unsigned int isValid = 0;
	DirEntry* temp = GetDirectoryContents(CURRENTCLUSTERNUM); //directory_entry.c
	int i=0;
	while (!temp[i].END_OF_ARRAY) {
		char tempBuff[12];
		memset(tempBuff, '\0', 12);
		strcpy(tempBuff, temp[i].DIR_Name);
		if(strcmp(tempBuff, dirName)==0){
			if(temp[i].DIR_Attr==16){			//check if attr is of a directory entry
				isValid = temp[i].DIR_FstClusLO;
			}
		}
		i++;
	}
	return isValid;
}

unsigned int isValidFile(char* fileName){
	unsigned int isValid = 0;
	DirEntry* temp = GetDirectoryContents(CURRENTCLUSTERNUM); //directory_entry.c
	int i=0;
	while (!temp[i].END_OF_ARRAY) {
		char tempBuff[12];
		memset(tempBuff, '\0', 12);
		strcpy(tempBuff, temp[i].DIR_Name);
		if(strcmp(tempBuff, fileName)==0){
			if(temp[i].DIR_Attr==32||temp[i].DIR_Attr==1){			//check if attr is of a file entry
				isValid = temp[i].DIR_FstClusLO;
				if(isValid==0){		//returns 1 for files that exist but that are empty
					isValid=1;
				}

			}
		}
		i++;
	}
	return isValid;
}

unsigned int isReadOnly(char* fileName){
	unsigned int isRead = 0;
	DirEntry* temp = GetDirectoryContents(CURRENTCLUSTERNUM); //directory_entry.c
	int i=0;
	while (!temp[i].END_OF_ARRAY) {
		char tempBuff[12];
		memset(tempBuff, '\0', 12);
		strcpy(tempBuff, temp[i].DIR_Name);
		if(strcmp(tempBuff, fileName)==0){
			if(temp[i].DIR_Attr==1){			//check if attr is of a file entry
				isRead = 1;
			}
		}
		i++;
	}
	return isRead;
}

