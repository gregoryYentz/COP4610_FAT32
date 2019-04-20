#include <stdio.h>
#include <stdlib.h>
#include "reserve.c"

unsigned int hex_to_int(unsigned char * temp, int num);

void parser(char * fileName, struct reservedRegion region)
{
  FILE * img;
  
  img = fopen(fileName, "r+b");
  if(img == NULL)
    {
      printf("Error: Invalid File\n");
      exit(1);
    }

  unsigned char temp[11];
  fseek(img,0, SEEK_SET);
  fread(temp, sizeof(char), 3, img);
  region.BS_jmpboot = hex_to_int(temp,3) & 0xff;
  printf("JMP: %x\n", region.BS_jmpboot);

  fseek(img, 3, SEEK_SET);
  fread(temp, sizeof(char), 8, img);
  temp[8] = '\0';
  strcpy(region.BS_OEMName, temp);
  printf("OEMN: %s\n",region.BS_OEMName);

  fseek(img , 11, SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_BytsPerSec = temp; 
  printf("Bytes %i\n",hex_to_int(temp,2));

  fseek(img, 13, SEEK_SET);
  fread(temp, sizeof(char), 1, img);
  region.BPB_SecPerClus = temp[0];
  printf("Clus: %x\n", region.BPB_SecPerClus);

  fseek(img,14,SEEK_SET);
  fread(temp, sizeof(char), 2,img);
  region.BPB_RsvdSecCnt = temp[0];
  printf("RESVD: %i\n", region.BPB_RsvdSecCnt);
  
  
  fseek(img , 16, SEEK_SET);
  fread(temp, sizeof(char), 1, img);
  region.BPB_NumFATs = temp[0];
  printf("NUM: %i\n",region.BPB_NumFATs);

  fseek(img , 17, SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_RootEntCnt = hex_to_int(temp,2);
  printf("ROOT: %i\n",region.BPB_RootEntCnt);

  fseek(img , 19, SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_TotSec16 = hex_to_int(temp,2);
  printf("TOTSEC16: %i\n",region.BPB_TotSec16);
  
  fseek(img , 21, SEEK_SET);
  fread(temp, sizeof(char), 1, img);
  region.BPB_Media = temp[0];
  printf("Media: %x\n",region.BPB_Media);

  fseek(img , 22, SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_Media = hex_to_int(temp,2); 
  printf("FATSz16: %i\n",region.BPB_FATSz16);

  fseek(img , 24, SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_SecPerTrk = hex_to_int(temp,2);
  printf("SecPerTrk: %u\n",region.BPB_SecPerTrk);

  fseek(img , 26, SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_NumHeads = hex_to_int(temp,2);
  printf("NUM_HEads: %u\n",region.BPB_NumHeads);

  fseek(img,28,SEEK_SET);
  fread(temp, sizeof(char), 4, img);
  region.BPB_HiddSec = hex_to_int(temp,4);
  printf("HIDDSEC: %u\n",region.BPB_HiddSec);

  fseek(img,32,SEEK_SET);
  fread(temp, sizeof(char), 4, img);
  region.BPB_TotSec32 = hex_to_int(temp,4);
  printf("TOTS32: %u\n",region.BPB_TotSec32);

  fseek(img,36,SEEK_SET);
  fread(temp, sizeof(char), 4, img);
  region.BPB_FATSz32 = hex_to_int(temp,4);
  printf("FATS32: %u\n",region.BPB_FATSz32);
  
  fseek(img,40,SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_ExtFlags = hex_to_int(temp,2);
  printf("EXT: %u\n",region.BPB_ExtFlags);

  fseek(img,42,SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_FSVer = hex_to_int(temp,2);
  printf("FSVER: %u\n",region.BPB_FSVer);

  fseek(img,44,SEEK_SET);
  fread(temp, sizeof(char), 4, img);
  region.BPB_RootClus = hex_to_int(temp,4);
  printf("ROOTCLUS: %u\n",region.BPB_RootClus); //num of the cluster with root dir
                                                // need to make a global variable to set = this

  fseek(img,48,SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_FSInfo = hex_to_int(temp,2);
  printf("FSINFO: %u\n",region.BPB_FSInfo);

  fseek(img,50,SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_BkBootSec = hex_to_int(temp,2);
  printf("BKBOOTSEC: %u\n",region.BPB_BkBootSec);

  fseek(img,52,SEEK_SET);
  fread(temp, sizeof(char), 12, img);
  region.BPB_Reserved = hex_to_int(temp,12);
  printf("Reserved: %u\n",region.BPB_Reserved);

  fseek(img,64,SEEK_SET);
  fread(temp, sizeof(char), 1, img);
  region.BS_DrvNum = temp[0];
  printf("DRVNUM: %u\n",region.BS_DrvNum);

  fseek(img,65,SEEK_SET);
  fread(temp, sizeof(char), 1, img);
  region.BS_Reserved1 = temp[0];
  printf("RES1: %u\n",region.BS_Reserved1);

  fseek(img,66,SEEK_SET);
  fread(temp, sizeof(char), 1, img);
  region.BS_BootSig = temp[0];
  printf("BOOTSIG: %u\n",region.BS_BootSig);

  fseek(img,67,SEEK_SET);
  fread(temp, sizeof(char), 4, img);
  region.BS_VolID = hex_to_int(temp,4);
  printf("VolID: %u\n",region.BS_VolID);

  fseek(img,71,SEEK_SET);
  fread(temp, sizeof(char), 11, img);
  temp[11] = '\0';
  strcpy(region.BS_Vollab,temp);
  printf("VOLLAB: %s\n",region.BS_Vollab);

  fseek(img,82,SEEK_SET);
  fread(temp, sizeof(char), 8, img);
  temp[8] = '\0';
  strcpy(region.BS_FilSysType, temp);
  printf("TOTS32: %s\n",region.BS_FilSysType);


  /*
    firstdatasector = resvdsectcnt + (numfATS * FATsz32)
    first sector of clus = firstdatasector + ((N - 2) * secperclus) where N is clus number
  
}

// Function to account for FAT32 being little endian, the least significant bits 
// must be first in the integer representation of numbers

unsigned int hex_to_int(unsigned char* temp, int num)
{
  int i; 
  unsigned int ans;
  ans = 0;

  for(i = 0; i < num; i++)
    {
      ans += (unsigned int)(temp[i] << (i * 8));
    }

  return ans;
}
