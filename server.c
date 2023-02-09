#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "server.h"

int main(int argc, char *argv[]) 
{   
    if(argc != 2){
        printf("Error: Please specify the PORT# \n");
        return -1;
    }
    const int PORT = atoi(argv[1]);
    // setup socket
    int server_socket = setupSocket(PORT);
    // server loop
    serverLoop(server_socket);

    
    return 0;
}

int setupSocket(const int PORT){
    // create socket and address
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    // bind and listen
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    listen(server_socket, 1);
    printf("Listening on port %i...\n",PORT);
    return server_socket;
}

void serverLoop(const int server_socket){
    int client_socket;
    struct sockaddr_in client_address;
    socklen_t client_address_size = sizeof(client_address);
    char msg[256] = "You have connected to the server\n";
    while((client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size)) != -1){
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_address.sin_addr, ip, INET_ADDRSTRLEN);
        printf("%s has connected\n", ip);
        send(client_socket, msg, sizeof(msg), 0);
    }
}

