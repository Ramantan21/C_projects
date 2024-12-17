#include <stdio.h>
#include <math.h>

/*int i;
    double sum = 0.0;

    for(i = 1; i <= 20000; i++){
        sum = sum + 1.0 / (i * i);
    }
    printf("sum is: %lf\n", sum);
    return 0;*/

void pi_approx(){
    
    int i;
    double sum = 0.0;

    do{
       sum += 1.0 /(i*i);
    }while(i<=100);
    
    double pi = 6 * sqrt(sum);
    printf("P aprox is:%lf",pi);

}
int main(){
    pi_approx();
    return 0;
}