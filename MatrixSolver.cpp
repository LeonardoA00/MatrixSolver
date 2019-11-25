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
void cmd_load(int DIM, int mat[][MEM_DIM], char cmd[], bool *mem_loaded);
void cmd_det(int DIM, int mat[][MEM_DIM], bool mem_loaded);
void cmd_inv(int DIM, int mat[][MEM_DIM], float inv[][MEM_DIM], bool mem_loaded, bool* inv_loaded, int fprecision);
void cmd_fprecision(char cmd[], int* fprecision);
void cmd_printmem(int DIM, int mat[][MEM_DIM], float inv[][MEM_DIM], char cmd[], bool mem_loaded, bool inv_loaded, int fprecision);
void cmd_clearmem(bool* mem_loaded, bool* inv_loaded);
void cmd_dim(int* DIM, char cmd[], bool* mem_loaded);
void cmd(char input[], char rootcommand[]);



int main()
{
	int DIM = 5;
	int mat[MEM_DIM][MEM_DIM];
	float inv[MEM_DIM][MEM_DIM];

	char input[CMD_LEN + 1];
	char rootcommand[CMD_LEN + 1];

	int fprecision = 4;
	bool mem_loaded, inv_loaded, exit;


	mem_loaded = false;
	inv_loaded = false;
	exit = false;

	cout << "---------------------" << endl
		 << "| MatixSolver [C++] |" << endl
		 << "---------------------" << endl << endl;

	cout << "Allocated MEM: " << MEM_DIM << "x" << MEM_DIM << endl << "Used MEM: " << DIM << "x" << DIM << endl << "Type /help for more..." << endl << endl;

	do {

		cmd(input, rootcommand);

		if (strcmp(rootcommand, "/help") == 0)
			cmd_help();
		else if (strcmp(rootcommand, "/load") == 0)
			cmd_load(DIM, mat, input, &mem_loaded);
		else if (strcmp(rootcommand, "/det") == 0)
			cmd_det(DIM, mat, mem_loaded);
		else if (strcmp(rootcommand, "/inv") == 0)
			cmd_inv(DIM, mat, inv, mem_loaded, &inv_loaded, fprecision);
		else if (strcmp(rootcommand, "/printmem") == 0)
			cmd_printmem(DIM, mat, inv, input, mem_loaded, inv_loaded, fprecision);
		else if (strcmp(rootcommand, "/clearmem") == 0)
			cmd_clearmem(&mem_loaded, &inv_loaded);
		else if (strcmp(rootcommand, "/dim") == 0)
			cmd_dim(&DIM, input, &mem_loaded);
		else if (strcmp(rootcommand, "/fprecision") == 0)
			cmd_fprecision(input, &fprecision);

		else if (strcmp(rootcommand, "/exit") == 0)
			exit = true;
		else if (strcmp(rootcommand, "\0") != 0 && strcmp(rootcommand, "\n") != 0)
			cout << '"' << rootcommand << '"' << ": Invalid Command" << endl;
		else
			cout << endl;
	}
	while (exit == false);


	return 0;
}

void cmd(char input[], char rootcommand[])
{
	int i;
	cout << ">>";
	gets(input);

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
		<< "    - n\n"
		<< "        Set n as the new matrix dimension\n"
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

		<< endl;

	cout << "/fprecision [args]\n"
		<< "  Change the precision of floating points numbers\n"
		<< "  Allowed precisions are 0 to 9 and 'm' for the maximum implemented\n"
		<< endl;

	cout << "/det:\n  Calculates the determinant of the loaded matrix"  << endl << endl;

	cout << "/inv:\n  Calculates the invese matrix of the loaded one" << endl << endl;

	cout << "/exit:\n  Exit the program" << endl << endl;

}

void cmd_printmem(int DIM, int mat[][MEM_DIM], float inv[][MEM_DIM], char cmd[], bool mem_loaded, bool inv_loaded, int fprecision) {
	if (strcmp(cmd, "/printmem mat") == 0) {
		if (mem_loaded) {
			cout << "Loaded in memory:" << endl;
			IO_PrintMat(DIM, mat);
		}
		else
			cout << "Error: Memory not loaded" << endl;
	}
	else if (strcmp(cmd, "/printmem inv") == 0) {
		if (inv_loaded) {
			cout << "Loaded in memory:" << endl;
			float_IO_PrintMat(DIM, inv, fprecision);
		}
		else
			cout << "Error: Memory not loaded" << endl;
	}
	else
		cout << "Error: Invalid Parameters" << endl;

}

void cmd_clearmem(bool* mem_loaded, bool* inv_loaded) {
	*mem_loaded = false;
	*inv_loaded = false;
}

void cmd_dim(int* DIM, char cmd[], bool* mem_loaded) {
	int i;
	char new_dim[16];

	if (strcmp(cmd, "/dim") == 0)
		cout << "Current matrix dimension: " << *DIM << "x" << *DIM << endl;
	else if (strcmp(cmd, "/dim alloc") == 0)
		cout << "Current allocated space per matrix: " << MEM_DIM << "x" << MEM_DIM << endl;
	else {
		i = 5;
		while (cmd[i] != '\0') {
			new_dim[i - 5] = cmd[i];
			i++;
		}
		new_dim[i] = '\0';

		if (atoi(new_dim) > 1 && atoi(new_dim) < MEM_DIM) {
			*DIM = atoi(new_dim);
			*mem_loaded = false;
		}
		else
			cout << "Error: Invalid dimension" << endl;
	}

}

void cmd_fprecision(char cmd[], int* fprecision) {
	if (cmd[12] >= '0' && cmd[12] < '10')
		*fprecision = cmd[12] - '0';
	else if (cmd[12] == 'm')
		*fprecision = MAX_PRECISION;
	else
		cout << "Error: Invalid parameter" << endl;
}

void cmd_load(int DIM, int mat[][MEM_DIM], char cmd[], bool *mem_loaded) {
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
			IO_RandMat(DIM, mat);

			cout << "Loaded in memory:" << endl;
			IO_PrintMat(DIM, mat);
			IO_fPrintMat(DIM, mat, "mat.txt");

			*mem_loaded = true;
		}
		else if (strcmp(mode, "input") == 0) {
			IO_UserInput(DIM, mat);
			IO_fPrintMat(DIM, mat, "mat.txt");

			*mem_loaded = true;
		}
		else if (strcmp(mode, "file") == 0) {
			char path[CMD_LEN];
			for (i = 11; cmd[i] != '\0'; i++)
				path[i - 11] = cmd[i];
			path[i - 11] = '\0';

			if (IO_Load_File(DIM, mat, path)) {
				*mem_loaded = true;
				IO_PrintMat(DIM, mat);
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

void cmd_inv(int DIM, int mat[][MEM_DIM], float inv[][MEM_DIM], bool mem_loaded, bool* inv_loaded, int fprecision) {
	if (mem_loaded) {
		Mat_Inverse(DIM, mat, inv);

		cout << "Inverse: " << endl;
		float_IO_PrintMat(DIM, inv, fprecision);
		float_IO_fPrintMat(DIM, inv, "inv.txt", fprecision);

		*inv_loaded = true;
	}
	else
		cout << "Error: Memory not loaded" << endl;
}

void cmd_det(int DIM, int mat[][MEM_DIM], bool mem_loaded) {
	if (mem_loaded)
		cout << "Det: " << Det_Laplace(DIM, mat) << endl;
	else
		cout << "Error: Memory not loaded" << endl;
}
