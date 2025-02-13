#include <stdio.h>
#include "mpi.h"

int main()
{
	int world_rank, world_size,token;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);
	
	if (world_rank != 0){
		MPI_Recv(&token,1,MPI_INT,(world_rank-1)%world_size,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("[Process %d] : received token as %d from process %d\n",world_rank,token,(world_rank-1)%world_size);
	}
	else {
		token = -1;
	}
	MPI_Send(&token,1,MPI_INT,(world_rank+1) % world_size,0,MPI_COMM_WORLD);
	if (world_rank == 0){
		MPI_Recv(&token,1,MPI_INT,(world_rank-1)%world_size,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("[Process 0] : received token as %d from process %d\n",token,world_size-1);
	}
	MPI_Finalize();
	return 0;
}
