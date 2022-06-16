#include "datastructure/hashtable.h"

int main()
{
  HASHTABLE *table = init_hashtable(table);
  for(int i=0;i<1000000;i++)
  {
    h_add(table,i,"hello");
  }
  h_add(table,10000000,"helo");
  h_add(table,120000000,"halo");

  search_key(table,100);
  search_key(table,120);
  delete_key(table,120);
  search_key(table,120);
  for(int i=0;i<16;i++)
  {
    search_key(table,i);
  }
}
