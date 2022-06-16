#include "jsonparser/jsonparser.h"

int main()
{
  char arr[BUFFERSIZE];
  file_read("/Users/leewongyu/Desktop/Test/jsonparser/packet.json",arr);
  printf("%s\n",arr);

  int len = strlen(arr);
  int cnt = 0;
  len -=5;
  //while (len !=cnt)
  //{
  //  write(1,&arr[cnt],1);
  //  cnt++;
  //}
  json_parser(arr,len);

}
