
#include "hashmap.h"
#include "string.h"
h_NODE *init_h_node(h_NODE *node)
{
    node = malloc(sizeof(h_NODE));
    node->value = 0;
    node->key = 0;
    node->next = 0;
    return node;
}
void h_add(BUCKET *table,BYTE *key,char *value)
{
    UINT keylen = strlen(key);
    BYTE hash[30];
    SHA256_Encrpyt(key,keylen,hash);
    h_NODE *newNode = init_h_node(newNode);
    newNode->value = value;
    newNode->key = hash;

    newNode->prev = table->tail->prev;
    newNode->next = table->tail;
    table->tail->prev->next = newNode;
    table->tail->prev = newNode;
    table->count++;

}

uint32_t hashcode(const char *str);
uint64_t hashcode_64(const char *str);

