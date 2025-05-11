# Jabbamaps Problem
This project calculates the fastest course, in order to go through all the towns from 
a file.

## Build & Dependencies
In order to compile this project you need the following tools: (1) `gcc` and (2) 
`libgcc-multilib`, to compile in 32bit systems. To download these tools execute the 
following commands:
```sh
sudo apt install gcc-multilib
```
Finally `compile` the project, with the command:
```sh
gcc -m32 -Ofast -Wall -Wextra -Werror -pedantic -o jabbamaps jabbamaps.c
```
## Usage
Now we `execute` the project without parameters, while the inputs are stdin:
```sh
./jabbamaps <filename>
```
## Demo
Here are some `examples` of this project, with different inputs:
```sh
$ ./jabbamaps
Usage: ./jabbamaps <filename>
$ echo $?
1
$ ./jabbamaps map4.txt
We will visit the cities in the following order:
Athens -(224)-> Patras -(223)-> Ioannina -(261)-> Thessaloniki
Total cost: 708
$ ./jabbamaps map6.txt
We will visit the cities in the following order:
Athens -(224)-> Patras -(122)-> Amfissa -(189)-> Volos -(211)-> Thessaloniki -(261)-> 
Ioannina
Total cost: 1007
$ ./jabbamaps map7.txt
We will visit the cities in the following order:
Athens -(211)-> Amfissa -(122)-> Patras -(223)-> Ioannina -(128)-> Trikala -(123)-> 
Volos -(211)-> Thessaloniki
Total cost: 1018
$ time ./jabbamaps tatooine.txt
We will visit the cities in the following order:
Republic City -(65)-> Aldera -(124)-> Anchorhead -(44)-> Lessu -(45)-> Mos Pelgo -(32)
-> Canto Bight -(65)-> Mos Espa -(80)-> Coronet City -(53)-> Hanna City -(50)-> Sern 
Prime -(62)-> NiJedha -(20)-> Kachirho -(66)-> Tipoca City -(141)-> Sundari -(51)-> 
Galactic City -(29)-> Capital City (Lothal City) -(157)-> Mos Eisley -(317)-> 
Stalgasin Hive -(26)-> Coral City -(25)-> Otoh Gunga -(13)-> Theed -(18)-> Cloud City -
(136)-> Eriadu City
Total cost: 1619

real    0m20,319s
user    0m19,739s
sys     0m0,580s
$ echo $?
0
```
## Technical Details
In order to complete my programm I used the Held Karp algorithm, about the Travelling 
salesman problem. The logic behind tsp function I implemented it from [Wikipedia](https://en.wikipedia.org/wiki/Held%E2%80%93Karp_algorithm#Pseudocode).