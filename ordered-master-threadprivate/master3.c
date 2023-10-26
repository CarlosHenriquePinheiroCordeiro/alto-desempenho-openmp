#include <stdio.h>
#include <omp.h>

int main() {
    int aVetor[10][10];

    #pragma omp parallel
    {
        #pragma omp master
        {
            printf("Inicializando a matriz...\n"); //Para garantir a integridade dos valores, apenas a thread master inicializa ela
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    aVetor[i][j] = i * 10 + j;
                }
            }
        }
        #pragma omp barrier

        int thread_id = omp_get_thread_num();
        int element = aVetor[thread_id][thread_id];
        printf("Thread %d: aVetor[%d][%d] = %d\n", thread_id, thread_id, thread_id, element);
    }

    return 0;
}
