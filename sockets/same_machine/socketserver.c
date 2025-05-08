#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//socket(),bind ip(),accept connection(),read data()

int main(){
    char server_message[255] = "You have reached the server!";
    //create server socket
    int server_socket;
    server_socket = socket(AF_INET,SOCK_STREAM,0);

    //define the server adress
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(9002);
    server_adress.sin_addr.s_addr = INADDR_ANY;

    //bind the socket to the ip and port
    bind(server_socket,(struct sockaddr*)&server_adress,sizeof(server_adress));

    //listen for connections
    listen(server_socket,5);
    int client_socket;
    client_socket = accept(server_socket,NULL,NULL);
    send(client_socket,server_message,sizeof(server_message),0);//send data to client

    //close the socket
    close(server_socket);
    return 0;
}