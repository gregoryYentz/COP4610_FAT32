#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int find_free_fat();
int get_fat_start();
int get_fat_end();

void CREAT(struct INSTRUCTION* instr){
  int new = find_free_fat();

  int f = to_FAT(new), i;
  FILE* img = GetImageFile();
  unsigned char *t, *temp;
  t = to_little(0x0FFFFFF8,4);
  DirEntry * n = GetDirectoryContents(CURRENTCLUSTERNUM);
  unsigned int addr, lo, hi;
  DirEntry test;
  unsigned char attr = 0x20;
  lo = new & 0xFF;
  hi = new >> 16;


  if(instr->numTokens==2)
    {
      if(isValidFile(instr->tokens[1]) == 0)
	{
	   strcpy(test.DIR_Name, instr->tokens[1]);
	   fseek(img, f, SEEK_SET);
	  for(i = 0; i < 3; i++)         // put the EOF marker in the FAT 
	    {
	     
	      fputc(0xFF,img);
	    }
	  fputc(0x0F,img);
	 
	    i = 0;
	  while(n[i].END_OF_ARRAY != 1)
	    {
	     
	      i++;
	    }
	  i--;
	  
	  addr = n[i].DIR_EntryByteAddress + 32;
	  
	  fseek(img, addr, SEEK_SET);
	  for(i = 0; i < 11; i++)
	    {
	      fputc(test.DIR_Name[i], img);
	    }
	  
	  fseek(img, addr + 11, SEEK_SET);
	  fputc(attr, img);

	  temp = to_little(lo,2);
	  fseek(img, addr + 26, SEEK_SET);
	  fputc(temp[0], img);
	  fputc(temp[1], img);

	  temp = to_little(hi,2);
	  fseek(img, addr + 20, SEEK_SET);
	  fputc(temp[0] , img);
	  fputc(temp[1], img);

	  temp = to_little(0, 4);
	  fseek(img, addr + 28, SEEK_SET);
	  for(i = 0; i < 4; i++)
	    {
	      fputc(temp[i], img);
	    }
	  
	  n = GetDirectoryContents(CURRENTCLUSTERNUM);
	  i = 0;
	  while(n[i].END_OF_ARRAY != 1)
	    {
	     
	      i++;
	    }
	  
	}
      else
	{
	  printf("ERROR: Dir Already Exists!\n");
	}
    }
  else
    {
      printf("creat ERROR: No Name Specified\n");
    }
}

int find_free_fat()             // returns number of first free cluster in fat
{
  FILE* img = GetImageFile();
  unsigned int pos = get_fat_start();
  unsigned int clus_num, clus_index = 0;    // fat clusters start at 2 but memory clusters start at 0
  unsigned char read[4];
  unsigned int i = 0;

  fseek(img, pos, SEEK_SET);
  fread(read, sizeof(char),4,img);
  clus_num = hex_to_int(read,4);
  pos = pos + 4;
  while(pos <= get_fat_end())
    {

      
      fseek(img, pos, SEEK_SET);
      fread(read, sizeof(char), 4, img);
      clus_index++;
      clus_num = hex_to_int(read,4);
      pos = pos + 4;

    
    
      if(clus_num == 0x00000000)
	break;
    }

  if(pos == get_fat_end())
    {
      printf("ERROR: FAT is full\n");
      return 0;
    }
  //clus_index--;

  return clus_index;
}

int get_fat_start()
{
  return to_FAT(0);
}

int get_fat_end()
{
  return (region.BPB_FATSz32 * region.BPB_BytsPerSec) + get_fat_start();
}
