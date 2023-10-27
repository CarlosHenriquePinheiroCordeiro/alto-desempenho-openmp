#include <stdio.h>
#include <omp.h>

int iRecursoCompartilhado = 0;

void acessoRecursoCompartilhado() {
    #pragma omp critical
    {
        iRecursoCompartilhado += 1;
        printf("Thread %d acessando recurso compartilhado: %d\n", omp_get_thread_num(), iRecursoCompartilhado);
    }
}

int main() {
    #pragma omp parallel
    {
        //Pode ser acessado por meio de funções também
        acessoRecursoCompartilhado();
    }
    printf("Final do recurso compartilhado: %d\n", iRecursoCompartilhado);
    return 0;
}
