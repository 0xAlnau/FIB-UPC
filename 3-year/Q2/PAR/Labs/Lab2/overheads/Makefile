CC = icx
NITER	 = 1
OPENMP	 = -qopenmp
CFLAGS   = -Wall -O0 -std=c99 $(OPENMP)
CLIBS    =
IINCL    = -I/usr/include/
ILIBS    = -lomptrace -L/usr/lib -lrt

TARGETS  = pi_sequential pi_omp_parallel pi_omp_tasks pi_omp_critical pi_omp_atomic pi_omp_sumlocal pi_omp_reduction
.PHONY: pi_sequential pi_omp_parallel pi_omp_tasks pi_omp_critical pi_omp_atomic pi_omp_sumlocal pi_omp_reduction

all: $(TARGETS)

pi_sequential: pi_sequential.c
	$(CC) $(CFLAGS) $< -o $@ $(CLIBS)

pi_omp_parallel: pi_omp_parallel.c
	$(CC) $(CFLAGS) -DNUMITERS=10000 $< -o $@ $(CLIBS)

pi_omp_tasks: pi_omp_tasks.c
	$(CC) $(CFLAGS) -DNUMITERS=10000 $< -o $@ $(CLIBS)

pi_omp_sumlocal: pi_omp_sumlocal.c
	$(CC) $(CFLAGS) -DNUMITERS=$(NITER) $< -o $@ $(CLIBS)

pi_omp_critical: pi_omp_critical.c
	$(CC) $(CFLAGS) -DNUMITERS=$(NITER) $< -o $@ $(CLIBS)

pi_omp_atomic: pi_omp_atomic.c
	$(CC) $(CFLAGS) -DNUMITERS=$(NITER) $< -o $@ $(CLIBS)

pi_omp_reduction: pi_omp_reduction.c
	$(CC) $(CFLAGS) -DNUMITERS=$(NITER) $< -o $@ $(CLIBS)

clean:
	rm -rf $(TARGETS)

ultraclean:
	rm -rf $(TARGETS) *.o* *.e* *.txt
