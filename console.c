#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <sys/inotify.h>
#include <time.h>
#include <poll.h>

#define FSS_IN "/tmp/fss_in"  // Pipe για εντολές γραφει προς τον manager
#define FSS_OUT "/tmp/fss_out"  // pipe για να διαβασει την απαντηση απτον manager



char *timestamp(){
    static char buffer[32];
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buffer,sizeof(buffer),"[%Y-%m-%d %H:%M:%S]",tm_info);
    return buffer;
}

int main(int argc,char *argv[]){
    if(argc != 3 || strcmp(argv[1],"-l") != 0){
        printf("Wrong usage of %s\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    char *console_log_file = argv[2];

    //Ανοιγουμε τον console-logfile για καταγραφη εντολων και απαντησεων
    FILE *fp = fopen(console_log_file,"a");
    if(fp == NULL){
        perror("Failed to open log file");
        exit(EXIT_FAILURE);
    }
    int fd[2];
    char command[256];
    char response[256];

    //Ανοιγμα pipes(ο console γραφει στο FSS_IN και διαβαζει απο FSS_OUT)
    fd[0] = open(FSS_OUT, O_RDONLY | O_NONBLOCK);
    fd[1] = open(FSS_IN, O_WRONLY | O_NONBLOCK);

    if(fd[0] == -1 || fd[1] == -1){
        perror("open failed");
        exit(1);
    }

    printf("FSS console - Available commands: add <source><target>,cancel <dir>,status,sync\n");

    while(1){
        printf("> ");
        if(fgets(command,sizeof(command),stdin) == NULL){//Διαβαζει εντολη απο τον χρηστη
            if(feof(stdin)){
                printf("\nExiting..\n");
                break;
            }
            perror("error on cmd command");
            continue;
        }
        command[strcspn(command,"\n")] = '\0'; //αφαιρεση newline

        fprintf(fp,"%s command %s\n",timestamp(),command);
        fflush(fp);

        
        //Στελνουμε εντολη στον manager
        if((write(fd[1],command,strlen(command)+1)) == -1){
            perror("write failed");
            exit(EXIT_FAILURE);
        }

        //Διαβαζει την απαντηση του manager
        ssize_t bytes = read(fd[0],response,sizeof(response));
        if(bytes == -1 && errno != EAGAIN){
            perror("read failed");
        }
        if(bytes > 0 ){
            fprintf(fp,"%s %s\n",timestamp(),response);
            fflush(fp);
            printf("%s\n",response);
        }else{
            printf("No response from manager\n");
        }
        //ελεγχουμε αν ειναι shutdown,τερματιζουμε το προγραμμα
        if(strcmp(command,"shutdown") == 0){
            break;
        }
    }

    close(fd[0]);
    close(fd[1]);
    return 0;
}