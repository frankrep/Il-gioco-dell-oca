/*
 * vincitore.c
 *
 */

#include <stdlib.h>
#include "vincitore.h"



void scrivere_carattere_nome_vincitore (vincitore* vincitore_attuale, int posizione, char simbolo) {
	vincitore_attuale->nome_vincitore [posizione] = simbolo;
    return;
}



char leggere_carattere_nome_vincitore (vincitore vincitore_attuale, int posizione) {
    char simbolo = vincitore_attuale.nome_vincitore [posizione];
    return simbolo;
}



void scrivere_pedina_vincitore (vincitore* vincitore_attuale, char pedina) {
    vincitore_attuale->pedina_vincitore = pedina;
}



char leggere_pedina_vincitore (vincitore vincitore_attuale) {
    char pedina = vincitore_attuale.pedina_vincitore;
    return pedina;
}



void scrivere_lunghezza_percorso_vincitore (vincitore* vincitore_attuale, int lunghezza) {
    vincitore_attuale->lunghezza_percorso_vincitore = lunghezza;
}



int leggere_lunghezza_percorso_vincitore (vincitore vincitore_attuale) {
    int lunghezza = vincitore_attuale.lunghezza_percorso_vincitore;
    return lunghezza;
}



void scrivere_lanci_vincitore (vincitore* vincitore_attuale, int lanci) {
    vincitore_attuale->lanci_vincitore = lanci;
}



int leggere_lanci_vincitore (vincitore vincitore_attuale) {
    int lanci = vincitore_attuale.lanci_vincitore;
    return lanci;
}



void scrivere_punteggio (vincitore* vincitore_attuale, float punteggio_vincitore) {
    vincitore_attuale->punteggio = punteggio_vincitore;
}



float leggere_punteggio (vincitore vincitore_attuale) {
    float punteggio_vincitore = vincitore_attuale.punteggio;
    return punteggio_vincitore;
}



void scrivere_nome_vincitore (vincitore* vincitore_attuale, char nome_da_inserire []) {
    int indice_nome = 0;
    while (nome_da_inserire [indice_nome] != FINE_STRINGA) {
        scrivere_carattere_nome_vincitore (vincitore_attuale, indice_nome, nome_da_inserire [indice_nome]);
        indice_nome = indice_nome + 1;
    }
    scrivere_carattere_nome_vincitore (vincitore_attuale, indice_nome, FINE_STRINGA);
    return;
}



void leggere_nome_vincitore (vincitore vincitore_attuale, char nome_letto []) {
    int indice_nome = 0;
    while (leggere_carattere_nome_vincitore (vincitore_attuale, indice_nome) != FINE_STRINGA){
        nome_letto [indice_nome] = leggere_carattere_nome_vincitore (vincitore_attuale, indice_nome);
        indice_nome = indice_nome + 1;
    }
    nome_letto [indice_nome] = FINE_STRINGA;
    return;
}
