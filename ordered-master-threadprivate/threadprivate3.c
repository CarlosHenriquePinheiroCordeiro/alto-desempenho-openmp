#include <stdio.h>
#include <omp.h>

int iPrivada;

#pragma omp threadprivate(iPrivada)

int main() {
    int iPublica = 0;
    #pragma omp parallel
    {
        iPrivada = omp_get_thread_num(); // Cada thread tem sua própria cópia da variável.
        iPublica += iPrivada;
        printf("Variável privada da Thread %d: %d. Pública: %d\n", omp_get_thread_num(), iPrivada, iPublica);
    }
    return 0;
}
