// ex1_hello_os/hello_os.c
#define _GNU_SOURCE
#include <mpi.h>
#include <stdio.h>
#include <unistd.h>   // getpid()
#include <sched.h>    // sched_getcpu()

int main(int argc, char** argv) {
    int my_rank, comm_sz;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    int pid = getpid();
    int cpu = sched_getcpu();

    printf("Hello from rank %d/%d -- PID = %d, CPU = %d\n", my_rank, comm_sz, pid, cpu);

    MPI_Finalize();
    return 0;
}