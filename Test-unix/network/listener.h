#ifndef LISTENER_H
    #define LISTENER_H
#endif LISTENER_H

#include "socketargs.h"

#define PORT 3000
#define BUFF_SIZE 1024

WSADATA wsaData;
SOCKET listen_socket;
SOCKADDR_IN addr;
OVERLAPPED *ovl_ptr = NULL;
HANDLE complete_port_ptr;
unsigned long complete_key;
unsigned int comp_readbytes;
int type;


void init_listener(SOCKADDR_IN addr,HANDLE comp_port);
void init_sock_args(SOCK_ARGS *args);
void reg_accept(SOCK_ARGS *args,HANDLE comp_port);
void accept_complete(void *sender,SOCK_ARGS *args);
BOOL accept_p(SOCKET listen_socket,SOCK_ARGS *args);