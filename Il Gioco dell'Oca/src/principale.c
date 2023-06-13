
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


int scegliere_opzione_menu (int * sale);
void iniziare_nuova_partita (vincitore* vincitore_partita, int * sale);
void riprendere_partita (vincitore* vincitore_partita, int * sale);
void scegliere_partita_da_caricare (partita* partita_attuale, int * sale);
void gestire_vincitore (vincitore vincitore_partita, int * sale);
void confermare_uscita (char * conferma, int * sale);



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

    int sale = 0;

    do {
        cancellare_schermata();
        opzione = scegliere_opzione_menu(&sale);
        
        if (opzione == 1) {
            iniziare_nuova_partita (&vincitore_partita, &sale);
            if (leggere_lunghezza_percorso_vincitore(vincitore_partita) != 0) {
                gestire_vincitore (vincitore_partita, &sale);
            }
        }
        else {
            if (opzione == 2) {
                riprendere_partita(&vincitore_partita, &sale);
                if (leggere_lunghezza_percorso_vincitore(vincitore_partita) != 0) {
                    gestire_vincitore (vincitore_partita, &sale);
                }
            }
            else {
                if (opzione == 3) {
                    stampare_classifica (&sale);
                }
                else {
                    if (opzione == 4) {
                        chiedere_aiuto (&sale);
                    }
                    else {
                        confermare_uscita(&uscita, &sale);
                    }
                }
            }
        }
    } while (uscita != RISPOSTA_AFFERMATIVA_MAIUSCOLO && uscita != RISPOSTA_AFFERMATIVA_MINUSCOLO);
    return 0;
}



int scegliere_opzione_menu (int * sale) {
    int opzione;
    stampare_testo(FILE_MENU_PRINCIPALE);
    do {
        verificare_correttezza_inserimento(FILE_MENU_PRINCIPALE, &opzione, sale);
        if ( (opzione < 0) || (opzione > NUMERO_MASSIMO_OPZIONI_PRINCIPALE) ) {
            stampare_messaggio_errore (FILE_MENU_PRINCIPALE);
        }
    } while ( (opzione < 0) || (opzione > NUMERO_MASSIMO_OPZIONI_PRINCIPALE) );
    if (opzione != 0) {
        cancellare_schermata();
    }
    return opzione;
}



void iniziare_nuova_partita (vincitore* vincitore_partita, int * sale) {
    partita partita_attuale;
    inizializzare_giocatori (&partita_attuale, sale);
    if (leggere_lunghezza_percorso (partita_attuale) != 0) {
        generare_percorso(&partita_attuale);
        *vincitore_partita = gestire_partita(&partita_attuale, sale);
    }
    else {
        scrivere_lunghezza_percorso_vincitore(vincitore_partita, 0);
    }
    return;
}



void riprendere_partita (vincitore* vincitore_partita, int * sale) {
    partita partita_attuale;
    scegliere_partita_da_caricare(&partita_attuale, sale);
    if (leggere_carattere_partita(partita_attuale, 0) != FINE_STRINGA) {
        *vincitore_partita = gestire_partita(&partita_attuale, sale);
    }
    else {
        scrivere_lunghezza_percorso_vincitore(vincitore_partita, 0);
    }
    return;
}



void scegliere_partita_da_caricare (partita* partita_attuale, int * sale) {
    int correttezza_inserimento;
    int slot_scelto;
    partita elenco_partite [NUMERO_MASSIMO_PARTITE];
    caricare_partite (elenco_partite);
    do {
        posizionare_cursore_in_attesa(FILE_MENU_CARICA_PARTITA);
        slot_scelto = selezionare_slot(elenco_partite, sale, FILE_MENU_CARICA_PARTITA);

        //se il giocatore ha deciso di caricare una partita, viene verificata la sua esistenza . . .
        if (slot_scelto != 0) {
            int scelta;
            cancellare_schermata();

            //se il giocatore ha scelto uno slot, verifica se al suo interno non vi è una partita da caricare . . .
            if (leggere_carattere_partita(elenco_partite[slot_scelto - 1], 0) == FINE_STRINGA) {
                stampare_testo(FILE_CARICAMENTO_FALLITO);

                do {

                    do {
                        posizionare_cursore_in_attesa(FILE_CARICAMENTO_FALLITO);
                        correttezza_inserimento = scanf("%d", &scelta);
                        fflush(stdin);
                        if (correttezza_inserimento == 0) {
                            stampare_messaggio_errore(FILE_CARICAMENTO_FALLITO);
                        }
                    } while (correttezza_inserimento == 0);

                    if (scelta != 0) {
                        stampare_messaggio_errore(FILE_CARICAMENTO_FALLITO);
                    }

                }while (scelta != 0);

                *sale = *sale + 1;
            }

            //. . . altrimenti carica la partita presente nello slot
            else {
                *partita_attuale = elenco_partite[slot_scelto - 1];
                //stampare schermata per confermare il caricamento con 0 per tornare indietro
                stampare_testo(FILE_CARICAMENTO_RIUSCITO);

                do {

                    do {
                        posizionare_cursore_in_attesa(FILE_CARICAMENTO_RIUSCITO);
                        correttezza_inserimento = scanf("%d", &scelta);
                        fflush(stdin);
                        if (correttezza_inserimento == 0) {
                            stampare_messaggio_errore(FILE_CARICAMENTO_FALLITO);
                        }
                    } while (correttezza_inserimento == 0);

                    if (scelta != 0) {
                        stampare_messaggio_errore(FILE_CARICAMENTO_FALLITO);
                    }

                }while (scelta != 0);

                *sale = *sale + 1;
                slot_scelto = 0;
            }
        }

        //. . . altrimenti si torna al menù precedente
        else {
            scrivere_carattere_partita(partita_attuale, 0, FINE_STRINGA);
        }
        cancellare_schermata();
    } while (slot_scelto != 0);
    return;
}



void confermare_uscita (char * conferma, int * sale) {
    cancellare_schermata();
    stampare_testo(FILE_USCITA_GIOCO);
    attendere_simbolo_risposta(FILE_USCITA_GIOCO, conferma, sale);
    return;
}



void gestire_vincitore (vincitore vincitore_partita, int* sale) {
    char nome_vincitore_partita [DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    leggere_nome_vincitore (vincitore_partita, nome_vincitore_partita);
    if (nome_vincitore_partita[0] != FINE_STRINGA) {
        aggiornare_classifica_top_10 (vincitore_partita);
        cancellare_schermata();
        stampare_vittoria(FILE_DETTAGLI_PARTITA);
        stampare_valore_testuale(FILE_DETTAGLI_PARTITA, nome_vincitore_partita, 1);
        stampare_valore_intero(FILE_DETTAGLI_PARTITA, leggere_lunghezza_percorso_vincitore(vincitore_partita), 2);
        stampare_valore_intero(FILE_DETTAGLI_PARTITA, leggere_lanci_vincitore(vincitore_partita), 3);
        stampare_valore_intero(FILE_DETTAGLI_PARTITA, leggere_punteggio(vincitore_partita), 4);
        //stampare_valore_intero(FILE_DETTAGLI_PARTITA, posizione_vincitore_classifica, 5);
        attendere_tasto_zero(FILE_DETTAGLI_PARTITA, sale);
    }
    return;
}