#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define DEFAULT_WINDOW 50
#define MAX_WINDOW 1000  // Safety limit

int moving_avg(const char* filename, size_t window) {   
    if (window <= 0 || window > MAX_WINDOW) {
        fprintf(stderr, "Error: Window size must be between 1 and %d\n", MAX_WINDOW);
        return 1;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file '%s' (%s)\n", filename, strerror(errno));
        return 1;
    }

    double* window_numbers = malloc(window * sizeof(double));
    if (window_numbers == NULL) {
        fclose(file);
        fprintf(stderr, "Error: Memory allocation failed for window size %zu\n", window);
        return 1;
    }

    size_t count = 0;
    double num;
    while (fscanf(file, "%lf", &num) == 1) {
        window_numbers[count % window] = num;
        count++;
    }

    if (ferror(file)) {
        fprintf(stderr, "Error: Failed to read from file\n");
        free(window_numbers);
        fclose(file);
        return 1;
    }

    if (count < window) {
        fprintf(stderr, "Error: Only %zu values in file (window size %zu too large)\n", count, window);
        free(window_numbers);
        fclose(file);
        return 1;
    }

    double sum = 0.0;
    for (size_t i = 0; i < window; i++) {
        sum += window_numbers[i];
    }
    printf("Moving average (window %zu): %.2f\n", window, sum/window);

    free(window_numbers);
    fclose(file);
    return 0;
}

void print_usage(const char* program_name) {
    fprintf(stderr, "Usage: %s <filename> [--window N]\n", program_name);
    fprintf(stderr, "  <filename> : File containing one number per line\n");
    fprintf(stderr, "  --window N : Optional window size (default: %d, max: %d)\n", 
            DEFAULT_WINDOW, MAX_WINDOW);
}

int main(int argc, char *argv[]) {
    size_t window_size = DEFAULT_WINDOW;
    const char* filename = NULL;

    if (argc < 2 || argc > 4) {
        print_usage(argv[0]);
        return 1;
    }

    filename = argv[1];

    if (argc == 4) {
        if (strcmp(argv[2], "--window") != 0) {
            fprintf(stderr, "Error: Invalid option '%s'\n", argv[2]);
            print_usage(argv[0]);
            return 1;
        }

        char* endptr;
        errno = 0;
        long temp_size = strtol(argv[3], &endptr, 10);
        
        if (*endptr != '\0' || errno != 0 || temp_size <= 0) {
            fprintf(stderr, "Error: Invalid window size '%s'\n", argv[3]);
            print_usage(argv[0]);
            return 1;
        }
        
        window_size = (size_t)temp_size;
    } else if (argc != 2) {
        print_usage(argv[0]);
        return 1;
    }

    return moving_avg(filename, window_size);
}