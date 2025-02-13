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
	int matrix_A[N][N] = {{1,6,3},{1,7,3},{8,2,3}};
	int matrix_B[N][N] = {{1,2,3},{1,2,-8},{7,2,3}};
	int matrix_result[N][N];
	int local_row_A[N];
	int local_row_B[N];
	int local_result[N];
	MPI_Scatter(matrix_A,N,MPI_INT,local_row_A,N,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(matrix_B,N,MPI_INT,local_row_B,N,MPI_INT,0,MPI_COMM_WORLD);
	for(int i =0;i < N; i++)
	{
		local_result[i] = local_row_A[i]+local_row_B[i];
	}
	MPI_Gather(local_result,N,MPI_INT,&matrix_result[rank],N,MPI_INT,0,MPI_COMM_WORLD);
	if (rank == 0)
	{
		printf("Result matrix:\n");
		for(int i =0; i< N;i++)
		{
			for(int j = 0; j < N;j++)
			{
				printf("%d ",matrix_result[i][j]);
			}
			printf("\n");
		}
	}
	MPI_Finalize();
	return 0;
}

