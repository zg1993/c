#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "print.h"


int partition(int a[], int left, int right)
{
    int i = left;
    int j = right;
    int temp = a[i];
    while(i != j)
    {
        while(i < j && a[j] >= temp)
            j--;
        if (i < j)
            a[i] = a[j];
        while(i < j && a[i] <= temp)
            i++;
        if (i < j)
            a[j] = a[i];
    }
    
    printf("i: %d j: %d\n", i, j);
    print11(a, 10);
    a[i] = temp;
    return i;
}


void quicksorted(int a[], int left, int right)
{
    if (left < right)
    {
        int flag = partition(a, left, right);
        printf("flag: %d\n", flag);
        quicksorted(a, left, flag-1);
        quicksorted(a, flag+1, right);
    }
}


int main()
{
    int a[10];
    int i;
    printf("sizeof(a): %d\n", sizeof(a));
    memset(a, 0, sizeof(a));
    for (i=0; i<10; i++)
        a[i] = rand()%100;
    print11(a, 10);
    quicksorted(a, 0, 9);
    return 0;
    
}
