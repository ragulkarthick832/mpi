/*
Implement an MPI program by simulating round-robin communication by passing an integer value. Messages are
send from 0-1-2->0 involving 3 processes. Each time the value is received, it should be decremented by a fixed
value (number which signifies the clock value). Once the value becomes zero or negative, the process that is currently
updating it should notify all other processes of its rank. Every process should then display the rank of the process where
the counter reached zero. You can supply the initial countdown value. A sample output for the initial integer value N-18 and
countdown value of dec- 3 in process 0 is shown for you.
Sample Output:

Process 1 has received the value (15 on the clock) and is still alive! Process 2 has received the value (12 on the clock) and is still alive!
Process 0 has received the value (9 on the clock) and is still alive! Process 1 has received the value (6 on the clock) and is still alive!
Process 2 has received the value (3 on the clock) and is still alive! Process 0 lost

I am process 0 and 0 is the loser
I am process 2 and 0 is the loser
I am process 1 and 0 is the loser
*/

#include <stdio.h>
#include "mpi.h"
#define DEC 3

int main()
{
	MPI_Init(NULL,NULL);
	int world_rank,world_size;
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);
	int main_number[2];
	int flag = 0;
	if (world_rank == 0)
	{
		// initialize the main number
		int temp[2] = {21,-1};
		main_number[0] = temp[0];
		main_number[1] = temp[1];
		main_number[0] -= DEC;
		MPI_Ssend(&main_number,2,MPI_INT,(world_rank+1)%world_size,0,MPI_COMM_WORLD);
	}
	MPI_Recv(&main_number,2,MPI_INT,(world_rank-1+world_size)%world_size,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	while(1){
		if (flag == 1){
		if (main_number[0] <= 0){
			MPI_Recv(&main_number,2,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			break;
		}
		MPI_Recv(&main_number,2,MPI_INT,(world_rank-1+world_size)%world_size,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

			if (main_number[1] != -1){
				break;
			}
		}
		
		if (main_number[0] > 0){
			flag = 1;
			printf("Process %d has received the value (%d on the clock) and is still alive\n",world_rank,main_number[0]);
			fflush(stdout);
			main_number[0] -= DEC;
			MPI_Ssend(&main_number,2,MPI_INT,(world_rank+1)%world_size,0,MPI_COMM_WORLD);
		}
		else{
			printf("Process %d is loser...\n",world_rank);
			main_number[1] = world_rank;
			
			break;
	 	}
	}
	
	if (world_rank == main_number[1]){
				main_number[0] += DEC;
				for(int i = 0; i < world_size; i++)
				{
					if (i!=main_number[1])	
						MPI_Ssend(&main_number,2,MPI_INT,i,0,MPI_COMM_WORLD);
			
				}
			}
		
	if (world_rank != main_number[1])
	{
		printf("I am process %d and %d is the loser\n",world_rank,main_number[1]);
	}
	MPI_Finalize();
	return 0;
}
