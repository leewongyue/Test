
#ifndef BUFFER_H
#define BUFFER_H

#endif
#include <stdlib.h>

typedef struct BUFFER
{
    char* buffer;
    int offset;
    int count;
}BUFFER;

BUFFER *buffer(char* buffer,int offset,int count);
char* slice_buffer(char* bytes,int startindex,int endindex);
int trywritebytes(char* source,char* dest,int destoffset);
void cpy_buffer(char* source,int s_start,int s_end,char* dest,int d_start);
int buffer_cmp(char* s1,char* s2);
