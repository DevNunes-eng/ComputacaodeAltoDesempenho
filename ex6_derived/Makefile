
CC = mpicc
CFLAGS = -O2 -Wall
NP = 4

# Alvos
EXEC1 = student_struct
EXEC2 = student_three_bcasts


all: $(EXEC1) $(EXEC2)

$(EXEC1): $(EXEC1).c
	$(CC) $(CFLAGS) -o $(EXEC1) $(EXEC1).c

$(EXEC2): $(EXEC2).c
	$(CC) $(CFLAGS) -o $(EXEC2) $(EXEC2).c


run_struct: $(EXEC1)
	@echo "--- Rodando versão com Tipo Derivado (Struct) ---"
	mpiexec  -n $(NP) ./$(EXEC1)

run_three: $(EXEC2)
	@echo "\n--- Rodando versão com 3 Bcasts separados ---"
	mpiexec  -n $(NP) ./$(EXEC2)


run: run_struct run_three


clean:
	rm -f $(EXEC1) $(EXEC2)