#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 64
#define MAX_DIST 2147483647

typedef struct {
    char name[50];
} City;

int **distance_matrix;
City *cities;
int total_cities = 0;
int visited[MAX_CITIES] = { 0 };
int min_cost = MAX_DIST;
int running_cost = 0;
int *best_path;
int *running_path;

// Επιστρέφει τη θέση της πόλης με όνομα που περνάμε σαν όρισμα
// μέσα στον πίνακα cities.
// Επίσης εισάγει μία πόλη που δεν υπάρχει στον πίνακα cities
// στην πρώτη κενή θέση του.
int get_city_index(const char* name) {
    for (int i = 0; i < total_cities; i++) {
        if (strcmp(cities[i].name, name) == 0) {
            return i;
        }
    }

    if (total_cities >= MAX_CITIES) {
        fprintf(stderr, "The cities array cannot accept all cities in file.\n");
        exit(1);
    }

    strcpy(cities[total_cities].name, name);
    return total_cities++;
}

// Διαβάζει το αρχείο εισόδου και δημιουργεί τον τετραγωνικό πίνακα
// distances με τις αποστάσεις κάθε πόλης με τις άλλες
void parse_file(const char* filename) {
    // Δέσμευση δυναμικής μνήμης
    cities = malloc(MAX_CITIES * sizeof(City));
    if (!cities) {
        fprintf(stderr, "Memory allocation failed for cities.");
        exit(1);
    }
    best_path = malloc(MAX_CITIES * sizeof(int));
    if (!best_path) {
        fprintf(stderr, "Memory allocation failed for best_path.");
        exit(1);
    }
    running_path = malloc(MAX_CITIES * sizeof(int));
    if (!running_path) {
        fprintf(stderr, "Memory allocation failed for running_path.");
        exit(1);
    }
    distance_matrix = malloc(MAX_CITIES * sizeof(int*));
    if (!distance_matrix) {
        fprintf(stderr, "Memory allocation failed for distance_matrix.");
        exit(1);
    }
    for (int i = 0; i < MAX_CITIES; i++) {
        distance_matrix[i] = malloc(MAX_CITIES * sizeof(int));
        if (!distance_matrix[i]) {
            fprintf(stderr, "Memory allocation failed for distance_matrix[%d].", i);
            exit(1);
        }
    }
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file '%s'.\n", filename);
        exit(1);
    }

    // Αρχικοποίηση του πίνακα με 0 στη διαγώνιο
    // Όλες οι άλλες θέσεις γεμίζουν με το μεγαλύτερο αριθμό
    for (int i = 0; i < MAX_CITIES; i++) {
        for (int j = 0; j < MAX_CITIES; j++) {
            if (i == j)
                distance_matrix[i][j] = 0;
            else 
                distance_matrix[i][j] = MAX_DIST;
        }
    }

    char line[256];
    int has_data = 0;
    while (fgets(line, sizeof(line), file)) {
        char city1[50], city2[50];
        int distance;

        if (sscanf(line, "%[^-]-%[^:]: %d", city1, city2, &distance) != 3) {
            fprintf(stderr, "Error: Invalid line format in file.\n");
            fclose(file);
            exit(1);
        }
        has_data = 1; //διαβαστικε εγκυρη γραμμη ,αρα το αρχειο δεν ειναι κενο

        int idx1 = get_city_index(city1);
        int idx2 = get_city_index(city2);

        distance_matrix[idx1][idx2] = distance;
        distance_matrix[idx2][idx1] = distance; 
    }
    if(!has_data){
        fprintf(stderr,"Error: the file is empty.\n");
        fclose(file);
        exit(1);
    }

    fclose(file);
}

void tsp(int city, int level) {
    if (level == total_cities) {
        if (running_cost < min_cost) {
            min_cost = running_cost;
            memcpy(best_path, running_path, total_cities * sizeof(int));
        }
        return;
    }

    for (int next = 0; next < total_cities; next++) {
        if (!visited[next] && distance_matrix[city][next] < MAX_DIST) {
            visited[next] = 1;
            running_cost += distance_matrix[city][next];
            running_path[level] = next;

            if (running_cost < min_cost) {
                tsp(next, level + 1);
            }

            visited[next] = 0;
            running_cost -= distance_matrix[city][next];
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

    parse_file(argv[1]);

    for (int i = 0; i < MAX_CITIES; i++) best_path[i] = -1;
    visited[0] = 1;
    running_path[0] = 0;

    tsp(0, 1);

    printf("We will visit the cities in the following order:\n");
    for (int i = 0; i < total_cities - 1; i++) {
        printf("%s -(%d)-> ", cities[best_path[i]].name, distance_matrix[best_path[i]][best_path[i+1]]);
    }
    printf("%s\n", cities[best_path[total_cities - 1]].name);
    printf("Total cost: %d\n", min_cost);

        // Αποδέσμευση δυναμικής μνήμης
    for (int i = 0; i < total_cities; i++) {
        free(distance_matrix[i]);
    }
    free(distance_matrix);
    free(cities);
    free(best_path);
    free(running_path);
    
    return 0;
}