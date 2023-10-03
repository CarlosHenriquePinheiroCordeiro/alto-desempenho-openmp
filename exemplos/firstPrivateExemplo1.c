#include <stdio.h>
#include <omp.h>

int main (int argc, char *argv[]) {
    int num = 3;
    printf("Serial %d \n", num);
    omp_set_num_threads(4);
    #pragma omp parallel firstprivate(num)
    {
        int id = omp_get_thread_num();
        num = num + id;
        printf("Paralela - Thread id - %d e (num+id) = %d \n", id, num);
    }
    printf("Serial %d \n", num);
    return 0;
}