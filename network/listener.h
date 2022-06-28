#ifndef LISTENER_H
    #define LISTENER_H
#endif

#include  <sys/socket.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include "socketargs.h"
#include "../log/log.h"

int clientsocket;
int listensocket;

void init_socket(struct sockaddr_in addr,SOCKETARGS *args,int port);
bool accept_socket(int serversocket,SOCKETARGS *args);
void reg_accept(SOCKETARGS *args);
void accept_complete(SOCKETARGS *args);
