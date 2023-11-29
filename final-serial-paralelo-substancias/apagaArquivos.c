#include <stdio.h>
#include <stdlib.h>

#define TOTAL_ARQUIVOS 32

void main() {
    for (int i = 1; i <= TOTAL_ARQUIVOS; ++i) {
        char nomeArquivo[10];
        snprintf(nomeArquivo, sizeof(nomeArquivo), "%d.txt", i);
        remove(nomeArquivo);
    }
}