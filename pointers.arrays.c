#include <stdio.h>
int main(){
    int my_numbers[4] = {25, 50, 75, 100};
    *my_numbers = 13;
    *(my_numbers + 1) = 17;

    printf("%d, %d", my_numbers[0], my_numbers[1]);
    return 0;
}