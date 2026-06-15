CC = mpicc
CFLAGS = -O2 -Wall
LIBS = -lm
TARGET = mpi_psum

all: $(TARGET)

$(TARGET): mpi_psum.c
	$(CC) $(CFLAGS) -o $(TARGET) mpi_psum.c $(LIBS)

run: $(TARGET)
	mpiexec  -n 4 ./$(TARGET)

clean:
	rm -f $(TARGET)