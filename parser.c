#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct reservedRegion region;

unsigned int hex_to_int(unsigned char * temp, int num);
void print_info();

void parser(const char * fileName)
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


  fseek(img, 3, SEEK_SET);
  fread(temp, sizeof(char), 8, img);
  temp[8] = '\0';
  strcpy(region.BS_OEMName, temp);


  fseek(img , 11, SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_BytsPerSec = hex_to_int(temp,2); 


  fseek(img, 13, SEEK_SET);
  fread(temp, sizeof(char), 1, img);
  region.BPB_SecPerClus = temp[0];


  fseek(img,14,SEEK_SET);
  fread(temp, sizeof(char), 2,img);
  region.BPB_RsvdSecCnt = temp[0];

  
  
  fseek(img , 16, SEEK_SET);
  fread(temp, sizeof(char), 1, img);
  region.BPB_NumFATs = temp[0];


  fseek(img , 17, SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_RootEntCnt = hex_to_int(temp,2);


  fseek(img , 19, SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_TotSec16 = hex_to_int(temp,2);

  
  fseek(img , 21, SEEK_SET);
  fread(temp, sizeof(char), 1, img);
  region.BPB_Media = temp[0];


  fseek(img , 22, SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_Media = hex_to_int(temp,2); 


  fseek(img , 24, SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_SecPerTrk = hex_to_int(temp,2);


  fseek(img , 26, SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_NumHeads = hex_to_int(temp,2);


  fseek(img,28,SEEK_SET);
  fread(temp, sizeof(char), 4, img);
  region.BPB_HiddSec = hex_to_int(temp,4);


  fseek(img,32,SEEK_SET);
  fread(temp, sizeof(char), 4, img);
  region.BPB_TotSec32 = hex_to_int(temp,4);


  fseek(img,36,SEEK_SET);
  fread(temp, sizeof(char), 4, img);
  region.BPB_FATSz32 = hex_to_int(temp,4);

  
  fseek(img,40,SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_ExtFlags = hex_to_int(temp,2);


  fseek(img,42,SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_FSVer = hex_to_int(temp,2);


  fseek(img,44,SEEK_SET);
  fread(temp, sizeof(char), 4, img);
  region.BPB_RootClus = hex_to_int(temp,4);

                                                // need to make a global variable to set = this

  fseek(img,48,SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_FSInfo = hex_to_int(temp,2);


  fseek(img,50,SEEK_SET);
  fread(temp, sizeof(char), 2, img);
  region.BPB_BkBootSec = hex_to_int(temp,2);


  fseek(img,52,SEEK_SET);
  fread(temp, sizeof(char), 12, img);
  region.BPB_Reserved = hex_to_int(temp,12);


  fseek(img,64,SEEK_SET);
  fread(temp, sizeof(char), 1, img);
  region.BS_DrvNum = temp[0];


  fseek(img,65,SEEK_SET);
  fread(temp, sizeof(char), 1, img);
  region.BS_Reserved1 = temp[0];


  fseek(img,66,SEEK_SET);
  fread(temp, sizeof(char), 1, img);
  region.BS_BootSig = temp[0];


  fseek(img,67,SEEK_SET);
  fread(temp, sizeof(char), 4, img);
  region.BS_VolID = hex_to_int(temp,4);


  fseek(img,71,SEEK_SET);
  fread(temp, sizeof(char), 11, img);
  temp[11] = '\0';
  strcpy(region.BS_Vollab,temp);


  fseek(img,82,SEEK_SET);
  fread(temp, sizeof(char), 8, img);
  temp[8] = '\0';
  strcpy(region.BS_FilSysType, temp);
 

  
  //firstdatasector = resvdsectcnt + (numfATS * FATsz32)
  //first sector of clus = firstdatasector + ((N - 2) * secperclus) where N is clus number
  
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

void print_info()
{

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
