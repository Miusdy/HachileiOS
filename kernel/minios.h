// System-wide constants that both the kernel and user programs need.
//
// Include this after a header that defines uint64 (e.g. kernel/types.h).

#ifndef XV6_MINIOS_H
#define XV6_MINIOS_H

// Total physical RAM the kernel manages.  Must match PHYSTOP - KERNBASE
// in kernel/memlayout.h; memlayout.h itself is not includable from user
// space because it references MAXVA from riscv.h.
#define MINIOS_MEM_TOTAL ((uint64)128 * 1024 * 1024)

#endif // XV6_MINIOS_H
