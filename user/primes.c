#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int p[2];
  pipe(p);
  
  if (fork() == 0)
  {
    close(p[1]);
    int prime;
    int n;
start:    
    n = read(p[0], &prime, sizeof(int));
    if (n == 0)
    {
      exit();
    }
    
    printf("prime %d\n", prime);

    int p2[2];
    pipe(p2);

    if (fork() == 0)
    {
      close(p[0]);
      p[0] = p2[0];
      goto start;
    } else
    {
      int number;
      while ((n = read(p[0], &number, sizeof(int))) > 0)
      {
        if (number % prime != 0)
        {
          write(p2[1], &number, sizeof(int));
        }
      }
      
    }
  } else 
  {
    for (int n = 2; n <= 35; n++)
    {
        write(p[1], &n, sizeof(int));
    }
  }

  exit();
}
