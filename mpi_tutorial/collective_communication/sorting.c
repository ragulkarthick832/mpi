#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

#define ARRAY_SIZE 16

int* create_rand_array(int number_of_elements)
{
	srand(time(NULL));
	int* array = (int *)malloc(sizeof(int) * number_of_elements);
	for(int i=0; i<number_of_elements;i++)
	{
		array[i] = (int)(rand()%100);
	}
	return array;
}

int compare(const void* a, const void* b)
{
	return (*(int *)a - *(int *)b);
}

void merge(int* array,int left, int mid, int right){
	int left_size = mid - left + 1;
	int right_size = right - mid;
	int* left_arr = (int *)malloc(sizeof(int) * left_size);
	int* right_arr = (int *)malloc(sizeof(int) * right_size);

	for(int i = 0; i < left_size; i++)
	{
		left_arr[i] = array[left+i];
	}
	for(int i = 0; i < right_size;i++)
	{
		right_arr[i] = array[mid+1+i];
	}
	int i = 0, j = 0, k = left;
	while (i < left_size && j < right_size){
		if (left_arr[i] <= right_arr[j])
			array[k++] = left_arr[i++];
		else
			array[k++] = right_arr[j++];
	}
	while (i < left_size)
		array[k++] = left_arr[i++];
	while (j < right_size)
		array[k++] = right_arr[j++];
	free(left_arr);
	free(right_arr);
}

void merge_sorted_sections(int* array,int num_sections,int section_size)
{
	for(int i = 1; i < num_sections;i++)
	{
		merge(array,0,(i * section_size) -1, (i+1) * section_size - 1);
	}
}
int main()
{
	MPI_Init(NULL,NULL);
	int world_rank,world_size;
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);
	int elements_per_proc = ARRAY_SIZE / world_size;
	int* rand_num = NULL;
	if (world_rank == 0)
	{
		// initialize the rand_num
		rand_num = create_rand_array(ARRAY_SIZE);
	}
	int* sub_array = (int *)malloc(sizeof(int) * elements_per_proc);
	MPI_Scatter(rand_num,elements_per_proc,MPI_INT,sub_array,elements_per_proc,MPI_INT,0,MPI_COMM_WORLD);
	// sort the subarray
	qsort(sub_array,elements_per_proc,sizeof(int),compare);
	MPI_Gather(sub_array,elements_per_proc,MPI_INT,rand_num,elements_per_proc,MPI_INT,0,MPI_COMM_WORLD);
	free(sub_array);
	if (world_rank == 0)
	{
		//  merge the received array
		merge_sorted_sections(rand_num,world_size,elements_per_proc);
		printf("Sorted array: \n");
		for(int i = 0; i < ARRAY_SIZE;i++)
		{
			printf("%d ",rand_num[i]);
		}
		printf("\n");

		free(rand_num);
	}
	
	MPI_Finalize();
	return 0;
}
