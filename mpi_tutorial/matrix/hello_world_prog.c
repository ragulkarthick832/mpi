#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define ARRAY_SIZE 4
int main()
{
	MPI_Init(NULL,NULL);
	int rank,size;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	int* matrix = NULL;
	int elements_per_proc = ARRAY_SIZE;
	if (rank == 0){
		matrix = (int *)malloc(sizeof(int)* 16);
		int temp[4][4] = {{1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}};
		for(int i = 0; i <4;i++)
		{
			for(int j = 0; j < 4;j++)
			{
				matrix[i*ARRAY_SIZE + j] = temp[i][j];
			}
		}
	}
	int* local_row = (int *)malloc(sizeof(int) * elements_per_proc);
	MPI_Scatter(matrix,elements_per_proc,MPI_INT,local_row,elements_per_proc,MPI_INT,0,MPI_COMM_WORLD);
	printf("Process %d local view: ",rank);
	for(int i = 0; i<elements_per_proc;i++){
		printf("%d ",local_row[i]);
	}
	printf("\n");
	free(local_row);
	if(rank == 0)
	{
		free(matrix);
	}
	MPI_Finalize();
	return 0;
}
