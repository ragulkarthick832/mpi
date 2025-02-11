#include <stdio.h>
#include "mpi.h"

int main()
{
	int world_rank;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
	int data1,data2;
	if (world_rank == 0){
		printf("Enter two numbers :");
		fflush(stdout);
		scanf("%d %d",&data1,&data2);
	}
	MPI_Bcast(&data1, 1, MPI_INT, 0, MPI_COMM_WORLD);
    	MPI_Bcast(&data2, 1, MPI_INT, 0, MPI_COMM_WORLD);

	fflush(stdout);
	if (world_rank == 1)
		printf("Addition : %d\n",data1+data2);
	else if (world_rank == 2)
		printf("Subtraction : %d\n",data1-data2);
	else if (world_rank == 3)
		printf("Multiplication : %d\n",data1*data2);
	else if (world_rank == 4)
		printf("Division : %d\n",data1/data2);
	MPI_Finalize();
	return 0;
}
