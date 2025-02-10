#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <time.h>

int main()
{
	MPI_Init(NULL,NULL);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	const int  MAX_NUMBERS = 100;
	int numbers[MAX_NUMBERS];
	int number_amount;
	if (rank == 0)
	{
		srand(time(NULL));
		number_amount = (rand() / (float)RAND_MAX) * MAX_NUMBERS;
		MPI_Send(numbers,number_amount,MPI_INT,1,0,MPI_COMM_WORLD);
		printf("0 sent %d numbers to 1\n",number_amount);
	} else if(rank == 1){
		MPI_Status status;
		MPI_Probe(0,0,MPI_COMM_WORLD,&status);
		MPI_Get_count(&status,MPI_INT,&number_amount);
		int* number_buf = (int *)malloc(sizeof(int) * number_amount);

		MPI_Recv(number_buf,number_amount,MPI_INT,0,0,MPI_COMM_WORLD,&status);

		printf("1 dynamically received %d numbers from 0. Message source = %d,"
			"tag = %d\n",
			number_amount,status.MPI_SOURCE,status.MPI_TAG);
		free(number_buf);
	}
	MPI_Finalize();
}
