# Greatest Common Divisor Problem
This project is about the greatest common divisor between two numbers. The greatest common divisor will be calculated with the Euclidean algorithm.

## Build & Dependencies
In order to compile this project you need the `gcc` tool. Now `compile` the project, with the command:
```sh
gcc -O3 -Wall -Wextra -Werror -pedantic -o gcd gcd.c
```
## Usage
Now we `execute` the project without parameters, while the inputs are stdin:
```sh
./gcd <num1> <num2>
```
## Demo
Here are some `examples` of this project, with different inputs:
```sh
$ ./gcd 1524 1524
gcd(1524, 1524) = 1524
$ ./gcd 567948
Usage: ./gcd <num1> <num2>
$ ./gcd 12545410 0
$ echo $?
1
$ ./gcd 449841121345484 84658741398411
gcd(449841121345484, 84658741398411) = 1
$ ./gcd 97556 445585894
gcd(97556, 445585894) = 2
$ ./gcd 48820000 24410000
gcd(48820000, 24410000) = 24410000
```
## Technical Details
In order to complete my programm I created an other function in order to complete the recursion, that calculates and returns with Euclidean algorithm the greatest common divisor, between a 
(num1) and b (num2).
```c
long long int gcd(long long int a, long long int b){ 
    if ( a%b == 0 ){
        return llabs(b);
    }
    return gcd(b, a%b);
}
```
The most critical string of commands in my code, was to check if the user types two numbers a, b, when b isn't a factor of a. I have put the aMODb value in the new b value, because I want to 
return the factor aMODb. So it calculates bMOD(aMODb)==0 and return aMODb, which it the correct greatest common divisor.
```c
return gcd(b, a%b);
```