// Lab 3: user-level thread library.
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/riscv.h"   // PGSIZE
#include "user/user.h"
#include "user/thread.h"

// Create a new thread that runs start_routine(arg) on its own
// PGSIZE-byte user stack. Returns 0 to the caller on succes if fail -1
// The new thread calls exit() when start_routine returns.
int
thread_create(void*(start_routine)(void*), void* arg) {
  void* stack = malloc(PGSIZE);
  if (stack == 0)
    return -1;

  int pid = clone(stack);
  if (pid < 0) {
    free(stack);
    return -1;
  }

  if (pid == 0) {
    start_routine(arg);
    exit(0);
  }
  return 0;
}

void
lock_init(struct lock_t* lock) {
  lock->locked = 0;
}

void
lock_acquire(struct lock_t* lock) {
  while (__sync_lock_test_and_set(&lock->locked, 1) != 0);
  __sync_synchronize();
}

void
lock_release(struct lock_t* lock) {
  __sync_synchronize();
  __sync_lock_release(&lock->locked);
}
