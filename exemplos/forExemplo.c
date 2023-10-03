#include <stdio.h>
#include <omp.h>

int main (int argc, char *argv[]) {
    #pragma omp parallel
    {
        #pragma omp for
        for (short i = 0; i < 10; i++)
        {
            printf("Thread %d - i = %d \n", omp_get_thread_num(), i);
        }
            
    }
    return 0;
}