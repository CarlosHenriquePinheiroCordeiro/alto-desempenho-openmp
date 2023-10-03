#include <stdio.h>
#include <omp.h>

//MOSTRA QUE DEVE SEMPRE INICIALIZAR VARIÁVEL, POIS SE FOR EXECUTAR, O VALOR DO NUM VAI ESTAR BAGUNÇADO POR CONTA DE VALORES LIXO NA MEMÓRIA
//ASSIM, SE MOSTRA QUE SEMPRE DEVE SER INICIALIZADA UMA VARIÁVEL DO TIPO PRIVATE

int main (int argc, char *argv[]) {
    int num = 0;
    printf("Serial %d \n", num);
    omp_set_num_threads(4);
    #pragma omp parallel private(num)
    {
        int id = omp_get_thread_num();
        printf("id = %d \n", id);
        printf("num = %d \n", num);
        num = num + id;
        printf("Paralela - Thread id - %d e (num+id) = %d \n\n", id, num);
    }
    printf("Serial %d \n\n", num);
    return 0;
}