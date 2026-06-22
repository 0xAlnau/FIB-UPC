#include <stdio.h>
#include <omp.h>
#include <unistd.h>



/* Execute with ./2.hello                               */
/* Q1: Is the execution of the program correct? Add a   */ //no, we need to add private(id), so between threads they dont mix id's
/*     data sharing clause to make it correct           */
/* Q2: Are the lines always printed in the same order?  */ //no, they are printed in different order because they are parallel, so hence, sometime they mix and that's okey, we can solve it with critical
/*     Why the messages sometimes appear intermixed?    */

int main ()
{
    volatile int id;
    #pragma omp parallel num_threads(8) private(id)
    {
      id =omp_get_thread_num();
      printf("(%d) Hello ",id);
      printf("(%d) world!\n",id);
      
    }
    return 0;
}
