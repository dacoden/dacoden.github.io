# Jason Problem
This project handles json files and prints the content as also as it does ai chat bot 
conversation.

## Build & Dependencies
In order to compile this project you need the `gcc` tool. Now `compile` the project, 
with these three commands:
```sh
gcc -Wall -Wextra -Werror -pedantic -c neurolib.c
gcc -Wall -Wextra -Werror -pedantic -c jason.c
gcc -o jason neurolib.o jason.o -lssl -lcrypto
```
## Usage
Now we `execute` the project without parameters, while the inputs are stdin:
```sh
./jason --bot / ./jason --extract <filename>
```
## Demo
Here are some `examples` of this project, with different inputs:
```sh
$ ./jason
Usage: ./jason --bot / ./jason --extract <filename>
$ echo $?
1
$ ./jason --extract json/1.json
Why do programmers always mix up Halloween and Christmas?
Because Oct 31 == Dec 25!
$ echo $?
0
$ ./jason --extract json/2.json
Not an accepted JSON!
$ echo $?
1
$ ./jason --extract json/3.json
A happy thought is picturing yourself surrounded by loved ones, laughing and enjoying 
each other's company.
$ ./jason --bot
> What would you like to know? What is the name of the cat in di in UOA?
Let me consult my magic eight-ball oh, it says 'try again later.' Classic eight-ball 
move!
> What would you like to know? How to open a door?
Do you want the correct answer or the one that makes us both laugh?
> What would you like to know? Terminating
$ echo $?
0
```
## Technical Details
In order to complete my programm I used a logic where instead of making a struct that 
has the structure of a json file and search there for the json.choices[0].message.
content, I just searched for the content inside the "" and compared it with the word 
content and if the word was content I just printed the content of the next "".