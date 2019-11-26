#pragma once

#include "MatrixFunctions.h"
#include "MatrixIO.h"
#include <math.h>

long long Laplace_Sum(int DIM, indexes_t mat_indexes, int mat[][MEM_DIM]);
int Det_Mat2(int a, int b, int c, int d);
int Det_Mat3(int a1, int a2, int a3, int b1, int b2, int b3, int c1, int c2, int c3);
long long Det_Laplace(int DIM, int mat[][MEM_DIM]);

long long Laplace_Sum(int DIM, indexes_t mat_indexes, int mat[][MEM_DIM])
{
	int i, j;
	int real_i, real_j;
	long long det = 0;
	long long temp;

	if (Mat_Dimension(DIM, mat_indexes) == 2) {
		int a, b, c, d;
		int countpos = 0;
		for (i = 0; i < DIM; i++) {
			if (mat_indexes.rows[i] == 1) {
				for (j = 0; j < DIM; j++) {
					if (mat_indexes.columns[j] == 1) {
						switch (countpos)
						{
						case 0:
							a = mat[i][j];
							break;
						case 1:
							b = mat[i][j];
							break;
						case 2:
							c = mat[i][j];
							break;
						case 3:
							d = mat[i][j];
							break;
						default:
							break;
						}
						countpos++;
					}
				}
			}
		}
		det = Det_Mat2(a, b, c, d);
	}

	if (Mat_Dimension(DIM, mat_indexes) == 3) {
		int a1, a2, a3, b1, b2, b3, c1, c2, c3;
		int countpos = 0;
		for (i = 0; i < DIM; i++) {
			if (mat_indexes.rows[i] == 1) {
				for (j = 0; j < DIM; j++) {
					if (mat_indexes.columns[j] == 1) {
						switch (countpos)
						{
						case 0:
							a1 = mat[i][j];
							break;
						case 1:
							a2 = mat[i][j];
							break;
						case 2:
							a3 = mat[i][j];
							break;
						case 3:
							b1 = mat[i][j];
							break;
						case 4:
							b2 = mat[i][j];
							break;
						case 5:
							b3 = mat[i][j];
							break;
						case 6:
							c1 = mat[i][j];
							break;
						case 7:
							c2 = mat[i][j];
							break;
						case 8:
							c3 = mat[i][j];
							break;
						default:
							break;
						}
						countpos++;
					}
				}
			}
		}
		det = Det_Mat3(a1, a2, a3, b1, b2, b3, c1, c2, c3);
	}

	else {
		i = 0;
		real_i = 0;
		real_j = 0;
		while (real_i == 0) {
			if (mat_indexes.rows[i] == 1) {
				real_i = 1;
				for (j = 0; j < DIM; j++) {
					if (mat_indexes.columns[j] == 1) {
						real_j++;
						temp = (long long)mat[i][j] * (int)pow(-1, (double)real_i + real_j);

						temp = temp * Laplace_Sum(DIM, Mat_SubMat(mat_indexes, i, j), mat);
						det = det + temp;
					}
				}

			}
			else
				i++;

		}
	}

	return det;
}

int Det_Mat2(int a, int b, int c, int d) {
	return a * d - c * b;
}

int Det_Mat3(int a1, int a2, int a3, int b1, int b2, int b3, int c1, int c2, int c3) {
	return a1 * b2 * c3 + a2 * b3 * c1 + a3 * b1 * c2 - c1 * b2 * a3 - c2 * b3 * a1 - c3 * b1 * a2;
}

long long Det_Laplace(int DIM, int mat[][MEM_DIM])
{
	int i;
	long long det;
	indexes_t mat_start;

	for (i = 0; i < DIM; i++) {
		mat_start.rows[i] = 1;
		mat_start.columns[i] = 1;
	}

	det = Laplace_Sum(DIM, mat_start, mat);

	return det;
}



/* Useful code for debugging (Place in Lapclace_Sum)

   cout << "Current computing: " << Mat_Dimension(DIM, mat_indexes) << endl;

   cout << temp << " x" << endl;
   IO_Print_SubMat(DIM, mat, Mat_SubMat(mat_indexes, i, j));

   cout << "= " << det << "End Of Computing"<< endl;

*/
