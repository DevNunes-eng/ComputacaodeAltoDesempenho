#define _GNU_SOURCE
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Função a ser integrada: f(x) = sin(x)
double f(double x) {
    return sin(x);
}

int main(int argc, char** argv) {
    int my_rank, comm_sz;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    // Começa a cronometrar AGORA (incluindo overhead inicial para p=1 ser justo)
    double start_time = MPI_Wtime();

    // Parâmetros padrão exigidos
    int n = 10000000; // 10^7 por padrão
    double a = 0.0;
    double b = M_PI; // Pi vindo de math.h

    // Permite passar o valor de n via linha de comando se desejado (ex: ./mpi_trap_generalized 10)
    if (argc > 1) {
        n = atoi(argv[1]);
    }

    double h = (b - a) / n;

    // Bloco generalizado para balanceamento de carga arbitrário (p não divide n)
    int rem     = n % comm_sz;
    int local_n = n / comm_sz + (my_rank < rem ? 1 : 0);
    int offset  = my_rank * (n / comm_sz) + (my_rank < rem ? my_rank : rem);
    double local_a = a + offset * h;
    double local_b = local_a + local_n * h;

    // Cálculo da regra do trapézio local
    double local_int = 0.0;
    if (local_n > 0) {
        local_int = (f(local_a) + f(local_b)) / 2.0;
        for (int i = 1; i < local_n; i++) {
            local_int += f(local_a + i * h);
        }
        local_int = local_int * h;
    }

    // Redução do resultado usando MPI_Reduce
    double total_int = 0.0;
    MPI_Reduce(&local_int, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Finaliza a medição de tempo de relógio
    double end_time = MPI_Wtime();
    double local_elapsed = end_time - start_time;

    // Captura o tempo do processo mais lento para representar o tempo paralelo real T_p
    double max_elapsed;
    MPI_Reduce(&local_elapsed, &max_elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (my_rank == 0) {
        // Formatação refinada mostrando o resultado e o tempo
        printf("N = %d | Resultado: %.15f | Tempo: %f s\n", n, total_int, max_elapsed);
    }

    MPI_Finalize();
    return 0;
}