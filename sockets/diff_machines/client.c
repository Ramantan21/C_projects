#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>

void perror_exit(char *message);

void main(int argc,char *argv[]){
    int port,sock,i;
    char buf[256];
    struct sockaddr_in server;
    struct sockaddr *serverptr = (struct sockaddr*)&server;
    struct hostent *rem;
    if(argc != 3){
        printf("Please give host name and port number\n");
        exit(1);
    }
    if(sock = socket(AF_INET,SOCK_STREAM,0) < 0) perror_exit("socket");
    if((rem = gethostbyname(argv[1])) == NULL){
        herror("get host by name");
        exit(2);
    }
    port = atoi(argv[2]);
    server.sin_family = AF_INET;
    memcpy(&server.sin_addr,rem->h_addr,rem->h_length);
    server.sin_port = htons(port);
    if(connect(sock,serverptr,sizeof(server)) < 0) perror_exit("connect");
    printf("Connecting to %s port %d\n",argv[1],port);
    do{
        printf("Give input string: ");
        fgets(buf,sizeof(buf),stdin);
        for(i = 0; buf[i] != '\0'; i++){
            if(write(sock,buf + i, 1) < 0) perror_exit("write");
            if(read(sock,buf +i, 1) < 0) perror_exit("read");
        }
        printf("Received string :%s\n",buf);
    }while(strcmp(buf,"END\n") != 0);
    close(sock);
}

void perror_exit(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}