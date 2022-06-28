#ifndef SOCKETARGS_H
    #define SOCKETARGS_H
#endif
#include <arpa/inet.h>
#include "../buffer/buffer.h"
#include "../datastructure/linkedlist.h"

#define STATE_DEFAULT 0
#define STATE_ACCEPTED 1
#define STATE_CLOSED 2

typedef struct SOCKETARGS
{
    BUFFER *buffer;
    int acceptsocket;
    int socketstate;
    int bytetransferred;
    struct sockaddr_in client_addr;

}SOCKETARGS;

void init_socketargs(SOCKETARGS *args)
{
    args->buffer = (BUFFER *)malloc(sizeof(BUFFER));
    args->acceptsocket = 0;
    args->socketstate = STATE_DEFAULT;
    args->bytetransferred = 0;
    memset(&args->client_addr,0,sizeof (args->client_addr));
}
