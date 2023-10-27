#include <stdio.h>
#include <omp.h>

int iPessoas = 0;

void entraPredio(int iQtdPessoas) {
    #pragma omp atomic
    iPessoas += iQtdPessoas;
    printf("%d pessoas entraram no prédio. Pessoas dentro: %d\n", iQtdPessoas, iPessoas);
}

void saiPredio(int iQtdPessoas) {
    #pragma omp atomic
    iPessoas -= iQtdPessoas;
    printf("%d pessoas saíram do prédio. Pessoas dentro: %d\n", iQtdPessoas, iPessoas);
}

int main() {
    #pragma omp parallel
    {
        int iThread = omp_get_thread_num();
        if (iThread % 2 == 0) {
            entraPredio(2);
        } else {
            saiPredio(1);
        }
    }
    return 0;
}