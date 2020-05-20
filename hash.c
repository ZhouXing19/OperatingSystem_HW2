#include "list.h"

typedef struct hash_t{
  int buckets;
  struct list_t** list;
  spinlock_t *lock;
}hash_t;
 
void Hash_Init(hash_t *hash, int buckets){
  hash->buckets = buckets;
  hash->list = (list_t**)malloc(buckets*sizeof(list_t));
  for(int i=0; i<buckets; i++){
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