#include <stdio.h>
#include <time.h>
#include <omp.h>

int main (int argc, char *argv[]) {
    float A[2048];
    float B[2048];
    float C[2048];
    for (int x = 0; x < 2048; x++)
    {
        A[x] = rand() % 5000;
        B[x] = rand() % 5000;
        C[x] = 0;
    }
    
    omp_set_num_threads(8);
        #pragma omp parallel for
        for (int i = 0; i < 2048; i++)
        {
            C[i] = A[i] + B[i];
        }

    for (int x = 0; x < 2048; x++)
    {
        printf("C[%d] = %f\n", x, C[x]);
    }
    return 0;
}