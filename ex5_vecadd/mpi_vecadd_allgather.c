/* mpi_vecadd_allgather.c
 * Module 3, Class 6 -- Parallel vector addition with
 * MPI_Scatter / MPI_Allgather.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define N 16  /* divisível por p */

int main(void) {
    int my_rank, comm_sz;
    double *x = NULL, *y = NULL;
    double *z_all = NULL; 

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    if (N % comm_sz != 0) {
        if (my_rank == 0)
            fprintf(stderr, "N=%d deve ser divisível por p=%d\n", N, comm_sz);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int local_n = N / comm_sz;
    double *local_x = (double *)malloc(local_n * sizeof(double));
    double *local_y = (double *)malloc(local_n * sizeof(double));
    double *local_z = (double *)malloc(local_n * sizeof(double));

    /* TODOS precisam alocar espaço para o vetor final no Allgather */
    z_all = (double *)malloc(N * sizeof(double));

    if (my_rank == 0) {
        x = (double *) malloc(N * sizeof(double));
        y = (double *) malloc(N * sizeof(double));
        for (int i = 0; i < N; i++) {
            x[i] = i;
            y[i] = 2.0 * i;
        }
    }

    MPI_Scatter(x, local_n, MPI_DOUBLE, local_x, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(y, local_n, MPI_DOUBLE, local_y, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < local_n; i++) {
        local_z[i] = local_x[i] + local_y[i];
    }

    /* Coleta o resultado em TODOS os processos */
    MPI_Allgather(local_z, local_n, MPI_DOUBLE, z_all, local_n, MPI_DOUBLE, MPI_COMM_WORLD);

    /* Verificando se todos os processos realmente possuem o resultado final */
    if (my_rank == comm_sz - 1) {
        printf("[ALLGATHER - Processo %d] Verificando último elemento: z_all[%d] = %g\n", my_rank, N-1, z_all[N-1]);
    }

    if (my_rank == 0) {
        free(x); free(y);
    }
    
    free(local_x); free(local_y); free(local_z); free(z_all);
    MPI_Finalize();
    return 0;
}