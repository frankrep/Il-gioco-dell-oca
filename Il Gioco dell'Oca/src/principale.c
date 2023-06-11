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
void iniziare_nuova_partita (vincitore* vincitore_partita, int * indietro);
void riprendere_partita (vincitore* vincitore_partita);
void scegliere_partita_da_caricare (partita* partita_attuale);
void gestire_vincitore (vincitore vincitore_partita);



int main() {
	char uscita;

    //stampa della schermata con il logo e la richiesta di premere un tasto qualsiasi

    stampare_testo(FILE_INTRO);
    posizionare_cursore_in_attesa(FILE_INTRO);
    fgetc(stdin);
    fflush(stdout);

    uscita = RISPOSTA_NEGATIVA_MAIUSCOLO;
    int opzione;
    vincitore vincitore_partita;

    int indietro;

    do {
        indietro = 0;
        system("cls");
        opzione = scegliere_opzione_menu();

        if (opzione == 1) {
            iniziare_nuova_partita (&vincitore_partita, &indietro);
            //inserire fine stringa come nome di vincitore_attuale nel caso in cui si interrompe la partita (stessa cosa per riprendere_partita)
            if (indietro == 0) {
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
                        chiedere_aiuto (opzione);
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

//se premo indietro:
        //se la funzione è stata chiamata, deve tornare alla funzione chiamante
                //la funzione chiamante intera si troverà in un do while con la condizione che il tasto indietro sia uguale a 1 e che come prima istruzione del do, a questo venga assegnato 0
                //le funzioni che seguono quella chiamante, all'interno dello stesso ramo, avranno come condizione che il tasto indietro sia uguale a 0
                //le funzioni che seguono quella chiamata avranno come condizione che indietro sia uguale a 0
        //altrimenti, se è parte e non la prima di un blocco, bisogna eseguire la funzione precedente
                //la funzione precedente si troverà in un ciclo do while con condizione che il tasto indietro sia uguale a 0
                //le funzioni che seguono quella di un blocco avranno come condizione che indietro sia uguale a 0



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



void iniziare_nuova_partita (vincitore* vincitore_partita, int * indietro) {
    partita partita_attuale;
    inizializzare_giocatori (&partita_attuale, indietro);
    if (indietro == 0) {
        generare_percorso(&partita_attuale);
        *vincitore_partita = gestire_partita(&partita_attuale);
    }
    return;
}



void riprendere_partita (vincitore* vincitore_partita) {
    partita partita_attuale;
    scegliere_partita_da_caricare(&partita_attuale);
    *vincitore_partita = gestire_partita (&partita_attuale);
    return;
}



void scegliere_partita_da_caricare (partita* partita_attuale) {
    partita elenco_partite [NUMERO_MASSIMO_PARTITE];
    caricare_partite (elenco_partite);
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