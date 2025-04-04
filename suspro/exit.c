#include <stdio.h>
#include <stdlib.h>

#define EXITCODE 157

int main(){
    printf("Going to terminate with status code 157\n");
    exit(EXITCODE);
}