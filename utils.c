#include<stdio.h>
//#include "utils.h"

int Gcd(unsigned int N, unsigned int M)
{
  unsigned int Rem;
  while(N > 0)
    {
      Rem = M%N;
      M = N;
      N = Rem;
    }
  return M;
}

int isEven(unsigned int n)
{
  return (n%2)?0:1;
}


long pow(unsigned int x, unsigned int n)
{
  if (n==0)
    return 1;
  if (n==1)
    return x;
  if (isEven(n))
    return pow(x*x, n/2);
  else
    return pow(x*x, n/2)*x;
}

int hash(const char *Key, int TableSize)
{
  return ( Key[0] + 27 *Key[1] + 729*Key[2]) % TableSize;
  
}


int hash1(const char *Key, int TableSize)
{
  unsigned int HashVal = 0;
  while(*Key != '\0')
    HashVal += (HashVal << 5) + *Key++;
  return HashVal%TableSize;

}


int prime(int n)
{
  int i;
  if ( n % 2 == 0)
    n++;
  for(; ; n += 2)
    {
      for (i = 3; i*i <= n; i += 2)
	if (n % i == 0)
	  continue;
      return n;
    }
}
