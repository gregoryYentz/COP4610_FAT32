#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define MAX_CLUS 65536

void remove_file(FILE* img, int clus);
void remove_file_data(FILE* img, int clus);

void RM(struct INSTRUCTION* instr){
  FILE *img = GetImageFile();
  unsigned int entry = 0;

  if(instr->numTokens==2){
    if(isValidFile(instr->tokens[1]) != 0)
      {
	entry = get_entry_addr(instr->tokens[1]);

	int clus = isValidFile(instr->tokens[1]);
	
	remove_file(img,clus);
	remove_dir_entry(img, entry);
      }
    else
      {
	printf("ERROR: Invalid File\n");
      }
    
  }
  else{
    printf("rm ERROR: No File Specified\n");
  }
}

void remove_file(FILE* img, int clus)
{
  int c[MAX_CLUS];                 // max possible clusters for entire image file
  int loc = to_FAT(clus);
  int i = 1, n_cluster;

  c[0] = clus;
  n_cluster = get_next_clus(clus);
  while(n_cluster < 0x0FFFFFF8)
    {
      c[i] = n_cluster;
      n_cluster = get_next_clus(n_cluster);
      i++;
    }
  

  i--;
  while(i >= 0)
    {
      removeFAT(c[i]);
      remove_file_data(img, c[i]);
      i--;
    }
}

void remove_file_data(FILE* img, int clus)
{
  int i;
  unsigned char * empty;
  empty = to_little(0,1);
  int size = region.BPB_SecPerClus * region.BPB_BytsPerSec;
  fseek(img, go_to_clus(clus), SEEK_SET);
  
  for(i = 0; i < size; i++)
    {
      fputc(empty[0], img);
    }
}
