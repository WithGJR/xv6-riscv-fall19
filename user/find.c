#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char *file_name(char *path)
{
  char *p = path + strlen(path);
  while (*p != '/' && p >= path)
  {
    p--;
  }
  p++;
  return p;
}

void find(char *path, char *name) 
{
  int fd;
  struct dirent directory_entry;
  struct stat st;
  char buf[512];
  char *p;

  strcpy(buf, path);
  p = buf + strlen(buf);
  *p++ = '/';

  if ((fd = open(path, 0)) < 0)
  {
    fprintf(2, "find: cannot open %s %d\n", path, fd);
    return;
  } 

  if (fstat(fd, &st) < 0)
  {
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }
  
  switch (st.type)
  {
  case T_FILE:
    if (strcmp(file_name(path), name) == 0)
    {
      printf("%s\n", path);
    }
    close(fd);
    
    break;
  case T_DIR:
    while (read(fd, &directory_entry, sizeof(directory_entry)) == sizeof(directory_entry))
    {
      if (directory_entry.inum == 0)
      {
        continue;
      }
      if (strcmp(directory_entry.name, ".") == 0)
      {
        continue;
      }
      if (strcmp(directory_entry.name, "..") == 0)
      {
        continue;
      }
       
      strcpy(p, directory_entry.name);
      find(buf, name);
    }
    close(fd);
    break;

  default:
    break;
  }
  
}

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    printf("error\n");
  } else 
  {
    find(argv[1], argv[2]); 
    // printf("%d\n",  open("./sh", 0));
  }
    
  exit();
}
