#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


//creates a new process by duplicating the calling process
//Returns the value 0 in the child-processID of the child process to the parent
//Returns -1 to the parent process if it is NOT feasible to create a new child-process

int main(){
    pid_t childpid;

    childpid = fork();
    if(childpid == -1){
        perror("Failed to fork");
        return 1;
    }

    if(childpid == 0){
        printf("I am the child process with ID: %lu\n",(long)getpid);
    }else
        printf("I am the parent process with ID: %lu\n",(long)getppid);
    return 0;
}