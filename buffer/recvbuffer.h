#ifndef RECVBUFFER_H
#define RECVBUFFER_H

#endif

#include "buffer.h"
#include <stdbool.h>

#define MAX_RECVBUFF_SIZE 65535

typedef struct {
    BUFFER* read_buffer;
    BUFFER* write_buffer;

    int recv_readpos;
    int recv_writepos;

    int recv_datasize;
    int recv_freesize;
}RECVBUFFER;

void init_recvbuff(int buffsize,RECVBUFFER *recvbuffer);
int get_datasize(RECVBUFFER *recvbuffer);
int get_freesize(RECVBUFFER *recvbuffer);

BUFFER* get_readbuffer(RECVBUFFER *recvbuffer);
BUFFER* get_writebuffer(RECVBUFFER *recvbuffer);

void clean_buffer(RECVBUFFER *recvbuffer);

bool onread_buffer(int numofbyte,RECVBUFFER *recvbuffer);
bool onwrite_buffer(int numofbyte,RECVBUFFER *recvbuffer);
