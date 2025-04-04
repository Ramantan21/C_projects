#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    int status,exit_status;

    if((pid= fork()) < 0){
        perror("fork failed");
        exit(1);
    }
    if(pid == 0){
        sleep(4);
        exit(5); //exit with non-zero value
    }
    else{
        printf("Hello im the parent process: %d with child %d\n",getpid(),pid);
    }
}