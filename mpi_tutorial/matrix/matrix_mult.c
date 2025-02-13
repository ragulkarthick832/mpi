#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int sumpro(int *arr1,int *arr2,int size){
    int result=0;
    for(int i=0;i<size;i++){
        
            result+=arr1[i]*arr2[i];
        
    }
    return result;
}
int main()
{
	int rank,size;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int a[3][3]={{1,2,3},{4,5,6},{7,8,9}};
    	int localrow[3];
    	int b[3][3]={{11,12,13},{14,15,16},{17,18,19}};
    	int bt[3][3];
    	int c[3][3];

	if(rank == 0)
	{
		printf("Matrix A:\n");
		for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                
                printf(" %d ",a[i][j]);
            }
            printf("\n");
        }
		printf("Matrix B:\n");
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                
                printf(" %d ",b[i][j]);
            }
            printf("\n");
        }
	}
	// scatter the contents of matrix b row wise and store it in local_row
	MPI_Scatter(b,3,MPI_INT,localrow,3,MPI_INT,0,MPI_COMM_WORLD);
	// transposing the matrix b
	for(int k=0;k<3;k++){
        MPI_Gather(&localrow[k],1,MPI_INT,bt[k],1,MPI_INT,0,MPI_COMM_WORLD);
    
    }
	// direct crossponding mulitplication of a and b(Transpose)
	if(rank==0){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                c[i][j]=sumpro(a[i],bt[j],3);
            }
        }
		printf("Matrix AxB:\n");

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                
                printf(" %d ",c[i][j]);
            }
            printf("\n");
        }
    }
	MPI_Finalize();
	return 0;
}

