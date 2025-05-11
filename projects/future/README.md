# Future Problem
This project predicts what the next number in a sequence could be using and the Simple 
Moving Average (SMA) method.

## Build & Dependencies
In order to compile this project you need the `gcc` tool. Now `compile` the project, 
with the command:
```sh
gcc -Os -Wall -Wextra -Werror -pedantic -o future future.c
```
## Usage
Now we `execute` the project without parameters, while the inputs are stdin:
```sh
./future <filename> [--window N (default: 50)]
```
## Demo
Here are some `examples` of this project, with different inputs:
```sh
$ ./future
Usage: ./future <filename> [--window N (default: 50)]
$ echo $?
1
$ ./future values.txt --window 8
8.75
$ echo $?
0
$ ./future values.txt --window 0
Window too small!
$ echo $?
1
$ ./future values.txt --window 1000000000000
Failed to allocate window memory
$ echo $?
1
$ ./future dow_jones.txt
43471.71
$ ./future dow_jones.txt --window 8164
15203.17
```
## Technical Details
In order to complete my programm I used a logic, in order to include in A array only 
the last window values of the file. Firstly, I initialize counter to 0 and this counts 
the position that the new value will take place. Every time the commands in the loop 
are completed are done counter increases by 1, because for example 3 % 10 = 3. Finaly 
when (counter + 1) gets the value window then the counter goes back to 0 because 
window % window = 0. With that way the older values in the array are being replaced by 
the recent values.
```c
long long int counter = 0;
for (i = 0; fscanf(filename, "%lf", &a) == 1; i++){
    A[counter] = a;
    counter = (counter + 1) % window;
}
```