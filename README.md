# Vector Calculator
## Description
Performs the following operations: 
*   Adding vectors
*   Subtracting vectors
*   Scalar multiplication of vectors
*   Storing vectors
*   Writing and loading .csv files with vector data

## Building program
Compile with $ make

## Commands
Run with ./VectCalc 
To run with help menu displayed :
* ./VectCalc -h
* ./VectCalc --help
Starts program and displays help menu
* 'help' - displays help menu
* 'quit' - exits program 
* 'list' - lists stored vectors
* 'clear' - clears list of stored vectors

## Use of dynamic memory
Dynamic memory was implemented into the program via a doubly linked list. Each vector is stored in a dynamically allocated Node within the linked list. The clear() function frees all allocated memory and atexit(clear) ensures no memory leaks occur when exiting the program.

