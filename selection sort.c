#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int n, int*x){
    int i, j, min;
    for(i = 1; i <= n-1; i++)
        min = i - 1;
        for (j=i; j <= n-1; j++)
            if(x[j]<x[min])
                min = j;
        swap(&x[i-1],&x[min]);
}
//Χρόνος πολυπλοκοτητας O(n^2)
//Χώρος πολυπλοκοτητας O(1)