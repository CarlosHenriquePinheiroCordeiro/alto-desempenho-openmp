#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>

FILE *oTxt;
FILE *oComplementar;
FILE* aTxts[10];

int main (int argc, char *argv[]) {
    clock_t inicio_serial = clock();
    montaFitaSerial();
    clock_t fim_serial = clock();
    double tempo_serial = (double)(fim_serial - inicio_serial) / CLOCKS_PER_SEC;
    printf("Tempo de execução programa Serial: %f\n", tempo_serial);

    clock_t inicio_paralelo = clock();
    montaFitaParalelo();
    clock_t fim_paralelo = clock();
    double tempo_paralelo = (double)(fim_paralelo - inicio_paralelo) / CLOCKS_PER_SEC;

    printf("Tempo de execução programa Paralelo: %f\n", tempo_paralelo);
    return 0;
}

void montaFitaSerial() {
    char sLinha[200];
    char *aArquivos[]      = {"dna-0.txt"    , "dna-1.txt"    , "dna-2.txt"    , "dna-3.txt"    , "dna-4.txt"    , "dna-5.txt"    , "dna-6.txt"    , "dna-7.txt"    , "dna-8.txt"    , "dna-9.txt"};
    char *aNovosArquivos[] = {"dna-0-c-s.txt", "dna-1-c-s.txt", "dna-2-c-s.txt", "dna-3-c-s.txt", "dna-4-c-s.txt", "dna-5-c-s.txt", "dna-6-c-s.txt", "dna-7-c-s.txt", "dna-8-c-s.txt", "dna-9-c-s.txt"};
    for (short i = 0; i < 10; i++)
    {
        oTxt          = fopen(aArquivos[i], "r");
        oComplementar = fopen(aNovosArquivos[i], "a");
        while (fgets(sLinha, 200, oTxt))
        {
            for (int x = 0; x < strlen(sLinha); x++)
            {
                char sLetra = sLinha[x];
                switch ((int)(sLetra))
                {
                    case 65:
                        fprintf(oComplementar, "%s", "T");
                        break;
                    case 67:
                        fprintf(oComplementar, "%s", "G");
                        break;
                    case 71:
                        fprintf(oComplementar, "%s", "C");
                        break;
                    case 84:
                        fprintf(oComplementar, "%s", "A");
                        break;
                    default:
                        break;
                }
            }
            fprintf(oComplementar, "\n");
        }
        fclose(oComplementar);
        fclose(oTxt);
    }
}

void montaFitaParalelo() {
    short iArquivos = 10;
    char *aArquivos[]      = {"dna-0.txt"    , "dna-1.txt"    , "dna-2.txt"    , "dna-3.txt"    , "dna-4.txt"    , "dna-5.txt"    , "dna-6.txt"    , "dna-7.txt"    , "dna-8.txt"    , "dna-9.txt"};
    char *aNovosArquivos[] = {"dna-0-c-p.txt", "dna-1-c-p.txt", "dna-2-c-p.txt", "dna-3-c-p.txt", "dna-4-c-p.txt", "dna-5-c-p.txt", "dna-6-c-p.txt", "dna-7-c-p.txt", "dna-8-c-p.txt", "dna-9-c-p.txt"};

    #pragma omp parallel for
    for (short i = 0; i < iArquivos; i++) {
        aTxts[i] = fopen(aNovosArquivos[i], "w");
        if (aTxts[i] == NULL) {
            exit(1);
        }
    }

    #pragma omp parallel for
    for (int i = 0; i < iArquivos; i++) {
        FILE* oNovoComplementar = fopen(aArquivos[i], "r");
        if (oNovoComplementar == NULL) {
            exit(1);
        }
        char sLetra;
        while ((sLetra = fgetc(oNovoComplementar)) != EOF) {
            switch ((int)(sLetra))
            {
                case 65:
                    fputc('T', aTxts[i]);
                    break;
                case 67:
                    fputc('G', aTxts[i]);
                    break;
                case 71:
                    fputc('C', aTxts[i]);
                    break;
                case 84:
                    fputc('A', aTxts[i]);
                    break;
                default:
                    fputc(sLetra, aTxts[i]);
                    break;
            }
        }
        fclose(oNovoComplementar);
        fclose(aTxts[i]);
    }
}