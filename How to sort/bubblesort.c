#include <stdio.h>
#include <stdlib.h>


void swap(int *a,int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


void bubblesort(int n, int *x){
    int i,j;
    for( i = 1; i <= n-1; i++)
        for ( j = n-1; j >= i; j--)
            if(x[j-1]> x[j])
                swap(&x[j-1], &x[j]);
}

//xronos poluplokothtas O(n^2)
//xoros : O(1)
