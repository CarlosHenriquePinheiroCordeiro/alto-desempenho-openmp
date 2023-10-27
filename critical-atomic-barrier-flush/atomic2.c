#include <stdio.h>
#include <omp.h>

double iSaldoConta = 1000.0; // Saldo inicial da conta bancária

void deposita(double iQuantidade) {
    #pragma omp atomic
    iSaldoConta += iQuantidade;
}

void saque(double iQuantidade) {
    #pragma omp atomic
    iSaldoConta -= iQuantidade;
}

int main() {
    #pragma omp parallel
    {
        int iThread = omp_get_thread_num();
        if (iThread == 0) {
            deposita(500.0);
        } else {
            saque(300.0);
        }
    }

    printf("Saldo da conta bancária: %.2f\n", iSaldoConta);
    return 0;
}
