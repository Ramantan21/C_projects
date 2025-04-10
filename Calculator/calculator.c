#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void displaymenu(){
    printf("\nSimple C Calculator\n");
    printf("------------------\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Exit\n");
}

float getNumber(const char *prompt) {
    float num;
    printf("%s",prompt);
    while(scanf("%f",&num) != 1){
        printf("Invalid input. Please enter a number: ");
        while(getchar() != '\n'); //Καθαρισμος buffer
    }
    return num;
}

void handle_sigint(int signum){
    (void)signum;
    signal(SIGINT,handle_sigint);
    printf("\n\nInterrupt received. Use menu option 5 to exit properly.\n");
    //we don't exit here,just notify the user
    displaymenu();
}


int main(){

    signal(SIGINT,handle_sigint);
    printf("Calculator started. Press CTRL+C to get menu at any time.\n");
    int choise;
    float num1,num2,result;
    do{
        displaymenu();
        printf("Choose an operation (1-5): ");
        scanf("%d",&choise);

        if(choise >= 1 && choise <= 4){
            num1 = getNumber("Enter first number: ");
            num2 = getNumber("Enter second number: ");
        }
        switch(choise) {
            case 1: 
                result = num1 + num2;
                printf("\nResult: %.2f + %.2f = %.2f\n",num1,num2,result);

                break;
            case 2:
                result = num1 - num2;
                printf("\nResult: %.2f - %.2f = %.2f",num1,num2,result);

                break;

            case 3:
                result = num1 * num2;
                printf("\nResult: %.2f * %.2f = %.2f\n", num1, num2, result);

                break;

            case 4:

                if(num2 != 0){
                    result = num1 / num2;
                    printf("\nResult: %.2f / %.2f = %.2f\n", num1, num2, result);
                }else{
                    printf("Error: Cannot divide by zero!\n");
                }

                break;

            case 5:
                printf("\nCalculator exited.\n");
                break;
            default:
                printf("\nInvalid choise. Please try again\n");
        }

    }while(choise != 5);

    return 0;
}