#include <stdlib.h>
#include <stdio.h>
#include "partita.h"
#include "generare_percorso.h"
#include "costanti.h"
#include "vincitore.h"
#include "inizializzare_partita.h"
#include "gestire_partita.h"
#include "classifica.h"
#include "aiuto.h"
#include "salvare_caricare_partita.h"
#include "gestire_stampa.h"
#include "stampare_percorso.h"


int scegliere_opzione_menu ();
void iniziare_nuova_partita (vincitore* vincitore_partita);
void riprendere_partita (vincitore* vincitore_partita);
void scegliere_partita_da_caricare (partita* partita_attuale);
void gestire_vincitore (vincitore vincitore_partita);



int main() {
	char uscita;

    //stampa della schermata con il logo e la richiesta di premere un tasto qualsiasi

    stampare_intro(FILE_INTRO);
    posizionare_cursore_in_attesa(FILE_INTRO);
    fgetc(stdin);
    fflush(stdout);

    uscita = RISPOSTA_NEGATIVA_MAIUSCOLO;
    int opzione;
    vincitore vincitore_partita;


    do {
        cancellare_schermata();
        opzione = scegliere_opzione_menu();
        
        if (opzione == 1) {
            iniziare_nuova_partita (&vincitore_partita);
            //inserire fine stringa come nome di vincitore_attuale nel caso in cui si interrompe la partita (stessa cosa per riprendere_partita)
            if (leggere_lunghezza_percorso_vincitore(vincitore_partita) != 0) {
                gestire_vincitore(vincitore_partita);
            }
        }
        else {
            if (opzione == 2) {
                riprendere_partita(&vincitore_partita);
                gestire_vincitore (vincitore_partita);
            }
            else {
                if (opzione == 3) {
                    stampare_classifica ();
                }
                else {
                    if (opzione == 4) {
                        chiedere_aiuto ();
                    }
                    else {
                        confermare_scelta (&uscita);
                    }
                }
            }
        }
    } while (uscita != RISPOSTA_AFFERMATIVA_MAIUSCOLO && uscita != RISPOSTA_AFFERMATIVA_MINUSCOLO);
    return 0;
}



int scegliere_opzione_menu () {
    int opzione;
    int correttezza_inserimento;
    stampare_testo(FILE_MENU_PRINCIPALE);

    do {


        //richiediamo l'opzione e verifichiamo che l'imput immesso sia del tipo consentito
        do {
            posizionare_cursore_in_attesa(FILE_MENU_PRINCIPALE);
            correttezza_inserimento = scanf("%d", &opzione);
            fflush(stdin);
            if (correttezza_inserimento == 0) {
                stampare_messaggio_errore(FILE_MENU_PRINCIPALE);
            }
        } while (correttezza_inserimento == 0);



        //verifichiamo se l'imput immesso sia consentito all'interno dei vincoli
        if ( (opzione < 0) || (opzione > NUMERO_MASSIMO_OPZIONI_PRINCIPALE) ) {
            stampare_messaggio_errore (FILE_MENU_PRINCIPALE);
        }


    } while ( (opzione < 0) || (opzione > NUMERO_MASSIMO_OPZIONI_PRINCIPALE) );

    if (opzione != 0) {
        system("cls");
    }
    return opzione;
}



void iniziare_nuova_partita (vincitore* vincitore_partita) {
    partita partita_attuale;
    inizializzare_giocatori (&partita_attuale);
    if (leggere_lunghezza_percorso (partita_attuale) != 0) {
        generare_percorso(&partita_attuale);
        *vincitore_partita = gestire_partita(&partita_attuale);
    }
    else {
        scrivere_lunghezza_percorso_vincitore(vincitore_partita, 0);
    }
    return;
}



void riprendere_partita (vincitore* vincitore_partita) {
    //VEDERE SCEGLIERE_PARTITA_DA_CARICARE PER INFORMAZIONI
    partita partita_attuale;
    scegliere_partita_da_caricare(&partita_attuale);
    *vincitore_partita = gestire_partita (&partita_attuale);
    return;
}



void scegliere_partita_da_caricare (partita* partita_attuale) {
    partita elenco_partite [NUMERO_MASSIMO_PARTITE];
    stampare_testo(FILE_MENU_CARICA_PARTITA);
    posizionare_cursore_in_attesa(FILE_MENU_CARICA_PARTITA);
    //AGGIUNGERE CONTROLLO CHE SE IL CAMPO DELLA PARTITA SALVATA è VUOTO ALLORA DEVE DARE ERRORE CHE NON ESISTE NESSUNA PARTITA IN QUELLO SLOT.
    caricare_partite (elenco_partite);
    //Stampare le partite salvate dal file dove ci sono le partite salvate su video su FILE_MENU_CARICA_PARTITA
    //AGGIUNGERE CONTROLLO SE SLOT_SCELTO != 1,2,3,4,5 DA ERRORE
    //AGGIUNGERE CONTROLLO SE SLOT_SCELTO = 0 TORNA AL MENU PRINCIPALE
    int slot_scelto = selezionare_slot (elenco_partite);
    *partita_attuale = elenco_partite [slot_scelto];
    return;
}



void gestire_vincitore (vincitore vincitore_partita) {
    char nome_vincitore_partita [DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    leggere_nome_vincitore (vincitore_partita, nome_vincitore_partita);
    if (confrontare_stringhe (nome_vincitore_partita, STRINGA_VUOTA) == FALSO) {
        aggiornare_classifica_top_10 (vincitore_partita);
    }
    return;
}