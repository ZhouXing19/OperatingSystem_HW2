typedef unsigned int uint;

static inline uint
xchg(volatile uint *addr, uint newval)
{
    uint result;
    asm volatile("lock; xchgl %0, %1" : "+m" (*addr), "=a" (result) : "1" (newval) : "cc");
    return result;
}

typedef struct spinlock_t{
  volatile uint flag;
} spinlock_t;

void  spinlock_acquire(spinlock_t *lock){
  while(xchg(&lock->flag, 1) == 1){
    // do nothing
  }
}

void spinlock_release(spinlock_t *lock){
  lock->flag = 0;
}
