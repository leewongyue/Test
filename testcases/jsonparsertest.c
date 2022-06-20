#include "packetgenerator/jsonparser.h"

int main_____()
{
  char arr[BUFFERSIZE];
  file_read("/Users/leewongyu/Desktop/Test/packet.json",arr);
  printf("%s\n",arr);

  int len = strlen(arr);
  int cnt = 0;
  len -=5;

  JSON_BUFF* json =  del_ws(arr,len);
  //while (json->buffer[cnt] !='\0')
  //{
  //  write(1,&json->buffer[cnt],1);
  //  cnt++;
  //}
  json_parser(json->buffer,json->len);


}
