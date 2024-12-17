#include <stdio.h>
#include <stdlib.h>



int main(){
    int number;
    printf("Enter a number:");
    scanf("%d",&number);
    if(number % 2 == 0)
        printf("number %d is even\n",number);
    else
        printf("Number %d is odd\n",number);
        
}
