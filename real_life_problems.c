#include <stdio.h>

int main(void){
    int i,j;
    int n;
    do
    {
        printf("Give an integer:");
        scanf("%d",&n);
    }while(n<1);

    for(i = 0; i < n; i++)
    {
        for( j =0; j< n; j++)
        {
         printf("#");
        }
    printf("\n");
    }


}



