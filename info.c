#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void print_info();

void INFO(){
	//printf(">info\n");
	print_info(); //parser.c
}

void print_info(){
	printf("JMP: %x\n", region.BS_jmpboot);

	printf("OEMN: %s\n",region.BS_OEMName);

	printf("Bytes %i\n",region.BPB_BytsPerSec); 

	printf("Clus: %x\n", region.BPB_SecPerClus);

	printf("RESVD: %i\n", region.BPB_RsvdSecCnt);

	printf("NUM: %i\n",region.BPB_NumFATs);

	printf("ROOT: %i\n",region.BPB_RootEntCnt);

	printf("TOTSEC16: %i\n",region.BPB_TotSec16);

	printf("Media: %x\n",region.BPB_Media);

	printf("FATSz16: %i\n",region.BPB_FATSz16);

	printf("SecPerTrk: %u\n",region.BPB_SecPerTrk);

	printf("NUM_HEads: %u\n",region.BPB_NumHeads);

	printf("HIDDSEC: %u\n",region.BPB_HiddSec);

	printf("TOTS32: %u\n",region.BPB_TotSec32);

	printf("FATS32: %u\n",region.BPB_FATSz32);

	printf("EXT: %u\n",region.BPB_ExtFlags);

	printf("FSVER: %u\n",region.BPB_FSVer);

	printf("ROOTCLUS: %u\n",region.BPB_RootClus); //num of the cluster with root dir
	                                            // need to make a global variable to set = this
	printf("FSINFO: %u\n",region.BPB_FSInfo);

	printf("BKBOOTSEC: %u\n",region.BPB_BkBootSec);

	printf("Reserved: %u\n",region.BPB_Reserved);

	printf("DRVNUM: %u\n",region.BS_DrvNum);

	printf("RES1: %u\n",region.BS_Reserved1);

	printf("BOOTSIG: %u\n",region.BS_BootSig);

	printf("VolID: %u\n",region.BS_VolID);

	printf("VOLLAB: %s\n",region.BS_Vollab);

	printf("FILSYSTYPE: %s\n", region.BS_FilSysType);

}