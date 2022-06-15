#include <stdio.h>
#include <string.h>

#include "SHA256/KISA_SHA256.h"
typedef unsigned char BYTE;
typedef unsigned int UINT;

int main__()
{
  BYTE pong[32];
  BYTE nong[32];
  UINT pong_len = 0;
  int i=0;

  memset(pong,0x00,sizeof(pong));
  memset(nong,0x00,sizeof(nong));

  printf("평문 : ");

  gets(pong);
  pong_len = strlen(pong);

  SHA256_Encrpyt(pong,pong_len,nong);

  printf("해쉬데이터 : ");

  for(i = 0;i<32;i++)
  {
    printf("%02X",nong[i]);
  }
  printf("\n");

}
