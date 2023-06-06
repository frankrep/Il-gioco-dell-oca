/*
 * gestire_partita.h
 *
 */

#ifndef GESTIRE_PARTITA_H_
#define GESTIRE_PARTITA_H_

#include "partita.h"
#include "vincitore.h"

vincitore gestire_partita(partita* partita_attuale);
void scegliere_giocatore(partita* partita_attuale);
vincitore inizializzare_vincitore(partita* partita_attuale);
int generare_numero(int numero_massimo, int numero_minimo);
int generare_seme(int seme);
int generare_casuale(int seme,int numero_massimo,int numero_minimo);
int trovare_posizione_massimo(int* valori, int dimensione_valori);
void cambiare_turno(partita* partita_attuale);
void lanciare_dadi(partita* partita_attuale);
void incrementare_lanci_effettuati(partita* partita_attuale);
void incrementare_turno(partita* partita_attuale);
void spostare_giocatore(partita* partita_attuale);
void sommare_lancio_posizione(partita* partita_attuale);
void calcolare_caselle_eccesso(partita* partita_attuale);
int sommare_dadi(partita* partita_attuale);
void gestire_casella(partita* partita_attuale);
void gestire_oca(partita* partita_attuale);
void impostare_autorizzazioni(partita* partita_attuale, char nome_casella_attuale[]);
void gestire_autorizzazione(partita* partita_attuale);
int confrontare_stringhe(char stringa_1[],char stringa_2[]);

#endif /* GESTIRE_PARTITA_H_ */
