#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc, char *argv[]) {
    int a[30][2];
    int b[30][2];
    srand(time(NULL));
    for (int x = 0; x < 30; x++) {
        a[x][0] = rand() % 361;
        a[x][1] = rand() % 361;
        b[x][0] = rand() % 361;
        b[x][1] = rand() % 361;
        if (rand() % 4 == 1) {
            a[x][0] = a[x][0] * -1;
        }
        if (rand() % 4 == 1) {
            a[x][1] = a[x][1] * -1;
        }
        if (rand() % 4 == 1) {
            b[x][0] = b[x][0] * -1;
        }
        if (rand() % 4 == 1) {
            b[x][1] = b[x][1] * -1;
        }
    }
    int iProdutoInterno = 0;
    int iVetor1         = 0;
    int iVetor2         = 0;
    int iCosseno        = 0;
    #pragma omp parallel private (iProdutoInterno, iVetor1, iVetor2, iCosseno)
    {
        #pragma omp for
        for (int i = 0; i < 30; i++) {
            #pragma omp critical
            iVetor1 = sqrt((a[i][0]*a[i][0]) + (a[i][1]*a[i][1]));
            iVetor2 = sqrt((b[i][0]*b[i][0]) + (b[i][1]*b[i][1]));
            iProdutoInterno = (a[i][0]*b[i][0]) + (a[i][1]*b[i][1]);
            if (iVetor1 < 0) {
                iVetor1 * -1;
            }
            if (iVetor2 < 0) {
                iVetor2 * -1;
            }
            iCosseno = iProdutoInterno/(iVetor1*iVetor2);
            if (iCosseno < 0) {
                printf("Ângulo %d: Obtusângulo\n", i);
            }
            if (iCosseno == 0) {
                printf("Ângulo %d: Reto\n", i);
            }
            if (iCosseno > 0) {
                printf("Ângulo %d: Agudo\n", i);
            }
        }
    }
    return 0;
}