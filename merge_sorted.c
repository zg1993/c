#include <stdio.h>
#include <stdlib.h>


void mergearrary(int *a, int first, int mid, int last, int *temp)
{
  int i = first, j = mid + 1;
  int m = mid, n = last;
  int k = 0;

  while (i <= m && j <= n)
    {
      if (a[i] <= a[j])
	temp[k++] = a[i++];
      else
	temp[k++] = a[j++];
    }
  
  while (i <= m)
    temp[k++] = a[i++];
  while (j <= n)
    temp[k++] = a[j++];
  for (i = 0; i < k; i++)
    a[first + i] = temp[i];
}

void mergesort(int *a, int first, int last, int *temp)
{
  if (first < last)
    {
      int mid = (first + last) / 2;
      mergesort(a, first, mid, temp);
      mergesort(a, mid+1, last, temp);
      mergearrary(a, first, mid, last, temp);
    }

}


int MergeSort(int a[], int n)
{
  // p int *p = malloc(sizeof(int)*n);
  int p[10]={};
  //  if (p == NULL)
    //    return 0;
  mergesort(a, 0, n-1, p);
  //  free(p);
  //  p = NULL;
  return 1;
}

void printf_arrary(int a[], int n)
{
  int i;
  for (i=0; i<n; i++)
    printf("%d ", a[i]);
  printf("\n");
}

int main()
{ 
  int a[10];
  int i;
  for (i=0; i<10; i++)
    a[i] = rand()%100;
  printf_arrary(a, 10);
  int result = MergeSort(a, 10);
  if (result == 0)
    printf("error\n");
  else
    printf_arrary(a, 10);
  return 0;
}
