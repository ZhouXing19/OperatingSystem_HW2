#include"list.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct hash_t{
  int buckets;
  struct list_t** list;
}hash_t;
 
void Hash_Init(hash_t *hash, int buckets){
  hash->buckets = buckets;
  hash->list = (list_t**)malloc(buckets*sizeof(list_t*));
  for(int i=0; i<buckets; i++){
    hash->list[i] = (list_t*)malloc(sizeof(list_t));
    List_Init(hash->list[i]);
  }
}

void Hash_Insert(hash_t *hash, void *element, unsigned int key){
  List_Insert(hash->list[key%hash->buckets], element, key);
}

void Hash_Delete(hash_t *hash, unsigned int key){
  List_Delete(hash->list[key%hash->buckets], key);
}

void *Hash_Lookup(hash_t *hash, unsigned int key){
  void* element = List_Lookup(hash->list[key%hash->buckets], key);
  return element;
}