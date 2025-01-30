#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv) {
    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Reading size and rank
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Printing
    printf("Hello world, from process #%d\n",rank);

    // Finalize MPI environment
    MPI_Finalize();

    return 0;
}
