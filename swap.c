
#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
   int a = 100, b = 200;
   printf("a is:%d b is:%d\n",a,b);
    swap(&a,&b);
    printf("a is:%d\n b is: %d\n",a,b);
   return 0;
}