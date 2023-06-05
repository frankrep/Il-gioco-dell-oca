#include <stdlib.h>
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

void main(void) {
    stampare_testo(file_intro); //schermata logo
    scanf("%d" , &uscita);
    int uscita = RISPOSTA_NEGATIVA_MAIUSCOLO;
    int opzione;
    vincitore vincitore_partita;
    vincitore vincitore_attuale;
    do {
        opzione = scegliere_opzione_menu;
        if (opzione == 1) 
        {
            vincitore_partita = iniziare_nuova_partita (); //inserire fine stringa come nome nel caso in cui si interrompe la partita (stessa cosa per riprendere_partita)
            if (leggere_nome_vincitore (vincitore_attuale) != FINE_STRINGA)
            {
                file_classifica_top_10 = aggiornare_classifica_top_10 (file_classifica_top_10, vincitore_partita);
            }    
        }
        else
        {
            if (opzione == 2)
            {
                vincitore_partita = riprendere_partita();
                if (leggere_nome_vincitore (vincitore_attuale) != FINE_STRINGA) 
                {
                    file_classifica_top_10 = aggiornare_classifica_top_10 (file_classifica_top_10, vincitore_partita);
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
                        uscita == confermare_scelta ();
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
    do 
    {
        scanf ("%d",&opzione);
        if ((opzione < 1) || (opzione > NUMERO_MASSIMO_OPZIONI_PRINCIPALE))
        {
            stampare_messaggio_errore(file_menu_principale);
        }
    }while ((opzione < 1) || (opzione > NUMERO_MASSIMO_OPZIONI_PRINCIPALE));
    return opzione;
}

vincitore* iniziare_nuova_partita (vincitore* vincitore_partita) {
    partita* partita_attuale = inziializzare_giocatori ();
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
    elenco_partite[NUMERO_MASSIMO_PARTITE] = caricare_partita (file_salvataggio);
    int slot_scelto = selezionare_slot (elenco_partite);
    partita* partita_attuale = elenco_partite[slot_scelto];
    return partita_attuale;
}

char confermare_scelta (char conferma_scelta)  {
    //stampare a video la richiesta di conferma dell'opzione (in stile: "Vuoi confermare?")
    do 
    {
        scanf("%c", &conferma_scelta);
        if ((confermare_scelta != RISPOSTA_AFFERMATIVA_MAIUSCOLO) && (confermare_scelta != RISPOSTA_AFFERMATIVA_MINUSCOLO) && (confermare_scelta != RISPOSTA_NEGATIVA_MAIUSCOLO) && (confermare_scelta != RISPSOTA_NEGATIVA_MINUSCOLO))
        {
            //stampare a video il messaggio d'errore relativo alla conferma
        }
    }while(confermare_scelta != RISPOSTA_AFFERMATIVA_MAIUSCOLO) && (confermare_scelta != RISPOSTA_AFFERMATIVA_MINUSCOLO) && (confermare_scelta != RISPOSTA_NEGATIVA_MAIUSCOLO) && (confermare_scelta != RISPOSTA_NEGATIVA_MINUSCOLO) )
    return conferma_scelta;
}
