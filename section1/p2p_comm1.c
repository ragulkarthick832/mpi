#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc,char **argv)
{
	MPI_Init(&argc,&argv);
	int size, rank;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	int local_value = atoi(argv[1]); // convert the command-line arguement to integer
	int other_value;
	if (rank == 0){
		// Code for process 0:
		// 1. Send the value to process 1
		// 2. Receive the value from process 1 (in other_value)
		// 3. Print the sum of the two values on stdout
		MPI_Recv(&other_value,1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Send(&local_value,1,MPI_INT,1,0,MPI_COMM_WORLD);
		printf("Process 0: Sum of values = %d\n",(local_value+other_value));
	} else if (rank == 1){
		 // 1. Receive the value from process 0 (in other_value)
        	 // 2. Send the value to process 0
        	 // 3. Print the product of the two values on stdout
        	 MPI_Send(&local_value,1,MPI_INT,0,0,MPI_COMM_WORLD);
        	 MPI_Recv(&other_value,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        	 printf("Process 1: Sum of values = %d\n",(local_value+other_value));
        }
        MPI_Finalize();
        return 0;
}
