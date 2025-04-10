#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DEFAULT_WINDOW 50

int moving_avg(char* filename,size_t window)
{   
    if(window <= 0){
        fprintf(stderr,"Window too small!\n");
        return 1;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr,"file does not exist!\n");
        return 1;
    }

    double* window_numbers = malloc(window * sizeof(double));
    if (window_numbers == NULL) {
        fclose(file);
        fprintf(stderr,"Failed to allocate window memory\n");
        return 1;
    }

    size_t count = 0; // Συνολικός αριθμός αριθμών που διαβάστηκαν
    double num;
	// Όσο διαβάζονται αριθμοί μέσα από το αρχείο
    while (fscanf(file, "%lf", &num) == 1) {
		// Οι αριθμοί αποθηκεύονται κυκλικά στoν πίνακα μεγέθους n
		// στη θέση count mod window (% window), έτσι ώστε μόνο οι τελευταίοι 
		// n αριθμοί να παραμένουν στον πίνακα
        window_numbers[count % window] = (double)num *1.0;
        count++;
    }
    if (count < window) {
        fprintf(stderr,"Window too large!\n");
        free(window_numbers);
        return 1;
    }

    double sum = 0.0;
    for(size_t i = 0; i<window; i++){
        sum+=*(window_numbers + i);
    }
    printf("%.2f\n",(sum/window));

    free(window_numbers);
    fclose(file);
    return 0;
}



int main(int argc,char *argv[]){
    if(argc == 2){
        return moving_avg(argv[1], DEFAULT_WINDOW);
    }
    if(argc == 4){
        if(strcmp(argv[2],"--window") == 0){
            char* endln;
            size_t window_size = strtoll(argv[3], &endln, 10);
            if(*endln != '\0'){
                fprintf(stderr,"invalid window size!\n");
            }
            return moving_avg(argv[1],window_size);
        }
    }
    fprintf(stderr,"Usage: ./future <filename> [--window N (default: 50)]\n");
    return 1;

}
