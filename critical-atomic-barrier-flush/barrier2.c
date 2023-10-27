#include <stdio.h>
#include <omp.h>

int iValores = 100;
double aValores[100];
double iSoma = 0.0;

int main() {
    for (int i = 0; i < iValores; i++) {
        aValores[i] = i + 1;
    }

    #pragma omp parallel
    {
        int iThread = omp_get_thread_num();
        double iSomaLocal = 0.0;

        // Cada thread calcula a média parcial
        for (int i = iThread * (iValores / 4); i < (iThread + 1) * (iValores / 4); i++) {
            iSomaLocal += aValores[i];
        }
        #pragma omp barrier

        //Média final
        #pragma omp atomic
        iSoma += iSomaLocal;
    }
    printf("A média dos valores é: %f\n", iSoma/iValores);

    return 0;
}
