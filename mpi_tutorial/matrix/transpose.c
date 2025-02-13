#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define N 4
#define M 4
int main()
{
	MPI_Init(NULL,NULL);
	int rank,size;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int* matrix = NULL;
	int* local_row = NULL;
	int* local_col = NULL;
	if (rank == 0)
	{
		int temp[N][M] = {{1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}};
		matrix = (int *)malloc(sizeof(int) * N * M);
		printf("Original matrix:\n");
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < M; j++)
			{
				matrix[i*N + j] = temp[i][j];
				printf("%d ",matrix[i*N+j]);
			}
			printf("\n");
		}
	}
	local_row = (int *)malloc(sizeof(int) * M);
	MPI_Scatter(matrix,M,MPI_INT,local_row,M,MPI_INT,0,MPI_COMM_WORLD);
	printf("process %d localview of row:",rank);
	for(int i =0;i<M;i++)
	{
		printf("%d ",local_row[i]);
	}
	printf("\n");
	local_col = (int *)malloc(sizeof(int) * N);
	MPI_Gather(&local_row[rank], 1, MPI_INT, local_col, 1, MPI_INT, rank, MPI_COMM_WORLD);

    	// Barrier for synchronization
    	MPI_Barrier(MPI_COMM_WORLD);
	printf("process %d localview col:",rank);
	for(int i =0;i<M;i++)
	{
		printf("%d ",local_col[i]);
	}
	printf("\n");
	free(local_row);
	free(local_col);
	if (rank == 0)
	{
		free(matrix);
	}
	MPI_Finalize();
	return 0;
}
