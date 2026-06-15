CC = mpicc
CFLAGS = -O2 -Wall
LIBS = -lm

TARGETS = mpi_hello_gather mpi_minmax

all: $(TARGETS)

mpi_hello_gather: mpi_hello_gather.c
	$(CC) $(CFLAGS) -o mpi_hello_gather mpi_hello_gather.c

mpi_minmax: mpi_minmax.c
	$(CC) $(CFLAGS) -o mpi_minmax mpi_minmax.c $(LIBS)

run_a: mpi_hello_gather
	mpiexec -n 4 ./mpi_hello_gather

run_b: mpi_minmax
	mpiexec -n 4 ./mpi_minmax


run: run_a run_b

clean:
	rm -f $(TARGETS)