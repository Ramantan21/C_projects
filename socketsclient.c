#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    //create a socket
    int network_socket;
    network_socket = socket(AF_INET,SOCK_STREAM,0);

    //specift an adress for the socket
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;//specify the type
    server_adress.sin_port = htons(9002);//specify the port
    server_adress.sin_addr.s_addr = INADDR_ANY; //data of the adress we try to connect

    int conn_status = connect(network_socket,(struct sockaddr *)&server_adress,sizeof(server_adress));
    if(conn_status = -1){
        perror("Conection failed\n");
        exit(EXIT_FAILURE);
    }
    //recieve data from the server
    char server_response[296];
    recv(network_socket,&server_response,sizeof(server_response),0);
    //print out the server's response
    printf("the servers response: %s\n",server_response);
    //close the socket
    close(network_socket);
    return 0;
}