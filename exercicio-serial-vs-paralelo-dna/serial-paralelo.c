#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

FILE *oTxt;
FILE *oComplementar;

int main (int argc, char *argv[]) {
    montaFitaSerial();
    montaFitaParalelo();
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
                if ((int)(sLetra) == 65)
                {
                    fprintf(oComplementar, "%s", "T");
                }
                if ((int)(sLetra) == 67)
                {
                    fprintf(oComplementar, "%s", "G");
                }
                if ((int)(sLetra) == 71)
                {
                    fprintf(oComplementar, "%s", "C");
                }
                if ((int)(sLetra) == 84)
                {
                    fprintf(oComplementar, "%s", "A");
                }
            }
            fprintf(oComplementar, "\n");
        }
        fclose(oComplementar);
        fclose(oTxt);
    }
}

void montaFitaParalelo() {

}