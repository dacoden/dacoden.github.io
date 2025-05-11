/*
File: jabbamaps.c
Author: Dimitrios Arvanitakis
ID: sdi2400007
Brief: Calculates the fastest course.
*/
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Defined maxc and maxd in order to not write every time the 60 and UINT_MAX.
#define maxc 60        // Maximum number of cities.
#define maxd UINT_MAX  // Equivalent to 2^32 - 1 for unsigned int.

// Defined parameter cities_count as global int in order to use it in tsp and
// not call every time tsp(unsigned int **distances, unsigned int **cities_karp,
// int **city_second, unsigned int visit, int index3, int cities_count).
int cities_count;

// Function to free memory allocated for cities.
void free_cities(char **cities) {
  for (int i = 0; i < maxc; i++) {
    if (cities[i]) {
      free(cities[i]);
    }
  }
}

// Held-Karp function for solving the TSP.
unsigned int tsp(unsigned int **distances, unsigned int **cities_karp,
                 int **city_second, unsigned int visit, int index3) {
  // Checked if all cities are visited.
  if (visit == (1U << cities_count) - 1) {
    return 0;
  }
  // Checked if the minimum cost for the current state visit, index3 has already
  // been computed. If it has, return the precomputed value, avoiding redundant
  // calculations.
  if (cities_karp[visit][index3] != -1U) {
    return cities_karp[visit][index3];
  }
  // Initiallized minimum dimension with the max dimension, as then it will find
  // the correct minimum.
  unsigned int mind = maxd;
  for (int city_first = 0; city_first < cities_count; city_first++) {
    // Checked if the city has not been visited.
    if (!(visit & (1U << city_first))) {
      // Added the distance from index3 (current city) to city_first (next
      // city). Recursively calculated the minimum cost for visiting the
      // remaining cities, starting at city_first. Updates the visit bitmask to
      // include city_first using visit | (1U << city_first).
      unsigned int nmind = distances[index3][city_first] +
                           tsp(distances, cities_karp, city_second,
                               visit | (1U << city_first), city_first);
      if (nmind < mind) {
        mind = nmind;
        city_second[visit][index3] = city_first;
      }
    }
  }

  cities_karp[visit][index3] = mind;
  return mind;
}
// I used argc to store the number of command line arguments passed by the user
// including the name of the program, and argv[] to use those arguments.
int main(int argc, char *argv[]) {
  // With argc != 2, I accept only the arguments wich have the formation of
  // "./jabbamaps <filename>".
  if (argc != 2) {
    fprintf(stderr, "Usage: ./jabbamaps <filename>\n");
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (!file) {
    fprintf(stderr, "File does not exist\n");
    return 1;
  }

  // Checked if the file is empty, by moving pointer of the first byte of the
  // file to the last byte of the file and then with ftell(file) that returns 0
  // if the file is empty, else the bytes of the file.
  fseek(file, 0, SEEK_END);
  if (ftell(file) == 0) {
    fprintf(stderr, "Error: The file is empty.\n");
    fclose(file);
    return 1;
  }
  fseek(file, 0, SEEK_SET);  // Reset the file pointer to the start of the file.
  // Made an adjacency matrix to put inside the distances between the towns.
  // Also I made a cities array for the names of the max 60 cities.
  int matrix[maxc][maxc] = {0};
  char *cities[maxc] = {0};

  int count = 0;
  // Made an infinitive loop that stop only if the pointer to the file shows
  // a the end of it or it doesn't read any character.
  while (1) {
    // Made a memory allocation for the first character of the name of city1.
    char *city1 = malloc(sizeof(char));
    if (!city1) {
      fprintf(stderr, "Memory allocation failed\n");
      free_cities(cities);
      fclose(file);
      return 1;
    }
    char ch;
    int i = 0;
    // Reallocated the city1 string until it reads '-' character from ch.
    // Added that character ch to string city1.
    while (fscanf(file, "%c", &ch) == 1 && ch != '-') {
      char *temp = realloc(city1, sizeof(char) * (i + 2));
      if (!temp) {
        fprintf(stderr, "Memory reallocation failed\n");
        free_cities(cities);
        free(city1);
        fclose(file);
        return 1;
      }
      city1 = temp;
      city1[i++] = ch;
    }
    if (feof(file) && i == 0) {
      free(city1);
      break;
    }
    // Added the NULL to string city1.
    city1[i] = '\0';
    // Made a memory allocation for the first character of the name of city2.
    char *city2 = malloc(sizeof(char));
    if (!city2) {
      fprintf(stderr, "Memory allocation failed\n");
      free_cities(cities);
      free(city1);
      fclose(file);
      return 1;
    }
    int k = 0;
    // Reallocated the city2 string until it reads ':' character from ch.
    // Added that character ch to string city2.
    while (fscanf(file, "%c", &ch) == 1 && ch != ':') {
      char *temp = realloc(city2, sizeof(char) * (k + 2));
      if (!temp) {
        fprintf(stderr, "Memory reallocation failed\n");
        free_cities(cities);
        free(city1);
        free(city2);
        fclose(file);
        return 1;
      }
      city2 = temp;
      city2[k++] = ch;
    }
    // Added the NULL to string city2.
    city2[k] = '\0';

    int distance;
    if (fscanf(file, "%d\n", &distance) != 1) {
      fprintf(stderr, "Failed to read distance\n");
      free_cities(cities);
      free(city1);
      free(city2);
      fclose(file);
      return 1;
    }
    // Checked if the name of the city is new or not and if not
    // then index = -1. I also used strdup in order to minimalize
    // my code insted of having a variable for the size of city, and doing
    // malloc.
    int index1 = -1, index2 = -1;
    for (int j = 0; j < count; j++) {
      if (cities[j] && strcmp(cities[j], city1) == 0) {
        index1 = j;
      }
      if (cities[j] && strcmp(cities[j], city2) == 0) {
        index2 = j;
      }
    }

    if (index1 == -1) {
      index1 = count++;
      cities[index1] = strdup(city1);
      if (!cities[index1]) {
        fprintf(stderr, "Memory allocation failed\n");
        free_cities(cities);
        free(city1);
        free(city2);
        fclose(file);
        return 1;
      }
    }
    if (index2 == -1) {
      index2 = count++;
      cities[index2] = strdup(city2);
      if (!cities[index2]) {
        fprintf(stderr, "Memory allocation failed\n");
        free_cities(cities);
        free(city1);
        free(city2);
        fclose(file);
        return 1;
      }
    }

    matrix[index1][index2] = distance;
    matrix[index2][index1] = distance;

    free(city1);
    free(city2);
  }

  cities_count = count;
  // Moved everything from matrix two dimensional array to distances.
  unsigned int **distances = malloc(cities_count * sizeof(unsigned int *));
  if (!distances) {
    fprintf(stderr, "Memory allocation failed\n");
    free_cities(cities);
    fclose(file);
    return 1;
  }
  for (int i = 0; i < cities_count; i++) {
    distances[i] = malloc(cities_count * sizeof(unsigned int));
    if (!distances[i]) {
      fprintf(stderr, "Memory allocation failed\n");
      for (int l = 0; l < i; l++) free(distances[l]);
      free(distances);
      free_cities(cities);
      fclose(file);
      return 1;
    }
    /*
    Brief: I used a sorted form (below) to minimalize my code.
    This checks if the cities i and j are the same. If they are the same (i ==
    j), the distance between a city and itself is 0. Else, proceed to the next
    part to assign the distance. If there is a valid distance between city i and
    city j in the matrix: Use the value from matrix[i][j], cast it to unsigned
    int. If there is no valid distance matrix[i][j] == 0, it assigns maxd.
    */
    for (int j = 0; j < cities_count; j++) {
      distances[i][j] =
          (i == j) ? 0 : (matrix[i][j] ? (unsigned int)matrix[i][j] : maxd);
    }
  }
  /*
  Brief: Created cities_karp a two dimensional array, of unsigned int values.
  It stores the minimum cost of visiting a subset of cities and ending at
  a specific city to avoid recalculating the same states. Also
  (1U << cities_count) creates a bitmask where all cities_count bits are 1.
  For example, if cities_count = 4, it creates 1111. Where a bit
  value of 1 indicates the city is visited and a bit value of 0 indicates the
  city is unvisited.
  */
  unsigned int **cities_karp =
      malloc((1U << cities_count) * sizeof(unsigned int *));
  if (!cities_karp) {
    fprintf(stderr, "Memory allocation failed\n");
    for (int l = 0; l < cities_count; l++) free(distances[l]);
    free(distances);
    free_cities(cities);
    fclose(file);
    return 1;
  }
  // Created city_second a two dimensional array, of int values, in order
  // to record the next city in the optimal path for reconstruction.
  int **city_second = malloc((1U << cities_count) * sizeof(int *));
  if (!city_second) {
    fprintf(stderr, "Memory allocation failed\n");
    for (unsigned int i = 0; i < (1U << cities_count); i++)
      free(cities_karp[i]);
    free(cities_karp);
    for (int l = 0; l < cities_count; l++) free(distances[l]);
    free(distances);
    free_cities(cities);
    fclose(file);
    return 1;
  }

  for (unsigned int i = 0; i < (1U << cities_count); i++) {
    cities_karp[i] = malloc(cities_count * sizeof(unsigned int));
    if (!cities_karp[i]) {
      fprintf(stderr, "Memory allocation failed\n");
      for (unsigned int l = 0; l < i; l++) free(cities_karp[l]);
      free(cities_karp);
      free(city_second);
      for (int l = 0; l < cities_count; l++) free(distances[l]);
      free(distances);
      free_cities(cities);
      fclose(file);
      return 1;
    }
    city_second[i] = malloc(cities_count * sizeof(int));
    if (!city_second[i]) {
      fprintf(stderr, "Memory allocation failed\n");
      for (unsigned int l = 0; l < i; l++) {
        free(cities_karp[l]);
        free(city_second[l]);
      }
      free(cities_karp);
      free(city_second);
      for (int l = 0; l < cities_count; l++) free(distances[l]);
      free(distances);
      free_cities(cities);
      fclose(file);
      return 1;
    }
    for (int j = 0; j < cities_count; j++) {
      cities_karp[i][j] = -1U;
    }
  }

  int start = 0;
  unsigned int mind =
      tsp(distances, cities_karp, city_second, 1U << start, start);

  if (mind == maxd) {
    printf("No valid path found\n");
  } else {
    printf("We will visit the cities in the following order:\n");
    // Started from the initial city.
    int current = start;
    // Initialized the 'visit' bitmask with only the starting city marked as
    // visited.
    unsigned int visit = 1U << start;

    for (int i = 0; i < cities_count - 1; i++) {
      // The next city to visit from the city_second array, which
      // stores the optimal next city.
      int next = city_second[visit][current];
      printf("%s -(%u)-> ", cities[current], distances[current][next]);
      // Updated the visit bitmask to mark the next city as visited.
      visit |= (1U << next);
      current = next;
    }
    printf("%s\n", cities[current]);
    printf("Total cost: %u\n", mind);
  }

  free_cities(cities);
  for (int i = 0; i < cities_count; i++) {
    free(distances[i]);
  }
  free(distances);
  for (unsigned int i = 0; i < (1U << cities_count); i++) {
    free(cities_karp[i]);
    free(city_second[i]);
  }
  free(cities_karp);
  free(city_second);

  fclose(file);
  return 0;
}