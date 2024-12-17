#include <stdio.h>

int count_digits(int n) {
	int counter = 0; //arxikopoioume enan counter gia na metraei ta psifia
	do{
		n/= 10; //dieroume kathe psifio me 10
		counter++; // opote diaroume to psifio auksanoume ton counter
	}while(n!=0); // mexri to psifio na einai 0
	return counter;
}

int main() { 
	int n;
	scanf("%d", &n);
	printf("%d", count_digits(n));
	return 0;
}