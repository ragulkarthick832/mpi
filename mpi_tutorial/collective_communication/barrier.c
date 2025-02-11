#include <stdio.h>
#include "mpi.h"

int main()
{
	MPI_Init(NULL,NULL);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
	printf("[Process %d] started to wait\n",world_rank);
	fflush(stdout);
	MPI_Barrier(MPI_COMM_WORLD);
	printf("[Process %d] after barrier\n",world_rank);
	fflush(stdout);	
	MPI_Finalize();
	return 0;
}
