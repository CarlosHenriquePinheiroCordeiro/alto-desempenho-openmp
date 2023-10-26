#include <stdio.h>
#include <omp.h>

int iPrivada;

#pragma omp threadprivate(iPrivada)

int main() {
    #pragma omp parallel
    {
        iPrivada = omp_get_thread_num(); // Cada thread tem sua própria cópia da variável.
        printf("Variável privada da Thread %d:  = %d\n", omp_get_thread_num(), iPrivada);
    }
    return 0;
}
