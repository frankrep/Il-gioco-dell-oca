/*
 * vincitore.h
 *
 */

#ifndef VINCITORE_H_
#define VINCITORE_H_

#include "costanti.h"

typedef struct
{
    char nome_vincitore[DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    char pedina_vincitore;
    int lanci_vincitore;
    int lunghezza_percorso_vincitore;
    float punteggio;

}vincitore;

void scrivere_carattere_nome_vincitore (vincitore* vincitore_attuale, int posizione, char simbolo);
char leggere_carattere_nome_vincitore (vincitore vincitore_attuale, int posizione);
void scrivere_pedina_vincitore (vincitore* vincitore_attuale, char pedina);
char leggere_pedina_vincitore (vincitore vincitore_attuale);
void scrivere_lunghezza_percorso_vincitore (vincitore* vincitore_attuale, int lunghezza);
int leggere_lunghezza_percorso_vincitore (vincitore vincitore_attuale);
void scrivere_lanci_vincitore (vincitore* vincitore_attuale, int lanci);
int leggere_lanci_vincitore (vincitore vincitore_attuale);
void scrivere_punteggio (vincitore* vincitore_attuale, float punteggio_vincitore);
float leggere_punteggio (vincitore vincitore_attuale);
void scrivere_nome_vincitore (vincitore* vincitore_attuale, char nome_da_inserire[]);
void leggere_nome_vincitore (vincitore vincitore_attuale, char nome_letto[]);

#endif /* VINCITORE_H_ */
