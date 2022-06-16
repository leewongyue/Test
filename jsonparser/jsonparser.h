#ifndef JSONPARSER_H
#define JSONPARSER_H
#endif

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define BUFFERSIZE 1024

typedef struct JSON_BUFF
{
    char* buffer;
    int len;
}JSON_BUFF;

char *file_read(char*path,char*buffer);
void json_parser(char *buffer,int len);
char *slice_buff(char *buffer,int s_index,int e_index);
JSON_BUFF *del_ws(char *buffer,int len);
