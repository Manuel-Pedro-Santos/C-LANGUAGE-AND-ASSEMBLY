#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Programe a função string_to_time que converte a informação de data e hora, recebida na forma de string C,
para uma struct do tipo struct tm . A string de entrada tem o formato “dd-mm-aaaa hh:mm:ss”. Os campos
tm_wday, tm_yday e tm_isdst devem ser colocados a zero. Se a string de entrada estiver mal formatada a
função devolve 0, senão devolve 1; */

struct tm {
int tm_sec;
int tm_min;
int tm_hour;
int tm_mday;
int tm_mon;
int tm_year;
int tm_wday;
int tm_yday;
int tm_isdst;
};

int string_to_time(const char *string, struct tm *newTm) {

    // Verifica se a string é válida
    if(sscanf(string, "%2d-%2d-%4d %2d:%2d:%2d", 
    &newTm->tm_mday, &newTm->tm_mon, 
    &newTm->tm_year, &newTm->tm_hour, 
    &newTm->tm_min, &newTm->tm_sec) != 6)
    {  return 0 ;  }
    // O ano começa em 1900 logo temos que decrementar 1900.
    newTm->tm_year -= 1900;
    // O mês começa em 0(Janeiro) logo temos que decrementar 1.
    newTm->tm_mon -= 1;
    //De resto colocar tudo a zero a pedido do Professor.
    newTm->tm_isdst = 0;
    newTm->tm_yday = 0;
    newTm->tm_wday = 0;
        
    return 1;
}