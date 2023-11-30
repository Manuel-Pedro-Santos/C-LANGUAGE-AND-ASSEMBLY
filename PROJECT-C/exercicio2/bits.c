#include <stdio.h>
#include <limits.h>
/*
Considere vetores de bits representados sobre arrays de unsigned long em que ULONG_BIT é o número de
bits de um unsigned long. No índice n de um array de unsigned long o bit de menor peso corresponde ao
índice n * ULONG_BIT do vector de bits, enquanto que o bit de maior peso corresponde ao índice (n + 1) *
ULONG_BIT - 1. A função getbits retorna o valor dos bits entre as posições index e index + length - 1
do vetor de bits representado por data. A função setbits escreve os len bits de menor peso de val nas
posições entre index e index + length - 1 do vetor de bits representado por data. Em ambas as funções,
length nunca é maior do que ULONG_BIT. Exemplo: para data = {0xBFFFFFECABCD1234, 0xC, 2, 3 }, a
chamada a getbits(data, 29, 8) retorna 0x00000000000000065. Defina ULONG_BIT com base em
CHAR_BIT e implemente as funções getbits e setbits.
*/

#define ULONG_BIT (CHAR_BIT * sizeof(unsigned long))

unsigned long getbits(unsigned long data[], unsigned index, unsigned length) {
    unsigned long bitMenor = index % ULONG_BIT;
    unsigned long arrIdx = index / ULONG_BIT;
    unsigned long result = 0;

    for (int i = 0; i < length; i++) {
        unsigned long actualNumber = data[arrIdx]; // palavra onde começo
        unsigned long bit_taken = (actualNumber >> bitMenor) & 1UL; // Extrai o bit atual corretamente
        bitMenor++;// Incrementa o bit atual
        result |= (bit_taken << i);// Coloca o bit no lugar certo
        // Verifica se o bit atual é maior que o tamanho de um unsigned long
        if (bitMenor >= ULONG_BIT) {
            bitMenor = 0;
            arrIdx++;
        }
    }
    return result;
}

void setbits(unsigned long data[], unsigned index, unsigned length, unsigned long val) {
    unsigned long bitMenor = index % ULONG_BIT;
    unsigned long actualNumber = index / ULONG_BIT;

    for (int i = 0; i < length; i++) {
        unsigned long bit = (val >> i) & 1UL;// Extrai o bit atual corretamente
        unsigned long first_bit = (data[actualNumber] & ~(1UL << bitMenor));// Coloca o bit a 0 na posição atual
        data[actualNumber] = first_bit | (bit << bitMenor);// Coloca o bit no lugar certo
        bitMenor++;
        if (bitMenor >= ULONG_BIT) {
            bitMenor = 0;
            actualNumber++;
        }
    }
}

