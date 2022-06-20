#ifndef SOCKETARGS_H
    #define SOCKETARGS_H
#endif 

#include <WinSock2.h>
#include <MSWSock.h>
#include <stdlib.h>
#include "buffer/buffer.h"
#include "datastructure/linkedlist.h"
#include "log/log.h"


#define S_ACCEPT 1
#define S_CLOSE 2
#define S_READ 3
#define S_WRITE 4

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
typedef struct SOCK_ARGS
{
    SOCKET accept_sock;
    BUFFER *buffer;
    LIST *buffer_list;
    int transf_bytes;
    SOCKADDR_IN sock_addr;
    OVERLAPPED *overlapped;
    HANDLE complete_port;
    int sock_state;
    unsigned long complete_key;
    unsigned int comp_readbytes;
    

}SOCK_ARGS;

void init_sock_args(SOCK_ARGS *args)
{
    args = malloc(sizeof(SOCK_ARGS));
    args->accept_sock = WSASocket(AF_INET,SOCK_STREAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
    args->overlapped = NULL;
    ZeroMemory(&(args->overlapped),sizeof(OVERLAPPED)); 
    args->sock_state = S_ACCEPT;
    args->buffer = malloc(sizeof(char)*1024);
}