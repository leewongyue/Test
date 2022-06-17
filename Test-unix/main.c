#include "datastructure/hashtable.h"
#include <Windows.h>
int main()
{
  HASHTABLE *table = malloc((sizeof(HASHTABLE)*3000000000ul));
  table->count=0;
  table->head=NULL;
  // Sleep(5000);
  for(uint32_t i=0;i<1000;i++)
  {
    printf("[value] : %ul [hashvalue] : %u \n",i,uint_hash(i));
  }

  h_add(table,1,"hello");
  h_add(table,2,"hello");
  for(int i=0;i<100000;i++)
  {
    h_add(table,i,"hello");
  }
   printf("Collision cnt : %d\n",table->count);
  for(int i=1;i<10;i++)
  {
    search_key(table,i);
  }
  delete_key(table,100);
  search_key(table,120);
  search_key(table,100);
  h_add(table,100,"hello");
  search_key(table,100);
  printf("Collision cnt : %d\n",table->count);
//   Sleep(5000);
//   free(table);
//   Sleep(20000);
}
