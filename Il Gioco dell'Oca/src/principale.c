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



int scegliere_opzione_menu ();
void iniziare_nuova_partita (vincitore* vincitore_partita);
void riprendere_partita (vincitore* vincitore_partita);
void scegliere_partita_da_caricare (partita* partita_attuale);
void gestire_vincitore (vincitore vincitore_partita);



int main(void) {
	char uscita;

    //stampa della schermata con il logo e la richiesta di premere un tasto qualsiasi
    stampare_testo(FILE_INTRO);
    fgetc(stdin);
    fflush(stdin);

    uscita = RISPOSTA_NEGATIVA_MAIUSCOLO;
    int opzione;
    vincitore vincitore_partita;

    do {
        opzione = scegliere_opzione_menu();
        if (opzione == 1) {
            iniziare_nuova_partita (&vincitore_partita);
            //inserire fine stringa come nome di vincitore_attuale nel caso in cui si interrompe la partita (stessa cosa per riprendere_partita)

            gestire_vincitore (vincitore_partita);
        }
        else {
            if (opzione == 2) {
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
    system("pause");
    return EXIT_SUCCESS;
}



int scegliere_opzione_menu () {
    int opzione;
    int correttezza_inserimento;
    do {


        //richiediamo l'opzione e verifichiamo che l'imput immesso sia del tipo consentito
        do {
            correttezza_inserimento = scanf("%d", &opzione);
            fflush(stdin);
            if (correttezza_inserimento == 0) {
                printf("Attenzione: input non valido.");
            }
        } while (correttezza_inserimento == 0);


        //verifichiamo se l'imput immesso sia consentito all'interno dei vincoli
        if ((opzione < 1) || (opzione > NUMERO_MASSIMO_OPZIONI_PRINCIPALE)) {
            stampare_messaggio_errore(FILE_MENU_PRINCIPALE);
        }


    } while ( (opzione < 1) || (opzione > NUMERO_MASSIMO_OPZIONI_PRINCIPALE) );
    return opzione;
}



void iniziare_nuova_partita (vincitore* vincitore_partita) {
    partita partita_attuale;
    inizializzare_giocatori (&partita_attuale);
    generare_percorso (&partita_attuale);
    *vincitore_partita = gestire_partita (&partita_attuale);
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