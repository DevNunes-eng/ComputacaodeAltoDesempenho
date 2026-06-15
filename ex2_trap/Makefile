CC = mpicc
CFLAGS = -O2 -Wall
LIBS = -lm
TARGET = mpi_trap_generalized

all: $(TARGET)

$(TARGET): mpi_trap_generalized.c
	$(CC) $(CFLAGS) -o $(TARGET) mpi_trap_generalized.c $(LIBS)

run: $(TARGET)
	mpiexec  -n 4 ./$(TARGET)

clean:
	rm -f $(TARGET)