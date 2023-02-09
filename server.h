#ifndef SERVER_H
#define SERVER_H

int setupSocket(const int PORT);
void serverLoop(const int server_socket);

#endif