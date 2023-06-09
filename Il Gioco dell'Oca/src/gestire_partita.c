/*
 * gestire_partita.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "casella.h"
#include "giocatore.h"
#include "partita.h"
#include "vincitore.h"
#include "costanti.h"
#include "gestire_partita.h"
#include "generare_numero_casuale.h"
#include "generare_percorso.h"
#include "gestire_stampa.h"



void scegliere_giocatore(partita* partita_attuale);
vincitore inizializzare_vincitore(partita* partita_attuale);
int trovare_posizione_massimo(const int valori[], int dimensione_valori);
void cambiare_turno(partita* partita_attuale);
void lanciare_dadi(partita* partita_attuale);
void incrementare_lanci_effettuati(partita* partita_attuale);
void incrementare_turno(partita* partita_attuale);
void spostare_giocatore(partita* partita_attuale);
void sommare_lancio_posizione(partita* partita_attuale);
void calcolare_caselle_eccesso(partita* partita_attuale);
int sommare_dadi (partita partita_attuale);
void verificare_casella(partita* partita_attuale);
void gestire_oca(partita* partita_attuale);
void impostare_autorizzazioni(partita* partita_attuale, const char nome_casella_attuale[]);
void gestire_autorizzazione(partita* partita_attuale);



vincitore gestire_partita (partita* partita_attuale) {
    if ( leggere_turno (*partita_attuale) == 0 ) {
        scegliere_giocatore (partita_attuale);
    }
    do{
        cambiare_turno (partita_attuale);
        if ( leggere_autorizzazione (leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) ) ) > 0) {
            gestire_autorizzazione(partita_attuale);
        }
        if ( leggere_autorizzazione (leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) ) ) == 0 ) {
            //stampare percorso con l'attesa con l'attesa dell'input
            lanciare_dadi (partita_attuale);
            //stampare percorso con i dadi aggiornati e attendere l'input
            spostare_giocatore (partita_attuale);
            //stampare percorso con input utente per proseguire con l'effetto
            verificare_casella (partita_attuale);
        }

        } while ( leggere_posizione_giocatore (leggere_giocatore (*partita_attuale,leggere_turno (*partita_attuale) ) ) != leggere_lunghezza_percorso (*partita_attuale) );
        vincitore vincitore_partita = inizializzare_vincitore (partita_attuale);
        return vincitore_partita;
}



void scegliere_giocatore (partita* partita_attuale) {
    stampare_testo (FILE_SCELTA_G_INIZIALE);
    int estrazioni [NUMERO_MASSIMO_GIOCATORI];
    int indice_giocatori = 0;
    while (indice_giocatori < leggere_numero_giocatori (*partita_attuale) ) {
        posizionare_cursore_in_attesa (FILE_SCELTA_G_INIZIALE);
        fgetc(stdin);
        estrazioni [indice_giocatori] = generare_numero (FACCIA_MINIMA_DADO, FACCIA_MASSIMA_DADO);
        stampare_dadi (FILE_SCELTA_G_INIZIALE, estrazioni);
        fgetc (stdin);
        indice_giocatori = indice_giocatori + 1;
    }
    scrivere_turno (partita_attuale, trovare_posizione_massimo (estrazioni, leggere_numero_giocatori (*partita_attuale) ) - 1);
    return;
}



vincitore inizializzare_vincitore (partita* partita_attuale) {
    vincitore vincitore_partita;
    char nome_vincitore[DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    leggere_nome_giocatore(leggere_giocatore(*partita_attuale, leggere_turno(*partita_attuale)), nome_vincitore);
    scrivere_nome_vincitore(&vincitore_partita, nome_vincitore);
    scrivere_pedina_vincitore(&vincitore_partita, leggere_pedina_giocatore(leggere_giocatore(*partita_attuale, leggere_turno(*partita_attuale))));
    scrivere_lanci_vincitore(&vincitore_partita, leggere_lanci_effettuati(leggere_giocatore(*partita_attuale, leggere_turno(*partita_attuale))));
    scrivere_lunghezza_percorso_vincitore(&vincitore_partita, leggere_lunghezza_percorso(*partita_attuale));
    //funzione per il campo punteggio
    return vincitore_partita;
}



int trovare_posizione_massimo (const int valori[], int dimensione_valori) {
    int indice_valori = 0;
    int massimo = valori[indice_valori];
    int posizione_massimo = indice_valori;
    while (indice_valori < dimensione_valori) {
        indice_valori = indice_valori + 1;
        if (massimo < valori [indice_valori]) {
            massimo = valori[indice_valori];
            posizione_massimo = indice_valori;
        }
    }
    return posizione_massimo;
}



void cambiare_turno (partita* partita_attuale) {
    scrivere_turno (partita_attuale, leggere_turno (*partita_attuale) + 1);
    if (leggere_turno (*partita_attuale) >= leggere_numero_giocatori (*partita_attuale) ) {
        scrivere_turno (partita_attuale, 0);
    }
    return;
}



void lanciare_dadi (partita* partita_attuale) {
    int indice_dado = 0;
    int lancio;
    while (indice_dado < NUMERO_DADI) {
        lancio = generare_numero(FACCIA_MINIMA_DADO, FACCIA_MASSIMA_DADO);
        scrivere_dadi (partita_attuale, indice_dado, lancio);
        indice_dado = indice_dado + 1;
    }
    return;
}



void incrementare_lanci_effettuati(partita* partita_attuale){
    giocatore giocatore_attuale;
    int lanci_effettuati;
    giocatore_attuale = leggere_giocatore(*partita_attuale, leggere_turno(*partita_attuale));
    lanci_effettuati = leggere_lanci_effettuati(giocatore_attuale);
    lanci_effettuati = lanci_effettuati + 1;
    scrivere_lanci_effettuati(&giocatore_attuale, lanci_effettuati);
    scrivere_giocatore(partita_attuale,giocatore_attuale, leggere_turno(*partita_attuale));
    return;
}



void spostare_giocatore (partita* partita_attuale) {
    sommare_lancio_posizione (partita_attuale);
    if ( leggere_posizione_giocatore (leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) ) ) > leggere_lunghezza_percorso (*partita_attuale) ) {
        calcolare_caselle_eccesso (partita_attuale);
    }
    return;
}

void sommare_lancio_posizione (partita* partita_attuale) {
    giocatore giocatore_attuale = leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) );
    scrivere_posizione_giocatore (&giocatore_attuale, leggere_posizione_giocatore (giocatore_attuale) + sommare_dadi (*partita_attuale) );
    scrivere_giocatore (partita_attuale, giocatore_attuale, leggere_turno (*partita_attuale) );
    return;
}

void calcolare_caselle_eccesso(partita* partita_attuale){
    giocatore giocatore_attuale;
    int eccesso = leggere_posizione_giocatore (leggere_giocatore ( *partita_attuale, leggere_turno (*partita_attuale) ) ) - leggere_lunghezza_percorso (*partita_attuale);
    giocatore_attuale = leggere_giocatore (*partita_attuale,leggere_turno (*partita_attuale) );
    scrivere_posizione_giocatore (&giocatore_attuale, leggere_posizione_giocatore (giocatore_attuale) - eccesso);
    scrivere_giocatore (partita_attuale, giocatore_attuale, leggere_turno (*partita_attuale) );
    return;
}

int sommare_dadi (partita partita_attuale) {
    int somma_dadi = 0;
    int indice_dado = 0;
    while (indice_dado < NUMERO_DADI) {
        somma_dadi = somma_dadi + leggere_dadi (partita_attuale, indice_dado);
        indice_dado = indice_dado + 1;
    }
    return somma_dadi;
}

void verificare_casella (partita* partita_attuale) {
    giocatore giocatore_attuale;
    char nome_casella[DIMENSIONE_MASSIMA_NOME_CASELLA];
    do{
        giocatore_attuale = leggere_giocatore (*partita_attuale, leggere_turno(*partita_attuale) );
        leggere_nome_casella (leggere_casella_percorso (*partita_attuale, leggere_posizione_giocatore (giocatore_attuale) ), nome_casella );
        if ( confrontare_stringhe (nome_casella, NOME_OCA) == VERO ) {
            //stampare schermata_oca e aspettare input
            gestire_oca (partita_attuale);
        }
        else if(confrontare_stringhe(nome_casella, NOME_PONTE) == VERO ) {
            //schermata_ponte e aspettare input
            spostare_giocatore(partita_attuale);
        }
        else if (confrontare_stringhe(nome_casella, NOME_LOCANDA) == VERO ) {
            //stampare schermata_locanda e aspettare input
            scrivere_autorizzazione(&giocatore_attuale, TURNI_ATTESA_LOCANDA);
            scrivere_giocatore(partita_attuale, giocatore_attuale, leggere_turno(*partita_attuale));
        }
        else if (confrontare_stringhe(nome_casella, NOME_POZZO) == VERO )
        {
            //stampare schermata_pozzo e aspettare input
            impostare_autorizzazioni(partita_attuale, NOME_POZZO);
        }
        else if (confrontare_stringhe(nome_casella, NOME_PRIGIONE) == VERO )
        {
            //stampare schermata_prigione e aspettare input
            impostare_autorizzazioni(partita_attuale, NOME_PRIGIONE);
        }
        else if (confrontare_stringhe(nome_casella, NOME_LABIRINTO) == VERO )
        {
            //stampare schermata_labirinto e aspettare input
            scrivere_posizione_giocatore(&giocatore_attuale, calcolare_proporzione(*partita_attuale, CASELLA_ARRIVO_LABIRINTO));
            leggere_nome_casella(leggere_casella_percorso(*partita_attuale, leggere_posizione_giocatore(giocatore_attuale)), nome_casella);
            while (confrontare_stringhe(nome_casella, STRINGA_VUOTA) == FALSO ){
            	leggere_nome_casella(leggere_casella_percorso(*partita_attuale, leggere_posizione_giocatore(giocatore_attuale)), nome_casella);
            	scrivere_posizione_giocatore(&giocatore_attuale, leggere_posizione_giocatore(giocatore_attuale) - 1);
            }
            scrivere_giocatore(partita_attuale, giocatore_attuale, leggere_turno(*partita_attuale));
        }
        else if (confrontare_stringhe(nome_casella, NOME_SCHELETRO) == VERO )
        {
            //stampare schermata_scheletro e aspettare input
            scrivere_posizione_giocatore(&giocatore_attuale, CASELLA_ARRIVO_SCHELETRO);
            scrivere_giocatore(partita_attuale, giocatore_attuale, leggere_turno(*partita_attuale));
        }
              //stampare percorso e aspettare input
        leggere_nome_casella(leggere_casella_percorso(*partita_attuale, leggere_posizione_giocatore(giocatore_attuale)), nome_casella);
    }while(confrontare_stringhe(nome_casella, STRINGA_VUOTA) == FALSO);
    return;
}

void gestire_oca (partita* partita_attuale) {
    giocatore giocatore_attuale = leggere_giocatore ( *partita_attuale, leggere_turno (*partita_attuale) );
    if (leggere_lanci_effettuati (giocatore_attuale) == 1) {
        if ( ( leggere_dadi (*partita_attuale, PRIMO_DADO) == DADO_MINORE_PRIMO_LANCIO) || (leggere_dadi (*partita_attuale, PRIMO_DADO) == DADO_MAGGIORE_PRIMO_LANCIO) ) {
            scrivere_posizione_giocatore (&giocatore_attuale, calcolare_proporzione (*partita_attuale, PRIMO_LANCIO_3_6) );
        }
        else {
            scrivere_posizione_giocatore (&giocatore_attuale, calcolare_proporzione (*partita_attuale, PRIMO_LANCIO_4_5) );
        }
        char nome_casella[DIMENSIONE_MASSIMA_NOME_CASELLA];
        leggere_nome_casella (leggere_casella_percorso (*partita_attuale, leggere_posizione_giocatore (giocatore_attuale) ), nome_casella);
        while (confrontare_stringhe (nome_casella, STRINGA_VUOTA) == FALSO)
        {
        	leggere_nome_casella(leggere_casella_percorso(*partita_attuale, leggere_posizione_giocatore(giocatore_attuale)), nome_casella);
            scrivere_posizione_giocatore(&giocatore_attuale, leggere_posizione_giocatore(giocatore_attuale) - 1);
        }
        scrivere_giocatore(partita_attuale, giocatore_attuale, leggere_turno(*partita_attuale));
    }else{
        spostare_giocatore(partita_attuale);
    }
    return;
}

void impostare_autorizzazioni(partita* partita_attuale, const char nome_casella_attuale[]){
    giocatore giocatore_attuale;
    int indice_giocatore = 0;
    while (indice_giocatore <= leggere_numero_giocatori(*partita_attuale)){
        giocatore_attuale = leggere_giocatore(*partita_attuale, indice_giocatore);
        char nome_casella[DIMENSIONE_MASSIMA_NOME_CASELLA];
        leggere_nome_casella(leggere_casella_percorso(*partita_attuale, leggere_posizione_giocatore(giocatore_attuale)), nome_casella);
        if (confrontare_stringhe (nome_casella, nome_casella_attuale) == VERO){
            //stampare schermata_liberato e attendere input
            scrivere_autorizzazione(&giocatore_attuale, 0);
            scrivere_giocatore(partita_attuale, giocatore_attuale, indice_giocatore);
        }
        indice_giocatore = indice_giocatore + 1;
    }
    leggere_giocatore(*partita_attuale, leggere_turno(*partita_attuale));
    scrivere_autorizzazione(&giocatore_attuale, 1);
    scrivere_giocatore(partita_attuale, giocatore_attuale, leggere_turno(*partita_attuale));
    return;
}

void gestire_autorizzazione (partita* partita_attuale) {
    giocatore giocatore_attuale = leggere_giocatore ( *partita_attuale, leggere_turno (*partita_attuale) );
    char nome_casella [DIMENSIONE_MASSIMA_NOME_CASELLA];
    leggere_nome_casella (leggere_casella_percorso ( *partita_attuale, leggere_posizione_giocatore (giocatore_attuale) ), nome_casella);

    //se il giocatore si trova sulla casella locanda, vengono diminuiti i turni di attesa di 1
    if ( confrontare_stringhe (nome_casella, NOME_LOCANDA) == VERO ) {
        scrivere_autorizzazione ( &giocatore_attuale, leggere_autorizzazione (giocatore_attuale) - 1);
        //stampare schermata_locanda_turno_passato e attende input
    }

    //se il giocatore si trova sulla casella prigione,
    else if ( confrontare_stringhe (nome_casella, NOME_PRIGIONE) == VERO ) {
        //stampare schermata_lancio_dadi_prigione e richiedere input
        lanciare_dadi (partita_attuale);
        //stampare schermata_lancio_dadi_prigione con lancio effettuato e richiedere input
        if ( (sommare_dadi (*partita_attuale) == DADO_MINORE_USCITA_PRIGIONE) || (sommare_dadi (*partita_attuale) == DADO_MAGGIORE_USCITA_PRIGIONE) ) {
            scrivere_autorizzazione (&giocatore_attuale, 0);
        }
    }
    scrivere_giocatore ( partita_attuale, giocatore_attuale, leggere_turno (*partita_attuale) );
    return;
}

int confrontare_stringhe (const char stringa_1[], const char stringa_2[]) {
    int indice_stringa = 0;
    int esito = VERO;
    while (stringa_1 [indice_stringa] != FINE_STRINGA && esito == VERO) {
        if (stringa_1 [indice_stringa] != stringa_2 [indice_stringa]) {
            esito = FALSO;
        }
        indice_stringa = indice_stringa + 1;
    }
    return esito;
}
