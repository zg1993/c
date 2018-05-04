#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

void handler(){
  printf("hello");
}


int main()
{
  int i;
  //  signal(SIGALRM, handler);
  //  alarm(0);
  char *a = "aaf asfa 1 asd fas";
  char *s = "afsd ajfdl aslf afjs;alo";
  char *delim;
  printf("%s\n", a);
  char c = 'f';
  char *p;
  char *argv[10];
  p = strchr(a, c);
  a = p+1;
  *p = '\0';
  printf("p: %s\n", p+1);
  printf("a: %s\n", a);
  int argc = 0;
  while ((delim = strchr(s, ' ')))
    {
      argv[argc++] = s;
      *delim = '\0';
      s = delim + 1;
      printf("%d\n", argc);
      while (*s && (*s == ' '))
	s++;
    }
  argv[argc] = NULL;
  printf("argv[0]: %s\n", argv[0]);
  for (i=0; i<7; i++)
    {
      printf("sleep %d...\n", i);
      //  sleep(1);
    }
  return 0;
}
