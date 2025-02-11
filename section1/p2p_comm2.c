#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    int rank, size;
    char msg[20];
    int tag = 99;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if (rank == 1){
        strcpy(msg, "Hello there");
        MPI_Send(msg, strlen(msg) + 1, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
        printf("message has been sent by process: %d\n", rank);
        fflush(stdout);  // Force output immediately
    } else if (rank == 0){
        MPI_Recv(msg, 20, MPI_CHAR, 1, tag, MPI_COMM_WORLD, &status);
        printf("message has been received by process: %d\n", rank);
        fflush(stdout);  // Force output immediately
    }

    MPI_Finalize();
    return 0;
}
