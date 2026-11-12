#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, data = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
        data = 100;

    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received data: %d\n", rank, data);

    MPI_Finalize();
    return 0;
}
cl p8.c msmpi.lib
    mpiexec -n 4 p8.exec
gcc p7.c -o p7 -lmsmpi
mpiexec -n 4 ./p7
