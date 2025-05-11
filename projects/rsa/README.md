# RSA (Rivest-Shamir-Adleman) Problem
This project encrypts and decrypts a message, using rsa method.

## Build & Dependencies
In order to compile this project you need the `gcc` tool. Now `compile` the project, with the command:
```sh
gcc -O3 -Wall -Wextra -Werror -pedantic -o rsa rsa.c
```
## Usage
Now we `execute` the project without parameters, while the inputs are stdin:
```sh
./rsa enc|dec <exp_exp> <priv_exp> <prime1> <prime2>
```
## Demo
Here are some `examples` of this project, with different inputs:
```sh
$ ./rsa 3
Usage: ./rsa enc|dec <exp_exp> <priv_exp> <prime1> <prime2>
$ echo $?
1
$ ./rsa heap 19 156 1454 7888
First argument must be 'enc' or 'dec'
$ echo $?
1
$ ./rsa enc 156 4562 4563 -45457454
Negative numbers are not allowed
$ echo $?
1
$ ./rsa enc 15 456 134 4
p and q must be prime
$ echo $?
1
$ echo 42 | ./rsa enc 5 173 17 19
264
$ echo 43434343 | ./rsa enc 65537 2278459553 62971 38609 | ./rsa dec 65537 2278459553 62971 38609
43434343
```
## Technical Details
In order to complete my programm I used another function in order to calculate if the number a is prime. Firstly I check if a is lower than 2, and it is prime. Then I check if a is divided by 2 
or 3, so I remove a huge ammount of numbers (all those multiple of 2 and 3) that I should have checked if they divided a. The method I used is after the number 5 if you add 2 so 7 and then 6 to 5 and after that 2 so 11 and 13 then you get all the prime numbers from 5 and on, plus some that are not prime, but with this way I am saving so much time than checking one by one.
```c
int isprime(long long int a) {
    if (a<2) {
        return 0;
    }
    if (a==2 || a==3) {
        return 1;
    }
    if (a%2 == 0 || a%3 == 0) {
        return 0;
    }
    for (long long int i=5; i<= a / i; i+=6) {
        if (a%i == 0 || a%(i+2) == 0) {
            return 0;
        }
    }
    return 1;
}
```