#include<stdio.h>
#include "utils.h"


//extern int Gcd(unsigned int N, unsigned int M);

void PrintOut(unsigned int N)
{
    if (N >= 10)
      PrintOut(N/10);
    printf("%d", N%10);
    }


int relatively_prime(unsigned int N)
{
  unsigned int Rel, Tot;
  int i, j;
  Rel = Tot = 0;
  for(i=1; i<=N; i++)
    for (j=i+1; j<=N; j++)
    {      
      Tot++;
      if (Gcd(i, j) == 1)
	Rel++;
    }
  printf("Ret: %d Tot: %d\n", Rel, Tot);
  printf("relatively_prime: %f\n", (double)Rel/Tot);
  return (Rel/Tot);
}

// long pow(unsigned int x, unsigned int n);

struct Test
{
  int a;
  char b;
};

int main()
{
  int TableSize = 10007;
  char s[19];
  int x;
  scanf("%d", &x);
  
  printf("%d\n", prime(x));
  printf("hash: %d\n", hash1(s, TableSize));
    //  int enter;

  printf("m^n: %d\n", (int) pow(10, 8));
  scanf("%d", &enter);
  //relatively_prime(enter);
    return 0;
    }
