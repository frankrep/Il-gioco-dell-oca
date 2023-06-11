/*
 * gestire_partita.c
 *
 */

#include <stdio.h>
#include "casella.h"
#include "giocatore.h"
#include "partita.h"
#include "vincitore.h"
#include "costanti.h"
#include "gestire_partita.h"
#include "generare_numero_casuale.h"
#include "generare_percorso.h"
#include "gestire_stampa.h"
#include "stampare_percorso.h"


void scegliere_giocatore(partita* partita_attuale);
vincitore inizializzare_vincitore(partita* partita_attuale);
int trovare_posizione_massimo(const int valori[], int dimensione_valori);
void cambiare_turno(partita* partita_attuale);
void lanciare_dadi(partita* partita_attuale);
void incrementare_lanci_effettuati(partita* partita_attuale);
void spostare_giocatore(partita* partita_attuale);
void sommare_lancio_posizione(partita* partita_attuale);
void calcolare_caselle_eccesso(partita* partita_attuale);
int sommare_dadi (partita partita_attuale);
void verificare_casella(partita* partita_attuale);
void gestire_oca(partita* partita_attuale);
void impostare_autorizzazioni(partita* partita_attuale, const char nome_casella_attuale[]);
void gestire_autorizzazione(partita* partita_attuale);



vincitore gestire_partita (partita* partita_attuale) {
    char scelta;
    if ( leggere_turno (*partita_attuale) == -1 ) {
        scegliere_giocatore (partita_attuale);
    }
    do{
        cambiare_turno (partita_attuale);
        if ( leggere_autorizzazione (leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) ) ) > 0) {
            gestire_autorizzazione(partita_attuale);
        }
        if ( leggere_autorizzazione (leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) ) ) == 0 ) {
            cancellare_schermata();
            stampare_interfaccia_percorso(partita_attuale, FILE_PERCORSO);
            do{
                posizionare_cursore_in_attesa (FILE_PERCORSO);
                fflush(stdin);
                scelta = fgetc(stdin);
                if((scelta != TASTO_LANCIO_DADI_MAIUSCOLO) && (scelta != TASTO_LANCIO_DADI_MINUSCOLO) && (scelta != TASTO_AVANZAMENTO_MAIUSCOLO) && (scelta != TASTO_AVANZAMENTO_MINUSCOLO) && (scelta != TASTO_MENU_MAIUSCOLO) && (scelta != TASTO_MENU_MINUSCOLO) && (scelta != TASTO_SALVATAGGIO_MAIUSCOLO) && (scelta != TASTO_SALVATAGGIO_MINUSCOLO) ){
                    stampare_messaggio_errore(FILE_PERCORSO);
                }
            } while ((scelta != TASTO_LANCIO_DADI_MAIUSCOLO) && (scelta != TASTO_LANCIO_DADI_MINUSCOLO) && (scelta != TASTO_AVANZAMENTO_MAIUSCOLO) && (scelta != TASTO_AVANZAMENTO_MINUSCOLO) && (scelta != TASTO_MENU_MAIUSCOLO) && (scelta != TASTO_MENU_MINUSCOLO) && (scelta != TASTO_SALVATAGGIO_MAIUSCOLO) && (scelta != TASTO_SALVATAGGIO_MINUSCOLO));

            if((scelta == TASTO_LANCIO_DADI_MAIUSCOLO) || (scelta == TASTO_LANCIO_DADI_MINUSCOLO)){
                lanciare_dadi (partita_attuale);
                incrementare_lanci_effettuati(partita_attuale);
                stampare_dadi_partita(FILE_PERCORSO, partita_attuale);
                posizionare_cursore_in_attesa(FILE_PERCORSO);
            }
            spostare_giocatore (partita_attuale);
            //stampare percorso con input utente per proseguire con l'effetto
            fgetc(stdin);
            verificare_casella (partita_attuale);
        }
        } while ( leggere_posizione_giocatore (leggere_giocatore (*partita_attuale,leggere_turno (*partita_attuale) ) ) != leggere_lunghezza_percorso (*partita_attuale) );
        cancellare_schermata();
        stampare_testo (FILE_VITTORIA_NOMI);
        char nome_giocatore[DIMENSIONE_MASSIMA_NOME_GIOCATORE];
        leggere_nome_giocatore(leggere_giocatore(*partita_attuale, leggere_turno(*partita_attuale)), nome_giocatore);
        stampare_valore_testuale(FILE_VITTORIA_NOMI, nome_giocatore, 1);
        posizionare_cursore_in_attesa(FILE_SCELTA_G_INIZIALE);
        vincitore vincitore_partita = inizializzare_vincitore (partita_attuale);
        return vincitore_partita;
}



void scegliere_giocatore (partita* partita_attuale) {
    char scelta;
    int estrazioni [NUMERO_MASSIMO_GIOCATORI];
    int indice_giocatori = 0;
    char nome_giocatore [DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    while (indice_giocatori < leggere_numero_giocatori (*partita_attuale) ) {
        cancellare_schermata();
        stampare_testo (FILE_SCELTA_G_INIZIALE);
        leggere_nome_giocatore(leggere_giocatore(*partita_attuale,indice_giocatori),nome_giocatore);
        stampare_valore_testuale(FILE_SCELTA_G_INIZIALE, nome_giocatore, 1);
        do{
            posizionare_cursore_in_attesa (FILE_SCELTA_G_INIZIALE);
            fflush(stdin);
            scelta = fgetc(stdin);
            if((scelta != TASTO_INDIETRO) && (scelta != TASTO_LANCIO_DADI_MAIUSCOLO) && (scelta != TASTO_LANCIO_DADI_MINUSCOLO)){
                stampare_messaggio_errore(FILE_SCELTA_G_INIZIALE);
            }
        } while ((scelta != TASTO_INDIETRO) && (scelta != TASTO_LANCIO_DADI_MAIUSCOLO) && (scelta != TASTO_LANCIO_DADI_MINUSCOLO));

        estrazioni [indice_giocatori] = generare_numero (FACCIA_MASSIMA_DADO, FACCIA_MINIMA_DADO);
        stampare_dado(FILE_SCELTA_G_INIZIALE, estrazioni [indice_giocatori]);
        posizionare_cursore_in_attesa (FILE_SCELTA_G_INIZIALE);
        fflush(stdin);
        fgetc(stdin);
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
    while (indice_valori < dimensione_valori - 1) {
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
        scanf("%d", &lancio);
        //lancio = generare_numero(FACCIA_MASSIMA_DADO, FACCIA_MINIMA_DADO);
        scrivere_dadi (partita_attuale, lancio, indice_dado);
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
    giocatore_attuale = leggere_giocatore (*partita_attuale,leggere_turno (*partita_attuale) );
    int eccesso = leggere_posizione_giocatore (giocatore_attuale ) - leggere_lunghezza_percorso (*partita_attuale);

    scrivere_posizione_giocatore (&giocatore_attuale, leggere_lunghezza_percorso (*partita_attuale) - eccesso);
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
        leggere_nome_casella (leggere_casella_percorso (*partita_attuale, leggere_posizione_giocatore (giocatore_attuale) - 1), nome_casella);
        if (confrontare_stringhe (nome_casella, NOME_OCA) == VERO ) {
            cancellare_schermata();
            stampare_testo(FILE_SCHERMATA_OCA);
            posizionare_cursore_in_attesa(FILE_SCHERMATA_OCA);
            fgetc(stdin);
            gestire_oca (partita_attuale);
        }
        else if(confrontare_stringhe(nome_casella, NOME_PONTE) == VERO ) {
            cancellare_schermata();
            stampare_testo(FILE_SCHERMATA_PONTE);
            posizionare_cursore_in_attesa(FILE_SCHERMATA_PONTE);
            fgetc(stdin);
            spostare_giocatore(partita_attuale);
        }
        else if (confrontare_stringhe(nome_casella, NOME_LOCANDA) == VERO ) {
            cancellare_schermata();
            stampare_testo(FILE_SCHERMATA_LOCANDA);
            posizionare_cursore_in_attesa(FILE_SCHERMATA_LOCANDA);
            fgetc(stdin);
            scrivere_autorizzazione(&giocatore_attuale, TURNI_ATTESA_LOCANDA);
            scrivere_giocatore(partita_attuale, giocatore_attuale, leggere_turno(*partita_attuale));
        }
        else if (confrontare_stringhe(nome_casella, NOME_POZZO) == VERO )
        {
            cancellare_schermata();
            stampare_testo(FILE_SCHERMATA_POZZO);
            posizionare_cursore_in_attesa(FILE_SCHERMATA_POZZO);
            fgetc(stdin);
            impostare_autorizzazioni(partita_attuale, NOME_POZZO);
        }
        else if (confrontare_stringhe(nome_casella, NOME_PRIGIONE) == VERO )
        {
            cancellare_schermata();
            stampare_testo(FILE_SCHERMATA_PRIGIONE);
            posizionare_cursore_in_attesa(FILE_SCHERMATA_PRIGIONE);
            fgetc(stdin);
            impostare_autorizzazioni(partita_attuale, NOME_PRIGIONE);
        }
        else if (confrontare_stringhe(nome_casella, NOME_LABIRINTO) == VERO )
        {
            cancellare_schermata();
            stampare_testo(FILE_SCHERMATA_LABIRINTO);
            posizionare_cursore_in_attesa(FILE_SCHERMATA_LABIRINTO);
            fgetc(stdin);
            scrivere_posizione_giocatore(&giocatore_attuale, calcolare_proporzione(*partita_attuale, CASELLA_ARRIVO_LABIRINTO));
            leggere_nome_casella(leggere_casella_percorso(*partita_attuale, leggere_posizione_giocatore(giocatore_attuale) - 1), nome_casella);
            while (confrontare_stringhe(nome_casella, STRINGA_VUOTA) == FALSO ){
            	leggere_nome_casella(leggere_casella_percorso(*partita_attuale, leggere_posizione_giocatore(giocatore_attuale) - 1), nome_casella);
            	scrivere_posizione_giocatore(&giocatore_attuale, leggere_posizione_giocatore(giocatore_attuale) - 1);
            }
            scrivere_giocatore(partita_attuale, giocatore_attuale, leggere_turno(*partita_attuale));
        }
        else if (confrontare_stringhe(nome_casella, NOME_SCHELETRO) == VERO )
        {
            cancellare_schermata();
            stampare_testo(FILE_SCHERMATA_SCHELETRO);
            posizionare_cursore_in_attesa(FILE_SCHERMATA_SCHELETRO);
            fgetc(stdin);
            scrivere_posizione_giocatore(&giocatore_attuale, CASELLA_ARRIVO_SCHELETRO);
            scrivere_giocatore(partita_attuale, giocatore_attuale, leggere_turno(*partita_attuale));
        }
              //stampare percorso e aspettare input
        giocatore_attuale = leggere_giocatore (*partita_attuale, leggere_turno(*partita_attuale) );
        leggere_nome_casella(leggere_casella_percorso(*partita_attuale, leggere_posizione_giocatore(giocatore_attuale) - 1), nome_casella);
    }while((nome_casella[0] != FINE_STRINGA) && (leggere_autorizzazione(giocatore_attuale) == 0) && (leggere_posizione_giocatore(giocatore_attuale) != leggere_lunghezza_percorso(*partita_attuale)));
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
        leggere_nome_casella (leggere_casella_percorso (*partita_attuale, leggere_posizione_giocatore (giocatore_attuale) - 1), nome_casella);
        while (nome_casella[0] != FINE_STRINGA)
        {
        	leggere_nome_casella(leggere_casella_percorso(*partita_attuale, leggere_posizione_giocatore(giocatore_attuale) - 1), nome_casella);
            scrivere_posizione_giocatore(&giocatore_attuale, leggere_posizione_giocatore(giocatore_attuale) - 1);
        }
        scrivere_giocatore(partita_attuale, giocatore_attuale, leggere_turno(*partita_attuale));
    }
    else {
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
        leggere_nome_casella(leggere_casella_percorso(*partita_attuale, leggere_posizione_giocatore(giocatore_attuale) - 1), nome_casella);
        if (confrontare_stringhe (nome_casella, nome_casella_attuale) == VERO){
            //stampare schermata_liberato e attendere input
            scrivere_autorizzazione(&giocatore_attuale, 0);
            scrivere_giocatore(partita_attuale, giocatore_attuale, indice_giocatore);
        }
        indice_giocatore = indice_giocatore + 1;
    }
    giocatore_attuale = leggere_giocatore(*partita_attuale, leggere_turno(*partita_attuale));
    scrivere_autorizzazione(&giocatore_attuale, 1);
    scrivere_giocatore(partita_attuale, giocatore_attuale, leggere_turno(*partita_attuale));
    return;
}

void gestire_autorizzazione (partita* partita_attuale) {
    giocatore giocatore_attuale = leggere_giocatore ( *partita_attuale, leggere_turno (*partita_attuale) );
    char nome_casella [DIMENSIONE_MASSIMA_NOME_CASELLA];
    leggere_nome_casella (leggere_casella_percorso ( *partita_attuale, leggere_posizione_giocatore (giocatore_attuale) - 1), nome_casella);

    //se il giocatore si trova sulla casella locanda, vengono diminuiti i turni di attesa di 1
    if ( confrontare_stringhe (nome_casella, NOME_LOCANDA) == VERO ) {
        //stampare schermata_locanda_turno_passato e attende input
        cancellare_schermata();
        stampare_testo(FILE_SCHERMATA_LOCANDA_TURNO_PASSATO);
        stampare_valore_intero(FILE_SCHERMATA_LOCANDA_TURNO_PASSATO, leggere_autorizzazione(giocatore_attuale), 1);
        posizionare_cursore_in_attesa(FILE_SCHERMATA_LOCANDA_TURNO_PASSATO);
        fgetc(stdin);
        scrivere_autorizzazione ( &giocatore_attuale, leggere_autorizzazione (giocatore_attuale) - 1);
    }

    //se il giocatore si trova sulla casella prigione,
    else if ( confrontare_stringhe (nome_casella, NOME_PRIGIONE) == VERO ) {
        //stampare schermata_lancio_dadi_prigione e richiedere input
        cancellare_schermata();
        stampare_testo(FILE_SCHERMATA_LANCIO_DADI_PRIGIONE);
        posizionare_cursore_in_attesa(FILE_SCHERMATA_LANCIO_DADI_PRIGIONE);
        fgetc(stdin);
        lanciare_dadi (partita_attuale);
        fgetc(stdin);
        //stampare schermata_lancio_dadi_prigione con lancio effettuato e richiedere input
        stampare_dadi_partita(FILE_SCHERMATA_LANCIO_DADI_PRIGIONE, partita_attuale);
        fgetc(stdin);
        if ( (sommare_dadi (*partita_attuale) == DADO_MINORE_USCITA_PRIGIONE) || (sommare_dadi (*partita_attuale) == DADO_MAGGIORE_USCITA_PRIGIONE) ) {
            cancellare_schermata();
            stampare_testo(FILE_SCHERMATA_LIBERATO);
            posizionare_cursore_in_attesa(FILE_SCHERMATA_LIBERATO);
            fgetc(stdin);
            scrivere_autorizzazione (&giocatore_attuale, 0);
        }
    }else if ( confrontare_stringhe (nome_casella, NOME_POZZO) == VERO ){
        cancellare_schermata();
        stampare_testo(FILE_SCHERMATA_POZZO);
        posizionare_cursore_in_attesa(FILE_SCHERMATA_POZZO);
        fgetc(stdin);
    }
    scrivere_giocatore ( partita_attuale, giocatore_attuale, leggere_turno (*partita_attuale) );
    return;
}

int confrontare_stringhe (const char stringa_1[], const char stringa_2[]) {
    int indice_stringa = 0;
    int esito = VERO;
        while ((stringa_1 [indice_stringa] != FINE_STRINGA) && (esito == VERO)) {
            if (stringa_1 [indice_stringa] != stringa_2 [indice_stringa]) {
                esito = FALSO;
            }
            indice_stringa = indice_stringa + 1;
        }

    return esito;
}
