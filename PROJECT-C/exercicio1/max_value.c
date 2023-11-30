#include <stdio.h>
#include <limits.h>

/**
 Considere o critério “complemento para 2” na representação de valores inteiros relativos (com sinal). Escreva a
função max_value, que retorna o maior valor positivo que pode ser representado pelo número de bits
equivalente ao número de bits de um char, vezes o valor indicado pelo parâmetro nchars. Se o valor não for
representável num unsigned long, deve retornar zero. Deve basear-se na macro CHAR_BIT, definida em
limits.h, para obter o número de bits de um char .
*/

unsigned long max_value(unsigned nchars){

    // Obtem o numero de bits que o tipo unsigned long tem.
    unsigned long result = sizeof(unsigned long) * nchars;
    
    // Verifica se o numero de bits é maior que o numero de bits que o tipo unsigned long tem.
    if (result > (sizeof(unsigned long) * CHAR_BIT) || nchars == 0)  
        return 0;
    else 
        return (1UL << (result-1)) -1;
}