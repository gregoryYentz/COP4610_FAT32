#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void removeFAT(int c);
unsigned char* to_little(unsigned int start, unsigned int num);


void RMDIR(struct INSTRUCTION* instr){
  FILE * img = GetImageFile();
  int i, k;
  int entry, firstclus;
  char t[4];
  unsigned int e = 0xE5;
  unsigned char* empty;
  empty = to_little(0,4);
  if(instr->numTokens==2){
	  if(isValidDirectory(instr->tokens[1]) != 0)
	    {
	      k = 0;
	      DirEntry * ind = GetDirectoryContents(CURRENTCLUSTERNUM);
	      while(!ind[k].END_OF_ARRAY)
		{
		  if(strcmp(ind[k].DIR_Name, instr->tokens[1]) == 0)
		    {
		      entry = ind[k].DIR_EntryByteAddress;
		      firstclus = ind[k].DIR_FstClusLO;
		    }
		  k++;
		}

	      int clus = isValidDirectory(instr->tokens[1]);
	      DirEntry * temp = GetDirectoryContents(clus);
	      if(temp[2].END_OF_ARRAY)
		{
		  
		  fseek(img,entry,SEEK_SET);
		  for(i = 0; i < 4; i++)
		    {
		      fputc(e,img);
		    }

		  fseek(img, go_to_clus(clus), SEEK_SET);
		  for(i = 0; i < 4; i++)
		    {
		      fputc(empty[i],img);
		    }
		 
		  removeFAT(clus);
		 
		} 
	      else
		{
		  printf("Error: Directory Not Empty\n");
		}

	    }
	  else
	    {
	      printf("Error: Not a Valid Directory\n");
	    }
	}
	else{
		printf("rmdir ERROR\n");
	}
}

void removeFAT(int c)
{
  FILE * img;
  int  f;
  unsigned int e = 0x00;

  img = GetImageFile();
  f = to_FAT(c);
  
  fseek(img,f, SEEK_SET);
  unsigned char * tmp;
  tmp =  to_little(0, 4);    // need to turn 0 value into little endian string to zero out
  int i = 0;
  while(i < 4)
    {
      fputc(tmp[i], img);
      i++;
    }
    
}

unsigned char* to_little(unsigned int start, unsigned int num) // opposite of hex_to_int
{                                                              // turns big endian to little endian
  int temp = start;
  static unsigned char new[4];    // causes a warning if variable is not static
  int i;
   
  for(i = 0; i < num; i++)
    {
      new[i] = start & 0xFF; // only care about 8 least significant bits
      start = start >> 8; // shift over to move on to the next 8 bits
      i++;
    }
    return new;
}
