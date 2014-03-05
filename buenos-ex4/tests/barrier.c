/* Barrier test.
 *
 * Use two semaphores to create a barrier for two processes.  Use another
 * semaphore as a lock to read and write atomically.
 */

#include "tests/lib.h"

#define VOLUME "[arkimedes]"

int main(void) {
  usr_sem_t *wait0, *wait1, *read_write_lock;
  uint32_t prog0, prog1;
  int ret0, ret1;

  /* Create the semaphores. */
  wait0 = syscall_sem_open("wait0", 0);
  wait1 = syscall_sem_open("wait1", 0);
  read_write_lock = syscall_sem_open("rwlock", 1);
  wait0 = wait0;
  wait1 = wait1;
  read_write_lock = read_write_lock;

  /* Run the childs. */
  prog0 = syscall_exec(VOLUME "prog0");
  prog1 = syscall_exec(VOLUME "prog1");

  /* Wait for them to finish. */
  ret0 = syscall_join(prog0);
  ret1 = syscall_join(prog1);
  printf("Childs joined with return values %d and %d.\n", ret0, ret1);

  syscall_halt();
  return 0;
}
