#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int first_unique_char(int n, char *s) {
    int char_count[256] = {0}; // Πίνακας για την καταμέτρηση των χαρακτήρων
    for(int i=0; i< n; i++){
        char_count[s[i]]++;
    }
    
    for(int i = 0; i <n; i++){
        if(char_count[s[i]] == 1){
            return i;
        }
    }
    return -1;
    }
            
            
    //epistrefoume thn thesi (index) tou prwtou xaraxthra pou den epanalamvanete


int main() {
	int n;
	scanf("%d", &n);

	char *s = malloc((n+1) * sizeof(char));
	if (!s)
		return 1;

	scanf("%s", s);
	printf("%d", first_unique_char(n, s));

	free(s);
	return 0;
}