.SUFFIXES: -omp -debug
CC       = icx

OPENMP	 = -qopenmp
CFLAGS   = -g -Wall -std=c99 -O3 $(OPENMP) -fno-inline -I.
CLIBS    = -L. -lm

.c-debug:
	$(CC) -D_DEBUG_ $< $(CFLAGS) -o $@ $(CLIBS)

.c-omp:
	$(CC) $< $(CFLAGS) -o $@ $(CLIBS)

clean:
	rm -f *-omp *-debug

ultraclean:
	rm -rf *-omp *-debug submit-omp.sh.o* submit-omp.sh.e*
