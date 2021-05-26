#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "uproc.h"

int
main(int argc, char * argv[]){
     int max = 72;

  if(argc > 1)
    max = atoi(argv[1]);

  struct uproc * table = malloc(sizeof(*table)*max);

  if(table == 0)
  {
    printf(1, "Unable to initialize table in ps.c\n");
    exit();
  }

    int process = getprocs(max, table);
    int curr_ticks;
    int curr_cpu;
    printf(1,"PID\tName\tUID\tGID\tPPID\tElapsed CPU\t State\tSize\n");
    if(process < 1)
    {
        free(table);
        printf(1, "Error\n");
    }

     for(int i = 0; i < process; i++)
  {
    printf(1, "%d\t%s\t%d\t%d\t%d\t", 
      table[i].pid, 
      table[i].name, 
      table[i].uid, 
      table[i].gid, 
      table[i].ppid);

    curr_ticks = table[i].elapsed_ticks;
    if (curr_ticks < 1000){
    if (curr_ticks >= 100){
      printf(1,"0.%d ", curr_ticks);
    }else{
      if (curr_ticks < 100){
        if (curr_ticks >= 10){
          printf(1,"0.0%d ", curr_ticks);
        }else{
          printf(1,"0.00%d ", curr_ticks);
        }
      }
    }
  }else{
    int ticks_left = curr_ticks / 1000;
    int ticks_right = curr_ticks % 1000;
    if (ticks_right >= 1 && ticks_right < 100){
      if (ticks_right >= 10){
        printf(1,"%d.0%d ",ticks_left, ticks_right);
      }else{
        printf(1,"%d.00%d ",ticks_left, ticks_right);
      }
    }else{
      printf(1,"%d.%d ",ticks_left, ticks_right);
    }
  }

    curr_cpu = table[i].CPU_total_ticks;
    if(curr_cpu < 1000){
    if (curr_cpu >= 100){
      printf(1,"\t0.%d ", curr_cpu);
    }else{
      if (curr_cpu < 100){
        if (curr_cpu >= 10){
          printf(1,"\t0.0%d ", curr_cpu);
        }else{
          printf(1,"\t0.00%d ", curr_cpu);
        }
      }
    }
    }else{
        int cpu_left = curr_cpu / 1000;
        int cpu_right = curr_cpu % 1000;
        if (cpu_right >= 1 && cpu_right < 100){
        if (cpu_right >= 10){
            printf(1,"\t%d.0%d ",cpu_left, cpu_right);
        }else{
            printf(1,"\t%d.00%d ",cpu_left, cpu_right);
        }
        }else{
            printf(1,"\t%d.%d ",cpu_left, cpu_right);
        }
    }
    printf(1, "\t%s", table[i].state);
    printf(1, "\t%d\n", table[i].size);
  } 
    free(table);
    exit();
}