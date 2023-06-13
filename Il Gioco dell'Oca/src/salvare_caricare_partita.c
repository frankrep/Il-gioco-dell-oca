#include <stdio.h>
#include "costanti.h"
#include "salvare_caricare_partita.h"
#include "partita.h"
#include "inizializzare_partita.h"
#include "gestire_stampa.h"



void scrivere_partite (partita elenco_partite[]);
void creare_file_salvataggio ();
void effettuare_salvataggio (partita * partita_attuale, partita elenco_partite [], int slot_scelto, const char interfaccia [], int * sale);



void caricare_partite (partita elenco_partite[]) {
    FILE * file_salvataggio = fopen (FILE_SALVATAGGIO, "rb");
    if (file_salvataggio == NULL) {
        creare_file_salvataggio ();
        caricare_partite (elenco_partite);
    } else {
        fread (elenco_partite, sizeof(partita), NUMERO_MASSIMO_PARTITE, file_salvataggio);
        fclose (file_salvataggio);
    }
    return;
}



void creare_file_salvataggio () {
    partita partita_attuale;
    scrivere_carattere_partita (&partita_attuale, 0, FINE_STRINGA);
    FILE * file_salvataggio = fopen (FILE_SALVATAGGIO, "wb");
    int indice_partita = 0;
    while (indice_partita < NUMERO_MASSIMO_PARTITE) {
        fwrite (&partita_attuale, sizeof (partita), 1, file_salvataggio);
        indice_partita = indice_partita + 1;
    }
    fclose (file_salvataggio);
    return;
}



void salvare_partita (partita* partita_attuale, int * sale) {
    int slot_scelto;
    int salvato = FALSO;
    partita elenco_partite [NUMERO_MASSIMO_PARTITE];
    caricare_partite (elenco_partite);
    do {
        slot_scelto = selezionare_slot (elenco_partite, sale, FILE_SCELTA_SLOT_SALVARE_PARTITA);
        if (slot_scelto != 0) {
            stampare_testo (FILE_SCELTA_NOME_PARTITA);
            char nome_partita_salvata [DIMENSIONE_MASSIMA_NOME_PARTITA + 1];


            //verifico se l'utente inserisce un nome per la partita da salvare o vuole tornare indietro . . .
            do {
                posizionare_cursore_in_attesa(FILE_SCELTA_NOME_PARTITA);
                inserire_stringa(DIMENSIONE_MINIMA_NOME_PARTITA, DIMENSIONE_MASSIMA_NOME_PARTITA, nome_partita_salvata,
                                 sale);

                //verifico se l'utente non ha inserito alcun carattere e ha confermato
                if (nome_partita_salvata[0] == FINE_STRINGA) {
                    stampare_messaggio_errore(FILE_SCELTA_NOME_PARTITA);
                }
            }while (nome_partita_salvata[0] == FINE_STRINGA);


            //. . . se il giocatore ha selezionato uno slot per salvare e non ha scelto di tornare al menù precedente . . .
            if (nome_partita_salvata[0] != '0') {
                scrivere_nome_partita (partita_attuale, nome_partita_salvata);
                leggere_nome_partita (elenco_partite[slot_scelto - 1], nome_partita_salvata);

                //. . . verifichiamo se lo slot selezionato è vuoto. Se lo è, salva la partita nello slot . . .
                if (nome_partita_salvata[0] == FINE_STRINGA) {
                    effettuare_salvataggio (partita_attuale, elenco_partite, slot_scelto, FILE_CONFERMA_SALVATAGGIO, sale);
                    salvato = 1;
                }

                //. . . altrimenti, se è presente una partita, chiediamo all'utente se vuole sovrascrivere . . .
                else {

                    //stampare messaggio richiesta sovrascrittura
                    char sovrascrivere;
                    stampare_testo(FILE_SOVRASCRIVERE);
                    attendere_simbolo_risposta (FILE_SOVRASCRIVERE, &sovrascrivere, sale);

                    //. . . e, nel caso in cui confermi, sovrascriviamo la partita
                    if ( (sovrascrivere == RISPOSTA_AFFERMATIVA_MAIUSCOLO) || (sovrascrivere == RISPOSTA_AFFERMATIVA_MINUSCOLO) ) {
                        effettuare_salvataggio (partita_attuale, elenco_partite, slot_scelto, FILE_CONFERMA_SALVATAGGIO, sale);
                        salvato = 1;
                    }
                }
            }
        }
    } while (salvato != VERO && slot_scelto != 0);
    return;
}



void inserire_simbolo (const char interfaccia [], char * simbolo, int * sale) {
    posizionare_cursore_in_attesa (interfaccia);
    scanf("%c", simbolo);
    fflush(stdin);
    *sale = *sale + 1;
    return;
}



void verificare_correttezza_inserimento (const char file_interfaccia [], int * input, int * sale) {
    int correttezza_inserimento;
    do {
        posizionare_cursore_in_attesa (file_interfaccia);
        correttezza_inserimento = scanf ("%d", input);
        fflush (stdin);
        *sale = *sale + 1;
        if (correttezza_inserimento == FALSO) {
            stampare_messaggio_errore (file_interfaccia);
        }
    } while (correttezza_inserimento == FALSO);
}



void effettuare_salvataggio (partita * partita_attuale, partita elenco_partite [], int slot_scelto, const char interfaccia [], int * sale) {
    scrivere_turno (partita_attuale, leggere_turno(*partita_attuale) - 1);
    elenco_partite [slot_scelto - 1] = *partita_attuale;
    scrivere_partite(elenco_partite);
    stampare_testo (FILE_CONFERMA_SALVATAGGIO);
    attendere_tasto_zero (FILE_CONFERMA_SALVATAGGIO, sale);
    return;
}


//attende che l'utente prema il tasto zero
void attendere_tasto_zero (const char interfaccia [], int * sale) {
    int scelta;
    do {
        verificare_correttezza_inserimento (interfaccia, &scelta, sale);
        if (scelta != TASTO_CONFERMA) {
            stampare_messaggio_errore (interfaccia);
        }
    } while (scelta != TASTO_CONFERMA);
    return;
}



void attendere_simbolo_risposta (const char interfaccia [], char * risposta, int * sale) {
    do {
        inserire_simbolo (interfaccia, risposta, sale);
        if ( *risposta != RISPOSTA_AFFERMATIVA_MAIUSCOLO && *risposta != RISPOSTA_AFFERMATIVA_MINUSCOLO && *risposta != RISPOSTA_NEGATIVA_MAIUSCOLO && *risposta != RISPOSTA_NEGATIVA_MINUSCOLO ) {
            stampare_messaggio_errore(interfaccia);
        }
    } while ( *risposta != RISPOSTA_AFFERMATIVA_MAIUSCOLO && *risposta != RISPOSTA_AFFERMATIVA_MINUSCOLO && *risposta != RISPOSTA_NEGATIVA_MAIUSCOLO && *risposta != RISPOSTA_NEGATIVA_MINUSCOLO );
    return;
}



int selezionare_slot (partita elenco_partite[], int * sale, const char file_interfaccia[]) {
    int slot_scelto = 0;
    cancellare_schermata();
    stampare_partite_salvate (file_interfaccia, elenco_partite);
    do {
        verificare_correttezza_inserimento (file_interfaccia, &slot_scelto, sale);
        if ( (slot_scelto < 0) || (slot_scelto > NUMERO_MASSIMO_PARTITE) ) {
            stampare_messaggio_errore(file_interfaccia);
        }
    } while ( (slot_scelto < 0) || (slot_scelto > NUMERO_MASSIMO_PARTITE) );
    return slot_scelto;
}



void scrivere_partite (partita elenco_partite[]) {
    FILE * file_salvataggio = fopen(FILE_SALVATAGGIO, "wb");
    fwrite(elenco_partite, sizeof (partita), NUMERO_MASSIMO_PARTITE, file_salvataggio);
    fclose(file_salvataggio);
    return;
}