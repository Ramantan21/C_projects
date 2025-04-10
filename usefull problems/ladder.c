#include <stdio.h>
#include <stdlib.h>


unsigned long long calculate_ways(int steps, unsigned long long *memo){
    if(steps == 0){
        return 1;
    }
    if(steps < 0){
        return 0;
    }
    if(memo[steps] != -1){
        return memo[steps];
    }
    memo[steps] = calculate_ways(steps -1,memo)+calculate_ways(steps - 2,memo)+
                  calculate_ways(steps - 3, memo);
    return memo[steps];
}



int main(){
    int steps;
    printf("Please provide the number of steps: ");
    if(scanf("%d",&steps) != 1){
        printf("Error : Invalid input. Please enter a valid number.\n");
        return 1;
    }
    if(steps < 0){
        printf("Error: numbers can't be negative\n");
        return 1;
    }
    unsigned long long *memo = malloc((steps + 1) * sizeof(unsigned long long));
    if(!memo){
        printf("Memory allocation failed.\n");
        return 1;
    }
    for(int i=0; i<=steps; i++){
        memo[i] = -1;    
    }
    unsigned long long wayS = calculate_ways(steps,memo);

    printf("There are %llu different ways to climb the ladder\n",wayS);
    free(memo);
    return 0;
}