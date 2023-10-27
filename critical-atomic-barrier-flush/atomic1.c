#include <stdio.h>
#include <omp.h>

int iAcessos = 0;

int main() {
    #pragma omp parallel
    {
        #pragma omp atomic
        iAcessos++;
    }

    printf("Total de acessos: %d\n", iAcessos);
    return 0;
}
