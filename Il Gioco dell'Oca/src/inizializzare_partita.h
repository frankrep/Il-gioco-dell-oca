#ifndef INIZIALIZZARE_PARTITA_H_
#define INIZIALIZZARE_PARTITA_H_
#include "partita.h"



void inizializzare_giocatori(partita* partita_attuale);
void inserire_stringa(int dimensione_minima_stringa, int dimensione_massima_stringa, char nome_da_inserire[]);
int calcolare_lunghezza_stringa (char stringa[]);
void richiedere_stringa(const char file_interfaccia[], int dimensione_minima_stringa, int dimensione_massima_stringa, char nome_da_inserire[]);


#endif /* INIZIALIZZARE_PARTITA_H_ */
