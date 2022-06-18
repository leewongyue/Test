
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
    char *sliced = malloc(sizeof(char) * e_index-s_index+2);
    while (s_index != e_index+1)
    {
        sliced[cnt] = buffer[s_index];
        cnt++;
        s_index++;
    }
    sliced[s_index] = '\0';
    return sliced;
}
void json_parser(char *buffer,int len)
{
  int depth = 0;
    int s_index = 0;
    int e_index = 0;
    int cnt = 0;
    int isdata = 0;

    while (buffer[cnt] != '\0')
    {
        if(s_index>0 && e_index>0)
        {
            char *data;
            switch (depth)
            {
                case 0:
                    data = slice_buff(buffer,s_index,e_index);
                    printf("[NODEDEPTH] : %d [DATA] : %s \n",depth,data);
                    data = 0;
                    free(data);
                    break;
                case 1:
                    data = slice_buff(buffer,s_index,e_index);
                    printf("[NODEDEPTH] : %d [DATA] : %s \n",depth,data);
                    data = 0;
                    free(data);
                    break;
                case 2:
                    data = slice_buff(buffer,s_index,e_index);
                    printf("[NODEDEPTH] : %d [DATA] : %s \n",depth,data);
                    data = 0;
                    free(data);
                    break;
                case 3:
                    data = slice_buff(buffer,s_index,e_index);
                    printf("[NODEDEPTH] : %d [DATA] : %s \n",depth,data);
                    data = 0;
                    free(data);
                    break;
            }
            s_index = 0;
            e_index = 0;
        }
        if(buffer[cnt] == '[' && buffer[cnt+1] == '{')
        {
            depth++;
        }
        if(buffer[cnt] == '}' && buffer[cnt+1] == ']')
        {
            depth--;
        }

        if(buffer[cnt] == '"')
        {
            if(buffer[cnt+1] == ':' && !(buffer[cnt+2] == '['))
            {
                isdata = 1;
            }
            if(isdata)
            {
                cnt+=2;
                cnt++;
                isdata = 0;
                continue;
            }
            else if(isdata == 0)
            {
                if(s_index >0)
                {
                    e_index = cnt;
                    cnt++;
                    continue;
                }
                s_index = cnt;
                cnt++;
                continue;
            }
        }
        cnt++;
    }
}

JSON_BUFF *del_ws(char *buffer,int len)
{
    JSON_BUFF *json_buf = malloc(sizeof(JSON_BUFF));
    int cnt = 0;
    int cpycnt = 0;
    char *buff = malloc(sizeof (char)*1024);
    while (buffer[cnt] != '\0')
    {
        if(buffer[cnt] =='\n'|| buffer[cnt] == ' ' || buffer[cnt] == '\r')
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

