# COP4610_FAT32

## Kyle Molter
## Gregory Yentz

## Complete
- exit
- info
- ls
- cd
- size
- open
- close
- read
- rm
- rmdir

## Problems
- all files that exist but that are empty return a FstCluster of 0. This makes so we can't OPEN empty files to write to because once we open any empty file, all empty files are considered to be open because we store the open files based on cluster num, not filename.
- attempting to open and close the same file with different r/w permissions sometimes freaks out the isOpen()
