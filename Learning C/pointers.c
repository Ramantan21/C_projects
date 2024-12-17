#include <stdio.h>

int main(){
    int my_age = 25;
    int *ptr = &my_age;

    printf("%p\n", ptr);
    printf("%d\n", *ptr);

    return 0;

}

