#include "vincitore.h"
#include <stlib.h>
void scrivere_nome_vincitore(vincitore* vincitore_attuale, char nome[]){
    vincitore_attuale->nome_vincitore = nome;
}
char* leggere_nome_vincitore(vincitore* vincitore_attuale){
    char* nome = vincitore_attuale->nome_vincitore;
    return nome;
}
void scrivere_pedina_vincitore(vincitore* vincitore_attuale, char pedina){
    vincitore_attuale->pedina_vincitore = pedina;
}
char leggere_pedina_vincitore(vincitore* vincitore_attuale){
    char pedina = vincitore_attuale->pedina_vincitore;
    return pedina;
}
void scrivere_lunghezza_percorso_vincitore(vincitore* vincitore_attuale, int lunghezza){
    vincitore_attuale->lunghezza_percorso_vincitore = lunghezza;
}
int leggere_lunghezza_percorso_vincitore(vincitore* vincitore_attuale){
    int lunghezza = vincitore_attuale->lunghezza_percorso_vincitore;
    return lunghezza;
}
void scrivere_lanci_vincitore(vincitore* vincitore_attuale, int lanci){
    vincitore_attuale->lanci_vincitore = lanci;
}
int leggere_lanci_vincitore(vincitore* vincitore_attuale){
    int lanci = vincitore_attuale->lanci_vincitore;
    return lanci;
}
void scrivere_punteggio(vincitore* vincitore_attuale, float punteggio_giocatore){
    vincitore_attuale->punteggio = punteggio_giocatore;

}
float leggere_punteggio(vincitore* vincitore_attuale){
    float punteggio_giocatore = vincitore_attuale->punteggio;
    return punteggio;
}