#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int random_num = 0;
    #pragma omp parallel
    {
        #pragma omp master
        {
            srand(123); //Somente a Thread Master terá um número aleatório diferente
        }
        random_num = rand();
        printf("Thread %d gerou um número aleatório: %d\n", omp_get_thread_num(), random_num);
    }

    return 0;
}
