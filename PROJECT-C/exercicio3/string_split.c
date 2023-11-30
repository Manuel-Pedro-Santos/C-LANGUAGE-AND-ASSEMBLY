#include <stdio.h>
#include <string.h>

/*
Programe em linguagem C a função string_split , que separa, em palavras isoladas, o texto recebido no
parâmetro text com formato string C. Palavra é uma sequência de caracteres delimitada por sequências de
um ou mais caracteres separadores (‘ ’, ‘\t’ ou ‘\n’). O array de ponteiros words, cuja dimensão é definida
por words_size, deve ser preenchido com os endereços de início das palavras, pela ordem em que se
encontram no texto. O caractere separador, no final de cada palavra, deve ser substituído por ‘\0’, para que
as palavras fiquem formatadas como strings C. A função devolve o número de palavras assinaladas em words.
No caso da função devolver um valor igual a words_size, pode também significar que o número de palavras
no texto é superior à capacidade de words. Nesse caso, as restantes palavras podem ser obtidas em
chamada(s) posterior(es). A forma de indicar que se pretende continuar a obter palavras do texto da chamada
anterior é usar o argumento NULL como primeiro parâmetro.
*/

size_t string_split(char *text, char *separators, char *words[], size_t words_size) {

    //Para guardar o ultimo sitio que tinhamos ficado.
    char *textStart = NULL;

    //Contar o numero de palavras recolhidas pelo programa.
    size_t wordCount = 0;

    //Iniciar a a variavel apenas se lá houver algo.
    if (text != NULL) {
        textStart = text;
    }
    while (wordCount < words_size) {
        //Esta função serve para simplificar a separação da string em várias strings mais pequenas.
        char  *token = strtok(textStart, separators);

        //Verifica se ainda existe alguma palavra.
        if (token == NULL) {
            break;
        }
        //Guardar o endereço no array.
        words[wordCount] = token;
        //Incrementar o contador de palavras.
        wordCount++;
        //Guardar o endereço da proxima palavra.
        textStart = NULL;
    }

    return wordCount;
}