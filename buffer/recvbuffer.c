
#include "recvbuffer.h"

void init_recvbuff(int buffsize,RECVBUFFER *recvbuffer)
{
    recvbuffer = malloc(sizeof (RECVBUFFER));
    recvbuffer->read_buffer->buffer = malloc(sizeof (char)*buffsize);
    recvbuffer->recv_writepos = 0;
    recvbuffer->recv_readpos = 0;
    recvbuffer->recv_freesize = 0;
    recvbuffer->recv_datasize = 0;
    recvbuffer->write_buffer =0;
}
int get_datasize(RECVBUFFER *recvbuffer)
{
    recvbuffer->recv_datasize = recvbuffer->recv_writepos - recvbuffer->recv_readpos;
    return recvbuffer->recv_datasize;
}
int get_freesize(RECVBUFFER *recvbuffer)
{
    recvbuffer->recv_freesize = recvbuffer->read_buffer->count - recvbuffer->recv_writepos;
    return recvbuffer->recv_freesize;
}
// 할당된 메모리 해재 후 새로운 버퍼로 바꿀때 할당 해제 문제
BUFFER* get_readbuffer(RECVBUFFER *recvbuffer)
{
    BUFFER *ptr = recvbuffer->read_buffer->buffer;
    char *cpybuff = cpy_buff(recvbuffer->read_buffer->buffer,cpybuff);
    recvbuffer->read_buffer = buffer(cpybuff,recvbuffer->read_buffer->offset+recvbuffer->recv_readpos,get_datasize(recvbuffer));
    free(ptr->buffer);
    free(ptr);
    return recvbuffer->read_buffer;
}
BUFFER* get_writebuffer(RECVBUFFER *recvbuffer)
{
    recvbuffer->write_buffer = buffer(recvbuffer->read_buffer->buffer,recvbuffer->read_buffer->offset+recvbuffer->recv_writepos,get_freesize(recvbuffer));
    return recvbuffer->write_buffer;
}

void clean_buffer(RECVBUFFER *recvbuffer)
{
    if(get_datasize(recvbuffer)==0)
    {
        recvbuffer->recv_readpos = recvbuffer->recv_writepos = 0;
    }
    else
    {
        clean_buff(recvbuffer->read_buffer->buffer,recvbuffer->read_buffer->offset,recvbuffer->read_buffer->offset+recvbuffer->recv_readpos,recvbuffer->read_buffer->buffer,0);
        recvbuffer->recv_readpos = 0;
        recvbuffer->recv_writepos=get_datasize(recvbuffer);
    }
}

bool onread_buffer(int numofbyte,RECVBUFFER *recvbuffer)
{
    if(numofbyte>get_datasize(recvbuffer))
        return false;

    recvbuffer->recv_readpos+=numofbyte;
    return true;
}
bool onwrite_buffer(int numofbyte,RECVBUFFER *recvbuffer)
{
    if(numofbyte>get_freesize(recvbuffer))
        return false;

    recvbuffer->recv_writepos+=numofbyte;
    return true;
}
