#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int n;
  char buf[1];
  char line[512];
  char *args[MAXARG];
  int i = 0;
  int argv_index;
  int args_index;
  int init_args_bound;

  if (argc < 2)
  {
    printf("error\n");
    exit();
  }

  args_index = 0;
  // push initial arguments into args   
  for (argv_index = 1; argv_index < argc; argv_index++)
  {
    args[args_index++] = argv[argv_index];
  }
  init_args_bound = args_index - 1;

  char *arg = line;

  for(;;)
  {
    n = read(0, buf, 1);
    if (n == 0)
    {
        break;
    }

    if (buf[0] == ' ' || buf[0] == '\n')
    {
      // push into args
      line[i++] = 0;
      args[args_index++] = arg;
      arg  = &line[i];

      if (buf[0] == ' ')
      {
        continue;
      }
    }

    if (buf[0] == '\n')
    {
      args[args_index] = 0;
      if (fork() == 0)
      {
        exec(argv[1], args);
        printf("exec failed\n");
      } else
      {
        wait();
      }
    
      i = 0;
      arg = line;
      args_index = init_args_bound + 1;
      continue;
    }
    
    line[i++] = buf[0];
  }
  
  exit();
}
