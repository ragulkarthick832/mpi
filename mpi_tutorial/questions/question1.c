/*
Write an MPI parallel search program to find all occurrences of a certain integer in an array.
The master stores the array and target value, then distributes portions to workers. Each worker
counts occurrences in its portion and sends the result back to the master, which finds the total
occurrences and displays them.

*/

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define ARRAY_SIZE 16
#define TARGET 10
int main()
{
	MPI_Init(NULL,NULL);
	int world_size,world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);
	int* main_array = NULL;
	int main_target;
	int elements_per_proc = ARRAY_SIZE / world_size;
	if (world_rank == 0)
	{
		main_array = (int *)malloc(sizeof(int) * ARRAY_SIZE);
		int temp[ARRAY_SIZE] = {1,2,10,10,5,6,7,8,9,10,11,12,13,14,15,16};
		for (int i = 0; i < ARRAY_SIZE; i++)
       		 {
            		main_array[i] = temp[i];
       		 }
        	main_target = TARGET; // Target value to find
	}
	int* sub_array = (int *)malloc(sizeof(int) * elements_per_proc);
	MPI_Scatter(main_array,elements_per_proc,MPI_INT,sub_array,elements_per_proc,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&main_target,1,MPI_INT,0,MPI_COMM_WORLD);
	int count = 0;
	for (int i = 0; i < elements_per_proc;i++)
	{
		if (sub_array[i] == main_target)
			count ++;
	}
	printf("The number of count in process %d is %d\n",world_rank,count);
	free(sub_array);
	int global_count;
	MPI_Reduce(&count,&global_count,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if (world_rank == 0)
	{
		printf("The number of occuerence in global view is %d\n",global_count);
		free(main_array);
	}
	MPI_Finalize();
	return 0;
}
