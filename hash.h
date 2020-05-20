#ifndef HASH_H_
#define HASH_H_

#include "list.h"
#include<stdio.h>

typedef struct hash_t{
  int buckets;
  struct list_t** list;
  spinlock_t *lock;
}hash_t;
 
void Hash_Init(hash_t *hash, int buckets){
  hash->buckets = buckets;
  hash->lock = (spinlock_t*)malloc(sizeof(spinlock_t));
  hash->list = (list_t**)malloc(buckets*sizeof(list_t*));
  for(int i=0; i<buckets; i++){
    hash->list[i] = (list_t*)malloc(sizeof(list_t));
    List_Init(hash->list[i]);
  }
}

void Hash_Insert(hash_t *hash, void *element, unsigned int key){
  spinlock_acquire(hash->lock);
  List_Insert(hash->list[key%hash->buckets], element, key);
  spinlock_release(hash->lock);
}

void Hash_Delete(hash_t *hash, unsigned int key){
  spinlock_acquire(hash->lock);
  List_Delete(hash->list[key%hash->buckets], key);
  spinlock_release(hash->lock);
}

void *Hash_Lookup(hash_t *hash, unsigned int key){
  spinlock_acquire(hash->lock);
  void* element = List_Lookup(hash->list[key%hash->buckets], key);
  spinlock_release(hash->lock);
  return element;
}
#endif