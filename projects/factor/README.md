# Factor Problem
This project finds the two prime factors of a semiprime number.

## Build & Dependencies
In order to compile this project you need the `gcc` tool. Now `compile` the project, with the command:
```sh
gcc -O3 -Wall -Wextra -Werror -o factor factor.c -lm
```
## Usage
Now we `execute` the project without parameters, while the inputs are stdin:
```sh
./factor <semiprime>
```
## Demo
Here are some `examples` of this project, with different inputs:
```sh
$ ./factor
Usage: ./factor <semiprime>
$ echo $?
1
$ ./factor 93
Factors: 3 31
$ echo $?
0
$ ./factor 9827348119
Factors: 613 16031563
$ echo $?
0
$ ./factor 2524891914334062643
Factors: 1175747593 2147477851
$ echo $?
0
```
## Technical Details
In order to complete my programm I used another function in order to print an unsigned 128 bit number. Firstly I take 2 cases if the number is greater than 1000000000000000000 or lower or equal. In the first case I divide the num with 1000000000000000000 in order to calculate the first N-18 digits of the num which gives me the first 64 bits(high) and now I take the modulus of dividing the num with 1000000000000000000 which calculate the last N-18 digits of the num which gives me the last 64 bits(low). Then I print the high number and after the low, while adding to the low number the remaining 0 in the 64-M digits, where are "blank" digits.(where N = num digits and M = low digits). Else it prints just the num because it takes less than 64 bits.
```c
void print_large_uint128(uint128_t num) {
    unsigned long long int ten_power_18 = 1000000000000000000ULL;
    if (num > ten_power_18) {
        unsigned long long int high = num / ten_power_18;
        unsigned long long int low = num % ten_power_18;
        printf("%llu%018llu", high, low);
    }
    else {
        printf("%llu", (unsigned long long int)num);
    }
}
```
The most critical string of commands in my code, was to use another function in order to convert a string of characters to a number sum. So I check if the str points to a valid memory location before attempting to dereference it(for example avoid reading the 0 value), and check if the string is empty. Then I subtract '0' from the biggest bit of the string and by multiplying with ten the previous sum it will get the biggest bit to the left and so on, while increasing the pointer by 1 every time, it will return the number I converted from a string.
```c
uint128_t atou128(const char *str) {
    uint128_t sum = 0;
    if (!str || *str == '\0') {
        exit(1);
    }
    while (*str) {
        if (*str >= '0' && *str <= '9') {
            sum = sum * 10 + (*str - '0');
        } 
        else {
            exit(1);
        }
        str++;
    }
    return sum;
}
```