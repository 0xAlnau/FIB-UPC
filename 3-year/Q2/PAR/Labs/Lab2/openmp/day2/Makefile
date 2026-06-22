CC       = icx

OPENMP   = -qopenmp
CFLAGS   = -Wall -g -O3 -fno-inline $(OPENMP)

TARGET  = 1.single 2.fibtasks 3.taskloop 4.reduction 5.synchtasks

program: $(TARGET)

1.single: 1.single.c
	$(CC) $< $(CFLAGS) -o $@

2.fibtasks: 2.fibtasks.c
	$(CC) $< $(CFLAGS) -o $@

3.taskloop: 3.taskloop.c
	$(CC) $< $(CFLAGS) -o $@

4.reduction: 4.reduction.c
	$(CC) $< $(CFLAGS) -o $@

5.synchtasks: 5.synchtasks.c
	$(CC) $< $(CFLAGS) -o $@

clean:
	rm -f $(TARGET)

