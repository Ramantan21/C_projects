#include <stdio.h>
#include <stdlib.h>


int isodd(int n){
    if(n % 2 == 0) // ελεγχουμε αν ο αριθμος ειναι αρτιος
        return 0;
    else
        return 1; // ελεγχουμε αν ο αριθμος ειναι περιττος
}

long long collatz_it(long long n){
    long long count = 0;
    if(n == 1)
        return 1;
    while(n != 1){
        if(n % 2 == 0){
            n = n / 2;
        }
        else{
            n = (n * 3) + 1;
        }
        count++;
    }
    return count + 1;
}

long long collatz(long long n){
    if(n == 1)
        return 1;
    if( n % 2 == 0){
        return 1 + collatz(n / 2);
    }
    else{
        return 1 + collatz(3 * n +1);
    }
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: ./collatz <number>\n");
        return 1;
    }

    long long n = atoll(argv[1]);
    
    printf("Iterative result: %lld\n", collatz_it(n));
    printf("Recursive result: %lld\n", collatz(n));
    return 0;
}