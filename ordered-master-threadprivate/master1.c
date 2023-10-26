#include <stdio.h>
#include <omp.h>

int main (int argc, char *argv[]) {
    #pragma omp parallel
    {
        printf("Thread %d fez os seus commits\n", omp_get_thread_num());
        #pragma omp barrier
        #pragma omp master
        {
            printf("Thread mestre (%d) realizando deploy em produção\n", omp_get_thread_num());
        }
    }
    return 0;
}