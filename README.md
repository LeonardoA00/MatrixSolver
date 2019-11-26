# MatrixSolver
A set of functions that can be helpful working around with matrixes

Here are listed the commands that can be used in the program.

 MatrixSolver.cpp
 -
           Developed by Leonardo Airoldi
            
HELP:
/help:
  Prints out all the commands available

/load [args]
  Load a matrix in the program memory and write that on the hard drive
  [args]
    - ''
        Show the memory status
    - random
        Load a random-generated matrix
    - input
        Load the matrix from the keyboard
    - file [FILENAME]
        Load the matrix from the file specified in FILENAME

/clearmem:
  Clear the program memory

/dim [args]
  Change the dimension of the matrix and show information on the memory
  [args]
    - ''
        Show the current matrix dimension
    - n m
        Set n m as the new matrix dimension
    - alloc
        Show the available memory for a matrix

/printmem [args]
  Print a matrix on screen
  [args]
    - mat
        Prints the matrix loaded in memory
    - inv
        Prints the inverse matrix loaded in memory
    - prod
        Prints the two matrixes stored in the multiplication memory space

/movemem [args]
  Copies the matrix stored in memory to the product memory
  [args]
    - ''
        Load the matrix in the first available product memory space
    - 1 / 2
        Load the matrix in the memory space specified

/fprecision [args]
  Change the precision of floating points numbers
  Allowed precisions are 0 to 9 and 'm' for the maximum implemented

/prod:
  Calculates the product of the 2 matrixes in the multiplication memory

/det:
  Calculates the determinant of the loaded matrix

/inv:
  Calculates the invese matrix of the loaded one

/exit:
  Exit the program

Program memory map:
[0]:
Main matrix memory. Can read and write
[1]:
Multiplication memory 1. Can read and write only loading a matrix from [0]. Contains information about the dimension as well
[2]:
Multiplicarion memory 2. Same as [1]
[3]:
Inverse matrix memory. Is float-type
DIM_R:
Variable for the nuber of rows of the matrix. Can be modified through /dim
DIM_C:
Variable for the nuber of rows of the matrix. Can be modified through /dim
