#pragma once

#include "MatrixFunctions.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

#define DIM_NUM 100
#define MAX_PRECISION 20
/*Remember to change the max_precision values in printfs too*/


using namespace std;

int IO_RandMat(int DIM_R, int DIM_C, int mat[][MEM_DIM])
{
	srand(time(NULL));
	for (int i = 0; i < DIM_R; i++) {
		for (int j = 0; j < DIM_C; j++)
			mat[i][j] = rand() % DIM_NUM;
	}

	return 1;
}

int IO_UserInput(int DIM_R, int DIM_C, int mat[][MEM_DIM])
{
	for (int i = 0; i < DIM_R; i++) {
		for (int j = 0; j < DIM_C; j++) {
			cin >> mat[i][j];
		}
	}

	return 1;
}

int float_IO_fPrintMat(int DIM_R, int DIM_C, float mat[][MEM_DIM], string path, int fprecision)
{
	int i, j;
	ofstream mat_log;
	mat_log.open(path);
	mat_log.precision(MAX_PRECISION);

	for (i = 0; i < DIM_R; i++) {
		for (j = 0; j < DIM_C; j++) {
			mat_log << mat[i][j] << "\t\t";
		}
		mat_log << endl;
	}

	mat_log.close();

	return 1;
}

int IO_fPrintMat(int DIM_R, int DIM_C, int mat[][MEM_DIM], string path)
{
	int i, j;
	ofstream mat_log;
	mat_log.open(path);
	for (i = 0; i < DIM_R; i++) {
		for (j = 0; j < DIM_C; j++) {
			mat_log << mat[i][j] << "\t";
		}
		mat_log << endl;
	}

	mat_log.close();

	return 1;
}


int float_IO_PrintMat(int DIM_R, int DIM_C, float mat[][MEM_DIM], int fprecision)
{
	int i, j;

	for (i = 0; i < DIM_R; i++) {
		for (j = 0; j < DIM_C; j++) {
			if (mat[i][j] < 0) {
				switch (fprecision) {
				case 0:
					printf("%d", (int)mat[i][j]);
					break;
				case 1:
					printf("%.1f\t", mat[i][j]);
					break;
				case 2:
					printf("%.2f\t", mat[i][j]);
					break;
				case 3:
					printf("%.3f\t", mat[i][j]);
					break;
				case 4:
					printf("%.4f\t", mat[i][j]);
					break;
				case 5:
					printf("%.5f\t", mat[i][j]);
					break;
				case 6:
					printf("%.6f\t", mat[i][j]);
					break;
				case 7:
					printf("%.7f\t", mat[i][j]);
					break;
				case 8:
					printf("%.8f\t", mat[i][j]);
					break;
				case 9:
					printf("%.9f\t", mat[i][j]);
					break;
				case 10:
					printf("%.10f\t", mat[i][j]);
					break;
				case MAX_PRECISION:
					printf("%.20f\t", mat[i][j]);
					break;
				}
			}
			else {
				switch (fprecision) {
				case 0:
					printf("%d", (int)mat[i][j]);
					break;
				case 1:
					printf(" %.1f\t", mat[i][j]);
					break;
				case 2:
					printf(" %.2f\t", mat[i][j]);
					break;
				case 3:
					printf(" %.3f\t", mat[i][j]);
					break;
				case 4:
					printf(" %.4f\t", mat[i][j]);
					break;
				case 5:
					printf(" %.5f\t", mat[i][j]);
					break;
				case 6:
					printf(" %.6f\t", mat[i][j]);
					break;
				case 7:
					printf(" %.7f\t", mat[i][j]);
					break;
				case 8:
					printf(" %.8f\t", mat[i][j]);
					break;
				case 9:
					printf(" %.9f\t", mat[i][j]);
					break;
				case 10:
					printf(" %.10f\t", mat[i][j]);
					break;
				case MAX_PRECISION:
					printf(" %.20f\t", mat[i][j]);
					break;
				}
			}

		}
		cout << endl;
	}

	return 1;
}


int IO_PrintMat(int DIM_R, int DIM_C, int mat[][MEM_DIM])
{
	int i, j;

	for (i = 0; i < DIM_R; i++) {
		for (j = 0; j < DIM_C; j++) {
			cout << mat[i][j] << "\t";
		}
		cout << endl;
	}

	return 1;
}

int IO_Load_File(int DIM_R, int DIM_C, int mat[][MEM_DIM], char path[]) {

	ifstream mat_file;
	mat_file.open(path);

	for (int i = 0; i < DIM_R; i++) {
		for (int j = 0; j < DIM_C; j++) {
			mat_file >> mat[i][j];
		}
	}

	mat_file.close();

	return 1;
}

int IO_Print_SubMat(int DIM, int mat[][MEM_DIM], indexes_t indexes) {
	int i = 0;
	int j;
	while (i < DIM) {
		if (indexes.rows[i] == 1) {
			for (j = 0; j < DIM; j++) {
				if (indexes.columns[j] == 1) {
					cout << mat[i][j] << "\t";
				}
			}
			cout << endl;

		}
		i++;

	}
	cout << endl;

	return 1;
}

void Matrix_Convert_Type(matrix_wdim_t* matwd, int mat[][MEM_DIM], int* DIM_R, int* DIM_C, int from_to) {
	/*fromm_to: The verse in which to do the conversion
		0: from array to strucy
		1: from struct to array
	*/
	int i, j;
	if (from_to == 0) {
		matwd->i = *DIM_R;
		matwd->j = *DIM_C;
		for (i = 0; i < *DIM_R; i++)
			for (j = 0; j < *DIM_C; j++)
				matwd->mat[i][j] = mat[i][j];
	}
	else if (from_to == 1) {
		*DIM_R = matwd->i;
		*DIM_C = matwd->j;
		for (i = 0; i < *DIM_R; i++)
			for (j = 0; j < *DIM_C; j++)
				mat[i][j] = matwd->mat[i][j];
	}
}
