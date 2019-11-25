#pragma once

#include "MatrixDeterminant.h"
#include "MatrixFunctions.h"

int Mat_AlgComp(int DIM, int mat[][MEM_DIM], int row, int col)
{
	int i;
	int comp;

	indexes_t mat_start;
	for (i = 0; i < DIM; i++) {
		mat_start.rows[i] = 1;
		mat_start.columns[i] = 1;
	}

	mat_start = Mat_SubMat(mat_start, row, col);
	comp = (int)pow(-1, (double)row + (double)col) * Laplace_Sum(DIM, mat_start, mat);

	return comp;
}


int Mat_Inverse(int DIM, int mat[][MEM_DIM], float inv[][MEM_DIM])
{
	int i, j;

	for (i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++) {
			inv[j][i] = (float)Mat_AlgComp(DIM, mat, i, j) / Det_Laplace(DIM, mat);
		}
	}

	return 0;
}
