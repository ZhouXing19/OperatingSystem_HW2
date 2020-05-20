#include "spin.h"

typedef struct counter_t{
  int value;
  spinlock_t lock;
} counter_t;

void Counter_Init(counter_t *c, int value){
  c->value = value;
  c-> lock.flag = 0;
}

int Counter_GetValue(counter_t *c){
  spinlock_acquire(&(c->lock));
  spinlock_release(&(c->lock));
  return c-> value;
}

void Counter_Increment(counter_t *c){
  spinlock_acquire(&(c->lock));
  c->value += 1;
  spinlock_release(&(c->lock));
}

void Counter_Decrement(counter_t *c){
  spinlock_acquire(&(c->lock));
  c->value -= 1;
  spinlock_release(&(c->lock));
}



