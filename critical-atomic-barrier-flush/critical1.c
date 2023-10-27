#include <stdio.h>
#include <omp.h>

int main() {
    int iRecursoCompartilhado = 0;
    #pragma omp parallel
    {
        //Garante que apenas uma thread por vez atualize o recurso compartilhado
        #pragma omp critical
        {
            iRecursoCompartilhado += 1;
        }
        printf("(%d) Recurso compartilhado compartilhado: %d\n", omp_get_thread_num(), iRecursoCompartilhado);
    }
    printf("Total compartilhado: %d\n", iRecursoCompartilhado);
    return 0;
}
