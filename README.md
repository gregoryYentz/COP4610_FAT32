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
- write
- rm
- rmdir

## Problems
- all files that exist but that are empty return a FstCluster of 0. This makes so we can't OPEN empty files to write to because once we open any empty file, all empty files are considered to be open because we store the open files based on cluster num, not filename.
- attempting to open and close the same file with different r/w permissions sometimes freaks out the isOpen()
- we were not able to remove a creaded file without passing the incorrect clusternum without error so mkdir and creat #included"" statements were commented out
- creat does create new files, they just can't be removed
- write cannot change the file size as we didn't want to overwrite any data if the input string is longer than the filesize
