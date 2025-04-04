#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *rev(char *str){
    int len;
    len = strlen(str);
    char *rev = (char*)malloc((sizeof(char))* (len +1));
    if( rev == NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }

    for(int i = 0; i<len; i++){
        rev[i] = str[len -i -1];
    }
    rev[len] = '\0';
    return rev;
}

int ispalindrome(char *str){
    char *reverse = rev(str);
    
    if(strcmp(str,reverse) == 0){
        printf("\"%s is palindrome",str);
    }else
        printf("\"%s is not palindrome",str);
    

}
int main(){
    ispalindrome("madam");
    ispalindrome("hello");
    return 0;
}




















































/*void reverse(int arr[],int l,int r){
   if( l >= r){
    return;
   }
   int temp = arr[l];
   arr[l] = arr[r];
   arr[r] = temp;
   reverse(arr,l+1,r-1);

}

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    reverse(arr,0,arr_size-1);
    for (int i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    return 0;

}*/

















































































/*struct pair{
    int min;
    int max;
};

struct pair getMinMax(int arr[],int n){
    struct pair minmax;
    if(n == 1){ // ελεγχουμε αν ο πινακας εχει μονο ενα στοιχειο.
        minmax.min = arr[0];
        minmax.max = arr[0];
        return minmax;
    }
    if( arr[0] > arr[1]){
        minmax.min = arr[1];
        minmax.max = arr[0];
    }else{
        minmax.max = arr[1];
        minmax.min = arr[0];
    }

    for( int i = 2; i<n; i++){
        if(arr[i] > minmax.max){
            minmax.max = arr[i];
        }else if(arr[i] < minmax.min){
            minmax.min = arr[i];
        }
    }
    return minmax;

}*/














































/*void swap(int *a,int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubblesort(int n, int *x){
    int i,j;
    for( i = 1; i <= n-1; i++)
        for ( j = n-1; j >= i; j--)
            if(x[j-1]> x[j])
                swap(&x[j-1], &x[j]);
}

int main(){
    int arr[] = {4, 7, 2, 1, 9};
    int n = sizeof(arr) / arr[0];

    for(int i=0; i<n; i++){
        bubblesort(n,arr);
    }
    printf("Minimum element is:%d",arr[0]);
    printf("Maximum element is:%d",arr[n-1]);
    return 0;
}*/



























/*int what(int *array, int x, int y){
int mid, low = 0, high = y - 1;
while (low <= high) {
mid = low + (high - low) / 2;
printf("%d\n", mid);
if (array[mid] == x) 
    return 1;
else if (array[mid] < x) low = mid + 1;
else high = mid - 1;
}
return 0;
}*/












































































/*void Array_movingAvg(int arr[],int n,int window,double* output){
    int sum = 0;
    if(n != 0 && output != 0){
        for(int i =0; i<n; i++){
            sum = sum+arr[i];
            if(i>=window){
                sum = sum - arr[i-window];
            }
            output[i] = (double)sum/window;
        }

    }
}

    int main(){
        int arr[] = { 9,7 ,7 ,1 ,4 ,4 ,4 ,38, 8, 4};
        int n = sizeof(arr) / sizeof(arr[0]); 
        double output[n];
        int window;
        scanf("%d",&window);
        Array_movingAvg(arr,n,window,output);
        for(int i = window-1; i<n; i++){
            printf("%.2f\n",output[i]);
        }
    return 0;
    }*/





















































/*int remove_dup(int arr[],int n){
    int j = 0;
    for(int i = 0; i<n-1; i++){

        if(arr[i] != arr[j]){
            arr[++j] = arr[i];
        }
    }
    return j+1;
}

int main(){
    int arr[] = {1,2,2,3,4,4,4,5,5};
    int n = sizeof (arr) / sizeof arr[0];
     n = remove_dup(arr,n);
    for(int i=0; i<n; i++){
    printf("%d",arr[i]);
    }

    return 0;

}*/

































/*//arr[] = {1,2,3,4,5} D = 2 -> arr[3,4,5,1,2]

void rotate(int arr[],int N,int D){
    if(D != 0){
        for(int i = 0; i<D; i++){
        int first = arr[0];
        for(int j = 0; j < N-1; j++){
            arr[j] = arr[j+1];
        }
        arr[N-1] = first;
        }
    }
    return ;
}

int main(){
   int arr[] = {1,2,3,4,5};
    int N = sizeof(arr) / sizeof(arr[0]);
    rotate(arr,N,2);
    for(int i = 0; i< N; i++){
        printf("%d",arr[i]);
    }
    return 0;
}*/
































// {1,2,3,4,5,6} -> {6,5,4,3,2,1}

/*void reverse(int arr[],int l,int r){
    int temp;
    if ( l > r)
        return;
    temp = arr[l];
    arr[l] = arr[r];
    arr[r] = temp;

    reverse(arr,l+1,r-1);

    }


int main(){
    int arr[] = {1,2,3,4,5,6};
    int n = sizeof(arr) / sizeof(arr[0]);
    reverse(arr,0,n-1);
    for(int i = 0; i<n; i++){
        printf("%d",arr[i]);
    }
    return 0;
}*/































































/*struct pair{
    int min;
    int max;
};

struct pair getMinMax(int arr[],int n)
{
    struct pair minmax;
    int i;
    if(n == 1){//ελεγχουμε αν εχει μονο 1 στοιχειο ο πινακας.
        minmax.max = arr[0];
        minmax.min = arr[0];
        return minmax;
    }
        if(arr[0] > arr[1]){ //ελεγχουμε αν το 1ο στοιχειο του πινακα ειναι μεγαλυτερο με το 2ο στοιχειο του πινακα
        minmax.max = arr[0];
        minmax.min = arr[1];
        }
        else{ //ελεγχουμε αν το 2ο στοιχειο ειανι μεγαλυτερο απο το 1ο
            minmax.max = arr[1];
            minmax.min = arr[0];
    }


    for(i = 2; i<n; i++){ //ελεγχουμε για τα υπολοιπα στοιχεια
        if(arr[i]>minmax.max){
            minmax.max = arr[i];
        }
        else if (arr[i] < minmax.min)
            minmax.min = arr[i];
    }
    return minmax;
}

int main(){
    int arr[] = {4,7,2,1,9};
    int arr_size = 5;
    struct pair minmax = getMinMax(arr,arr_size);
    printf("Minimum element is :%d",minmax.min);
    printf("Maximum element is :%d",minmax.max);
    getchar();
}*/


























/*int main()
{
   char op; double result; int operand1 = 7; int operand2 = 8;
   printf("Enter operand 1:");
   scanf("")
   printf("Enter operand 2: 8");
   if(op == '+'){
    result = operand1 + operand2;
   }
   if(op == '-'){
    result = operand1 - operand2;
   }
   if(op == '*'){
    result = operand1 * operand2;
   }
    result = operand1 / operand2;
   printf("%1.f",result);
return 0;
   

}*/












/*int main()
{   
    int number;
    printf("Enter a number:");
    scanf("%d",&number);
    if(number % 2 == 0)
        printf("even\n");
    else
        printf("Is not even\n");
    return 0;


}*/