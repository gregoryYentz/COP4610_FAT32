#include"reserve.c"
#include"shell.c"

int main(int argc, const char * argv[]){
	parser(argv[1]);
	Shell(argv[1]);			//opens shell utility to execute instructions on .img file
	return 0;
}