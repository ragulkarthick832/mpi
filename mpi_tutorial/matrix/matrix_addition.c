#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define N 3
int main()
{
	int rank,size;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int matrix_A[N][N] = {{1,2,3},{1,2,3},{1,2,3}};
	int matrix_B[N][N];
}

