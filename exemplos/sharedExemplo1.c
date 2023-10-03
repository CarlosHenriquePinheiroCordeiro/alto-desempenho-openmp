#include <stdio.h>
#include <omp.h>

int main (int argc, char *argv[]) {
    int num = 0;
    printf("Serial %d \n", num);
    omp_set_num_threads(8);
    #pragma omp parallel shared(num)
    {
        int id = omp_get_thread_num();
        num = num + 1;
        printf("Paralela - Thread id - %d e (num+id) = %d \n", id, num);
    }
    printf("Serial %d \n", num);
    return 0;
}