#include <stdio.h>
#include <omp.h>

int iSomaGlobal = 0;

int main() {
    #pragma omp parallel
    {
        int iSomaLocal = omp_get_thread_num() + 1;
        #pragma omp critical
        {
            iSomaGlobal += iSomaLocal;
            #pragma omp flush(iSomaGlobal)
        }
    }
    printf("Soma global = %d\n", iSomaGlobal);
    return 0;
}
