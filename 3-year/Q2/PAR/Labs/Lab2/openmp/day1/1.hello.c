#include <stdio.h>
#include <omp.h>

/* Q1: How many times will you see the "Hello world!"        */ //two times
/*     message if the program is executed with "./1.hello"?  */    
/* Q2: Without changing the program, how to make it to       */ //putting the OMP_NUM_THREADS=4 ./1.hello
/*     print 4 times the "Hello World!" message?             */

int main ()
{
    #pragma omp parallel
    printf("Hello world!\n");
	
    return 0;
}
