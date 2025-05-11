/*
File: rsa.c
Author: Dimitrios Arvanitakis
ID: sdi2400007
Brief: Encode and decode messages with rsa.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// I implemented the gcd() function from the gcd.c programm.
long long int gcd(long long int a, long long int b) {
  if (a % b == 0) {
    return llabs(b);
  }
  return gcd(b, a % b);
}
// Implemented the code from wikepedia about modular exponentiation by squaring.
long long int modular_exponentiation(long long int b, long long int e,
                                     long long int m) {
  long long int c = 1;
  b = b % m;  // Reduce base modulo m initially.
  while (e > 0) {
    if (e % 2 == 1) {  // If e is odd.
      c = (c * b) % m;
    }
    e = e / 2;        // Divide e by 2.
    b = (b * b) % m;  // Square the base.
  }
  return c;
}
// I used another function in order to calculate if the number a is prime.
int isprime(long long int a) {
  if (a < 2) {
    return 0;
  }
  if (a == 2 || a == 3) {
    return 1;
  }
  if (a % 2 == 0 || a % 3 == 0) {
    return 0;
  }
  for (long long int i = 5; i <= a / i; i += 6) {
    if (a % i == 0 || a % (i + 2) == 0) {
      return 0;
    }
  }
  return 1;
}
// I used argc to store the number of command line arguments passed by the user
// including the name of the program, and argv[] to use those arguments.
int main(int argc, char *argv[]) {
  // With argc != 6, I accept only the arguments wich have the formation of
  // "./rsa enc|dec <exp_exp> <priv_exp> <prime1> <prime2>".
  if (argc != 6) {
    printf("Usage: ./rsa enc|dec <exp_exp> <priv_exp> <prime1> <prime2>\n");
    return 1;
  }
  // Used the strcmp() function to check if the second argument argv[1] is enc
  // or dec, and if not so the difference is not 0, return 1 and print the
  // message.
  if (strcmp(argv[1], "enc") != 0 && strcmp(argv[1], "dec") != 0) {
    printf("First argument must be 'enc' or 'dec'\n");
    return 1;
  }
  /*
  Brief: Used τhe atoll() function to convert the string argv[2], argv[3],
  argv[4], argv[5] (which are the arguments except from the first one, programm
  name and the second one, enc or dec) to a long long integer e, d, p, q.
  Defined every parameter as "long long decimal integer", in order to accept
  only the decimal integer costs from −10^18 to 10^18.
  */
  long long int e = atoll(argv[2]);
  long long int d = atoll(argv[3]);
  long long int p = atoll(argv[4]);
  long long int q = atoll(argv[5]);
  // Checked if e or d or p or q are negative and returns 1.
  if (e < 0 || d < 0 || p < 0 || q < 0) {
    printf("Negative numbers are not allowed\n");
    return 1;
  }
  // Checked if p or q are not prime and returns 1.
  if (isprime(p) == 0 || isprime(q) == 0) {
    printf("p and q must be prime\n");
    return 1;
  }
  // Checked if e is not coprime with phi(N) and returns 1.
  long long int f_N = (p - 1) * (q - 1);
  if (gcd(f_N, e) != 1) {
    printf("e is not coprime with phi(N)\n");
    return 1;
  }
  // Checked if e * d mod phi(N) is not 1 returns 1.
  if (e * d % f_N != 1) {
    printf("e * d mod phi(N) is not 1\n");
    return 1;
  }
  long long int m;
  // Checked if the command that reads the m, doesn't read a decimal integer and
  // returns 1.
  while (scanf("%lld", &m) == 1) {
    // Checked if m is negative and returns 1.
    if (m < 0) {
      printf("Negative numbers are not allowed\n");
      return 1;
    }
    long long int N = p * q;
    // Checked if message is larger than N and returns 1.
    if (N <= m) {
      printf("Message is larger than N\n");
      return 1;
    }
    long long int ans;
    /*
    Brief: Checked if the second argument argv[1] is enc and use the function
    modular_exponentiation() with arguments m, e, N. Else if the second argument
    argv[1] is enc, use the function modular_exponentiation() with arguments m,
    d, N.
    */
    if (strcmp(argv[1], "enc") == 0) {
      ans = modular_exponentiation(m, e, N);
    } else {
      ans = modular_exponentiation(m, d, N);
    }
    printf("%lld\n", ans);
    return 0;
  }
  return 1;
}