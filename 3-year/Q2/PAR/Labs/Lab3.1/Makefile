# C compiler
OMPC    = icx
OPT3 	= -g -O3 -fp-model precise
OPT3 	= -g -O3
OPTG0 	= -g -O0
CFLAGS  = -std=c99 # -Wall
OPENMP	= -qopenmp
LFLAGS  = -lX11 -L/usr/X11R6/lib -lm
CINCL    = -I. -I/Soft/stb/20200430
CLIBS    = -L.

# Tareador compiler
TAREADORCC = tar-clang
TAREADOR_FLAGS = -tareador-lite -isystem/scratch/nas/1/par0/Soft

TARGETS  = mandel-seq-iter mandel-seq-rec mandel-seq-iter-tar mandel-seq-rec-tar
all: $(TARGETS)

.PHONY: mandel-seq-iter mandel-seq-rec mandel-seq-iter-tar mandel-seq-rec-tar

mandel-seq-iter: mandel-seq-iter.c
	$(OMPC) $(CINCL) -o $@ $(OPT3) $(CFLAGS) $^ $(LFLAGS)

mandel-seq-rec: mandel-seq-rec.c
	$(OMPC) $(CINCL) -o $@ $(OPT3) $(CFLAGS) $^ $(LFLAGS)

mandel-seq-rec-tar: mandel-seq-rec-tar.c
	@schroot -p -c tareador make mandel-seq-rec-tar_env

mandel-seq-rec-tar_env:	mandel-seq-rec-tar.c
	$(TAREADORCC) $(OPTG0) $(TAREADOR_FLAGS) $(CFLAGS) -I. $< -o mandel-seq-rec-tar $(CLIBS) -lm  $(LFLAGS)

mandel-seq-iter-tar: mandel-seq-iter-tar.c
	@schroot -p -c tareador make mandel-seq-iter-tar_env

mandel-seq-iter-tar_env:	mandel-seq-iter-tar.c
	$(TAREADORCC) $(OPTG0) $(TAREADOR_FLAGS) $(CFLAGS) -I. $< -o mandel-seq-iter-tar $(CLIBS) -lm  $(LFLAGS)

clean:
	rm -rf $(TARGETS) .tareador_precomputed* logs *.log

ultraclean:
	rm -rf $(TARGETS) .tareador_precomputed* logs *.log *.prv *.pcf *.row dependency_graph* time-mandel* *.sh.o* *.sh.e* elapsed.txt speedup.txt hash_labels.txt TRACE.sym TRACE.mpits set-0 *.ps *.out *.txt mandel-omp-strong-extrae
