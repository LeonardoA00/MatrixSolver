#pragma once

#include <math.h>
#include <iostream>

#define MEM_DIM 32

typedef struct indexes_s {
	int rows[MEM_DIM] = {};
	int columns[MEM_DIM] = {};
} indexes_t;

typedef struct matrix_wdim_s {
	int mat[MEM_DIM][MEM_DIM] = {};
	int i = 0, j = 0;
} matrix_wdim_t;

int Mat_Dimension(int DIM, indexes_t mat_indexes)
{
	int i, count;
	count = 0;
	for (i = 0; i < DIM; i++) {
		if (mat_indexes.rows[i] == 1)
			count++;
	}

	return count;
}

indexes_t Mat_SubMat(indexes_t mat_indexes, int i, int j) {
	mat_indexes.rows[i] = 0;
	mat_indexes.columns[j] = 0;
	return mat_indexes;
}

matrix_wdim_t Matrix_Multiplicaion(matrix_wdim_t mat1, matrix_wdim_t mat2)
{
	matrix_wdim_t prod;
	int i, j, k, r;

	//Check for multiplication compatiility
	if (mat1.j != mat2.i) {
		prod.i = 0;
		prod.j = 0;
		return prod;
	}

	r = mat1.j; //(i x r)(r x j)
	prod.i = mat1.i;
	prod.j = mat2.j;

	for (i = 0; i < prod.i; i++) {
		for (j = 0; j < prod.j; j++) {
			prod.mat[i][j] = 0;
			for (k = 0; k < r; k++) {
				//std::cout << prod.mat[i][j] << " + ";
				prod.mat[i][j] += mat1.mat[i][k] * mat2.mat[k][j];
			}
			//std::cout << std::endl;
		}
	}

	return prod;
}
