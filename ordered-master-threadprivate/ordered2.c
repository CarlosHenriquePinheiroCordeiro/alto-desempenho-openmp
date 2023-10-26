#include <stdio.h>
#include <omp.h>

int main (int argc, char *argv[]) {
    #pragma omp parallel for ordered
    for (short i = 0; i < omp_get_num_threads(); i++) {
        #pragma omp ordered
        printf("Thread %d executando na ordem\n", omp_get_thread_num());
    }
    return 0;
}