/*
 * giocatore.c
 *
 */



#include "giocatore.h"



void scrivere_carattere_nome_giocatore (giocatore* giocatore_attuale, int posizione, char simbolo) {
	giocatore_attuale->nome_giocatore [posizione] = simbolo;
    return;
}



char leggere_carattere_nome_giocatore (giocatore giocatore_attuale, int posizione) {
    char simbolo = giocatore_attuale.nome_giocatore [posizione];
    return simbolo;
}



void scrivere_posizione_giocatore (giocatore* giocatore_attuale, int posizione) {
	giocatore_attuale->posizione_giocatore = posizione;
    return;
}



int leggere_posizione_giocatore (giocatore giocatore_attuale) {
    int posizione = giocatore_attuale.posizione_giocatore;
    return posizione;
}



void scrivere_pedina_giocatore (giocatore* giocatore_attuale, char pedina) {
	giocatore_attuale->pedina_giocatore = pedina;
    return;
}



char leggere_pedina_giocatore (giocatore giocatore_attuale) {
    char pedina = giocatore_attuale.pedina_giocatore;
    return pedina;
}



void scrivere_lanci_effettuati (giocatore* giocatore_attuale, int lanci) {
	giocatore_attuale->lanci_effettuati = lanci;
    return;
}



int leggere_lanci_effettuati (giocatore giocatore_attuale) {
    int lanci = giocatore_attuale.lanci_effettuati;
    return lanci;
}



void scrivere_autorizzazione (giocatore* giocatore_attuale, int autorizzazione_da_inserire){
	giocatore_attuale->autorizzazione = autorizzazione_da_inserire;
    return;
}



int leggere_autorizzazione (giocatore giocatore_attuale) {
    int autorizzazione_letta = giocatore_attuale.autorizzazione;
    return autorizzazione_letta;
}



void scrivere_nome_giocatore (giocatore* giocatore_attuale, char nome_da_inserire[]) {
    int indice_nome = 0;
    while (nome_da_inserire [indice_nome] != FINE_STRINGA) {
        scrivere_carattere_nome_giocatore (giocatore_attuale, indice_nome, nome_da_inserire[indice_nome]);
        indice_nome = indice_nome + 1;
    }
    scrivere_carattere_nome_giocatore (giocatore_attuale, indice_nome, nome_da_inserire[indice_nome]);
    return;
}



void leggere_nome_giocatore (giocatore giocatore_attuale, char nome_letto[]) {
    int indice_nome = 0;
    while (leggere_carattere_nome_giocatore (giocatore_attuale, indice_nome) != FINE_STRINGA) {
        nome_letto [indice_nome] = leggere_carattere_nome_giocatore (giocatore_attuale, indice_nome);
        indice_nome = indice_nome + 1;
    }
    nome_letto [indice_nome] = FINE_STRINGA;
    return;
}
