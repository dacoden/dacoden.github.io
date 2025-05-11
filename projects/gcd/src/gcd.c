/*
File: gcd.c
Author: Dimitrios Arvanitakis
ID: sdi2400007
Brief: Find the greatest common divisor.
*/
#include <stdio.h>
#include <stdlib.h>

long long int gcd(long long int a, long long int b) {
  if (a % b == 0) {
    return llabs(b);  // Used the llabs() function to return the absolute
                      // positive value of b, if b is a factor of a.
  }
  return gcd(b, a % b);
}
// I used argc to store the number of command line arguments passed by the user
// including the name of the program, and argv[] to use those arguments.
int main(int argc, char *argv[]) {
  // With argc != 3, I accept only the arguments wich have the formation of
  // "./gcd <num1> <num2>".
  if (argc != 3) {
    printf("Usage: ./gcd <num1> <num2>\n");
    return 1;
  }
  /*
  Brief: Used τhe atoll() function to convert the string argv[1], argv[2] (which
  are the arguments except from the first one, programm name), to a long long
  integer num1, num2. Defined every parameter as "long long decimal integer", in
  order to accept only the decimal integer costs from −10^18 to 10^18.
  */
  long long int num1 = atoll(argv[1]);
  long long int num2 = atoll(argv[2]);
  // Checks if num1 or num2 are 0 and returns 1.
  if (num1 == 0 || num2 == 0) {
    return 1;
  }
  printf("gcd(%lld, %lld) = %lld\n", num1, num2, gcd(num1, num2));
  return 0;
}