#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int rank,size;
    const int rows = 4, cols =4;
    int matrix[rows][cols]={{1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}};

    int transposed[rows][cols];

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int chunksize = rows/size;
    int submatrix[chunksize][cols];
    int subtranspose[chunksize][cols];

    MPI_Scatter(matrix,chunksize*cols,MPI_INT,submatrix,chunksize*cols,MPI_INT,MPI_COMM_WORLD);

    for(int i =0; i<chunksize;i++)
    {
        for(int j=0; j<cols;j++)
        {
            subtranspose[j][i]=submatrix[i][j];
        }
    }
    MPI_Gather(subtranspose,chunksize*cols,MPI_INT,transposed,chunksize*cols,MPI_INT,0,MPI_COMM_WORLD);
    if (rank == 0) {
        printf("Transposed Matrix:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%d ", transposed[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
return 0;
}
