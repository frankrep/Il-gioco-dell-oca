#include "giocatore.h"
#include <stdlib.h>
void scrivere_nome_giocatore(giocatore* giocatore_attuale, char nome[]){
    giocatore_attuale->nome_giocatore = nome;
}
char* leggere_nome_giocatore(giocatore* giocatore_attuale){
    char* nome = giocatore_attuale->nome_giocatore;
    return nome;
}
void scrivere_posizione_giocatore(giocatore* giocatore_attuale, int posizione){
	giocatore_attuale->posizione_giocatore = posizione;
}
int leggere_posizione_giocatore(giocatore* giocatore_attuale){
    int posizione = giocatore_attuale->posizione_giocatore;
    return posizione;
}
void scrivere_pedina_giocatore(giocatore* giocatore_attuale, char pedina){
	giocatore_attuale->pedina_giocatore = pedina;
}
char leggere_pedina_giocatore(giocatore* giocatore_attuale){
    char pedina = giocatore_attuale->pedina_giocatore;
    return pedina;
}   
void scrivere_lanci_effettuati(giocatore* giocatore_attuale, int lanci){
	giocatore_attuale->lanci_effettuati = lanci;
}
int leggere_lanci_effettuati(giocatore* giocatore_attuale){
    int lanci = giocatore_attuale->lanci_effettuati;
    return lanci;
}
void scrivere_autorizzazione(giocatore* giocatore_attuale, int autorizzazione_da_inserire){
	giocatore_attuale->autorizzazione = autorizzazione_da_inserire;
}
int leggere_autorizzazione(giocatore* giocatore_attuale){
    int autorizzazione_letta = giocatore_attuale->autorizzazione;
    return autorizzazione_letta;
}
