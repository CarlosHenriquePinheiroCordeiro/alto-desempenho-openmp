#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc, char *argv[]) {
    int ic = 0, i;
    #pragma omp parallel shared(ic) private (i)
    for (i = 0; i < 5; i++) {
        #pragma omp atomic
        ic++;
    }
    printf("counter = %d\n", ic);
    return 0;
}