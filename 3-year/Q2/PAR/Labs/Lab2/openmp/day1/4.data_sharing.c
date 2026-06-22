#include <stdio.h>
#include <unistd.h>
#include <omp.h>

/* Execute with ./4.data_sharing                               */
/* Q1: Which is the value of x after the execution of each     */ // ·shared: it's the last id thread to finish (race condition)
/*     parallel region with different data-sharing attribute   */ // ·private: it's always 5, because x is private for the each thread
							   	  //           and does not affect the global x. Private creates a new
							   	  //           local variable inicialized with trash
/*     (shared, private, firstprivate and reduction)?          */ // ·firstprivate: it's always 5, because as the same before, but the
								  //           difference it's in the fact that the local x is inicia
								  //           with the previous value of x (5).
/*     Explain why, repeating the execution many times if      */ // ·reduction: here creates local variables that make the partial 
 							          //             sum and then it sums it to the global x giving 11
/*     necessary.                                              */

int main ()
{
    omp_set_num_threads(4);

    int x=0;
    #pragma omp parallel shared(x) // shared could be removed, it is the default, es fa race condition, ultim escriu el seu id
    {
        int tmp = x;
        sleep(1);                 // this is just to force problems
	    x= tmp + omp_get_thread_num();
    }
    printf("After first parallel (shared) x is: %d\n",x);

    x=5;
    #pragma omp parallel private(x) //x es privada i inicia a 0
    {
	x+=omp_get_thread_num();
    }
    printf("After second parallel (private) x is: %d\n",x);

    #pragma omp parallel firstprivate(x) //copia de x privada a cadascu amb x = 5, x no canvia
    {
	x+=omp_get_thread_num();
    }
    printf("After third  parallel (firstprivate) x is: %d\n",x); 

    #pragma omp parallel reduction(+:x) //inicialitza a 0
    {
	x+=omp_get_thread_num();
    }
    printf("After fourth parallel (reduction) x is: %d\n",x);

    return 0;
}
