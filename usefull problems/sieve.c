#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long modular_exp(long long a,long long b,long long N){
    int result = 1;
    a = a % N;
    if(a == 0)
        return 0;
    while(b>0){
        if(b & 1)
          result = (result*a) % N;
        b = b/2;
        a = (a*a) % N;
    }
    return result;
}

int main(int argc, char* argv[]){
    if(argc != 4){
        printf("wrong input:");
        return 1;
    }

    char* endln1;
    char* endln2;
    char* endln3;
    long long num1 = strtoll(argv[1], &endln1,10);
    long long num2 = strtoll(argv[2], &endln2, 10);
    long long num3 = strtoll(argv[3], &endln3, 10);
    /*if((*endln2 != '\0') || (*endln1 != '\0' ) || (*endln2 != '\0') || (*endln3 != '\0' )){//ελεγχουμε οτι ειναι αριθμητικα τα arguments.
        printf("Usage: ./rsa enc|dec <exp_exp> <priv_exp> <prime1> <prime2>\n");
        return 1;    
    }*/
    modular_exp(num1,num2,num3);
    printf("modular exp is: %lld",modular_exp(num1,num2,num3));
    return 0;

}