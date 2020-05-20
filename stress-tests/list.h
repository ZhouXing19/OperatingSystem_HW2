#ifndef LIST_H_
#define LIST_H_
#include "spin.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node_t{
  uint key;
  void* element;
  struct node_t *next;
}node_t;

typedef struct list_t{
  spinlock_t *lock;
  struct node_t *head;
}list_t;

node_t* create_node(uint key, void* element){
  struct node_t *node = (node_t*)malloc(sizeof(node_t));
  node->key = key;
  node->element = element;
  node->next = NULL;
  return node;
}

void List_Init(list_t *list){
  list->lock = (spinlock_t*)malloc(sizeof(spinlock_t));
  list->head = NULL;
}

void List_Insert(list_t *list, void *element, uint key){
  spinlock_acquire(list->lock);
  struct node_t *node = create_node(key, element);
  if(list->head == NULL){
    list->head = node;
    list->head->next = NULL;
  }
  else{
    node->next = list->head;
    list->head = node;
  }
  spinlock_release(list->lock);
}

void List_Delete(list_t *list, unsigned int key){
  spinlock_acquire(list->lock);
  struct node_t *cur;
  cur = list->head;
  if(cur == NULL) {
    spinlock_release(list->lock);
    return;
  }
  if(cur!= NULL && cur->key == key){
    list->head = cur->next;
    spinlock_release(list->lock);
    return;
  }
  while(cur->next!= NULL){
    if(cur->next->key == key){
      cur->next = cur->next->next;
      spinlock_release(list->lock);
      return;
    }
    else{
      cur = cur->next;
    }
  }
  spinlock_release(list->lock);
  return;
}

void *List_Lookup(list_t *list, unsigned int key){
  spinlock_acquire(list->lock);
  struct node_t *cur;
  cur = list->head;
  while(cur != NULL){
    if(cur->key == key){
      spinlock_release(list->lock);
      return cur->element;
    }
    else{
      cur = cur->next;
    }
  }
  spinlock_release(list->lock);
  return NULL;
}
#endif