#include <stdio.h>
#include <omp.h>

int iIdDocumento = -1;
int iContador = 0;

void imprimir() {
    int iImprimir;

    //Criando um documento
    #pragma omp critical
    {
        iImprimir = iContador;
        iContador++;
    }

    //Imprimindo em uma impressora compartilhada
    #pragma omp critical
    {
        iIdDocumento = iImprimir;
        printf("Documento %d está sendo impresso...\n", iImprimir);
    }
}

int main() {
    int iDocumentos = 5;
    iIdDocumento = -1;
    #pragma omp parallel
    {
        for (int i = 0; i < iDocumentos; i++) {
            imprimir();
        }
    }
    printf("Todos os documentos foram impressos.\n");
    return 0;
}
