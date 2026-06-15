#define _GNU_SOURCE
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char** argv) {
    int my_rank, comm_sz;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    int N = 100000; // Tamanho do vetor exigido (10^5)
    double *vetor_global = NULL;
    double soma_serial = 0.0;

    // Apenas o Processo 0 gera os dados aleatorios e calcula a referencia serial
    if (my_rank == 0) {
        srand(42); // Semente fixa para reprodutibilidade
        vetor_global = (double*)malloc(N * sizeof(double));
        for (int i = 0; i < N; i++) {
            vetor_global[i] = (double)rand() / RAND_MAX;
            soma_serial += vetor_global[i];
        }
    }

    // Divisao de carga para N arbitrario (caso p nao divida N perfeitamente)
    int rem = N % comm_sz;
    int local_N = N / comm_sz + (my_rank < rem ? 1 : 0);
    double *vetor_local = (double*)malloc(local_N * sizeof(double));

    // [AULA 5] Distribuicao manual usando um laco de MPI_Send
    if (my_rank == 0) {
        // O processo 0 apenas copia a sua propria fatia local
        for (int i = 0; i < local_N; i++) {
            vetor_local[i] = vetor_global[i];
        }

        // Laco para enviar as respectivas fatias aos demais processos
        int offset = local_N;
        for (int p = 1; p < comm_sz; p++) {
            int p_local_N = N / comm_sz + (p < rem ? 1 : 0);
            MPI_Send(&vetor_global[offset], p_local_N, MPI_DOUBLE, p, 0, MPI_COMM_WORLD);
            offset += p_local_N;
        }
    } else {
        // Os demais processos recebem suas fatias passivamente
        MPI_Recv(vetor_local, local_N, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Cada processo calcula sua soma local
    double soma_local = 0.0;
    for (int i = 0; i < local_N; i++) {
        soma_local += vetor_local[i];
    }

    // Coleta manual das somas parciais no Processo 0
    double soma_paralela = 0.0;
    if (my_rank == 0) {
        soma_paralela = soma_local; // Inclui a soma do proprio processo 0
        for (int p = 1; p < comm_sz; p++) {
            double soma_recebida;
            MPI_Recv(&soma_recebida, 1, MPI_DOUBLE, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            soma_paralela += soma_recebida;
        }

        // Computa o erro relativo (espera-se uma micro diferenca por conta da reordenacao)
        double erro_relativo = fabs(soma_paralela - soma_serial) / soma_serial;

        printf("Soma Serial:   %.10f\n", soma_serial);
        printf("Soma Paralela: %.10f\n", soma_paralela);
        printf("Erro Relativo: %e\n", erro_relativo);
    } else {
        // Processos escravos devolvem suas somas parciais para o root
        MPI_Send(&soma_local, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    // Liberacao de memoria limpa (evita vazamentos)
    free(vetor_local);
    if (my_rank == 0) {
        free(vetor_global);
    }

    MPI_Finalize();
    return 0;
}