#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {

    char *inFile = NULL, *outFile = NULL, *pattern = NULL;
    int coluna = -1, caps = 0;

    int temp;
    //getopt analisa a linha de comandos e retorna o próximo argumento da linha de comandos
    while ((temp = getopt(argc, argv, "i:o:c")) != -1) {
        //switch para escolher o que fazer com o argumento
        switch (temp) {
            case 'i':
                inFile = optarg;
                break;
            case 'o':
                outFile = optarg;
                break;
            case 'c':
                caps = 1;
                break;
            default:
                fprintf(stderr, "Tens que escolher (i, o, c)\n");
                exit(EXIT_FAILURE);
        }
    }
    // Modifica o inFile para o caminho completo tendo em conta a variável de ambiente CSV_FILTER_PATH
    char *csvFilterPath = getenv("CSV_FILTER_PATH");
    if (csvFilterPath) {
        char inPath[MAX_LINE];
        snprintf(inPath, sizeof(inPath), "%s/%s", csvFilterPath, inFile);
        inFile = inPath;
    }

    // verifica se o número de argumentos é o correto
    if (optind + 2 > argc) {
        fprintf(stderr, "Falta Argumentos: ");
        exit(EXIT_FAILURE);
    }

    // atoi converte uma string para um inteiro
    coluna = atoi(argv[optind]);
    // guarda o padrão a procurar
    pattern = argv[optind + 1];
    FILE *fin, *fout;
    // abre o ficheiro de input
    if (inFile) {
        // abre o ficheiro de input para leitura.
        fin = fopen(inFile, "r");
        if (fin == NULL) {
            perror("Erro a abrir o ficheiro de input\n");
            exit(EXIT_FAILURE);
        }
    } else
        // stdin é um apontador para o ficheiro de input 
        fin = stdin;
    

    if (outFile) {
        // abre o ficheiro de output para escrita.
        fout = fopen(outFile, "w");
        if (fout == NULL) {
            perror("Erro a abrir o ficheiro de output\n");
            exit(EXIT_FAILURE);
        }
    } else 
        // stdout é um apontador para o ficheiro de output
        fout = stdout;
    
    /**
     * fgets lê uma linha do ficheiro de input e guarda-a na variável line
     * strdub duplica a string line e a strtok divide a string line em tokens
     * col é o número da coluna que estamos a ler.
    */
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fin) != NULL) {
        char *token, *copy = strdup(line);
        int colunaAtual = 1;
        token = strtok(copy, ",");
        while (token != NULL && colunaAtual != coluna) {
            token = strtok(NULL, ",");
            colunaAtual++;
        }
        if (token != NULL) {
            while (isspace((unsigned char)token[0])) {
                token++;
            }
            int len = strlen(token);
            // remove os espaços no fim do token 
            while (len > 0 && isspace((unsigned char)token[len - 1])) {
                token[len - 1] = '\0';
                len--;
            }
            // compara o token com o padrão e escreve a linha no ficheiro de output se for igual
            if ((!caps && strcasecmp(token, pattern) == 0) ||
                (caps && strcmp(token, pattern) == 0)) {
                fprintf(fout, "%s", line);
            }
        }
    free(copy);
    }
    if (inFile) 
        fclose(fin);
    
    if (outFile) 
        fclose(fout);

    return 0;
}


   