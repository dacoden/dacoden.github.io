/*
File: future.c
Author: Dimitrios Arvanitakis
ID: sdi2400007
Brief: Calculates the Simple Moving Average of a sequence.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// I used argc to store the number of command line arguments passed by the user
// including the name of the program, and argv[] to use those arguments.
int main(int argc, char *argv[]) {
  // With argc != 6, I accepted only the arguments wich have the formation of
  // "./future <filename> [--window N (default: 50)]".
  if (argc != 2 && argc != 4) {
    fprintf(stderr, "Usage: ./future <filename> [--window N (default: 50)]\n");
    return 1;
  }
  // Used the strcmp() function to check if the third argument argv[2] is
  // --window and if not so the difference is not 0, return 1 and print the
  // message.
  if (argc == 4 && strcmp(argv[2], "--window") != 0) {
    fprintf(stderr, "Usage: ./future <filename> [--window N (default: 50)]\n");
    return 1;
  }
  /*
  Brief: Initialized the default value of window to 50, and defined parameter
  as "long long decimal integer", in order to accept only the decimal
  integer costs from 0 to 10^18. I could have put long long unsigned
  but because I check if it negative cost later I used int.
  */
  long long int window = 50;
  // Changed the value of window only if it has 4 arguments (--window N).
  if (argc == 4) {
    window = atoll(argv[3]);
  }
  // Checked if the window is smaller than 1 or negative, return 1 and
  // print the message.
  if (window < 1) {
    fprintf(stderr, "Window too small!\n");
    return 1;
  }
  FILE *filename;
  filename = fopen(argv[1], "r");
  if (!filename) {
    fprintf(stderr, "File does not exist\n");
    return 1;
  }
  /*
  Brief: Defined every parameter about the values of the file as
  as "double", in order to accept numbers with two decimal digits.
  I also made an array size sizeof(double) * window, in order to
  help me find the Simple Moving Average with window.
  */
  double *A = malloc(sizeof(double) * window);
  if (A == NULL) {
    fprintf(stderr, "Failed to allocate window memory\n");
    fclose(filename);
    return 1;
  }
  double a;
  long long int i;
  long long int counter = 0;
  // Read values from the file until it can't read anything else.
  for (i = 0; fscanf(filename, "%lf", &a) == 1; i++) {
    A[counter] = a;
    counter = (counter + 1) % window;
  }
  // Checked if the window is larger than i that has the count of
  // values in the file, return 1 and print the message.
  if (window > i) {
    fprintf(stderr, "Window too large!\n");
    free(A);
    fclose(filename);
    return 1;
  }
  double sum = 0;
  // Calculated the sum of all the values in the array, then divided
  // it by the size of the window and print it with "%.2lf\n" where
  // .2 indicates that it will print up to two decimal digits.
  for (long long int i = 0; i < window; i++) {
    sum += A[i];
  }
  printf("%.2lf\n", sum / window);
  free(A);
  fclose(filename);
  return 0;
}