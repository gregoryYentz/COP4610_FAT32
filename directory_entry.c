typedef struct DirectoryEntry {
	char DIR_Name[12];
	unsigned char DIR_Attr;	
	unsigned int DIR_FstClusHI;
	unsigned int DIR_FstClusLO;
	unsigned int DIR_FileSize;
	unsigned int DIR_EntryByteAddress;
	unsigned char END_OF_ARRAY;
} DirEntry;


DirEntry* GetDirectoryContents(unsigned int clusterNum){
	FILE* imgFILE = GetImageFile();		//parser.c
	static DirEntry returnEntrys[20];
	unsigned int currentClusterNum = clusterNum;
	unsigned char data[32]; //data being read in 32 byte chunks from data region
	unsigned int INDEX = 0;

	do{
		unsigned int sector = go_to_clus(currentClusterNum);	//parser.c
		unsigned int nextByte = 0;
		do{
			fseek(imgFILE, sector+nextByte, SEEK_SET);
			fread(data, sizeof(char), 32, imgFILE);
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
		}while(data[0] != 0x00 && nextByte < region.BPB_BytsPerSec*region.BPB_SecPerClus);
		currentClusterNum = get_next_clus(currentClusterNum); //parser.c
	}while(currentClusterNum<0x0FFFFFF8);
	returnEntrys[INDEX-1].END_OF_ARRAY = 1;
	return returnEntrys;
}