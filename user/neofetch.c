// neofetch: a one-shot summary of the running system.

#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/psinfo.h"
#include "kernel/minios.h"
#include "user/user.h"

static struct psinfo procs[NPROC];

int
main(int argc, char *argv[])
{
  int n, i, nproc = 0;
  uint64 free_mem;

  n = psinfo(procs, NPROC);
  if (n < 0) {
    fprintf(2, "neofetch: psinfo failed\n");
    exit(1);
  }
  for (i = 0; i < n; i++)
    if (procs[i].state != PSTATE_UNUSED)
      nproc++;

  free_mem = freemem();

  printf("     +------------------------------+\n");
  printf("     |    m i n i O S   x v 6       |\n");
  printf("     |    riscv64  .  rv64gc        |\n");
  printf("     +------------------------------+\n");
  printf("\n");
  printf("   user      : user\n");
  printf("   os        : miniOS on xv6-riscv\n");
  printf("   arch      : riscv64 (rv64gc)\n");
  printf("   cpus      : %d (NCPU maximum)\n", NCPU);
  printf("   memory    : %ld MB total, %ld KB free\n",
         MINIOS_MEM_TOTAL / (1024 * 1024), free_mem / 1024);
  printf("   processes : %d\n", nproc);
  printf("   uptime    : %d ticks\n", uptime());
  printf("\n");

  exit(0);
}
