#include <stdio.h>
#include <omp.h>

int main (int argc, char *argv[]) {
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("Iniciando construção do primeiro andar...\n\n");
        }
        printf("Thread %d construiu sua parte do primeiro andar\n", omp_get_thread_num());
        #pragma omp barrier
        #pragma omp single
        {
            printf("Iniciando construção do segundo andar...\n\n");
        }
        printf("Thread %d construiu sua parte do segundo andar\n", omp_get_thread_num());
    }
    return 0;
}