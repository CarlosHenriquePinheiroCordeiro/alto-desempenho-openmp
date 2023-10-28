#include <stdio.h>
#include <omp.h>

#define iTamanho 4
short matrix[iTamanho][iTamanho];

short main() {
    #pragma omp parallel
    {
        if (omp_get_thread_num() == 0) {
            for (short i = 0; i < iTamanho; i++) {
                for (short j = 0; j < iTamanho; j++) {
                    matrix[i][j] = i * iTamanho + j;
                }
                #pragma omp flush(matrix)
            }
        } else {
            #pragma omp flush(matrix)
            printf("Thread %d: Valor compartilhado = %d\n",omp_get_thread_num(), matrix[2][2]);
        }
    }

    return 0;
}
