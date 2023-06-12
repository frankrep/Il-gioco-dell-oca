#include "inizializzare_partita.h"
#include "partita.h"
#include "giocatore.h"
#include "costanti.h"
#include <stdlib.h>
#include <stdio.h>
#include "gestire_stampa.h"
#include "gestire_partita.h"


void richiedere_numero_caselle(partita *partita_attuale, int * sale);
void inizializzare_numero_giocatori (partita *partita_attuale, int * sale);
void inizializzare_nomi_giocatori (partita *partita_attuale, int * sale);
void inizializzare_pedine_giocatori (partita* partita_attuale);
void rimuovere_carattere_nuova_riga (char stringa[]);
void inizializzare_autorizzazione_giocatori(partita *partita_attuale);
void inizializzare_posizione_giocatori(partita *partita_attuale);
void inizializzare_lanci_giocatore(partita *partita_attuale);



void inizializzare_giocatori (partita *partita_attuale, int * sale) {
    int indietro = 0;
    do {
        richiedere_numero_caselle(partita_attuale, sale);
        if (leggere_lunghezza_percorso (*partita_attuale) == 0) {
            indietro = 1;
        }
        else {
            do {
                if (indietro == 1) {
                    indietro = 0;
                }
                inizializzare_numero_giocatori(partita_attuale, sale);
                if (leggere_numero_giocatori(*partita_attuale) == 0) {
                    indietro = 0;
                }
                else {
                    inizializzare_nomi_giocatori(partita_attuale, sale);
                    char nome_giocatore[DIMENSIONE_MASSIMA_NOME_GIOCATORE];
                    leggere_nome_giocatore(leggere_giocatore(*partita_attuale, 0), nome_giocatore);
                    if (confrontare_stringhe(nome_giocatore, NOME_GIOCATORE_INDIETRO) == VERO) {
                        indietro = 1;
                    }
                    else {
                        inizializzare_pedine_giocatori(partita_attuale);
                        inizializzare_autorizzazione_giocatori(partita_attuale);
                        inizializzare_posizione_giocatori(partita_attuale);
                        inizializzare_lanci_giocatore(partita_attuale);
                        scrivere_turno(partita_attuale, -1);
                    }
                }
            } while (indietro != 0);
        }
    } while (indietro != 1 && leggere_numero_giocatori (*partita_attuale) == 0);
    return;
}



void richiedere_numero_caselle(partita *partita_attuale, int * sale) {
    int dimensione_percorso;
    stampare_testo(FILE_SCELTA_LUNG_PERCO);
    do {



        int correttezza_inserimento;
        do {
            posizionare_cursore_in_attesa(FILE_SCELTA_LUNG_PERCO);
            correttezza_inserimento = scanf("%d", &dimensione_percorso);
            fflush(stdin);
            *sale = *sale + 1;
            if (correttezza_inserimento == 0) {
                stampare_messaggio_errore(FILE_SCELTA_LUNG_PERCO);
            }
        } while (correttezza_inserimento == 0);



        if ( ( (dimensione_percorso < DIMENSIONE_MINIMA_PERCORSO) || (dimensione_percorso > DIMENSIONE_MASSIMA_PERCORSO) ) && dimensione_percorso != 0) {
            stampare_messaggio_errore(FILE_SCELTA_LUNG_PERCO);
        }



    } while ( ( (dimensione_percorso < DIMENSIONE_MINIMA_PERCORSO) || (dimensione_percorso > DIMENSIONE_MASSIMA_PERCORSO) ) && dimensione_percorso != 0);
    scrivere_lunghezza_percorso(partita_attuale, dimensione_percorso);
    cancellare_schermata();
    return;
}



void inizializzare_numero_giocatori (partita *partita_attuale, int * sale) {
    int numero_partecipanti;
    stampare_testo(FILE_SCELTA_N_GIOCATORI);
    do {


        int correttezza_inserimento;
        do {
            posizionare_cursore_in_attesa(FILE_SCELTA_N_GIOCATORI);
            correttezza_inserimento = scanf("%d", &numero_partecipanti);
            fflush(stdin);
            *sale = *sale + 1;
            if (correttezza_inserimento == 0) {
                stampare_messaggio_errore(FILE_SCELTA_N_GIOCATORI);
            }
        } while (correttezza_inserimento == 0);


        if ( ( (numero_partecipanti < NUMERO_MINIMO_GIOCATORI) || (numero_partecipanti > NUMERO_MASSIMO_GIOCATORI) ) && numero_partecipanti != 0) {
            stampare_messaggio_errore(FILE_SCELTA_N_GIOCATORI);
        }


    } while ( ( (numero_partecipanti < NUMERO_MINIMO_GIOCATORI) || (numero_partecipanti > NUMERO_MASSIMO_GIOCATORI) ) && numero_partecipanti != 0);
    scrivere_numero_giocatori(partita_attuale, numero_partecipanti);
    cancellare_schermata();
    return;
}



void inizializzare_nomi_giocatori (partita *partita_attuale, int * sale) {
    int indice_giocatori = 0;
    char nome_da_inserire[DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    while (indice_giocatori < leggere_numero_giocatori (*partita_attuale) ) {
        stampare_testo (FILE_SCELTA_NOMI_GIOCATORI);
        stampare_valore_intero(FILE_SCELTA_NOMI_GIOCATORI, indice_giocatori+1, 1);
        posizionare_cursore_in_attesa (FILE_SCELTA_NOMI_GIOCATORI);
        richiedere_stringa (FILE_SCELTA_NOMI_GIOCATORI, DIMENSIONE_MINIMA_NOME_GIOCATORE, DIMENSIONE_MASSIMA_NOME_GIOCATORE, nome_da_inserire, sale);
        if (confrontare_stringhe (nome_da_inserire, NOME_GIOCATORE_INDIETRO) == FALSO) {
            giocatore giocatore_attuale = leggere_giocatore(*partita_attuale, indice_giocatori);
            scrivere_nome_giocatore(&giocatore_attuale, nome_da_inserire);
            scrivere_giocatore(partita_attuale, giocatore_attuale, indice_giocatori);
            indice_giocatori = indice_giocatori + 1;
        }
        else {
            giocatore giocatore_attuale = leggere_giocatore(*partita_attuale, 0);
            scrivere_nome_giocatore(&giocatore_attuale, nome_da_inserire);
            scrivere_giocatore(partita_attuale, giocatore_attuale, 0);
            indice_giocatori = leggere_numero_giocatori (*partita_attuale);
        }
        system("cls");
    }
    return;
}


void richiedere_stringa (const char file_interfaccia[], int dimensione_minima_stringa, int dimensione_massima_stringa, char nome_da_inserire[], int * sale) {
    nome_da_inserire[0] = FINE_STRINGA;
    while (nome_da_inserire[0] == FINE_STRINGA) {
        inserire_stringa (dimensione_minima_stringa, dimensione_massima_stringa, nome_da_inserire, sale);
        if (nome_da_inserire[0] == FINE_STRINGA) {
            stampare_messaggio_errore (file_interfaccia);
            posizionare_cursore_in_attesa (FILE_SCELTA_NOMI_GIOCATORI);
        }
    }
}


void inserire_stringa (int dimensione_minima_stringa, int dimensione_massima_stringa, char nome_da_inserire[], int * sale) {
    fgets (nome_da_inserire, dimensione_massima_stringa + 1, stdin);
    fflush(stdin);
    *sale = *sale + 1;
    rimuovere_carattere_nuova_riga (nome_da_inserire);
    if ((calcolare_lunghezza_stringa (nome_da_inserire) < dimensione_minima_stringa) && (confrontare_stringhe (nome_da_inserire, NOME_GIOCATORE_INDIETRO) == FALSO)) {
        nome_da_inserire[0] = FINE_STRINGA;
    }
    return;
}



void rimuovere_carattere_nuova_riga (char stringa[]) {
    int indice_stringa = 0;
    while (indice_stringa < calcolare_lunghezza_stringa (stringa) ) {
        if (stringa[indice_stringa] == CARATTERE_A_CAPO) {
            stringa[indice_stringa] = FINE_STRINGA;
        }
        indice_stringa = indice_stringa + 1;
    }
    return;
}



int calcolare_lunghezza_stringa (const char stringa[]) {
    int lunghezza_stringa = 0;
    while (stringa[lunghezza_stringa] != FINE_STRINGA) {
        lunghezza_stringa = lunghezza_stringa + 1;
    }
    return lunghezza_stringa;
}



void inizializzare_pedine_giocatori(partita *partita_attuale) {
    int indice_pedine = 0;
    giocatore giocatore_attuale;
    do {
        giocatore_attuale = leggere_giocatore (*partita_attuale, indice_pedine);
        scrivere_pedina_giocatore (&giocatore_attuale, PEDINE_DISPONIBILI[indice_pedine]);
        scrivere_giocatore (partita_attuale, giocatore_attuale, indice_pedine);
        indice_pedine = indice_pedine + 1;
    } while (indice_pedine < leggere_numero_giocatori (*partita_attuale) );
    while (indice_pedine < NUMERO_MASSIMO_GIOCATORI){
        scrivere_pedina_giocatore (&giocatore_attuale, FINE_STRINGA);
        scrivere_giocatore (partita_attuale, giocatore_attuale, indice_pedine);
        indice_pedine = indice_pedine + 1;
    }
    return;
}

void inizializzare_autorizzazione_giocatori(partita *partita_attuale) {
    int indice_giocatori = 0;
    giocatore giocatore_attuale;
    do {
        giocatore_attuale = leggere_giocatore (*partita_attuale, indice_giocatori);
        scrivere_autorizzazione(&giocatore_attuale, 0);
        scrivere_giocatore (partita_attuale, giocatore_attuale, indice_giocatori);
        indice_giocatori = indice_giocatori + 1;
    } while (indice_giocatori < leggere_numero_giocatori (*partita_attuale) );
    return;
}

void inizializzare_posizione_giocatori(partita *partita_attuale) {
    int indice_giocatori = 0;
    giocatore giocatore_attuale;
    do {
        giocatore_attuale = leggere_giocatore (*partita_attuale, indice_giocatori);
        scrivere_posizione_giocatore(&giocatore_attuale, 0);
        scrivere_giocatore (partita_attuale, giocatore_attuale, indice_giocatori);
        indice_giocatori = indice_giocatori + 1;
    } while (indice_giocatori < leggere_numero_giocatori (*partita_attuale) );
    return;
}

void inizializzare_lanci_giocatore(partita *partita_attuale) {
    int indice_giocatori = 0;
    giocatore giocatore_attuale;
    do {
        giocatore_attuale = leggere_giocatore (*partita_attuale, indice_giocatori);
        scrivere_lanci_effettuati(&giocatore_attuale, 0);
        scrivere_giocatore (partita_attuale, giocatore_attuale, indice_giocatori);
        indice_giocatori = indice_giocatori + 1;
    } while (indice_giocatori < leggere_numero_giocatori (*partita_attuale) );
    return;
}