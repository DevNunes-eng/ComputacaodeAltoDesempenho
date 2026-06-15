#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

#define MAX_STRING 100

int main(void) {
    char greeting[MAX_STRING];
    int  comm_sz, my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Cada processo monta sua propria saudacao
    snprintf(greeting, MAX_STRING, "Greetings from process %d of %d!", my_rank, comm_sz);

    // O processo 0 precisa de um vetor grande o suficiente para guardar todas as strings
    char* matriz_global = NULL;
    if (my_rank == 0) {
        matriz_global = (char*)malloc(comm_sz * MAX_STRING * sizeof(char));
    }

    // Coleta coletiva: todos enviam MAX_STRING caracteres, processo 0 recebe tudo ordenado
    MPI_Gather(greeting, MAX_STRING, MPI_CHAR, 
               matriz_global, MAX_STRING, MPI_CHAR, 
               0, MPI_COMM_WORLD);

    // O processo 0 imprime tudo na ordem correta dos ranks
    if (my_rank == 0) {
        for (int q = 0; q < comm_sz; q++) {
            // Avanca o ponteiro de MAX_STRING em MAX_STRING bytes para ler cada rank
            printf("%s\n", &matriz_global[q * MAX_STRING]);
        }
        free(matriz_global);
    }

    MPI_Finalize();
    return 0;
}