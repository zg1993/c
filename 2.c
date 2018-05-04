#include<stdio.h>

int MaxSubsequenceSum2(const int A[], int N)
{
  int ThisSum, MaxSum, j;
  ThisSum = MaxSum = 0;
  for(j=0; j<N; j++)
    {
      ThisSum += A[j];
      if (ThisSum > MaxSum)
	MaxSum = ThisSum;
      else if (ThisSum < 0)
	ThisSum = 0;
      
    }
  return MaxSum;
}

int MaxSubsequenceSum(const int A[], int N)
{
  int ThisSum, MaxSum, i, j, k;
  MaxSum = 0;
  for(i=0; i<N; i++)
    for(j=i; j<N; j++)
      {
	ThisSum = 0;
	for(k=i; k<=j; k++)
	  ThisSum += A[k];  
	if(ThisSum > MaxSum)
	  MaxSum = ThisSum;
	printf("-----------------------%d\n", MaxSum);
      }
  return MaxSum;
}

int Max3(int a, int b, int c)
{
  int max;
  max = a>b?a:b;
  max = max>c?max:c;
  return max;
}

int MaxSubSum(const int A[], int left, int right)
{
  int MaxleftSum, MaxrightSum;
  int MaxLeftBorderSum, MaxRightBorderSum;
  int LeftBorderSum, RightBorderSum;
  int Center, i;

  if(left == right)
    if(A[left] > 0)
      return A[left];
    else
      return 0;

  Center = (left+right)/2;
  MaxleftSum = MaxSubSum(A, left, Center);
  MaxrightSum = MaxSubSum(A, Center+1, right);

  MaxLeftBorderSum = 0; LeftBorderSum = 0;
  for(i=Center; i>=left; i--)
    {
      LeftBorderSum += A[i];
      if (LeftBorderSum > MaxLeftBorderSum)
	MaxLeftBorderSum = LeftBorderSum;
    }

  MaxRightBorderSum = 0; RightBorderSum = 0;
  for (i=Center+1; i<=right; i++)
    {
      RightBorderSum += A[i];
      if (RightBorderSum > MaxRightBorderSum)
	MaxRightBorderSum = RightBorderSum;
    }
  return Max3(MaxleftSum, MaxrightSum, MaxLeftBorderSum+MaxRightBorderSum);
}


int main()
{
  int sum, sum2;
  int A[6] = {-2, 11, -4, 13, -5, -2};
  printf("sizeof(a): %d", sizeof(A));
  sum = MaxSubsequenceSum2(A, 6);
  printf("%d, %d\n", sum,A[2]);
  sum2 = MaxSubSum(A, 0, 5);
  printf("sum2: %d\n", sum2);
  return 0;
}
