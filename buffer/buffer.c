#include "buffer.h"


BUFFER *buffer(char* buffer,int offset,int count){
    BUFFER *buff;
    buff = malloc(sizeof(BUFFER));
    buff->buffer=buffer;
    buff->count=count;
    buff->offset=offset;
    return buff;
}
char* slice_buffer(char* bytes,int startindex,int endindex)
{
    if(bytes==NULL)
        return NULL;
    if(endindex==0||startindex==0)
        return NULL;

    char* cpyarr = malloc(endindex-startindex+1);
    int cpycount =0;
    int destcount =startindex;

    do {
        cpyarr[cpycount] = bytes[destcount];
        cpycount++;
        destcount++;
    } while (destcount!=(endindex+1));
    return cpyarr;
}
int trywritebytes(char* source,char* dest,int destoffset)
{
    if(source==NULL)
        return 0;
    if(dest==NULL)
        return 0;
    if(destoffset<0)
        return 0;

    int count=0;
    int destcount = destoffset;
    do{
        dest[destcount]=source[count];
        count++;
        destcount++;
    } while (count!=sizeof(source));

    return 1;
}
void cpy_buffer(char* source,int s_start,int s_end,char* dest,int d_start)
{
    if(source==NULL)
        return;
    if(dest==NULL)
        return;
    int sourcecnt=s_start;
    int destcnt=d_start;
    dest = malloc(1024);
    do {
        dest[destcnt] = source[sourcecnt];
        destcnt++;
        sourcecnt++;
    } while (sourcecnt!=s_end);
}