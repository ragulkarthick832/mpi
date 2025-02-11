#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>
#define ARRAY_SIZE 16

float compute_average(float *array,int number_of_elements){
	float sum = 0.0;
	for (int i = 0; i < number_of_elements; i++)
	{
		sum += array[i];
	}
	return sum / number_of_elements;
}

float* create_rand_num(int number_of_elements)
{
	float* array = (float *)malloc(sizeof(float) * number_of_elements);
	srand(time(NULL));
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

	int elements_per_proc = ARRAY_SIZE / world_size;
	float *rand_arr = NULL;
	if (world_rank == 0)
	{
		// root process initialize the random array
		rand_arr = create_rand_num(ARRAY_SIZE);
		//float rand_arr[ARRAY_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	}
	float *sub_array = (float *)malloc(sizeof(float) * elements_per_proc);
	MPI_Scatter(rand_arr,elements_per_proc,MPI_FLOAT,sub_array,elements_per_proc,MPI_FLOAT,0,MPI_COMM_WORLD);
	float sub_avg = compute_average(sub_array,elements_per_proc);
	free(sub_array);
	float *sub_avgs = NULL;
	if (world_rank == 0)
	{
		sub_avgs = (float *)malloc(sizeof(float) * world_size);
	}
	MPI_Gather(&sub_avg,1,MPI_FLOAT,sub_avgs,1,MPI_FLOAT,0,MPI_COMM_WORLD);
	if (world_rank == 0){
		float avg = compute_average(sub_avgs,world_size);
		printf("Overall avgs: %f\n",avg);
		free(sub_avgs);
		free(rand_arr);
	}
	MPI_Finalize();
	return 0;
}
