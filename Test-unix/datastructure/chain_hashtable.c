
#include "chain_hashtable.h"



ch_NODE *init_ch_node(ch_NODE *node)
{
    node = malloc(sizeof(ch_NODE));
    node->value = 0;
    node->key = 0;
    node->next = 0;
    return node;
}

C_HASHTABLE *init_c_hashtable(C_HASHTABLE *bucket){
    bucket = malloc(sizeof(C_HASHTABLE)*3000000000ul);
    bucket->count = 0;
    bucket->head = 0;
    return bucket;
}

void ch_add(C_HASHTABLE *table,uint32_t key,void *value)
{
    uint32_t hashIndex = c_uint_hash(key);
    ch_NODE *newNode = malloc(sizeof(ch_NODE));
    newNode->next = NULL;
    newNode->value = value;
    newNode->key = key;
    if(table[hashIndex].count == 0)
    {
        table[hashIndex].count = 1;
        table[hashIndex].head = newNode;
        table[hashIndex].head = newNode;
    }
    else
    {
       newNode->next = table[hashIndex].head;
       table[hashIndex].head = newNode;
       table[hashIndex].count++;
       table->count++;
       table->col_cnt++;
    }

}

void c_delete_key(C_HASHTABLE *table,uint32_t key)
{
    uint32_t index = uint_hash(key);
    ch_NODE *node = table[index].head;

    if (node->key == key)
    {
      if (node == table[index].head)
      {

        while (node != NULL)
        {
            
        }
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
        printf("DEBUG : DATA NOT FOUND:           %p\n",table[index].head->value);
    }
        printf("=========================================================\n\n");
}

uint32_t c_uint_hash(uint32_t a)
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

void *c_search_key(C_HASHTABLE *table,uint32_t key){
    uint32_t index = uint_hash(key);
    ch_NODE* node =table[index].head;

    if(node->key == key)
    {
        while (node != NULL)
        {
            printf("\n key : [ %u ], value : [ %s ]\n", node->key, (char*)node->value);
            node = node->next;
        }
    }
    else
    {
        printf("DEBUG : DATA NOT FOUND :      %p\n",table[index].head->value);
        return NULL;
    }
}
