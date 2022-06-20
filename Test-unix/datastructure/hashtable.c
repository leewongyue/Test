
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
    bucket = malloc(sizeof(HASHTABLE));
    bucket->count = 0;
    bucket->head = 0;
    return bucket;
}

void h_add(HASHTABLE *table,uint32_t key,void *value)
{
    // printf("DEBUG : [TABLE]                     %p\n",table);
    // printf("DEBUG : [TABLE->HEAD ADDRESS]       %p\n",table->head);
    // printf("=========================================================\n\n");
    uint32_t hashIndex = uint_hash(key);
    // printf("DEBUG : [TABLE->HEAD ADDRESS]       %p\n",table->head);
    if(table[hashIndex].count==1)
    {
    // printf("DEBUG : [TABLE]                     %p\n",table);
    // printf("DEBUG : [TABLE->HEAD ADDRESS]       %p\n",table->head);
    // printf("=========================================================\n\n");
        table->count++;
        return ;
    }
    h_NODE *newNode = malloc(sizeof(h_NODE));
    newNode->next = NULL;
    newNode->value = value;
    newNode->key = key;
    // printf("DEBUG : [NEWNODE]                  %p\n",newNode);
    // printf("=========================================================\n\n");

    // printf("DEBUG : [TABLE[HASHINDEX]]         %p\n",table[hashIndex]);
    // printf("DEBUG : [TABLE[HASHINDEX].head]    %p\n",table[hashIndex].head);
    // printf("=========================================================\n\n");
    if(table[hashIndex].count == 0)
    {
        table[hashIndex].count = 1;
        table[hashIndex].head = newNode;
    // printf("DEBUG : [TABLE[HASHINDEX]]         %p\n",table[hashIndex]);
    // printf("DEBUG : [TABLE[HASHINDEX].head]    %p\n",table[hashIndex].head);
    // printf("=========================================================\n\n");
    }
    // table->count++;
    // printf("DEBUG : [TABLE cnt]                %d\n",table->count);
    // else
    // {
    //    newNode->next = table[hashIndex].head;
    //    table[hashIndex].head = newNode;
    //    table[hashIndex].count++;
    //    table->count++;
    // }

}

void delete_key(HASHTABLE *table,uint32_t key)
{
    uint32_t index = uint_hash(key);
    h_NODE *node = table[index].head;

    if (node->key == key)
    {
      if (node == table[index].head)
      {
        //데이터 존재할 경우 메모리 해제
        printf("DEBUG : DELETE_DATA :              %p\n",table[index].head->value);
        node->key = NULL;
        node->value = NULL;
        node = NULL;
        table[index].count = 0;
        free(node);
        
        printf("DEBUG : DELETE_AFTER_DATA_POINTER :%p\n",table[index].head->value);
        return;
      }
    }else
    {
        printf("DEBUG : 데이터 존재하지 않음 :      %p\n",table[index].head->value);
    }
        printf("=========================================================\n\n");
}

uint32_t uint_hash(uint32_t a)
{
    a = (a+0x7ed55d16) + (a<<12);
    a = (a^0xc761c23c) ^ (a>>19);
    a = (a+0x165667b1) + (a<<5);
    a = (a+0xd3a2646c) ^ (a<<9);
    a = (a+0xfd7046c5) + (a<<3);
    a = (a^0xb55a4f09) ^ (a>>16);
    a = a>>4;
    return a;
    // return a%3000000000ul;
    // return ((a*1548954)* a) % (3000000000ul/2);
}

void *search_key(HASHTABLE *table,uint32_t key){
    uint32_t index = uint_hash(key);
    h_NODE* node =table[index].head;
    if (node->key == key)
    {
      printf("\n key : [ %u ], value : [ %s ]\n", node->key, (char*)node->value);
      return (node->value);
    }
    printf("DEBUG : DATA NOT FOUND :      %p\n",table[index].head->value);
    return NULL;
}