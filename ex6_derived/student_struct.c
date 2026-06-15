/* student_struct.c
 * Transmissão de uma struct via MPI usando Derived Datatypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h> 
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

    MPI_Datatype mpi_student_type;
    
    int blocklengths[3] = {50, 1, 1}; 
    MPI_Datatype types[3] = {MPI_CHAR, MPI_DOUBLE, MPI_INT};
    
    MPI_Aint displacements[3];
    displacements[0] = offsetof(struct Student, name);
    displacements[1] = offsetof(struct Student, grade);
    displacements[2] = offsetof(struct Student, id);

    // Constrói e "comita" o tipo para o MPI entender o layout de memória
    MPI_Type_create_struct(3, blocklengths, displacements, types, &mpi_student_type);
    MPI_Type_commit(&mpi_student_type);

    if (my_rank == 0) {
        strcpy(student.name, "Ada Lovelace");
        student.grade = 9.8;
        student.id = 101010;
        printf("[STRUCT - Processo 0] Transmitindo: '%s', Nota: %.1f, ID: %d\n", 
               student.name, student.grade, student.id);
    }

    /* Uma ÚNICA chamada envia a struct inteira para todos */
    MPI_Bcast(&student, 1, mpi_student_type, 0, MPI_COMM_WORLD);

    if (my_rank != 0) {
        printf("[STRUCT - Processo %d] Recebeu: '%s', Nota: %.1f, ID: %d\n", 
               my_rank, student.name, student.grade, student.id);
    }

    MPI_Type_free(&mpi_student_type);
    MPI_Finalize();
    return 0;
}