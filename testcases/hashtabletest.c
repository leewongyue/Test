
#include <string.h>
#include "datastructure/hashtable.h"

int main___()
{
  HASHTABLE *table = init_bucket(table);
  for(int i=0;i<1000000;i++)
  {
    h_add(table,i,"hello");
  }
  h_add(table,10000000,"helo");
  h_add(table,120000000,"halo");

  search(table,100);
  search(table,120);
  delete_key(table,120);
  search(table,120);
  for(int i=0;i<16;i++)
  {
    search(table,i);
  }
}
