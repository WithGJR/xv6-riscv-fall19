#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int parent_fd[2];
  int child_fd[2];
  char buf[1];

  pipe(parent_fd);
  pipe(child_fd);

  if (fork() == 0)
  {
    read(parent_fd[0], buf, 1);
    printf("%d: received ping\n", getpid());
    buf[0] = 'c';
    write(child_fd[1], buf, 1);
  } else 
  {
    buf[0] = 'p';
    write(parent_fd[1], buf, 1);
    read(child_fd[0], buf, 1);
    printf("%d: received pong\n", getpid());
  }
  
  exit();
}
