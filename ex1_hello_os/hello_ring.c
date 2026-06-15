#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    int my_rank, comm_sz;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    if (comm_sz < 2) {
        if (my_rank == 0) {
            printf("Modo anel precisa de pelo menos 2 processos para circular.\n");
        }
        MPI_Finalize();
        return 0;
    }

    char msg_send[100], msg_recv[100];
    sprintf(msg_send, "Hello de %d", my_rank);

    int dest = (my_rank + 1) % comm_sz;
    int source = (my_rank - 1 + comm_sz) % comm_sz;

    // MPI_Sendrecv evita o deadlock enviando e recebendo concorrentemente
    MPI_Sendrecv(msg_send, 100, MPI_CHAR, dest, 0,
                 msg_recv, 100, MPI_CHAR, source, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // O processo 0 coleta e imprime todas as saudações recebidas
    if (my_rank == 0) {
        printf("--- Centralizado no Rank 0 ---\n");
        printf("Rank 0 recebeu: [%s]\n", msg_recv);

        // Coleta sequencialmente o que os outros ranks receberam
        for (int p = 1; p < comm_sz; p++) {
            char msg_coleta[100];
            MPI_Recv(msg_coleta, 100, MPI_CHAR, p, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Rank %d recebeu: [%s]\n", p, msg_coleta);
        }
    } else {
        // Envia o resultado obtido no anel para o processo 0 imprimir ordenadamente
        MPI_Send(msg_recv, 100, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}