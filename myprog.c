#include <stdio.h>

void badf(int x, int y, int sum, int diff){
    sum = x+y;
    diff = x-y;
}

void goodf(int x, int y, int* sum, int* diff){
    *sum = x+y;
    *diff = x-y;

}

int main(void){
    int a, b, sum, diff;
    sum = 0; diff =0;
    printf("a is:");
    scanf("%d",&a);
    printf("b is:");
    scanf("%d",&b);
    goodf(a,b,&sum,&diff);
    printf("sum is: %d",sum);
    printf("Difference is:%d",diff);
}