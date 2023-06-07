#include <stdlib.h>
#include <stdio.h>
#include "partita.h"
#include "generare_percorso.h"
#include "casella.h"
#include "costanti.h"
#include "vincitore.h"
#include "inizializzare_partita.h"
#include "giocatore.h"
#include "gestire_partita.h"
#include "classifica.h"
#include "aiuto.h"
#include "salvare_caricare_partita.h"
#include "stampare_percorso.h"

int scegliere_opzione_menu ();

void main(void) {
	char uscita;
    stampare_testo(FILE_INTRO); //schermata logo
    scanf();//PREMERE UN TASTO QUALSIASI PER CONTINUARE
    uscita = RISPOSTA_NEGATIVA_MAIUSCOLO;
    int opzione;
    vincitore vincitore_partita;
    vincitore vincitore_attuale;
    do {
        opzione = scegliere_opzione_menu();
        if (opzione == 1) 
        {
            //iniziare_nuova_partita (&vincitore_partita);
            vincitore_partita = iniziare_nuova_partita (); //inserire fine stringa come nome nel caso in cui si interrompe la partita (stessa cosa per riprendere_partita)
            if (leggere_nome_vincitore (vincitore_attuale) != FINE_STRINGA)
            {
                FILE_CLASSIFICA_TOP_10 = aggiornare_classifica_top_10 (FILE_CLASSIFICA_TOP_10, vincitore_partita);
            }    
        }
        else
        {
            if (opzione == 2)
            {
                vincitore_partita = riprendere_partita();
                if (leggere_nome_vincitore (vincitore_attuale) != FINE_STRINGA) 
                {
                    FILE_CLASSIFICA_TOP_10 = aggiornare_classifica_top_10 (FILE_CLASSIFICA_TOP_10, vincitore_partita);
                }
            }
            else
            {
                if (opzione == 3)
                {
                    stampare_classifica();
                }
                else 
                {
                    if (opzione == 4)
                    {
                        chiedere_aiuto();
                    }
                    else
                    {
                        uscita = confermare_scelta (&uscita);
                    }
                }
            }
        }
    } while (uscita != RISPOSTA_AFFERMATIVA_MAIUSCOLO && uscita != RISPOSTA_AFFERMATIVA_MINUSCOLO);
    system("pause");
    return ;
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


vincitore* iniziare_nuova_partita (vincitore* vincitore_partita) {
    partita* partita_attuale = inizializzare_giocatori ();
    partita_attuale = generare_percorso (partita_attuale);
    vincitore_partita = gestire_partita (partita_attuale);
    return vincitore_partita;
}

vincitore* riprendere_partita () {
    partita* partita_attuale = scegliere_partita_da_caricare();
    vincitore* vincitore_partita = giocare_partita (partita_attuale);
    return vincitore_partita;
}

partita* scegliere_partita_da_caricare () {
    partita elenco_partite [NUMERO_MASSIMO_PARTITE];
    caricare_partite (elenco_partite);
    int slot_scelto = selezionare_slot (elenco_partite);

    //partita partita_attuale = elenco_partite [slot_scelto];
    partita* partita_attuale = elenco_partite [slot_scelto];

    return partita_attuale;
}

void confermare_scelta (char *conferma_scelta)  {
    //stampare a video la richiesta di conferma dell'opzione (in stile: "Vuoi confermare?")
    do 
    {
        scanf("%c", &conferma_scelta);
        if ((conferma_scelta != RISPOSTA_AFFERMATIVA_MAIUSCOLO) && (conferma_scelta != RISPOSTA_AFFERMATIVA_MINUSCOLO) && (conferma_scelta != RISPOSTA_NEGATIVA_MAIUSCOLO) && (conferma_scelta != RISPSOTA_NEGATIVA_MINUSCOLO))
        {
            //stampare a video il messaggio d'errore relativo alla conferma
        }
    }while((conferma_scelta != RISPOSTA_AFFERMATIVA_MAIUSCOLO) && (conferma_scelta != RISPOSTA_AFFERMATIVA_MINUSCOLO) && (conferma_scelta != RISPOSTA_NEGATIVA_MAIUSCOLO) && (conferma_scelta != RISPOSTA_NEGATIVA_MINUSCOLO) );
    return ;
}
