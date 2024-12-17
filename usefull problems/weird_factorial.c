#include <stdio.h>

long long int weird_factorial(int n) {
    long long result = 1;
    int const M = 1000000007;
    for(int i=1; i<=n; i++){
        if(n % i != 0){
            result = (result * i) % M;
        }
    }
    return result;
        
}

int main() { 
	int n;
	scanf("%d", &n);
	printf("%lld", weird_factorial(n));
	return 0;
}