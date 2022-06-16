
#include "jsonparser.h"

char *file_read(char*path,char*buffer)
{
    int fd;
    if(0<(fd = open(path,O_RDONLY)))
    {
        fd = read(fd,buffer,BUFFERSIZE);
    }
    if(fd == -1)
    {
        return 0;
    }
    close(fd);
    return buffer;
}
char *slice_buff(char *buffer,int s_index,int e_index)
{
    if(e_index<s_index)
        return 0;
    int cnt =0;
    int buffindex = s_index;
    char *sliced = malloc(sizeof(char)*(e_index-s_index+1));
    while (s_index != e_index)
    {
        sliced[cnt] = buffer[buffindex];
        cnt++;
        buffindex++;
    }
    buffer[buffindex] = '\0';
    return sliced;
}
void json_parser(char *buffer,int len)
{
    int depth = 0;
    int s_index = 0;
    int e_index = 0;
    int cnt = 0;

    while (cnt != len)
    {
        if(buffer[cnt] == '[' && buffer[cnt+1] == '{')
        {
            depth++;
        }
        cnt++;
    }
}

JSON_BUFF *del_ws(char *buffer,int len)
{
    JSON_BUFF *json_buf = malloc(sizeof(JSON_BUFF));
    int cnt = 0;
    int cpycnt = 0;
    char buff[1024];
    while (cnt != len)
    {
        if(buffer[cnt] =='\n'|| buffer[cnt] == ' ' || buffer[cnt] == '\r' || buffer[cnt] == 'r')
        {
            cnt++;
            continue;
        }
        buff[cpycnt] = buffer[cnt];
        cnt++;
        cpycnt++;
    }
    buff[cpycnt] = '\0';
    json_buf->len = (cnt - cpycnt);
    json_buf->buffer = buff;
    return json_buf;
}
