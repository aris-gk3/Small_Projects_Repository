#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
#   include <omp.h>
#endif

void Hello(void); /* Thread function */

int main(int argc ,char* argv[]){
    /* Get number of threads from command line */
    int thread_count = strtol (argv[1] ,NULL , 10);

    #pragma omp parallel num_threads(thread_count)
    Hello ( ) ;
    
    int max_threads = omp_get_max_threads();
    printf(" Maximum number of PARALLEL threads available: %d\n", max_threads);

    return 0;
} /* main */

void Hello(void){
    #ifdef _OPENMP
        int my_rank = omp_get_thread_num();
        int thread_count = omp_get_num_threads();
    #else
        int my_rank = 0;
        int thread_count = 1;
    #endif

    printf ( " Hello from thread %d of %d\n" ,my_rank , thread_count);

} /* Hello */
