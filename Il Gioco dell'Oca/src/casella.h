/*
 * casella.h
 *
 */

#ifndef CASELLA_H_
#define CASELLA_H_

#include "costanti.h"

typedef struct {
    char nome_casella [DIMENSIONE_MASSIMA_NOME_CASELLA];
    int numero_casella;
    char simbolo [NUMERO_MASSIMO_CARATTERI_SIMBOLO];
} casella;

void scrivere_carattere_casella (casella* casella_attuale, int posizione, char simbolo);
char leggere_carattere_casella (casella casella_attuale, int posizione);
void scrivere_numero_casella (casella* casella_attuale, int numero_casella_da_inserire);
int leggere_numero_casella (casella casella_attuale);
void scrivere_carattere_simbolo (casella* casella_attuale, int posizione, char simbolo_da_inserire);
char leggere_carattere_simbolo (casella casella_attuale, int posizione);
void scrivere_nome_casella (casella* casella_attuale, const char nome_da_inserire[]);
void leggere_nome_casella (casella casella_attuale, char nome_letto[]);
void scrivere_simbolo (casella* casella_attuale, const char simbolo_da_inserire[]);
void leggere_simbolo (casella casella_attuale, char simbolo_letto[]);

#endif /* CASELLA_H_ */
