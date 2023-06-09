#include "inizializzare_partita.h"
#include "partita.h"
#include "giocatore.h"
#include "vincitore.h"
#include "costanti.h"
#include "casella.h"
#include <stdlib.h>
#include <stdio.h>
#include "gestire_stampa.h"


partita *inizializzare_giocatori (partita *partita_attuale) {
    richiedere_numero_caselle(partita_attuale);
    inizializzare_numero_giocatori(partita_attuale);
    inizializzare_nomi_giocatori(partita_attuale);
    inizializzare_pedine_giocatori(partita_attuale);
    return partita_attuale;
}

void richiedere_numero_caselle(partita *partita_attuale) {
    int dimensione_percorso;
    stampare_testo(FILE_SCELTA_LUNG_PERCO);
    do {


        int correttezza_inserimento;
        do {
            posizionare_cursore_in_attesa(FILE_SCELTA_LUNG_PERCO);
            correttezza_inserimento = scanf("%d", &dimensione_percorso);
            fflush(stdin);
            if (correttezza_inserimento == 0) {
                printf("%s","Attenzione: input non valido.\n");
            }
        } while (correttezza_inserimento == 0);


        if ((dimensione_percorso < DIMENSIONE_MINIMA_PERCORSO) || (dimensione_percorso > DIMENSIONE_MASSIMA_PERCORSO)) {
            stampare_messaggio_errore(FILE_SCELTA_LUNG_PERCO);
        }


    } while ((dimensione_percorso < DIMENSIONE_MINIMA_PERCORSO) || (dimensione_percorso > DIMENSIONE_MASSIMA_PERCORSO));
    scrivere_lunghezza_percorso(partita_attuale, dimensione_percorso);
    return;
}



void inizializzare_numero_giocatori (partita *partita_attuale) {
    int numero_partecipanti;
    stampare_testo(FILE_SCELTA_N_GIOCATORI);
    do {


        int correttezza_inserimento;
        do {
            posizionare_cursore_in_attesa(FILE_SCELTA_N_GIOCATORI);
            correttezza_inserimento = scanf("%d", &numero_partecipanti);
            fflush(stdin);
            if (correttezza_inserimento == 0) {
                printf("%s","Attenzione: input non valido.\n");
            }
        } while (correttezza_inserimento == 0);


        if ((numero_partecipanti < NUMERO_MINIMO_GIOCATORI) || (numero_partecipanti > NUMERO_MASSIMO_GIOCATORI)) {
            stampare_messaggio_errore(FILE_SCELTA_N_GIOCATORI);
        }
    } while ((numero_partecipanti < NUMERO_MINIMO_GIOCATORI) || (numero_partecipanti > NUMERO_MASSIMO_GIOCATORI));
    scrivere_numero_giocatori(partita_attuale, numero_partecipanti);
    return;
}

void inizializzare_nomi_giocatori(partita *partita_attuale) {
    int indice_giocatori = 0;
    giocatore giocatore_attuale;
    char nome_da_inserire[DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    while (indice_giocatori <= leggere_numero_giocatori(*partita_attuale)) {
        //stampare richiesta
        inserire_stringa(DIMENSIONE_MINIMA_NOME_GIOCATORE, DIMENSIONE_MASSIMA_NOME_GIOCATORE, nome_da_inserire);
        giocatore_attuale = leggere_giocatore(*partita_attuale, indice_giocatori);
        scrivere_nome_giocatore(&giocatore_attuale, nome_da_inserire);
        scrivere_giocatore(partita_attuale, giocatore_attuale, indice_giocatori);
        indice_giocatori = indice_giocatori + 1;
    }
    return;
}

void inserire_stringa(int dimensione_minima_stringa, int dimensione_massima_stringa, char nome_da_inserire[]) {
    int indice_stringa = 0;
    int terminato = 0;
    while ((indice_stringa < dimensione_massima_stringa) && (terminato == FALSO) &&
           (indice_stringa < dimensione_minima_stringa)) {
        char carattere;
        scanf("%c", &carattere);
        if (carattere != CARATTERE_A_CAPO) {
            nome_da_inserire[indice_stringa] = carattere;
            indice_stringa = indice_stringa + 1;
        } else if (indice_stringa <= dimensione_minima_stringa) {
            //stampare messaggio errore minimo caratteri richiesti
        } else {
            terminato = VERO;
        }
    }
    nome_da_inserire[indice_stringa] = FINE_STRINGA;
    return;
}

void inizializzare_pedine_giocatori(partita *partita_attuale) {
    int indice_pedine = 0;
    giocatore giocatore_attuale;
    do {
        giocatore_attuale = leggere_giocatore(*partita_attuale, indice_pedine);
        scrivere_pedina_giocatore(&giocatore_attuale, PEDINE_DISPONIBILI[indice_pedine]);
        scrivere_giocatore(partita_attuale, giocatore_attuale, indice_pedine);
        indice_pedine = indice_pedine + 1;
    } while (indice_pedine <= leggere_numero_giocatori(*partita_attuale));
    return;
}

