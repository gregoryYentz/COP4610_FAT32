typedef struct DirectoryEntry {
	char DIR_Name[12];
	unsigned char DIR_Attr;	
	unsigned int DIR_FstClusHI;
	unsigned int DIR_FstCLusLO;
	unsigned int DIR_FileSize;
	unsigned int DIR_EntryByteAddress;
	unsigned char END_OF_ARRAY;
} DirEntry;


DirEntry* GetDirectoryContents(unsigned int clusterNum){
	FILE* imgFILE = GetImageFile();		//parser.c
	DirEntry returnEntrys[2048];



}