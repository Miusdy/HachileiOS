// dmesg: print the kernel log ring buffer.
//
// The klog() syscall takes an in/out cursor so we can drain the ring a
// chunk at a time without the kernel having to remember any per-process
// state.

#include "kernel/types.h"
#include "user/user.h"

#define CHUNK 512

// Draining the whole ring takes at most KLOGSIZE/CHUNK rounds (the ring
// is 16 KB in kernel/printk.c); a few times that is plenty and, unlike
// looping until an empty read, guarantees we terminate even while the
// kernel is still logging.
#define MAXROUNDS 64

int
main(int argc, char *argv[])
{
  char buf[CHUNK];
  uint64 seq = 0, lost, total_lost = 0;
  int i, n;

  for (i = 0; i < MAXROUNDS; i++) {
    n = klog(buf, sizeof(buf), &seq, &lost);
    if (n < 0) {
      fprintf(2, "dmesg: klog failed\n");
      exit(1);
    }
    total_lost += lost;
    if (n == 0)
      break;
    if (write(1, buf, n) != n) {
      fprintf(2, "dmesg: write failed\n");
      exit(1);
    }
  }

  if (total_lost)
    printf("\n[dmesg: %ld bytes of older log were overwritten]\n", total_lost);

  exit(0);
}
