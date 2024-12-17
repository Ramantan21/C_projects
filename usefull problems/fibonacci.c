#include <stdio.h>

int recursive_calls = 0;

int fib(int n){
    //Καθε φορα που καλουμε την συναρτηση αυξανουμε την μεταβλητη recursive_calls
    recursive_calls++;
    if(n == 0){
       return 0;
    }
    else if( n == 1){
        return 1;
    }
    else if( n >= 2){
      return fib(n-1) + fib(n -2);
    }
}

int main(){
    long long int n;
    int terms;
    printf("How many fibonacci terms would you like:");
    scanf("%d",&terms);
    for(n = 0; n <= terms - 1; n++){
        fib(n);
        printf("%d\n",fib(n));

    }
    /*printf("How many fibonacci terms would you like:");
    scanf("%d",&terms);*/
    printf("Enter the value of n: ");
    scanf("%lldd",&n);
    printf("The %lldd-th fibonnaci number is: %d\n",n, fib(n));
    printf("Recursive calls are: %d\n",recursive_calls);
    return 0;
}