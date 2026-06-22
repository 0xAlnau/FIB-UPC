#include <stdio.h>
#include <omp.h>
/* Q1: Execute several times.                                 */ //No, because countmax it's shared and can be wrongly accessed
/*     Is the program executing correctly? Why?               */
/* Q2: Propose two alternative solutions to make it correct,  */ //Using reduction(+:countmax)
/*     without changing the structure of the program (just    */ //Using atomic at the countmax++
/*     using directives or clauses) and never making use of   */
/*     critical. Explain why they make the execution correct. */

#define N (1 << 20)
int vector[N];

int main()
{
    int i;
    volatile int countmax = 0;
    int maxvalue = 15;

    for (i=0;i<N;i++)
        vector[i]=15;
    vector[49]=0;

    omp_set_num_threads(8);
    #pragma omp parallel private(i)
    {
    int id = omp_get_thread_num();
    int howmany = omp_get_num_threads();

    for (i=id; i < N; i+=howmany)
        if (vector[i]==maxvalue)
            #pragma omp atomic
            countmax++;
    }

    if (countmax==N-1)
         printf("Program executed correctly - maxvalue=%d found %d times\n", maxvalue, countmax);
    else printf("Sorry, something went wrong - incorrect maxvalue=%d found %d times\n", maxvalue, countmax);

    return 0;
}
