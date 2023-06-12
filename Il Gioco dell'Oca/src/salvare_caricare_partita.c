#include <stdio.h>
#include "costanti.h"
#include "salvare_caricare_partita.h"
#include "partita.h"
#include "inizializzare_partita.h"
#include "gestire_stampa.h"



void scrivere_partite (partita elenco_partite[]);
void creare_file_salvataggio();




void caricare_partite (partita elenco_partite[]) {
    FILE * file_salvataggio = fopen(FILE_SALVATAGGIO, "rb");
    if (file_salvataggio == NULL) {
        creare_file_salvataggio();
        caricare_partite(elenco_partite);
    }
    else {
        fread(elenco_partite, sizeof(partita), NUMERO_MASSIMO_PARTITE, file_salvataggio);
        fclose(file_salvataggio);
    }
    return;
}



void creare_file_salvataggio() {
    FILE * file_salvataggio = fopen(FILE_SALVATAGGIO, "wb");
    partita partita_attuale;
    scrivere_carattere_partita(&partita_attuale, 0, FINE_STRINGA);
    int indice_partita = 0;
    while (indice_partita < NUMERO_MASSIMO_PARTITE) {
        fwrite(&partita_attuale, sizeof(partita), 1, file_salvataggio);
        indice_partita = indice_partita + 1;
    }
    fclose(file_salvataggio);
    return;
}


void salvare_partita (partita* partita_attuale, int * sale) {
    int slot_scelto;
    int salvato = 0;
    partita elenco_partite [NUMERO_MASSIMO_PARTITE];
    caricare_partite (elenco_partite);
    do {
        slot_scelto = selezionare_slot (elenco_partite, sale);
        char nome_partita_salvata [DIMENSIONE_MASSIMA_NOME_PARTITA];
        inserire_stringa (DIMENSIONE_MINIMA_NOME_PARTITA, DIMENSIONE_MASSIMA_NOME_PARTITA, nome_partita_salvata, sale);
        scrivere_nome_partita (partita_attuale,  nome_partita_salvata);
        leggere_nome_partita (elenco_partite [slot_scelto], nome_partita_salvata);
        if (nome_partita_salvata[0] == FINE_STRINGA) {
            elenco_partite [slot_scelto] = *partita_attuale;
            scrivere_partite (elenco_partite);
            salvato = 1;
        }
        else {
            //stampare messaggio richiesta sovrascrittura
            char sovrascrivere;
            confermare_scelta (&sovrascrivere, sale);
            if ( (sovrascrivere == RISPOSTA_AFFERMATIVA_MAIUSCOLO) || (sovrascrivere = RISPOSTA_AFFERMATIVA_MINUSCOLO) ) {
                elenco_partite[slot_scelto] = *partita_attuale;
                scrivere_partite (elenco_partite);
                salvato = 1;
            }
        }
    } while (salvato != 1);
    return;
}



void confermare_scelta (char * risposta, int * sale) {
    //decidere se stampare da file la frase così da poterla personalizzare
    printf ("Vuoi confermare? (%c/%c)  ", RISPOSTA_AFFERMATIVA_MAIUSCOLO, RISPOSTA_NEGATIVA_MAIUSCOLO);
    do {
        scanf("%c", risposta);
        fflush (stdin);
        *sale = *sale + 1;

        //decidere se stampare da file la frase
        if ( *risposta != RISPOSTA_AFFERMATIVA_MAIUSCOLO && *risposta != RISPOSTA_AFFERMATIVA_MINUSCOLO && *risposta != RISPOSTA_NEGATIVA_MAIUSCOLO && *risposta != RISPOSTA_NEGATIVA_MINUSCOLO )
            printf("La scelta inserita non e' valida, riprovare: ");

    } while ( *risposta != RISPOSTA_AFFERMATIVA_MAIUSCOLO && *risposta != RISPOSTA_AFFERMATIVA_MINUSCOLO && *risposta != RISPOSTA_NEGATIVA_MAIUSCOLO && *risposta != RISPOSTA_NEGATIVA_MINUSCOLO );
    return;
}



int selezionare_slot (partita elenco_partite[], int * sale) {
    int slot_scelto = 0;
    //interfaccia per la scelta tra le partite salvate (interfaccer muvt!)
    stampare_partite_salvate (elenco_partite);
    do {


        //verifica della correttezza del tipo dell'input inserito dall'utente
        int correttezza_inserimento;
        do {
            correttezza_inserimento = scanf("%d", &slot_scelto);
            fflush(stdin);
            *sale = *sale + 1;
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