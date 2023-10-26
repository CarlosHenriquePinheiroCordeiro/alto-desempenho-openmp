#include <stdio.h>
#include <omp.h>

int aVetorPrivado[8];

#pragma omp threadprivate(aVetorPrivado)

int main() {
    #pragma omp parallel num_threads(8)
    {
        aVetorPrivado[omp_get_thread_num()] = omp_get_thread_num();
        printf("Valores Thread %d = %d\n", omp_get_thread_num(), aVetorPrivado[omp_get_thread_num()]);
    }
    return 0;
}
