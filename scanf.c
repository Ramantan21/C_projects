#include <stdio.h>
#include <stdlib.h>


long long llpower(long long a, long long b){ //φτιαχνουμε μια συναρτηση για να υπολογισουμε την δυναμη ενος ακεραιου
    long long calculate = 1;
    for(long long i = 1; i<=b; i++){
        calculate *= a;
    }
    return calculate;
}

int main(){
    long long int n;
    long long ekth;
    printf("give an integer:\n");
    scanf("%lld",&n);
    printf("dwse ton ektheti:");
    scanf("%lld",&ekth);
    llpower(n,ekth);
    printf("power of integer is: %lld",llpower(n,ekth));

    return 0;
}
