#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertion_sort(int n, int *x){
    int i,j;
    for ( i = 1; i <= n-1; i++){
        j = j - 1;
        while(j>=0 && x[j] > x[j+1]){
            swap(&x[j],&x[j+1]);
            j--;
        }
    }
}