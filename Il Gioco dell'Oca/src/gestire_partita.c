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
#include "salvare_caricare_partita.h"
#include "aiuto.h"
#include "classifica.h"


void scegliere_giocatore (partita* partita_attuale, int * sale);
vincitore inizializzare_vincitore (partita* partita_attuale, int * sale);
int trovare_posizione_massimo(const int valori[], int dimensione_valori);
void cambiare_turno(partita* partita_attuale);
void lanciare_dadi(partita* partita_attuale, int sale);
void incrementare_lanci_effettuati(partita* partita_attuale);
void spostare_giocatore(partita* partita_attuale);
void sommare_lancio_posizione(partita* partita_attuale);
void calcolare_caselle_eccesso(partita* partita_attuale);
int sommare_dadi (partita partita_attuale);
void verificare_casella (partita* partita_attuale, int * sale);
void gestire_oca(partita* partita_attuale);
void impostare_autorizzazioni(partita* partita_attuale, const char nome_casella_attuale[]);
void gestire_autorizzazione (partita* partita_attuale, int * sale);
int scegliere_opzione_menu_di_pausa (int * sale);
int gestire_menu_di_pausa (partita* partita_attuale, int * sale);
void azzerare_vincitore(vincitore* vincitore_attuale);



vincitore gestire_partita (partita* partita_attuale, int * sale) {
    int indietro;
    char scelta;
    if ( leggere_turno (*partita_attuale) == -2 ) {
        scegliere_giocatore (partita_attuale, sale);
    }
    do{
        cambiare_turno (partita_attuale);
        if ( leggere_autorizzazione (leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) ) ) > 0) {
            gestire_autorizzazione(partita_attuale, sale);
        }
        if ( leggere_autorizzazione (leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) ) ) == 0 ) {
            cancellare_schermata();
            stampare_interfaccia_percorso(partita_attuale, FILE_PERCORSO);

            do {
                stampare_messaggio_valore(FILE_PERCORSO, 2);
                do {
                    posizionare_cursore_in_attesa(FILE_PERCORSO);
                    fflush(stdin);
                    scelta = fgetc(stdin);
                    *sale = *sale + 1;
                    if ((scelta != TASTO_LANCIO_DADI_MAIUSCOLO) && (scelta != TASTO_LANCIO_DADI_MINUSCOLO) && (scelta != TASTO_MENU_MAIUSCOLO) && (scelta != TASTO_MENU_MINUSCOLO)) {
                        stampare_messaggio_errore(FILE_PERCORSO);
                    }
                } while ((scelta != TASTO_LANCIO_DADI_MAIUSCOLO) && (scelta != TASTO_LANCIO_DADI_MINUSCOLO) && (scelta != TASTO_MENU_MAIUSCOLO) && (scelta != TASTO_MENU_MINUSCOLO));

                if ((scelta == TASTO_LANCIO_DADI_MAIUSCOLO) || (scelta == TASTO_LANCIO_DADI_MINUSCOLO)) {
                    lanciare_dadi(partita_attuale, *sale);
                    incrementare_lanci_effettuati(partita_attuale);
                    stampare_dadi_partita(FILE_PERCORSO, partita_attuale);

                    do {
                        //inserire scritta per l'inserimento di A per avanzare
                        stampare_messaggio_valore(FILE_PERCORSO, 3);
                        do {
                            posizionare_cursore_in_attesa(FILE_PERCORSO);
                            scanf("%c", &scelta);
                            fflush(stdin);
                            *sale = *sale + 1;
                            if ((scelta != TASTO_AVANZAMENTO_MAIUSCOLO) && (scelta != TASTO_AVANZAMENTO_MINUSCOLO) && (scelta != TASTO_MENU_MAIUSCOLO) && (scelta != TASTO_MENU_MINUSCOLO)) {
                                stampare_messaggio_errore(FILE_PERCORSO);
                            }
                        } while ((scelta != TASTO_AVANZAMENTO_MAIUSCOLO) && (scelta != TASTO_AVANZAMENTO_MINUSCOLO) && (scelta != TASTO_MENU_MAIUSCOLO) && (scelta != TASTO_MENU_MINUSCOLO));

                        if ((scelta == TASTO_AVANZAMENTO_MAIUSCOLO) || (scelta == TASTO_AVANZAMENTO_MINUSCOLO)) {
                            spostare_giocatore(partita_attuale);
                            //stampare percorso con input utente per proseguire con l'effetto
                            cancellare_schermata();
                            stampare_interfaccia_percorso(partita_attuale, FILE_PERCORSO);
                            posizionare_cursore_in_attesa(FILE_PERCORSO);
                            fgetc(stdin);
                            fflush(stdin);
                            *sale = *sale + 1;
                            verificare_casella(partita_attuale, sale);


                            stampare_interfaccia_percorso(partita_attuale, FILE_PERCORSO);
                            posizionare_cursore_in_attesa(FILE_PERCORSO);
                            //inserire il messaggio per dire di premere un tasto per concludere il turno
                        }
                        else {
                            indietro = gestire_menu_di_pausa(partita_attuale, sale);
                            stampare_interfaccia_percorso(partita_attuale, FILE_PERCORSO);
                        }
                    } while (indietro == 1);
                }
                else {
                    indietro = gestire_menu_di_pausa(partita_attuale, sale);
                    stampare_interfaccia_percorso(partita_attuale, FILE_PERCORSO);
                    //stampare menu
                }
            } while (indietro == 1);

        }

    } while ( leggere_posizione_giocatore (leggere_giocatore (*partita_attuale,leggere_turno (*partita_attuale) ) ) != leggere_lunghezza_percorso (*partita_attuale)  && (indietro != 0));
    vincitore vincitore_partita;
    if(leggere_posizione_giocatore (leggere_giocatore (*partita_attuale,leggere_turno (*partita_attuale) ) ) == leggere_lunghezza_percorso (*partita_attuale)) {
        vincitore_partita = inizializzare_vincitore (partita_attuale, sale);
        aggiornare_classifica_top_10(vincitore_partita);
    }
    else {
        azzerare_vincitore(&vincitore_partita);
    }
    return vincitore_partita;
}



int gestire_menu_di_pausa (partita* partita_attuale, int * sale) {
    char uscita;
    int scelta;
    do {
        scelta = scegliere_opzione_menu_di_pausa(sale);
        if (scelta == 2) {
            salvare_partita (partita_attuale, sale);
        } else {
            if (scelta == 3) {
                chiedere_aiuto(sale);
            } else {
                if (scelta == 0) {
                    stampare_testo(FILE_RICHIESTA_USCITA);

                    do {
                        posizionare_cursore_in_attesa(FILE_RICHIESTA_USCITA);
                        scanf("%c", &uscita);
                        if (uscita != RISPOSTA_NEGATIVA_MINUSCOLO && uscita != RISPOSTA_NEGATIVA_MAIUSCOLO && uscita != RISPOSTA_AFFERMATIVA_MAIUSCOLO && uscita != RISPOSTA_AFFERMATIVA_MINUSCOLO) {
                            stampare_messaggio_errore(FILE_RICHIESTA_USCITA);
                        }
                    } while (uscita != RISPOSTA_NEGATIVA_MINUSCOLO && uscita != RISPOSTA_NEGATIVA_MAIUSCOLO && uscita != RISPOSTA_AFFERMATIVA_MAIUSCOLO && uscita != RISPOSTA_AFFERMATIVA_MINUSCOLO);

                }
            }
        }
    } while (scelta != 1 && (uscita != RISPOSTA_AFFERMATIVA_MAIUSCOLO && uscita != RISPOSTA_AFFERMATIVA_MINUSCOLO) );
    cancellare_schermata();
    return scelta;
}



int scegliere_opzione_menu_di_pausa (int * sale) {
    int scelta;
    cancellare_schermata();
    stampare_testo(FILE_MENU_DI_PAUSA);

    do {


        //modificare messaggio per coerenza con quello a cui risponde
        int correttezza_inserimento;
        do {
            posizionare_cursore_in_attesa(FILE_MENU_DI_PAUSA);
            correttezza_inserimento = scanf("%d", &scelta);
            fflush(stdin);
            *sale = *sale + 1;
            if (correttezza_inserimento == 0) {
                stampare_messaggio_errore(FILE_MENU_DI_PAUSA);
            }
        } while (correttezza_inserimento == 0);


        //modificare messaggio per coerenza con quello a cui risponde
        if ( scelta < 0 || scelta > NUMERO_MASSIMO_OPZIONE_PAUSA ) {
            stampare_messaggio_errore(FILE_MENU_DI_PAUSA);
        }


    } while (scelta < 0 || scelta > NUMERO_MASSIMO_OPZIONE_PAUSA );
    cancellare_schermata();
    return scelta;
}



void scegliere_giocatore (partita* partita_attuale, int * sale) {
    char scelta;
    int estrazioni [NUMERO_MASSIMO_GIOCATORI];
    int indice_giocatori = 0;
    char nome_giocatore [DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    while (indice_giocatori < leggere_numero_giocatori (*partita_attuale) ) {
        cancellare_schermata();
        stampare_testo (FILE_SCELTA_G_INIZIALE);
        leggere_nome_giocatore(leggere_giocatore(*partita_attuale,indice_giocatori),nome_giocatore);
        stampare_valore_testuale_centrato(FILE_SCELTA_G_INIZIALE, nome_giocatore, 1, DIMENSIONE_MASSIMA_NOME_GIOCATORE);
        do{
            posizionare_cursore_in_attesa (FILE_SCELTA_G_INIZIALE);
            fflush(stdin);
            scelta = fgetc(stdin);
            fflush(stdin);
            *sale = *sale + 1;
            if((scelta != TASTO_INDIETRO) && (scelta != TASTO_LANCIO_DADI_MAIUSCOLO) && (scelta != TASTO_LANCIO_DADI_MINUSCOLO)){
                stampare_messaggio_errore(FILE_SCELTA_G_INIZIALE);
            }
        } while ((scelta != TASTO_INDIETRO) && (scelta != TASTO_LANCIO_DADI_MAIUSCOLO) && (scelta != TASTO_LANCIO_DADI_MINUSCOLO));

        estrazioni [indice_giocatori] = generare_numero (FACCIA_MASSIMA_DADO, FACCIA_MINIMA_DADO, *sale);
        stampare_dado(FILE_SCELTA_G_INIZIALE, estrazioni [indice_giocatori]);
        posizionare_cursore_in_attesa (FILE_SCELTA_G_INIZIALE);
        fflush(stdin);
        fgetc(stdin);
        *sale = *sale + 1;
        indice_giocatori = indice_giocatori + 1;
    }
    scrivere_turno (partita_attuale, trovare_posizione_massimo (estrazioni, leggere_numero_giocatori (*partita_attuale) ) - 1);
    return;
}



vincitore inizializzare_vincitore (partita* partita_attuale, int * sale) {
    vincitore vincitore_partita;
    char nome_vincitore[DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    leggere_nome_giocatore(leggere_giocatore(*partita_attuale, leggere_turno(*partita_attuale)), nome_vincitore);
    scrivere_nome_vincitore(&vincitore_partita, nome_vincitore);
    scrivere_pedina_vincitore(&vincitore_partita, leggere_pedina_giocatore(leggere_giocatore(*partita_attuale, leggere_turno(*partita_attuale))));
    scrivere_lanci_vincitore(&vincitore_partita, leggere_lanci_effettuati(leggere_giocatore(*partita_attuale, leggere_turno(*partita_attuale))));
    scrivere_lunghezza_percorso_vincitore(&vincitore_partita, leggere_lunghezza_percorso(*partita_attuale));

    cancellare_schermata();
    stampare_vittoria(FILE_VITTORIA_NOMI);
    char nome_giocatore[DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    leggere_nome_giocatore(leggere_giocatore(*partita_attuale, leggere_turno(*partita_attuale)), nome_giocatore);
    cambiare_colore_testo(COLORI_GIOCATORI[leggere_turno(*partita_attuale)]);
    stampare_valore_testuale_centrato(FILE_VITTORIA_NOMI, nome_vincitore, 1, DIMENSIONE_MASSIMA_NOME_GIOCATORE);
    cambiare_colore_testo(COLORE_PRINCIPALE_SCHERMATA);
    posizionare_cursore_in_attesa(FILE_VITTORIA_NOMI);
    fgetc(stdin);

    cancellare_schermata();
    stampare_vittoria(FILE_DETTAGLI_PARTITA);
    stampare_valore_testuale(FILE_DETTAGLI_PARTITA, nome_vincitore, 1);
    stampare_valore_intero(FILE_DETTAGLI_PARTITA, leggere_lunghezza_percorso_vincitore(vincitore_partita), 2);
    stampare_valore_intero(FILE_DETTAGLI_PARTITA, leggere_lanci_vincitore(vincitore_partita), 3);
    stampare_valore_intero(FILE_DETTAGLI_PARTITA, leggere_punteggio(vincitore_partita), 4);
    //stampare_valore_intero(FILE_DETTAGLI_PARTITA, posizione_vincitore_classifica, 5);
    posizionare_cursore_in_attesa(FILE_DETTAGLI_PARTITA);
    fgetc(stdin);
    *sale = *sale + 1;
    //funzione per il campo punteggio
    return vincitore_partita;
}



void azzerare_vincitore (vincitore* vincitore_attuale) {
    scrivere_carattere_nome_vincitore(vincitore_attuale, 0, FINE_STRINGA);
    scrivere_pedina_vincitore(vincitore_attuale, 0);
    scrivere_lanci_vincitore(vincitore_attuale, 0);
    scrivere_lunghezza_percorso_vincitore(vincitore_attuale, 0);
    scrivere_punteggio(vincitore_attuale, 0.0);
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



void lanciare_dadi (partita* partita_attuale, int sale) {
    int indice_dado = 0;
    int lancio;
    while (indice_dado < NUMERO_DADI) {
        scanf("%d", &lancio);
        //lancio = generare_numero(FACCIA_MASSIMA_DADO, FACCIA_MINIMA_DADO, sale);
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



void verificare_casella (partita* partita_attuale, int * sale) {
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
            fflush(stdin);
            *sale = *sale + 1;
            gestire_oca (partita_attuale);
        }
        else if(confrontare_stringhe(nome_casella, NOME_PONTE) == VERO ) {
            cancellare_schermata();
            stampare_testo(FILE_SCHERMATA_PONTE);
            posizionare_cursore_in_attesa(FILE_SCHERMATA_PONTE);
            fgetc(stdin);
            fflush(stdin);
            *sale = *sale + 1;
            spostare_giocatore(partita_attuale);
        }
        else if (confrontare_stringhe(nome_casella, NOME_LOCANDA) == VERO ) {
            cancellare_schermata();
            stampare_testo(FILE_SCHERMATA_LOCANDA);
            posizionare_cursore_in_attesa(FILE_SCHERMATA_LOCANDA);
            fgetc(stdin);
            fflush(stdin);
            *sale = *sale + 1;
            scrivere_autorizzazione(&giocatore_attuale, TURNI_ATTESA_LOCANDA);
            scrivere_giocatore(partita_attuale, giocatore_attuale, leggere_turno(*partita_attuale));
        }
        else if (confrontare_stringhe(nome_casella, NOME_POZZO) == VERO )
        {
            cancellare_schermata();
            stampare_testo(FILE_SCHERMATA_POZZO);
            posizionare_cursore_in_attesa(FILE_SCHERMATA_POZZO);
            fgetc(stdin);
            fflush(stdin);
            *sale = *sale + 1;
            impostare_autorizzazioni(partita_attuale, NOME_POZZO);
        }
        else if (confrontare_stringhe(nome_casella, NOME_PRIGIONE) == VERO )
        {
            cancellare_schermata();
            stampare_testo(FILE_SCHERMATA_PRIGIONE);
            posizionare_cursore_in_attesa(FILE_SCHERMATA_PRIGIONE);
            fgetc(stdin);
            fflush(stdin);
            *sale = *sale + 1;
            impostare_autorizzazioni(partita_attuale, NOME_PRIGIONE);
        }
        else if (confrontare_stringhe(nome_casella, NOME_LABIRINTO) == VERO )
        {
            cancellare_schermata();
            stampare_testo(FILE_SCHERMATA_LABIRINTO);
            posizionare_cursore_in_attesa(FILE_SCHERMATA_LABIRINTO);
            fgetc(stdin);
            fflush(stdin);
            *sale = *sale + 1;
            scrivere_posizione_giocatore(&giocatore_attuale, calcolare_proporzione(*partita_attuale, CASELLA_ARRIVO_LABIRINTO));
            leggere_nome_casella(leggere_casella_percorso(*partita_attuale, leggere_posizione_giocatore(giocatore_attuale) - 1), nome_casella);
            while (nome_casella[0] != FINE_STRINGA){
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
            fflush(stdin);
            *sale = *sale + 1;
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
    while ( indice_giocatore < leggere_numero_giocatori (*partita_attuale) ) {
        giocatore_attuale = leggere_giocatore (*partita_attuale, indice_giocatore);
        char nome_casella[DIMENSIONE_MASSIMA_NOME_CASELLA];
        leggere_nome_casella(leggere_casella_percorso (*partita_attuale, leggere_posizione_giocatore (giocatore_attuale) - 1), nome_casella);
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

void gestire_autorizzazione (partita* partita_attuale, int * sale) {
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
        fflush(stdin);
        *sale = *sale + 1;
        scrivere_autorizzazione ( &giocatore_attuale, leggere_autorizzazione (giocatore_attuale) - 1);
    }

    //se il giocatore si trova sulla casella prigione,
    else if ( confrontare_stringhe (nome_casella, NOME_PRIGIONE) == VERO ) {
        //stampare schermata_lancio_dadi_prigione e richiedere input
        cancellare_schermata();
        stampare_testo(FILE_SCHERMATA_LANCIO_DADI_PRIGIONE);
        posizionare_cursore_in_attesa(FILE_SCHERMATA_LANCIO_DADI_PRIGIONE);
        fgetc(stdin);
        fflush(stdin);
        *sale = *sale + 1;
        lanciare_dadi (partita_attuale, *sale);
        fgetc(stdin);
        fflush(stdin);
        *sale = *sale + 1;
        //stampare schermata_lancio_dadi_prigione con lancio effettuato e richiedere input
        stampare_dadi_partita(FILE_SCHERMATA_LANCIO_DADI_PRIGIONE, partita_attuale);
        posizionare_cursore_in_attesa(FILE_SCHERMATA_LANCIO_DADI_PRIGIONE);
        fgetc(stdin);
        fflush(stdin);
        *sale = *sale + 1;
        if ( (sommare_dadi (*partita_attuale) == DADO_MINORE_USCITA_PRIGIONE) || (sommare_dadi (*partita_attuale) == DADO_MAGGIORE_USCITA_PRIGIONE) ) {
            cancellare_schermata();
            stampare_testo(FILE_SCHERMATA_LIBERATO);
            posizionare_cursore_in_attesa(FILE_SCHERMATA_LIBERATO);
            fgetc(stdin);
            fflush(stdin);
            *sale = *sale + 1;
            scrivere_autorizzazione (&giocatore_attuale, 0);
        }
    }else if ( confrontare_stringhe (nome_casella, NOME_POZZO) == VERO ){
        cancellare_schermata();
        stampare_testo(FILE_SCHERMATA_PERM_POZZO);
        posizionare_cursore_in_attesa(FILE_SCHERMATA_PERM_POZZO);
        fgetc(stdin);
        fflush(stdin);
        *sale = *sale + 1;
    }
    scrivere_giocatore ( partita_attuale, giocatore_attuale, leggere_turno (*partita_attuale) );
    return;
}

int confrontare_stringhe (const char stringa_1[], const char stringa_2[]) {
    int indice_stringa = 0;
    int esito = VERO;
        while ((stringa_2 [indice_stringa] != FINE_STRINGA) && (esito == VERO)) {
            if (stringa_2 [indice_stringa] != stringa_1 [indice_stringa]) {
                esito = FALSO;
            }
            indice_stringa = indice_stringa + 1;
        }

    return esito;
}
