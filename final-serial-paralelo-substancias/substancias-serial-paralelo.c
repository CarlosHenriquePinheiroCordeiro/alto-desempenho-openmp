#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>

#define MAX_CONTEUDOS 54
#define QTD_ARQUIVOS 32

/**
 * Link para download dos arquivos XML - https://drive.google.com/drive/folders/1hb4mqulNTCIiVW4TblltDbWd_ZY4Dhuu?usp=sharing
 * Após realizar o download, copiar todos os 32 arquivos XML para dentro da mesma pasta onde se encontra este arquivo "substancias-serial-paralelo.c"
 */
int main() {
    clock_t iTempoInicio = clock();
    executaSerial();
    // executaParalelo(2);
    // executaParalelo(4);
    // executaParalelo(8);
    // executaParalelo(12);
    // executaParalelo(16);
    clock_t iTempoFim = clock();
    double iTempoExecucao = (double)(iTempoFim - iTempoInicio) / CLOCKS_PER_SEC;
    printf("Tempo de execução programa: %f\n", iTempoExecucao);
    return 0;
}

/**
 * Executa o algoritmo de forma serial
 */
void executaSerial() {
    for (int i = 1; i <= QTD_ARQUIVOS; ++i) {
        montaArquivoArquivoSubstancias(i);
    }
}

/**
 * Executa o algoritmo de forma paralela, conforme o número de threads desejado
 */
void executaParalelo(int iThreads) {
    omp_set_num_threads(iThreads);
    #pragma omp parallel for
    for (int i = 1; i <= QTD_ARQUIVOS; ++i) {
        montaArquivoArquivoSubstancias(i);
    }
}

/**
 * Prepara a base para a montagem do arquivo que contém as informações das substâncias, presentes no arquivo com id informado, e invoca a criação do arquivo
 */
void montaArquivoArquivoSubstancias(int iIdArquivo) {
    long iTamanhoArquivo;
    char *sXml;
    char nomeArquivo[10];
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%d.xml", iIdArquivo);
    FILE *oArquivo = fopen(nomeArquivo, "r");
    fseek(oArquivo, 0, SEEK_END);
    iTamanhoArquivo = ftell(oArquivo);
    rewind(oArquivo);
    sXml = (char *)malloc(iTamanhoArquivo + 1);

    fread(sXml, 1, iTamanhoArquivo, oArquivo);
    sXml[iTamanhoArquivo] = '\0';
    fclose(oArquivo);

    char **aConteudos = (char **)malloc(sizeof(char *) * MAX_CONTEUDOS);
    for (int i = 0; i < MAX_CONTEUDOS; i++) {
        aConteudos[i] = NULL;
    }
    int iNumConteudos = 0;
    montaArquivo(sXml, aConteudos, &iNumConteudos, iIdArquivo);

    for (int i = 0; i < MAX_CONTEUDOS; i++) {
        free(aConteudos[i]);
    }
    free(aConteudos);
    free(sXml);
}

/**
 * Realiza a montagem do arquivo das substâncias conforme conteúdo em XML informado
 */
void montaArquivo(const char *sXml, char **sConteudoXml, int *iNumConteudos, int iIdArquivo) {
    *iNumConteudos = 0;
    const char *sInicio = strstr(sXml, "<PC-Substance>");
    char nomeArquivoNovo[10];
    snprintf(nomeArquivoNovo, sizeof(nomeArquivoNovo), "%d.txt", iIdArquivo);
    FILE *oArquivoNovo = fopen(nomeArquivoNovo, "a");
    while (sInicio != NULL && *iNumConteudos < MAX_CONTEUDOS) {
        const char *sInicioSub = strstr(sInicio, "<info-sub>");
        while (sInicioSub != NULL && sInicioSub < strstr(sInicio, "</PC-Substance>")) {
            const char *sInicioInfo = strchr(sInicioSub, '>');
            if (sInicioInfo != NULL) {
                sInicioInfo++;
                const char *sFimInfo = strstr(sInicioInfo, "</info-sub>");
                if (sFimInfo != NULL) {
                    size_t iTamanho = sFimInfo - sInicioInfo;
                    sConteudoXml[*iNumConteudos] = (char *)malloc(iTamanho + 1);
                    if (sConteudoXml[*iNumConteudos] != NULL) {
                        strncpy(sConteudoXml[*iNumConteudos], sInicioInfo, iTamanho);
                        sConteudoXml[*iNumConteudos][iTamanho] = '\0';
                        (*iNumConteudos)++;
                    }
                }
            }
            trataInformacaoXml(&sConteudoXml[*iNumConteudos-1]);
            fprintf(oArquivoNovo, "%s", sConteudoXml[*iNumConteudos-1]);
            sInicioSub = strstr(sInicioSub + 1, "<info-sub>");
        }
        fprintf(oArquivoNovo, "\n");
        sInicio = strstr(sInicio + 1, "<PC-Substance>");
    }
    fclose(oArquivoNovo);
}

/**
 * Trata a informação do XML, de modo que limpa as tags da string, deixando somente os valores.
 * Os espaços em branco são substituídos por "_" e as informações são contacentadas por ";"
 */
void trataInformacaoXml(char **sXml) {
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