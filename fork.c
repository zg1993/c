#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main()
{
  int pid;
  printf("start pid: %d\n", getpid());
  printf("ppid: %d\n", getppid());
  pid = fork();
  if (pid == 0){
    printf("child pid %d\n", getpid());
    printf("my father is %d\n", getppid());
    return 0;
    }
  printf("father pid is %d\n", getpid());
  printf("fork child is %d\n", pid);
  
  return 0;
}
