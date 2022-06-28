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
    if(endindex<startindex)
        return 0;
    int cnt =0;
    char *sliced = malloc(sizeof(char) * endindex-startindex+1);
    while (startindex != endindex+1)
    {
        sliced[cnt] = bytes[startindex];
        cnt++;
        startindex++;
    }
    sliced[startindex] = '\0';
    return sliced;
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
    char * tmp;
    int sourcecnt=s_start;
    int destcnt=d_start;
    dest = malloc(1024);
    do {
        dest[destcnt] = source[sourcecnt];
        destcnt++;
        sourcecnt++;
    } while (sourcecnt!=s_end);
}
int buffer_len(char* buffer)
{
    int cnt = 0;
    while (buffer[cnt] != '\0')
    {
        cnt++;
    }
    return cnt;
}
char* cpy_buff(char* src,char *dest)
{
    int cnt=0;
    while (src[cnt] != '\0')
    {
        dest[cnt] = src[cnt];
    }
    dest[cnt] = '\0';
    return dest;
}
void clean_buff(char *src,int s_startindex,int s_endindex,char*dest,int d_offset)
{
    int srccnt = s_startindex;
    int destcnt =d_offset;
    char *tmp = malloc(sizeof (char)*1024);
    cpy_buff(src,tmp);
    do
    {
        dest[destcnt] = tmp[srccnt];
        srccnt++;
        destcnt++;
    }
    while (srccnt != s_endindex);
    free(tmp);
}
int buffer_cmp(char* s1,char* s2)
{
    int cnt;

    cnt = 0;
    while (s1[cnt] != '\0' || s2[cnt] != '\0')
    {
        if(s1[cnt] != s2[cnt])
        {
            return 0;
        }
        cnt++;
    }
    return 1;
}
