#ifndef INIZIALIZZARE_PARTITA_H_
#define INIZIALIZZARE_PARTITA_H_
#include "partita.h"



void inizializzare_giocatori (partita *partita_attuale, int * indietro_precedente);
void inserire_stringa (int dimensione_minima_stringa, int dimensione_massima_stringa, char nome_da_inserire[], int * indietro);
int calcolare_lunghezza_stringa (const char stringa[]);
void richiedere_stringa (const char file_interfaccia[], int dimensione_minima_stringa, int dimensione_massima_stringa, char nome_da_inserire[], int * indietro);
void inizializzare_autorizzazione_giocatori(partita *partita_attuale);
void inizializzare_posizione_giocatori(partita *partita_attuale);

#endif /* INIZIALIZZARE_PARTITA_H_ */
