/* student_three_bcasts.c
 * Transmissão de dados heterogêneos usando 3 chamadas separadas de MPI_Bcast.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

struct Student {
    char name[50];
    double grade;
    int id;
};

int main(void) {
    int my_rank, comm_sz;
    struct Student student;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    if (my_rank == 0) {
        strcpy(student.name, "Ada Lovelace");
        student.grade = 9.8;
        student.id = 101010;
        printf("[3 BCASTS - Processo 0] Transmitindo: '%s', Nota: %.1f, ID: %d\n", 
               student.name, student.grade, student.id);
    }

    /* TRÊS chamadas separadas na rede */
    MPI_Bcast(student.name, 50, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(&student.grade, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&student.id, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (my_rank != 0) {
        printf("[3 BCASTS - Processo %d] Recebeu: '%s', Nota: %.1f, ID: %d\n", 
               my_rank, student.name, student.grade, student.id);
    }

    MPI_Finalize();
    return 0;
}