#include <stdio.h>
#include <omp.h>

int iCompartilhada = 0;

int main() {
    #pragma omp parallel
    {
        if (omp_get_thread_num() == 0) {
            iCompartilhada = 42;
            #pragma omp flush(iCompartilhada)
        }
        printf("Thread %d: Valor compartilhado = %d\n", omp_get_thread_num(), iCompartilhada);
    }

    return 0;
}
