#include "kernel/types.h"
#include "user/user.h"


int main(int argc, char *argv[]){
    if(argc == 1){
		fprintf(2, "ERROR: sleep time required\n");
        exit(1);
    }
    int sec = atoi(argv[1]);
	fprintf(2, "%d\n",sec);
    sleep(sec);
    exit(0);
}