/*
 * partita.c
 *
 */

#include <stdlib.h>
#include "partita.h"

void scrivere_carattere_partita (partita* partita_attuale, int posizione, char simbolo) {
    partita_attuale->nome_partita[posizione] = simbolo;
    return;
}
char leggere_carattere_partita (partita partita_attuale, int posizione) {
    char simbolo = partita_attuale.nome_partita[posizione];
    return simbolo;
}
void scrivere_numero_giocatori (partita* partita_attuale, int numero_partecipanti) {
	partita_attuale->numero_giocatori = numero_partecipanti;
    return;
}
int leggere_numero_giocatori (partita partita_attuale) {
    int numero_partecipanti = partita_attuale.numero_giocatori;
    return numero_partecipanti;
}
void scrivere_lunghezza_percorso (partita* partita_attuale, int dimensione_caselle){
	partita_attuale->lunghezza_percorso = dimensione_caselle;
    return;
}
int leggere_lunghezza_percorso (partita partita_attuale) {
    int dimensione_caselle = partita_attuale.lunghezza_percorso;
    return dimensione_caselle;
}
void scrivere_casella_percorso (partita* partita_attuale, casella casella_attuale, int posizione_casella) {
	partita_attuale->percorso[posizione_casella] = casella_attuale;
    return;
}
casella leggere_casella_percorso (partita partita_attuale, int posizione_casella) {
    casella casella_attuale = partita_attuale.percorso[posizione_casella];
    return casella_attuale;
}
void scrivere_turno (partita* partita_attuale, int turno_attuale) {
	partita_attuale->turno = turno_attuale;
    return;
}
int leggere_turno (partita partita_attuale) {
    int turno_attuale = partita_attuale.turno;
    return turno_attuale;
}
void scrivere_dadi (partita* partita_attuale, int faccia_dado, int posizione_dado) {
	partita_attuale->dadi[posizione_dado] = faccia_dado;
}
int leggere_dadi (partita partita_attuale, int posizione_dado) {
    int faccia_dado = partita_attuale.dadi[posizione_dado];
    return faccia_dado;
}
void scrivere_giocatore (partita* partita_attuale, giocatore giocatore_attuale, int posizione_elenco_giocatori) {
	partita_attuale->giocatori[posizione_elenco_giocatori] = giocatore_attuale;
    return;
}
giocatore leggere_giocatore (partita partita_attuale, int posizione_elenco_giocatori) {
    giocatore giocatore_attuale = partita_attuale.giocatori[posizione_elenco_giocatori];
    return giocatore_attuale;
}

void scrivere_nome_partita (partita* partita_attuale, char nome_da_inserire[]) {
    int indice_nome = 0;
    while (nome_da_inserire[indice_nome] != FINE_STRINGA) {
        scrivere_carattere_partita(partita_attuale, indice_nome, nome_da_inserire[indice_nome]);
        indice_nome = indice_nome + 1;
    }
    scrivere_carattere_partita(partita_attuale, indice_nome, FINE_STRINGA);
    return;
}

void leggere_nome_partita (partita partita_attuale, char nome_letto[]) {
    int indice_nome = 0;
    while(leggere_carattere_partita (partita_attuale, indice_nome) != FINE_STRINGA){
        nome_letto[indice_nome] = leggere_carattere_partita(partita_attuale, indice_nome);
        indice_nome = indice_nome + 1;
    }
    nome_letto [indice_nome] = FINE_STRINGA;
    return;
}
