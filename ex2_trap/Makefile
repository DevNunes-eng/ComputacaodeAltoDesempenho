CC = mpicc
CFLAGS = -O2 -Wall
LIBS = -lm
TARGET = mpi_trap_generalized

all: $(TARGET)

$(TARGET): mpi_trap_generalized.c
	$(CC) $(CFLAGS) -o $(TARGET) mpi_trap_generalized.c $(LIBS)

# Executa o caso do Exercício 2(a)
run_2a: $(TARGET)
	@echo "--- Executando Exercício 2(a) ---"
	mpiexec --oversubscribe -n 3 ./$(TARGET) 10

# Executa os casos de escalabilidade do Exercício 2(b)
run_2b: $(TARGET)
	@echo "--- Executando Exercício 2(b) ---"
	mpiexec --oversubscribe -n 1 ./$(TARGET)
	mpiexec --oversubscribe -n 2 ./$(TARGET)
	mpiexec --oversubscribe -n 4 ./$(TARGET)
	mpiexec --oversubscribe -n 8 ./$(TARGET)

# Executa as coletas de convergência do Exercício 2(c)
run_2c: $(TARGET)
	@echo "--- Executando Exercício 2(c) ---"
	mpiexec --oversubscribe -n 4 ./$(TARGET) 64
	mpiexec --oversubscribe -n 4 ./$(TARGET) 256
	mpiexec --oversubscribe -n 4 ./$(TARGET) 1024
	mpiexec --oversubscribe -n 4 ./$(TARGET) 4096
	mpiexec --oversubscribe -n 4 ./$(TARGET) 16384

# Executa todos os exercícios de uma vez
run: run_2a run_2b run_2c

clean:
	rm -f $(TARGET)