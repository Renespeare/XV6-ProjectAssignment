#ifdef CS333_P2
#include "types.h"
#include "user.h"

int
main(int argc, char * argv[])
{
  int timeIn = uptime();
  if(argc < 2)
  {
    printf(1, "(null) ran 0.000 seconds\n");
    exit();
  }
  
  int val = fork();
  if(val < 0){
    exit();
  }else if(val == 0){
    exec(argv[1], &argv[1]);
  }else if(val > 0){
    wait();
    int currTime = uptime();
    currTime = currTime - timeIn;
    int leftover = currTime % 1000;
    currTime /= 1000;
    if(leftover < 10)
      printf(1, "%s ran in %d.00%d seconds\n",argv[1], currTime, leftover);
    else if(leftover < 100 && leftover >= 10)
      printf(1, "%s ran in %d.0%d seconds\n", argv[1], currTime, leftover);
    else
      printf(1, "%s ran in %d.%d seconds\n", argv[1], currTime, leftover);
  }
    exit();
}

#endif