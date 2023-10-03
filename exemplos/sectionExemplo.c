#include <stdio.h>
#include <omp.h>

int main (int argc, char *argv[]) {
    printf("\nSerial \n\n");
    omp_set_num_threads(8);
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            printf("Teste %d\n", omp_get_thread_num());
            #pragma omp section
            printf("Teste %d\n", omp_get_thread_num());
        }
    }
    printf("\nSerial \n\n");
    return 0;
}