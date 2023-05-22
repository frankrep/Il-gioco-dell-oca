#ifndef CASELLA_H_
#define CASELLA_H_
#include "costanti.h"
typedef struct
{
    char nome_casella[DIMENSIONE_MASSIMA_NOME_CASELLA];
    int numero_casella;
    char file_interfaccia[NUMERO_MASSIMO_CARATTERI_PERCORSO];
    char simbolo[NUMERO_MASSIMO_CARATTERI_SIMBOLO];
}casella;

void scrivere_nome_casella(casellla* casella_attuale, char nome_da_inserire[]);
char* leggere_nome_casella(casella* casella_attuale);
void scrivere_numero_casella(casella* casella_attuale, int numero_casella_da_inserire);
int leggere_numero_casella(casella* casella_attuale);
void scrivere_file_interfaccia(casella* casella_attuale, char file[]);
char* leggere_file_interfaccia(casella* casella_attuale);
void scrivere_simbolo(casella* casella_attuale, char simbolo_da_inserire[]);
char* leggere_simbolo(casella* casella_attuale);
#endif /* CASELLA_H_ */