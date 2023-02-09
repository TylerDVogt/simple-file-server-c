#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "client.h"


int main (int argc, char *argv[]) 
{ 
    if(argc != 3){
        printf("Error: Please specify the IPV4 & PORT# \n");
        return -1;
    }
    const char *IPV4 = argv[1];
    const int PORT = atoi(argv[2]);

    setupSocket(IPV4, PORT);

    return 0;
}

int setupSocket(const char *IPV4, const int PORT){
    // create socket and address
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    inet_pton(AF_INET, IPV4, &server_address.sin_addr);

    // connect
    connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    char msg[256];
    recv(client_socket, &msg, sizeof(msg),0);
    printf("Message: %s",msg);

}