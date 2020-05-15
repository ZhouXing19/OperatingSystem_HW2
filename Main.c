#include <stdlib.h>
#include <stdio.h>

typedef unsigned int uint;

static inline uint
xchg(volatile uint *addr, uint newval)
{
    uint result;
    asm volatile("lock; xchgl %0, %1" : "+m" (*addr), "=a" (result) : "1" (newval) : "cc");
    //xchg: exchange the two source operands
    //two outputs: *addr and result
    //"+m", m means the operand is directly from memory, + means read and write
    //"=a": suggest gcc to put the operand value into eax register; `=' means write only
    //one input: newval, "1" means it uses the same constraint as the earlier 1th, i.e., it 
    // will be put into eax and then be overwritten
    //"cc" means the condition register might be altered
    return result;
}

typedef struct spinlock_t{
  volatile uint flag;
} spinlock_t;

void  spinlock_acquire(spinlock_t *lock){
  while(xchg(&lock->flag, 1) == 1){
    //wait()
  }
  // else{
  //   printf("lock is acquired.\n");
  // }
}

void spinlock_release(spinlock_t *lock){
  lock->flag = 0;
}

int main(){
  struct spinlock_t lock;
  spinlock_acquire(&lock);
  printf("after acquired lock, flag is %d\n", lock.flag);
  spinlock_release(&lock);
  printf("after release lock, flag is %d\n", lock.flag);
}