CC = mpicc
CFLAGS = -O2 -Wall
LIBS = -lm

all: hello_os hello_ring

hello_os: hello_os.c
	$(CC) $(CFLAGS) -o hello_os hello_os.c $(LIBS)

hello_ring: hello_ring.c
	$(CC) $(CFLAGS) -o hello_ring hello_ring.c $(LIBS)

run: hello_os hello_ring
	mpiexec  -n 8 ./hello_os
	@echo "---------------------------------------"
	mpiexec  -n 4 ./hello_ring

clean:
	rm -f hello_os hello_ring