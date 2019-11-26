#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <string.h>
#include <stdio.h>

#include "MatrixDeterminant.h"
#include "MatrixFunctions.h"
#include "MatrixIO.h"
#include "MatrixInverse.h"

#define CMD_LEN 32

/*
 *  MEM_DIM is located in MatrixFunctions.h
 *  MEM_DIM represents the memory allocated for the array,
 *  while DIM, a variable, represents the real dimensionof the matrix
*/

using namespace std;


void cmd_help();
void cmd_load(int DIM_R, int DIM_C, int mat[][MEM_DIM], char cmd[], bool* mem_loaded);
void cmd_det(int DIM_R, int DIM_C, int mat[][MEM_DIM], bool mem_loaded);
void cmd_inv(int DIM_R, int DIM_C, int mat[][MEM_DIM], float inv[][MEM_DIM], bool mem_loaded, bool* inv_loaded, int fprecision);
void cmd_prod(int* DIM_R, int* DIM_C, int mat[][MEM_DIM], matrix_wdim_t prod1, matrix_wdim_t prod2, bool prod1_loaded, bool prod2_loaded, bool* mem_loaded);
void cmd_fprecision(char cmd[], int* fprecision);
void cmd_printmem(int DIM_R, int DIM_C, int mat[][MEM_DIM], float inv[][MEM_DIM], matrix_wdim_t prod1, matrix_wdim_t prod2, char cmd[], bool mem_loaded, bool inv_loaded, bool prod1_loaded, bool prod2_loaded, int fprecision);
void cmd_movemem(char cmd[], int DIM_R, int DIM_C, int mat[][MEM_DIM], matrix_wdim_t* prod1, matrix_wdim_t* prod2, bool* prod1_loaded, bool* prod2_loaded, bool mem_loaded);
void cmd_clearmem(bool* mem_loaded, bool* inv_loaded, bool* prod1_loaded, bool* prod2_loaded);
void cmd_dim(int* DIM_R, int* DIM_C, char cmd[], bool* mem_loaded);
void cmd(char input[], char rootcommand[]);



int main()
{
	int DIM_R = 5;
	int DIM_C = 5;
	int mat[MEM_DIM][MEM_DIM];
	float inv[MEM_DIM][MEM_DIM];
	matrix_wdim_t prod1, prod2;

	char input[CMD_LEN + 1];
	char rootcommand[CMD_LEN + 1];

	int fprecision = 4;
	bool mem_loaded, inv_loaded, exit, prod1_loaded, prod2_loaded;


	mem_loaded = false;
	inv_loaded = false;
	prod1_loaded = false;
	prod2_loaded = false;
	exit = false;

	cout << "---------------------" << endl
		<< "| MatixSolver [C++] |" << endl
		<< "---------------------" << endl << endl;

	cout << "Allocated MEM: " << MEM_DIM << "x" << MEM_DIM << endl << "Used MEM: " << DIM_R << "x" << DIM_C << endl << "Type /help for more..." << endl << endl;

	do {

		cmd(input, rootcommand);

		if (strcmp(rootcommand, "/help") == 0)
			cmd_help();
		else if (strcmp(rootcommand, "/load") == 0)
			cmd_load(DIM_R, DIM_C, mat, input, &mem_loaded);
		else if (strcmp(rootcommand, "/det") == 0)
			cmd_det(DIM_R, DIM_C, mat, mem_loaded);
		else if (strcmp(rootcommand, "/inv") == 0)
			cmd_inv(DIM_R, DIM_C, mat, inv, mem_loaded, &inv_loaded, fprecision);
		else if (strcmp(rootcommand, "/prod") == 0)
			cmd_prod(&DIM_R, &DIM_C, mat, prod1, prod2, prod1_loaded, prod2_loaded, &mem_loaded);
		else if (strcmp(rootcommand, "/printmem") == 0)
			cmd_printmem(DIM_R, DIM_C, mat, inv, prod1, prod2, input, mem_loaded, inv_loaded, prod1_loaded, prod2_loaded, fprecision);
		else if (strcmp(rootcommand, "/clearmem") == 0)
			cmd_clearmem(&mem_loaded, &inv_loaded, &prod1_loaded, &prod2_loaded);
		else if (strcmp(rootcommand, "/movemem") == 0)
			cmd_movemem(input, DIM_R, DIM_C, mat, &prod1, &prod2, &prod1_loaded, &prod2_loaded, mem_loaded);
		else if (strcmp(rootcommand, "/dim") == 0)
			cmd_dim(&DIM_R, &DIM_C, input, &mem_loaded);
		else if (strcmp(rootcommand, "/fprecision") == 0)
			cmd_fprecision(input, &fprecision);

		else if (strcmp(rootcommand, "/exit") == 0)
			exit = true;
		else if (strcmp(rootcommand, "\0") != 0 && strcmp(rootcommand, "\n") != 0)
			cout << '"' << rootcommand << '"' << ": Invalid Command" << endl;
		else
			cout << endl;
	} while (exit == false);


	return 0;
}

void cmd(char input[], char rootcommand[])
{
	int i;
	cout << ">>";
	gets_s(input, CMD_LEN);

	i = 0;
	while (input[i] != ' ' && input[i] != '\0') {
		rootcommand[i] = input[i];
		i++;
	}
	rootcommand[i] = '\0';
}

void cmd_help() {
	cout << "------------------------------------------\n";
	cout << " MatrixSolver.cpp \n" <<
		"            Developed by Leonardo Airoldi \n";
	cout << "------------------------------------------\n";

	cout << "HELP:" << endl;

	cout << "/help:\n  Prints out all the commands available" << endl << endl;

	cout << "/load [args]\n"
		<< "  Load a matrix in the program memory and write that on the hard drive\n"
		<< "  [args]\n"
		<< "    - ''\n"
		<< "        Show the memory status\n"
		<< "    - random\n"
		<< "        Load a random-generated matrix\n"
		<< "    - input\n"
		<< "        Load the matrix from the keyboard\n"
		<< "    - file [FILENAME]\n"
		<< "        Load the matrix from the file specified in FILENAME\n"
		<< endl;

	cout << "/clearmem:\n  Clear the program memory" << endl << endl;

	cout << "/dim [args]\n"
		<< "  Change the dimension of the matrix and show information on the memory\n"
		<< "  [args]\n"
		<< "    - ''\n"
		<< "        Show the current matrix dimension\n"
		<< "    - n m\n"
		<< "        Set n m as the new matrix dimension\n"
		<< "    - alloc\n"
		<< "        Show the available memory for a matrix\n"
		<< endl;

	cout << "/printmem [args]\n"
		<< "  Print a matrix on screen\n"
		<< "  [args]\n"
		<< "    - mat\n"
		<< "        Prints the matrix loaded in memory\n"
		<< "    - inv\n"
		<< "        Prints the inverse matrix loaded in memory\n"
		<< "    - prod\n"
		<< "        Prints the two matrixes stored in the multiplication memory space\n"
		<< endl;

	cout << "/movemem [args]\n"
		<< "  Copies the matrix stored in memory to the product memory\n"
		<< "  [args]\n"
		<< "    - ''\n"
		<< "        Load the matrix in the first available product memory space\n"
		<< "    - 1 / 2\n"
		<< "        Load the matrix in the memory space specified\n"
		<< endl;

	cout << "/fprecision [args]\n"
		<< "  Change the precision of floating points numbers\n"
		<< "  Allowed precisions are 0 to 9 and 'm' for the maximum implemented\n"
		<< endl;

	cout << "/prod:\n  Calculates the product of the 2 matrixes in the multiplication memory" << endl << endl;

	cout << "/det:\n  Calculates the determinant of the loaded matrix" << endl << endl;

	cout << "/inv:\n  Calculates the invese matrix of the loaded one" << endl << endl;

	cout << "/exit:\n  Exit the program" << endl << endl;

	cout << "Program memory map: \n"
		<< "[0]: \n"
		<< "Main matrix memory. Can read and write\n"
		<< "[1]: \n"
		<< "Multiplication memory 1. Can read and write only loading a matrix from [0]. Contains information about the dimension as well\n"
		<< "[2]: \n"
		<< "Multiplicarion memory 2. Same as [1]\n"
		<< "[3]: \n"
		<< "Inverse matrix memory. Is float-type\n"
		<< "DIM_R: \n"
		<< "Variable for the nuber of rows of the matrix. Can be modified through /dim\n"
		<< "DIM_C: \n"
		<< "Variable for the nuber of rows of the matrix. Can be modified through /dim\n"
		<< endl;

}

void cmd_printmem(int DIM_R, int DIM_C, int mat[][MEM_DIM], float inv[][MEM_DIM], matrix_wdim_t prod1, matrix_wdim_t prod2, char cmd[], bool mem_loaded, bool inv_loaded, bool prod1_loaded, bool prod2_loaded, int fprecision) {
	if (strcmp(cmd, "/printmem mat") == 0) {
		if (mem_loaded) {
			cout << "Loaded in memory:" << endl;
			IO_PrintMat(DIM_R, DIM_C, mat);
		}
		else
			cout << "Error: Memory not loaded" << endl;
	}
	else if (strcmp(cmd, "/printmem inv") == 0) {
		if (inv_loaded) {
			cout << "Loaded in memory:" << endl;
			float_IO_PrintMat(DIM_R, DIM_C, inv, fprecision);
		}
		else
			cout << "Error: Memory not loaded" << endl;
	}
	else if (strcmp(cmd, "/printmem prod") == 0) {
		if (prod1_loaded) {
			cout << "Loaded in memory[1]:" << endl;
			IO_PrintMat(prod1.i, prod1.j, prod1.mat);
		}
		else
			cout << "Error: Memory[1] not loaded" << endl;
		if (prod2_loaded) {
			cout << "Loaded in memory[2]:" << endl;
			IO_PrintMat(prod2.i, prod2.j, prod2.mat);
		}
		else
			cout << "Error: Memory[2] not loaded" << endl;
	}
	else
		cout << "Error: Invalid Parameters" << endl;

}

void cmd_clearmem(bool* mem_loaded, bool* inv_loaded, bool* prod1_loaded, bool* prod2_loaded) {
	*mem_loaded = false;
	*inv_loaded = false;
	*prod1_loaded = false;
	*prod2_loaded = false;
}

void cmd_dim(int* DIM_R, int* DIM_C, char cmd[], bool* mem_loaded) {
	int i, start;
	char new_dim_r[16];
	char new_dim_c[16];

	if (strcmp(cmd, "/dim") == 0)
		cout << "Current matrix dimension: " << *DIM_R << "x" << *DIM_C << endl;
	else if (strcmp(cmd, "/dim alloc") == 0)
		cout << "Current allocated space per matrix: " << MEM_DIM << "x" << MEM_DIM << endl;
	else {
		start = 5;
		i = start;
		while (cmd[i] != ' ') {
			new_dim_r[i - start] = cmd[i];
			i++;
		}
		new_dim_r[i] = '\0';

		i++;
		start = i;

		while (cmd[i] != '\0') {
			new_dim_c[i - start] = cmd[i];
			i++;
		}
		new_dim_c[i] = '\0';

		if (atoi(new_dim_r) > 1 && atoi(new_dim_r) < MEM_DIM && atoi(new_dim_c) > 1 && atoi(new_dim_c) < MEM_DIM) {
			*DIM_R = atoi(new_dim_r);
			*DIM_C = atoi(new_dim_c);
			*mem_loaded = false;
		}
		else
			cout << "Error: Invalid dimension" << endl;
	}

}

void cmd_fprecision(char cmd[], int* fprecision) {
	if (cmd[12] >= '0' && cmd[12] <= '9')
		*fprecision = cmd[12] - '0';
	else if (cmd[12] == 'm')
		*fprecision = MAX_PRECISION;
	else
		cout << "Error: Invalid parameter" << endl;
}

void cmd_load(int DIM_R, int DIM_C, int mat[][MEM_DIM], char cmd[], bool* mem_loaded) {
	if (strcmp(cmd, "/load") == 0) {
		cout << "Memory status: [" << *mem_loaded << "]" << endl;
	}
	else {
		int i;
		char mode[CMD_LEN];
		for (i = 6; cmd[i] != '\0' && cmd[i] != ' '; i++)
			mode[i - 6] = cmd[i];
		mode[i - 6] = '\0';

		if (strcmp(mode, "random") == 0) {
			IO_RandMat(DIM_R, DIM_C, mat);

			cout << "Loaded in memory:" << endl;
			IO_PrintMat(DIM_R, DIM_C, mat);
			IO_fPrintMat(DIM_R, DIM_C, mat, "mat.txt");

			*mem_loaded = true;
		}
		else if (strcmp(mode, "input") == 0) {
			IO_UserInput(DIM_R, DIM_C, mat);
			IO_fPrintMat(DIM_R, DIM_C, mat, "mat.txt");

			*mem_loaded = true;
		}
		else if (strcmp(mode, "file") == 0) {
			char path[CMD_LEN];
			for (i = 11; cmd[i] != '\0'; i++)
				path[i - 11] = cmd[i];
			path[i - 11] = '\0';

			if (IO_Load_File(DIM_R, DIM_C, mat, path)) {
				*mem_loaded = true;
				IO_PrintMat(DIM_R, DIM_C, mat);
			}
			else {
				*mem_loaded = false;
				cout << "Error opening the file";
			}
		}
		else
			cout << "Error: Invalid Parameters" << endl;
	}

}

void cmd_inv(int DIM_R, int DIM_C, int mat[][MEM_DIM], float inv[][MEM_DIM], bool mem_loaded, bool* inv_loaded, int fprecision) {
	if (mem_loaded) {
		if (DIM_R == DIM_C) {
			Mat_Inverse(DIM_R, mat, inv);

			cout << "Inverse: " << endl;
			float_IO_PrintMat(DIM_R, DIM_C, inv, fprecision);
			float_IO_fPrintMat(DIM_R, DIM_C, inv, "inv.txt", fprecision);

			*inv_loaded = true;
		}
		else
			cout << "Error: Matrix is not square" << endl;
	}
	else
		cout << "Error: Memory not loaded" << endl;
}

void cmd_det(int DIM_R, int DIM_C, int mat[][MEM_DIM], bool mem_loaded) {
	if (mem_loaded) {
		if (DIM_R == DIM_C)
			cout << "Det: " << Det_Laplace(DIM_R, mat) << endl;
		else
			cout << "Error: Matrix is not squared" << endl;
	}
	else
		cout << "Error: Memory not loaded" << endl;
}

void cmd_movemem(char cmd[], int DIM_R, int DIM_C, int mat[][MEM_DIM], matrix_wdim_t* prod1, matrix_wdim_t* prod2, bool* prod1_loaded, bool* prod2_loaded, bool mem_loaded)
{
	if (mem_loaded)
	{
		if (cmd[8] == '\0') {
			if (!*prod1_loaded) {
				Matrix_Convert_Type(prod1, mat, &DIM_R, &DIM_C, 0);
				*prod1_loaded = true;
				cout << "Matrix loaded into [1]" << endl;
			}
			else if (!*prod2_loaded) {
				Matrix_Convert_Type(prod2, mat, &DIM_R, &DIM_C, 0);
				*prod2_loaded = true;
				cout << "Matrix loaded into [2]" << endl;
			}
			else {
				Matrix_Convert_Type(prod1, mat, &DIM_R, &DIM_C, 0);
				*prod1_loaded = true;
				cout << "Matrix loaded into [1]" << endl;
			}
		}
		else {
			if (cmd[9] == '1') {
				Matrix_Convert_Type(prod1, mat, &DIM_R, &DIM_C, 0);
				*prod1_loaded = true;
				cout << "Matrix loaded into [1]" << endl;
			}
			else if (cmd[9] == '2') {
				Matrix_Convert_Type(prod2, mat, &DIM_R, &DIM_C, 0);
				*prod2_loaded = true;
				cout << "Matrix loaded into [2]" << endl;
			}
			else
				cout << "Error: invalid product memory address" << endl;
		}
	}
	else
		cout << "Error: Memory not loaded" << endl;


}

void cmd_prod(int* DIM_R, int* DIM_C, int mat[][MEM_DIM], matrix_wdim_t prod1, matrix_wdim_t prod2, bool prod1_loaded, bool prod2_loaded, bool* mem_loaded)
{
	matrix_wdim_t p;

	if (prod1_loaded && prod2_loaded) {
		p = Matrix_Multiplicaion(prod1, prod2);

		Matrix_Convert_Type(&p, mat, DIM_R, DIM_C, 1);
		*mem_loaded = true;

		cout << "Matrix product: " << endl;
		IO_PrintMat(*DIM_R, *DIM_C, mat);
	}
	else
		cout << "Error: Memory not loaded" << endl;

}
