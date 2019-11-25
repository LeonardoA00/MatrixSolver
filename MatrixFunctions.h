#pragma once

#include <math.h>

#define MEM_DIM 32

typedef struct indexes_s {
	int rows[MEM_DIM] = {};
	int columns[MEM_DIM] = {};
} indexes_t;

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
