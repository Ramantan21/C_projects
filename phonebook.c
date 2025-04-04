#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *name = malloc(40 * sizeof(char));
    if(name == NULL){
        printf("Memory alocation failed.\n");
        free(name);
        return 1;
    }
    char *numbers = malloc(15 * sizeof(char));
    if(numbers == NULL){
        printf("Memory allocation failed.\n");
        free(numbers);
        return 1;
    }
    FILE *file = fopen("phonebook.csv", "a");
    if(file == NULL)
    {
        printf("Error opening file.\n");
        free(name);
        free(numbers);
        return 1;
    }
    printf("Give me a name:");
    if(scanf("%s",name) == 1 ){
        printf("Give me a number:");
        if(scanf("%s",numbers) == 1)
            fprintf(file,"%s %s",name,numbers);
    }
    

    free(name);
    free(numbers);
    fclose(file);

}