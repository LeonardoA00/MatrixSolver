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
    - n
        Set n as the new matrix dimension
    - alloc
        Show the available memory for a matrix

/printmem [args]
  Print a matrix on screen
  [args]
    - mat
        Prints the matrix loaded in memory
    - inv
        Prints the inverse matrix loaded in memory

/fprecision [args]
  Change the precision of floating points numbers
  Allowed precisions are 0 to 9 and 'm' for the maximum implemented

/det:
  Calculates the determinant of the loaded matrix

  Calculates the invese matrix of the loaded one

/exit:
  Exit the program
