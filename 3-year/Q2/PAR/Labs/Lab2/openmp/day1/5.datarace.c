#include <stdio.h>
#include <unistd.h>
#include <omp.h>
/* Q1: Execute several times.                                 */
/*     Is the program executing correctly? Why?               */ //No, it's executing badly. Because it's sharing maxvalue and 
								 //changing constantly
/* Q2: Propose two alternative solutions to make it correct,  */ //Using reduction(max:maxvalue)
/*     without changing the structure of the code (just add   */ //Using critical a la comparacio
/*     directives or clauses). Explain why they make the      */
/*     execution correct.                                     */
/* Q3: Write an alternative distribution of iterations to     */
/*     implicit tasks (threads) so that each of them executes */
/*     only one block of consecutive iterations (i.e. N       */
/*     divided by the number of threads.                      */

#define N 1 << 20
int vector[N]={0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 15, 14, 13, 12, 11, 10, 9, 8, 15, 15};

int main()
{
    int i, maxvalue=3;
    int offset = 20 / 5; //20 nums, 5 threads -> 4 nums per thread

    omp_set_num_threads(5);
    #pragma omp parallel private(i) reduction(max:maxvalue)
    {
       int id = omp_get_thread_num();
       int howmany = omp_get_num_threads();

       for (i=0; i < offset; ++i) {
         if (vector[id*offset + i] > maxvalue)
         {
             sleep(1); // this is just to force problems
             maxvalue = vector[id*offset + i];
         }
       }
    }

    if (maxvalue==15)
         printf("Program executed correctly - maxvalue=%d found\n", maxvalue);
    else printf("Sorry, something went wrong - incorrect maxvalue=%d found\n", maxvalue);

    return 0;
}
