#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc, char *argv[]) {
    int id = 0;
    #pragma omp parallel private (id)
    {
        id = omp_get_thread_num();
        if (id < omp_get_num_threads()/2) {
            system("sleep 3");
        }
        printf("id: %d - (antes)\n", id);
        #pragma omp barrier
        printf("id: %d - (depois)\n", id);
    }
    return 0;
}