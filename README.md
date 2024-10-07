# Maze

Goals: Understand recursion and solve a maze

Given a text file representing a maze, as below, find the path for
creature to get to the exit and mark the path explored.
```
20 7
0 18
6 12
XXXXXXXXXXXXXXXXXX X
X     X       XXXX X
X XXXXX XXXXX   XX X
X XXXXX XXXXXXX XX X
X X          XX XX X
X XXXXXXXXXX XX    X
XXXXXXXXXXXX XXXXXXX
```

Solution:

`*` shows the final path to exit

`+` shows areas explored but not part of the final path

Might backtrack or not depending on order of directions being tried
```
*** Solving maze1.txt
Path: NNWWWWWNNNEEEEEESEESSSEEENNNNN
XXXXXXXXXXXXXXXXXX*X
X     X*******XXXX*X
X XXXXX*XXXXX***XX*X
X XXXXX*XXXXXXX*XX*X
X X    ******XX*XX*X
X XXXXXXXXXX*XX****X
XXXXXXXXXXXX*XXXXXXX
```

## Included Files

- `maze.cpp` and `maze.h`: Definitions for maze functions

- `main.cpp`: Runs all tests

- `output.txt`: Output from `./create-output.sh > output.txt 2>&1`
showing how the program is compiled and run.

- `create-output.sh`: Unix bash script file to compile, run 
and then delete the executable. Can be used to create an output.txt file

- `check-code-coverage.sh`: Check if every line of code is being executed


## Compile and Run

```
./create-output.sh`
```

or

```
g++ -g -std=c++11 -Wall -Wextra -Wno-sign-compare *.cpp
```


### Style Explanation
The options are defined in `.clang-tidy` file.

## Issues / Notes

At maze.cpp:94 I was trying to put a return false to address the warning:
"warning: control reaches end of non-void function [-Wreturn-type]"
but when adding the return false my maze would be registered as failed to solve; even though the printed maze would show a solved path. I lose my code coverage and get this warning in exchange for code that solves the maze. I'll attach the code coverage I get when adding the return false in the Canvas submission notes if I can.

