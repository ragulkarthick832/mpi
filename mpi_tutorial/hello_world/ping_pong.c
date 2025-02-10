#include <stdio.h>
#include "mpi.h"

int ping_count = 0;
#define MAX_PING_COUNT  10
#define TAG 100
int main()
{
	MPI_Init(NULL,NULL);
	int world_rank,world_size;
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);

	int partner_process = (world_rank+1) % 2;
	while (ping_count < MAX_PING_COUNT)
	{
		if (world_rank == ping_count % 2){
			ping_count ++;
			MPI_Send(&ping_count,1,MPI_INT,partner_process,TAG,MPI_COMM_WORLD);
			printf("[Process %d] send %d to process %d\n",world_rank,ping_count,partner_process);
			fflush(stdout);
		} else {
			MPI_Recv(&ping_count,1,MPI_INT,partner_process,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("[Process %d] received %d from process %d\n",world_rank,ping_count,partner_process);
			fflush(stdout);
		}
	}
	MPI_Finalize();
	return 0;
}
