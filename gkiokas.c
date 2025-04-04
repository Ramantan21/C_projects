#include <stdio.h>



int main(){
    int *ptr1, *ptr2, i = 10, j = 20;
    ptr1 = &i; // ptr1 deixnei stin dieuthinsi mnimis tou i = 10
    ptr2 = &j; // ptr2 deixnei stin dieuthinsi mnimis tou j = 20
    ptr2 = ptr1; // o ptr2 dinxei stin dieuthinsi mnimis tou ptr1
    *ptr1 = *ptr1 + *ptr2; // ptr1 = 10 + 10 = 20
    *ptr2 *= 2; // pleon o ptr2 einai 20 giati eipame dixnei stin idia dieuthinsi me ton ptr1 ara i = 40
    printf("%d\n",*ptr1+*ptr2);

    return 0;
}