#include <stdio.h>
#include "costanti.h"
#include "salvare_caricare_partita.h"
#include "partita.h"
#include "gestire_partita.h"
#include "inizializzare_partita.h"

void stampare_partite_salvate (partita elenco_partite[]);
void scrivere_partite (partita elenco_partite[]);

void caricare_partite (partita elenco_partite[]) {
    FILE * file_salvataggio = fopen(FILE_SALVATAGGIO, "rb");
    if (file_salvataggio == NULL) {
        //stampare messaggio di errore nell'apertura del file o del file inesistente
        //gestire l'errore nel caso di apertura, cioè restituisce la funzione
    }
    else {
        fread(elenco_partite, sizeof(partita), NUMERO_MASSIMO_PARTITE, file_salvataggio);
        fclose(file_salvataggio);
    }
    return;
}



void salvare_partita (partita* partita_attuale) {
    int indietro = FALSO;
    int slot_scelto;
    int salvato = 0;
    partita elenco_partite [NUMERO_MASSIMO_PARTITE];
    caricare_partite (elenco_partite);
    do {
        slot_scelto = selezionare_slot (elenco_partite);
        char nome_partita_salvata [DIMENSIONE_MASSIMA_NOME_PARTITA];
        inserire_stringa (DIMENSIONE_MINIMA_NOME_PARTITA, DIMENSIONE_MASSIMA_NOME_PARTITA, nome_partita_salvata, &indietro);
        scrivere_nome_partita (partita_attuale,  nome_partita_salvata);
        leggere_nome_partita (elenco_partite [slot_scelto], nome_partita_salvata);
        if (confrontare_stringhe (nome_partita_salvata,STRINGA_VUOTA) == VERO) {
            elenco_partite [slot_scelto] = *partita_attuale;
            scrivere_partite (elenco_partite);
            salvato = 1;
        }
        else {
            //stampare messaggio richiesta sovrascrittura
            char sovrascrivere;
            confermare_scelta (&sovrascrivere);
            if ( (sovrascrivere == RISPOSTA_AFFERMATIVA_MAIUSCOLO) || (sovrascrivere = RISPOSTA_AFFERMATIVA_MINUSCOLO) ) {
                elenco_partite[slot_scelto] = *partita_attuale;
                scrivere_partite (elenco_partite);
                salvato = 1;
            }
        }
    } while (salvato != 1);
    return;
}



void confermare_scelta (char * risposta) {
    //decidere se stampare da file la frase
    printf ("Vuoi confermare? (%c/%c)  ", RISPOSTA_AFFERMATIVA_MAIUSCOLO, RISPOSTA_NEGATIVA_MAIUSCOLO);
    do {
        scanf("%c", risposta);
        fflush (stdin);

        //decidere se stampare da file la frase
        if ( *risposta != RISPOSTA_AFFERMATIVA_MAIUSCOLO && *risposta != RISPOSTA_AFFERMATIVA_MINUSCOLO && *risposta != RISPOSTA_NEGATIVA_MAIUSCOLO && *risposta != RISPOSTA_NEGATIVA_MINUSCOLO )
            printf("La scelta inserita non e' valida, riprovare: ");

    } while ( *risposta != RISPOSTA_AFFERMATIVA_MAIUSCOLO && *risposta != RISPOSTA_AFFERMATIVA_MINUSCOLO && *risposta != RISPOSTA_NEGATIVA_MAIUSCOLO && *risposta != RISPOSTA_NEGATIVA_MINUSCOLO );
    return;
}



void stampare_partite_salvate (partita elenco_partite[]) {
    int indice_partita = 0;
    char nome [DIMENSIONE_MASSIMA_NOME_PARTITA];
    while (indice_partita < NUMERO_MASSIMO_PARTITE) {
        leggere_nome_partita (elenco_partite[indice_partita], nome);
        if (confrontare_stringhe (nome,STRINGA_VUOTA) == VERO) {
             //stampare il nome dello slot con il simbolo vuoto
        }
        else {
            //stampare il nome relativo alla partita salvata nella posizione individuata dallo slot
        }
        indice_partita = indice_partita + 1;
    }
    return;
}



int selezionare_slot (partita elenco_partite[]) {
    int slot_scelto = 0;
    //interfaccia per la scelta tra le partite salvate (interfaccer muvt!)
    stampare_partite_salvate (elenco_partite);
    do {


        //verifica della correttezza del tipo dell'input inserito dall'utente
        int correttezza_inserimento;
        do {
            correttezza_inserimento = scanf("%d", &slot_scelto);
            fflush(stdin);
            if (correttezza_inserimento == 0) {
                printf("Attenzione: input non valido.");
            }
        } while (correttezza_inserimento == 0);


        if ( (slot_scelto < 0) || (slot_scelto > NUMERO_MASSIMO_PARTITE) )
        {
            //stampare messaggio errore
        }

    }while ( (slot_scelto < 1) || (slot_scelto > NUMERO_MASSIMO_PARTITE) );
    return slot_scelto;
}



void scrivere_partite (partita elenco_partite[]) {
    FILE * file_salvataggio = fopen(FILE_SALVATAGGIO, "wb");
    fwrite(elenco_partite, sizeof (partita), NUMERO_MASSIMO_PARTITE, file_salvataggio);
    fclose(file_salvataggio);
    return;
}