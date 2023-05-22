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

void scrivere_nome_vincitore(vincitore* vincitore_attuale, char nome[]);
char* leggere_nome_vincitore(vincitore* vincitore_attuale);
void scrivere_pedina_vincitore(vincitore* vincitore_attuale, char pedina);
char leggere_pedina_vincitore(vincitore* vincitore_attuale);
void scrivere_lunghezza_percorso_vincitore(vincitore* vincitore_attuale, int lunghezza);
int leggere_lunghezza_percorso_vincitore(vincitore* vincitore_attuale);
void scrivere_lanci_vincitore(vincitore* vincitore_attuale, int lanci);
int leggere_lanci_vincitore(vincitore* vincitore_attuale);
void scrivere_punteggio(vincitore* vincitore_attuale, float punteggio);
float leggere_punteggio(vincitore* vincitore_attuale);
#endif /* VINCITORE_H_ */