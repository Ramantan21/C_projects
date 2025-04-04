#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    pid_t childpid;
    pid_t mypid;

    mypid = getpid();//ΙD του πατερα.Το mypid αντιγραφεται στο παιδι μετα το fork
    childpid = fork();

    if(childpid == -1){
        perror("Failed to fork\n");
        return 1;
    }

    if(childpid == 0){
        printf("I am the child process with ID: %lu -- %lu\n",(long)getpid,(long)mypid);

    }else
        printf("I am the parent process with ID: %lu -- %lu",(long)mypid,(long)getpid);
    return 0;
}