#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>
#define ARRAY_SIZE 16


float* create_rand_num(int number_of_elements)
{
	float* array = (float *)malloc(sizeof(float) * number_of_elements);
	for(int i = 0; i < number_of_elements;i++)
	{
		array[i] = (float)(rand() % 100);
	}
	return array;
}
int main()
{
	MPI_Init(NULL,NULL);
	int world_size,world_rank;
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
	srand(time(NULL)+world_rank);
	int elements_per_proc = ARRAY_SIZE / world_size;

	float* rand_arr = create_rand_num(elements_per_proc);
	float local_sum = 0;
	int i;
	for (int i = 0; i < elements_per_proc; i++)
	{
		local_sum += rand_arr[i];
	}
	printf("Local sum for process %d - %f, avg = %f\n",world_rank,local_sum,local_sum / elements_per_proc);
	float global_sum;
	MPI_Reduce(&local_sum,&global_sum,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
	if (world_rank == 0)
	{
		printf("Total sum = %f, avg = %f\n",global_sum,global_sum / (world_size * elements_per_proc));
	}
	free(rand_arr);
	MPI_Finalize();
	return 0;
}
