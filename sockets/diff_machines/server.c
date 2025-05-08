#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <signal.h>

void child_server(int newsock);
void perror_exit(char *message);
void sigchld_handler(int sig);

void main(int argc,char *argv[]){
    int port,sock,newsock;
    struct sockaddr_in server,client;
    socklen_t clientlen;
    struct sockaddr *serverptr = (struct sockaddr*)&server;
    struct sockaddr *clientptr = (struct sockaddr*)&client;
    struct hostent *rem;
    if(argc != 2){
        printf("Please give port number\n");
        exit(1);
    }
    port = atoi(argv[1]);
    signal(SIGCHLD,sigchld_handler);
    if(sock = socket(AF_INET,SOCK_STREAM,0) < 0) perror_exit("socket");

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sock,serverptr,sizeof(server)) < 0) perror_exit("bind");

    if(listen(sock,5) < 0 ) perror_exit("listen");
    printf("Listening for connections to port: %d\n",port);
    while(1){
        clientlen = sizeof(client);
        if((newsock = accept(sock,clientptr,&clientlen)) < 0) perror_exit("accept");

        if((rem = gethostbyaddr((char *)&client.sin_addr.s_addr,sizeof(client.sin_addr.s_addr),client.sin_family)) == NULL){
            herror("gethostbyaddr");
            exit(2);
        }
        printf("Accepted connection from %s\n",rem->h_name);
        switch(fork()){
            case -1:
                perror_exit("fork failed");
                break;
            case 0: //chld process
                close(sock);
                child_server(newsock);
                exit(3);
        }
        close(newsock); //parent process closes socket to client
    }
}

void child_server(int newsock){
    char buf[1];
    while(read(newsock,buf,1) > 0){
        putchar(buf[0]);
        buf[0] = toupper(buf[0]);
        if(write(newsock,buf,1) < 0 ) perror_exit("write");
    }
    printf("Closing connection");
    close(newsock);
}

void sigchld_handler(int sig){
    while(waitpid(-1,NULL,WNOHANG) >0);
}

void perror_exit(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}