#include <stdio.h>
#include <stdlib.h>


#define N 4 


void swap(int *x,int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}


void print_array(int array[],int N){
    for(int i = 0; i< N; i++){
        printf("%d\n",array[i]);
    }
    printf("\n");
}

void quicksort(int *x,int lower,int upper){
    if(lower < upper){
        int pivot = (x[(lower + upper) / 2]);
        int i,j;
        for( i = lower, j = upper; i<=j;){
            while(x[i] < pivot){
                i++;
            }
            while(x[j] > pivot){
                j--;
            }
        if(i <= j){
            swap(&x[i++],&x[j--]);
        }
        }
        quicksort(x,lower,j);
    quicksort(x,i,upper);
    }
}

void transpose(int A[][N],int B[][N])
{
    int i,j;
    for(i=0; i< N; i++){
        for(j = 0; j< N; j++){
            B[i][j] = A[j][i];
        }
    }
}


int main(){
    int A[N][N] = {{1,1,1,1},
                        {2,2,2,2},
                        {3,3,3,3},
                        {4,4,4,4} };
    int B[N][N],i,j;

    transpose(A,B);

    printf("Result matrix is: \n");
    for( i = 0; i< N; i++){
        for(j = 0; j < N; j++){
            printf("%d ",B[i][j]);
        
        }
    printf("\n");

    }
    return 0;
}