#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define N 4
#define M 5


int main()
{
	MPI_Init(NULL,NULL);
	int rank,size;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int matrix[N][M];
	int transpose[M][N];
	int local_row[M];
	if (rank == 0)
	{
		// initialize the matrix
		printf("Original Matrix:\n");
		for(int i =0;i<N;i++)
		{
			for(int j = 0; j<M;j++)
			{
				matrix[i][j] = i*N+j+1;
				printf("%d ",matrix[i][j]);
			}
			printf("\n");
		}
	}
	MPI_Scatter(matrix,M,MPI_INT,local_row,M,MPI_INT,0,MPI_COMM_WORLD);
	for(int i = 0; i < M; i++)
	{
		MPI_Gather(&local_row[i],1,MPI_INT,transpose[i],1,MPI_INT,0,MPI_COMM_WORLD);
	}
	if (rank == 0)
	{
		printf("Transpose Matrix:\n");
                for(int i =0;i<M;i++)
                {
                        for(int j = 0; j<N;j++)
                        {
                                printf("%d ",transpose[i][j]);
                        }
                        printf("\n");
                }
	}
	MPI_Finalize();
	return 0;
}
