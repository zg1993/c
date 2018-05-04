#include <stdio.h>
#include "print.h"

void print11(int *a, int n)
{
    int i;
    for (i=0; i<n; i++)
        printf("%d ", a[i]);
    printf("\n");
}
