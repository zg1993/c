#include <stdio.h>
#include <stdlib.h>

#define random(x) (rand()%x)


void insert_sorted(int arrary[], unsigned int N)
{
    int p, i, temp;

    for (i=1; i<N; i++)
    {
        temp = arrary[i];
        printf("i:%d\n", i);
        for(p=i-1; p>=0 && temp<arrary[p]; p--)
        {
            printf("p:%d\n", p);
            arrary[p+1] = arrary[p];
        }
        arrary[p+1] = temp;
    }
}


void print_arrary(int arrary[], int N)
{
    int i;
    for(i=0; i<N; i++)
        printf("%d ", arrary[i]);
    printf("\n");
}


void random_arrary(int arrary[], int N)
{
    int i;
    for (i=0; i<N; i++)
        arrary[i] = random(100);
}


int main()
{
    int arrary[10] = {};
    random_arrary(arrary, 10);
    print_arrary(arrary, 10);
    insert_sorted(arrary, 10);
    print_arrary(arrary, 10);
    return 0;
    
}
