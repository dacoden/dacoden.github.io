/*
File: factor.c
Author: Dimitrios Arvanitakis
ID: sdi2400007
Brief: Find the factors of a semiprime number.
*/
#include <stdio.h>
#include <stdlib.h>
typedef unsigned __int128 uint128_t;
// I used another function in order to print an unsigned 128 bit number.
void print_large_uint128(uint128_t num) {
  unsigned long long int ten_power_18 = 1000000000000000000ULL;
  if (num > ten_power_18) {
    unsigned long long int high = num / ten_power_18;
    unsigned long long int low = num % ten_power_18;
    printf("%llu%018llu", high, low);
  } else {
    printf("%llu", (unsigned long long int)num);
  }
}
// I used another function in order to convert a string of characters to a
// number sum.
uint128_t atou128(const char *str) {
  uint128_t sum = 0;
  if (!str || *str == '\0') {
    exit(1);
  }
  while (*str) {
    if (*str >= '0' && *str <= '9') {
      sum = sum * 10 + (*str - '0');
    } else {
      exit(1);
    }
    str++;
  }
  return sum;
}
// I used argc to store the number of command line arguments passed by the user
// including the name of the program, and argv[] to use those arguments.
int main(int argc, char *argv[]) {
  // With argc != 2, I accept only the arguments wich have the formation of
  // "./factor <semiprime>".
  if (argc != 2) {
    printf("Usage: ./factor <semiprime>\n");
    return 1;
  }
  /*
  Brief: Used τhe atou128() function to convert the string argv[1](which is the
  argument except from the first one, programm name) to an unsigned 128 bit
  sprime. Defined every parameter as "uint128_t", in order to accept only the
  unsigned decimal integer costs from 0 to 2^127.
  */
  uint128_t sprime = atou128(argv[1]);
  /*
  Brief: Checked if sprime is divided by 2 or 3, so I remove a huge ammount of
  numbers (all those multiple of 2 and 3) that I should have checked if they
  divided sprime, and with that I can find and the second factor.
  */
  if (sprime % 2 == 0) {
    printf("Factors: 2");
    printf(" ");
    print_large_uint128(sprime / 2);
    printf("\n");
    return 0;
  }
  if (sprime % 3 == 0) {
    printf("Factors: 3");
    printf(" ");
    print_large_uint128(sprime / 3);
    printf("\n");
    return 0;
  }
  /*
  Brief: I used this, because after the number 5 if you add 2 so 7 and then 6 to
  5 and after that 2 so 11 and 13 then you get all the prime numbers from 5 and
  on, plus some that are not prime, but with this way I am saving so much time
  than checking one by one.
  */
  for (uint128_t i = 5; i <= sprime / i; i += 6) {
    if (sprime % i == 0) {
      printf("Factors: ");
      print_large_uint128(i);
      printf(" ");
      print_large_uint128(sprime / i);
      printf("\n");
      return 0;
    }
    if (sprime % (i + 2) == 0) {
      printf("Factors: ");
      print_large_uint128(i + 2);
      printf(" ");
      print_large_uint128(sprime / (i + 2));
      printf("\n");
      return 0;
    }
  }
  return 1;
}