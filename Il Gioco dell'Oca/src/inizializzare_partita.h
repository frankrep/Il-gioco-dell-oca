#ifndef INIZIALIZZARE_PARTITA_H_
#define INIZIALIZZARE_PARTITA_H_

partita* inizializzare_giocatori(partita* partita_attuale);
partita* richiedere_numero_caselle(partita* partita_attuale);
partita* inizializzare_numero_giocatori(partita* partita_attuale);
partita* inizializzare_nomi_giocatori(partita* partita_attuale);
char* inserire_stringa(int dimensione_minima_stringa, int dimensione_massima_stringa);
partita* inizializzare_pedine_giocatori(partita* partita_attuale);
#endif /* INIZIALIZZARE_PARTITA_H_ */