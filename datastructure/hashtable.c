
#include "hashtable.h"
h_NODE *init_h_node(h_NODE *node)
{
    node = malloc(sizeof(h_NODE));
    node->value = 0;
    node->key = 0;
    node->next = 0;
    return node;
}

HASHTABLE *init_hashtable(HASHTABLE *bucket){
    bucket = malloc(MAX_BUCKET*sizeof(HASHTABLE));
    bucket->count = 0;
    bucket->head = 0;
    return bucket;
}

void h_add(HASHTABLE *table,uint32_t key,void *value)
{
    uint32_t hashIndex = uint_hash(key);

    h_NODE *newNode = init_h_node(newNode);
    newNode->value = value;
    newNode->key = key;

    if(table[hashIndex].count == 0)
    {
        table[hashIndex].count = 1;
        table->count++;
        table[hashIndex].head = newNode;
    }
    //else
    //{
    //    newNode->next = table[hashIndex].head;
    //    table[hashIndex].head = newNode;
    //    table[hashIndex].count++;
    //    table->count++;
    //}

}

void delete_key(HASHTABLE *table,uint32_t key)
{
    uint32_t index = uint_hash(key);
    h_NODE *node;

    node = table[index].head;
   if (node->key == key)
    {
      if (node == table[index].head)
      {
        //데이터 존재할 경우 메모리 해제
        free(node);
        return;
      }
    }else
    {
        //데이터 없을 경우
    }
}

uint32_t uint_hash(uint32_t a)
{
    a = (a+0x7ed55d16) + (a<<12);
    a = (a^0xc761c23c) ^ (a>>19);
    a = (a+0x165667b1) + (a<<5);
    a = (a+0xd3a2646c) ^ (a<<9);
    a = (a+0xfd7046c5) + (a<<3);
    a = (a^0xb55a4f09) ^ (a>>16);
    return a;
}

void *search_key(HASHTABLE *table,uint32_t key){
    uint32_t index = uint_hash(key);
    h_NODE* node = table[index].head;
    if (node->key == key)
    {
        //데이터 존재할 경우
      printf("\n key : [ %u ], value : [ %s ]\n", node->key, (char*)node->value);
      return node->value;
    }
    else
    {
        //데이터 없을 경우
    }
}
