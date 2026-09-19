// free: report how much physical memory is free, using the freemem()
// system call, which returns the number of free bytes.

#include "kernel/types.h"
#include "kernel/minios.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  uint64 avail = freemem();
  uint64 used = MINIOS_MEM_TOTAL - avail;
  uint64 pct = avail * 100 / MINIOS_MEM_TOTAL;

  printf("         total        used        free\n");
  printf("bytes  %ld  %ld  %ld\n", MINIOS_MEM_TOTAL, used, avail);
  printf("KB     %ld  %ld  %ld\n", MINIOS_MEM_TOTAL / 1024, used / 1024,
         avail / 1024);
  printf("pages  %ld  %ld  %ld\n", MINIOS_MEM_TOTAL / 4096, used / 4096,
         avail / 4096);
  printf("%ld%% of physical memory is free\n", pct);

  exit(0);
}
