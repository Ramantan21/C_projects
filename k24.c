#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
void chatchinterupt(int signo){
    printf("\nCatching signo = %d\n",signo);
    printf("Catching: returning\n");
}

int main(){
    static struct sigaction act;
    act.sa_handler = chatchinterupt;
    sigfillset(&(act.sa_mask));
    sigaction(SIGINT,&act,NULL);
    printf("Sleep call #1\n");
    sleep(1);
    printf("Sleep call #2\n");
    sleep(1);
    printf("Sleep call #3\n");
    sleep(1);
    printf("sleep call #4\n");
    sleep(1);

    printf("Exiting \n");
    exit(0);
}


    