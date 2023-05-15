#ifndef PARTITA_H_
#define PARTITA_H_
#include "casella.h"
#include "giocatore.h"
#include "casella.c"
#include "giocatore.c"

typedef struct
{
    char* nome_partita;
    int numero_giocatori;
    int lunghezza_percorso;
    casella* percorso;
    giocatore* giocatori;
    int turno;
    int* dadi;
    
}partita;

void scrivere_nome_partita(partita* partita_attuale, char* nome);
char* leggere_nome_partita(partita* partita_attuale);
void scrivere_numero_giocatori(partita* partita_attuale, int numero_partecipanti);
int leggere_numero_giocatori(partita* partita_attuale);
void scrivere_lunghezza_percorso(partita* partita_attuale, int dimensione_caselle);
int leggere_lunghezza_percorso(partita* partita_attuale);
void scrivere_casella_percorso(partita* partita_attuale, casella* casella_attuale,int posizione_casella);
casella* leggere_casella_percorso(partita* partita_attuale, int posizione_casella);
void scrivere_turnop(partita* partita_attuale,int turno_attuale);
int leggere_turno(partita* partita_attuale);
void scrivere_dadi(partita* partita_attuale,int faccia_dado,int posizione_dado);
int* leggere_dadi(partita* partita_attuale,int posizione_dado);
void scrivere_giocatore(partita* partita_attuale, giocatore* giocatore_attuale,int posizione_elenco_giocatori);
giocatore* leggere_giocatore(partita* partita_attuale,int posizione_elenco_giocatori);
#endif /* PARTITA_H_ */