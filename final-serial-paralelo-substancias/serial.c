#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTEUDOS 100

void trataXml(char **sXml) {
    int iTamanho    = strlen(*sXml);
    char *sConteudo = (char *)malloc(iTamanho + 1);
    int iIndice     = 0;
    int bDentroTag  = 0;

    for (int i = 0; i < iTamanho; ++i) {
        if ((*sXml)[i] == '<') {
            bDentroTag = 1;
        } else if ((*sXml)[i] == '>') {
            bDentroTag = 0;
        } else if (!bDentroTag) {
            if ((*sXml)[i] == '\n' || (*sXml)[i] == '\t') {
                if (iIndice > 0 && sConteudo[iIndice - 1] != ';') {
                    sConteudo[iIndice] = ';';
                    ++iIndice;
                }
            } else {
                if ((*sXml)[i] == ' ') {
                    if (iIndice > 0 && sConteudo[iIndice - 1] != ';') {
                        sConteudo[iIndice] = '_';
                        ++iIndice;
                    }
                } else {
                    sConteudo[iIndice] = (*sXml)[i];
                    ++iIndice;
                }
            }
        }
    }

    while (iIndice > 0 && (sConteudo[iIndice - 1] == '\n' || sConteudo[iIndice - 1] == '\r')) {
        --iIndice;
    }

    if (iIndice > 0 && sConteudo[iIndice - 1] != ';') {
        sConteudo[iIndice] = ';';
        ++iIndice;
    }
    sConteudo[iIndice] = '\0';

    for (int i = 0; i < iIndice - 1; ++i) {
        if (sConteudo[i] == ' ' && sConteudo[i + 1] != ';') {
            sConteudo[i] = '_';
        }
    }
    free(*sXml);
    *sXml = strdup(sConteudo);
    free(sConteudo);
}

void montaArquivo(const char *sXml, char ***sConteudoXml, int *iNumConteudos) {
    *iNumConteudos = 0;
    const char *sInicio = strstr(sXml, "<PC-Substance>");
    while (sInicio != NULL) {
        const char *sInicioSub = strstr(sInicio, "<info-sub>");
        while (sInicioSub != NULL && sInicioSub < strstr(sInicio, "</PC-Substance>")) {
            const char *sInicioInfo = strchr(sInicioSub, '>');
            if (sInicioInfo != NULL) {
                sInicioInfo++;
                const char *sFimInfo = strstr(sInicioInfo, "</info-sub>");
                if (sFimInfo != NULL) {
                    size_t iTamanho = sFimInfo - sInicioInfo;
                    (*sConteudoXml)[*iNumConteudos] = (char *)malloc(iTamanho + 1);
                    if ((*sConteudoXml)[*iNumConteudos] != NULL) {
                        strncpy((*sConteudoXml)[*iNumConteudos], sInicioInfo, iTamanho);
                        (*sConteudoXml)[*iNumConteudos][iTamanho] = '\0';
                        (*iNumConteudos)++;
                    }
                }
            }
            trataXml(&(*sConteudoXml)[*iNumConteudos-1]);
            printf("%s", (*sConteudoXml)[*iNumConteudos-1]);
            sInicioSub = strstr(sInicioSub + 1, "<info-sub>");
        }
        printf("\n");
        sInicio = strstr(sInicio + 1, "<PC-Substance>");
    }
}

int main() {
    FILE *oArquivo;
    long iTamanhoArquivo;
    char *sXml;

    oArquivo = fopen("1.xml", "r");

    fseek(oArquivo, 0, SEEK_END);
    iTamanhoArquivo = ftell(oArquivo);
    rewind(oArquivo);
    sXml = (char *)malloc(iTamanhoArquivo + 1);

    fread(sXml, 1, iTamanhoArquivo, oArquivo);
    sXml[iTamanhoArquivo] = '\0';
    fclose(oArquivo);

    char ***aConteudos = (char ***)malloc(sizeof(char **) * MAX_CONTEUDOS);
    for (int i = 0; i < MAX_CONTEUDOS; i++) {
        aConteudos[i] = (char **)malloc(sizeof(char *));
    }
    int iNumConteudos = 0;
    montaArquivo(sXml, aConteudos, &iNumConteudos);

    for (int i = 0; i < MAX_CONTEUDOS; i++) {
        free(aConteudos[i][0]);
        free(aConteudos[i]);
    }
    free(aConteudos);
    free(sXml);

    return 0;
}