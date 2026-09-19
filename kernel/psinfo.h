// Process information exported to user space for observability
// (the ps/top programs).  This header is included by BOTH kernel and
// user code, so the layout must be identical in both worlds.  It relies
// on fixed-width types (int = 4 bytes, uint64 = 8 bytes on rv64) and on
// explicit padding, and it must be included after a header that defines
// uint64 (kernel/types.h or user/user.h via kernel/types.h).

#ifndef XV6_PSINFO_H
#define XV6_PSINFO_H

// Must equal sizeof(((struct proc *)0)->name) in kernel/proc.h.
#define PINFO_NAME 16

// Mirror of enum procstate in kernel/proc.h.  Kept as plain #defines so
// user code does not need to include kernel/proc.h (which drags in the
// whole kernel process structure).
#define PSTATE_UNUSED   0
#define PSTATE_USED     1
#define PSTATE_SLEEPING 2
#define PSTATE_RUNNABLE 3
#define PSTATE_RUNNING  4
#define PSTATE_ZOMBIE   5

struct psinfo {
  int pid;               // process id
  int ppid;              // parent process id (0 if none)
  int state;             // one of the PSTATE_* values above
  int _pad;              // explicit padding; keeps sz 8-byte aligned
  uint64 sz;             // virtual memory size in bytes, NOT resident set size
  uint64 u_ticks;        // timer ticks charged while in user mode
  uint64 k_ticks;        // timer ticks charged while in supervisor mode
  char name[PINFO_NAME]; // process name, always NUL-terminated
};

// psinfo() snapshots one struct psinfo per process slot into a single
// kalloc page, so NPROC * sizeof(struct psinfo) must fit in a page.
// kernel/proc.c enforces this at compile time.  sizeof is currently 56
// bytes (56 * NPROC(64) = 3584 <= PGSIZE); one more 8-byte field would
// land exactly on 4096 and still fit, but nothing may follow it.

#endif // XV6_PSINFO_H
