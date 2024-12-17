#include <stdio.h>
#include <stdlib.h>

int main(){
    char a,b;
    printf("a: %p\t b:%p\n",&a,&b);
    printf("distance between a and b: %ld\n",&a-&b);
    printf("\n");

    char *pa=malloc(sizeof(char));
    char *pb = malloc(sizeof(char));
    printf("pa = %p\t pb = %p\n",pa,pa);
    printf("distance between pa and pb: %ld\n",pa-pb);
    free(pa);
    free(pb);

    return 0;

    }

    
    #define N 400000000
   int main(){
        int *arr,i;
        arr = malloc(N*sizeof(int));
        if(arr == NULL){
            printf("Malloc failed!\n");
            return 1;
        }
        for(i=0; i<N; ++i){
            arr[i]=rand();
        }
        for(i=0; i<N; ++i){
            printf("%d\n",arr[i]);
        }
        free(arr);
        return 0;
   }




