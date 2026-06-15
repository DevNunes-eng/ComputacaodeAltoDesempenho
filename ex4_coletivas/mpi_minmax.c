#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int my_rank, comm_sz;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    int N = 100000; // Tamanho do vetor (10^5)
    double *vetor_global = NULL;
    double max_serial = -1.0, min_serial = 2.0;

    if (my_rank == 0) {
        srand(123); // Semente fixa
        vetor_global = (double*)malloc(N * sizeof(double));
        for (int i = 0; i < N; i++) {
            vetor_global[i] = (double)rand() / RAND_MAX; // Valores entre 0 e 1
            if (vetor_global[i] > max_serial) max_serial = vetor_global[i];
            if (vetor_global[i] < min_serial) min_serial = vetor_global[i];
        }
    }

    // Como p divide N (hipotese padrão), cada um recebe N/p elementos
    int local_N = N / comm_sz;
    double *vetor_local = (double*)malloc(local_N * sizeof(double));

    // Dispersão coletiva
    MPI_Scatter(vetor_global, local_N, MPI_DOUBLE, 
                vetor_local, local_N, MPI_DOUBLE, 
                0, MPI_COMM_WORLD);

    // Cada processo calcula seu maximo e minimo local
    double local_max = -1.0;
    double local_min = 2.0;
    for (int i = 0; i < local_N; i++) {
        if (vetor_local[i] > local_max) local_max = vetor_local[i];
        if (vetor_local[i] < local_min) local_min = vetor_local[i];
    }

    // Reducoes globais
    double global_max, global_min;
    MPI_Reduce(&local_max, &global_max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_min, &global_min, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);

    if (my_rank == 0) {
        printf("[SERIAL]   Min: %.10f | Max: %.10f\n", min_serial, max_serial);
        printf("[PARALELO] Min: %.10f | Max: %.10f\n", global_min, global_max);
        printf("Verificacao: %s\n", (fabs(global_max - max_serial) < 1e-9 && fabs(global_min - min_serial) < 1e-9) ? "SUCESSO" : "FALHA");
        free(vetor_global);
    }

    free(vetor_local);
    MPI_Finalize();
    return 0;
}