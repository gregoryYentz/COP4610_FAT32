#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int CURRENTCLUSTERNUM;
unsigned int CLUSTERNUMSTACK[100];
int CLUSTERNUMSTACKINDEX;

struct reservedRegion region;

unsigned int hex_to_int(unsigned char * temp, int num);
int go_to_clus(int t);
unsigned int get_next_clus(unsigned int c);
int to_FAT(int s);

FILE* img;

FILE* GetImageFile() {
  return img;
}

void parser(const char * fileName){
  img = fopen(fileName, "r+b");
  if(img == NULL){
    printf("Error: Invalid File\n");
    exit(1);
  }

  
  unsigned char temp[11];
  char data[32];
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

  /*
  fseek(img, go_to_clus(2), SEEK_SET);
  fread(data, sizeof(char), 32, img);
  printf("DATA:\t%s\n", data);
  */
  
  
  CURRENTCLUSTERNUM = region.BPB_RootClus;

  CLUSTERNUMSTACK[0] = CURRENTCLUSTERNUM;
  CLUSTERNUMSTACKINDEX = 0;
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

int go_to_clus(int t)   //returns byte location of data at cluster[t] in data region
{
  int first = region.BPB_RsvdSecCnt + (region.BPB_NumFATs * region.BPB_FATSz32);
  int dt = ((t - 2) * region.BPB_SecPerClus) + first;
  int final = dt * region.BPB_BytsPerSec;
  return final;
}

int to_FAT(int s)      // returns the location of the first fat entry for cluster s
{
  int SEC = region.BPB_RsvdSecCnt + ((region.BPB_RootClus * 4)/region.BPB_BytsPerSec);
  //int off = (s * 4) % region.BPB_BytsPerSec;

  SEC = SEC * region.BPB_BytsPerSec;
  SEC = SEC + (s * 4);
  return SEC;
}

unsigned int get_next_clus(unsigned int c)  // checks fat for next cluster entry value
{
  char data[32];
  fseek(img,(to_FAT(c)), SEEK_SET);
  
  fread(data,sizeof(unsigned char), 4, img);
  return hex_to_int(data,4);
}
