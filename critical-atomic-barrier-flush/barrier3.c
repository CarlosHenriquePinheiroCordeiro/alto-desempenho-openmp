#include <stdio.h>
#include <omp.h>

int iCarros = 0;

int main() {
    #pragma omp parallel
    {
        printf("Carro %d está se preparando...\n", omp_get_thread_num());

        #pragma omp atomic
        iCarros++;

        #pragma omp barrier
        printf("Carro %d começou a corrida!\n", omp_get_thread_num());
    }

    printf("Todos os carros estão prontos. Largada!\n");
    return 0;
}
