#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("sleep: operand omitted\n");
  } else {
    int ticks = atoi(argv[1]);
    sleep(ticks);
  }

  exit();
}
