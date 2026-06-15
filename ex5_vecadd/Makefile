# Variáveis
CC = mpicc
CFLAGS = -O2 -Wall
LDFLAGS = -lm
NP = 4

# Alvos
EXEC1 = mpi_vecadd_gather
EXEC2 = mpi_vecadd_allgather

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(EXEC1).c
	$(CC) $(CFLAGS) -o $(EXEC1) $(EXEC1).c $(LDFLAGS)

$(EXEC2): $(EXEC2).c
	$(CC) $(CFLAGS) -o $(EXEC2) $(EXEC2).c $(LDFLAGS)

run: $(EXEC1) $(EXEC2)
	@echo "--- Rodando versão GATHER ---"
	mpiexec  -n $(NP) ./$(EXEC1)
	@echo "\n--- Rodando versão ALLGATHER ---"
	mpiexec  -n $(NP) ./$(EXEC2)

clean:
	rm -f $(EXEC1) $(EXEC2)