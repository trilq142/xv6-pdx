#ifdef CS333_P2
#include "types.h"
#include "user.h"

#define UPROCS_MAX 64 // 1 16 64 72

int
main(void)
{
  int millisec, num_uprocs,  max = UPROCS_MAX;
  struct uproc* table = malloc(sizeof(struct uproc) * max);
  struct uproc *begin, *end;

  if (!table) {
    printf(2, "malloc failed in ps.c\n\n");
    exit();
  }
  
  num_uprocs = getprocs(max, table);

  if (num_uprocs < 0) {
    printf(2,"Error retrieving info for processes.\n");
    free(table);
    exit();
  }
  
  printf(1,"PID\tName\tUID\tGID\tPPID\tElapsed\tCPU\tState\tSize\n");

  begin = table;
  end = table + num_uprocs;
  while (begin < end) {
    printf(1,"%d\t%s\t%d\t%d\t%d\t", begin->pid,
         begin->name,begin->uid,begin->gid,begin->ppid);
//    print_millisec(begin->elapsed_ticks);
    millisec = begin->elapsed_ticks;
    printf(1,"%d.", millisec /1000);

    millisec %= 1000;
    if (millisec < 100)
      printf(1,"0");
    if (millisec < 10)
      printf(1,"0");

    printf(1,"%d\t", millisec);
    millisec = begin->CPU_total_ticks;
    printf(1,"%d.", millisec /1000);

    millisec %= 1000;
    if (millisec < 100)
      printf(1,"0");
    if (millisec < 10)
      printf(1,"0");

    printf(1,"%d\t", millisec);
    printf(1,"%s\t%d\n",begin->state,begin->size);

    ++begin;
  }

  free(table);
  exit();
}
#endif
