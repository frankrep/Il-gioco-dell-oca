#include <stdio.h>
#include <stdlib.h>
#include "costanti.h"
#include "salvare_caricare_partita.h"
#include "partita.h"
#include "gestire_partita.h"
parita caricare_partite () {
    int indice_partita = 0;
    partita elenco_partite[NUMERO_MASSIMO_PARTITE];
    while (indice_partita <= NUMERO_MASSIMO_PARTITE)
    {
        elenco_partite[indice_partita] = leggere_da_file(file_salvataggio);
        indice_partita = indice_partita + 1;
    }
    return elenco_partite;
}

FILE* salvare_partita (partita* partita_attuale, int slot_scelto) {
    int salvato = 0;
    partita elenco_partite[NUMERO_MASSIMO_PARTITE];
    elenco_partite = caricare_partite();
    do {
        slot_scelto = selezionare_slot (elenco_partite);
        partita_attuale = scrivere_nome_partita(partita_attuale,inserire_stringa(DIMENSIONE_MINIMA_NOME_PARTITA,DIMENSIONE_NOME_PARTITA));
        if (confrontare_stringhe(leggere_nome_partita(elenco_partite[slot_scelto]),FINE_STRINGA) == 1)
        {
            elenco_partite[slot_scelto] = partita_attuale;
            indice_partita = 1;
            while(indice_partita <= NUMERO_MASSIMO_PARTITE)
            {
                file_salvataggio = scrivere_su_file(file_salvataggio,elenco_partite[indice_partita]);
                indice_partita = indice_partita + 1;
            }
            salvato = 1;
        }
        else
        {
            //stampare messaggio richiesta sovrascritta
            char sovrascrivere = confermare_scelta();
            if ((sovrascrivere == RISPOSTA_AFFERMATIVA_MAIUSCOOLO) || (sovrascrivere = RISPOSTA_AFFERMATIVA_MINUSCOLO))
            {
                elenco_partite[slot_scelto] = partita_attuale;
                indice_partita = 1;
                while (indice_partita <= NUMERO_MASSIMO_PARTITE)
                {
                    file_salvataggio = scrivere_su_file(file_salvataggio,elenco_partite[indice_partita]);
                    indice_partita = indice_partita + 1;
                }
                salvato = 1;
            }
        }
    }while(salvato != 1);
    return file_salvataggio;
}

void stampare_partite_salvato(partita* elenco_partite) {
    int indice_partita = 0;
    char nome[DIMENSIONE_NOME_PARTITA];
    while (indice_partita <= NUMERO_MASSIMO_PARTITE)
    {
        nome = leggere_nome_partita(elenco_partite[indice_partita]);
        if (confrontare_stringhe(nome,FINE_STRINGA) == 1)
        {
             //stampare il nome dello slot con il simbolo vuoto
        }
        else
        {
            //stampare il nome relativo alla partita salvata nella posizione individuata dallo slot
        }
    }
}

int selezionare_slot (partita* elenco_partite) {
    int slot_scelto = 0;
    //interfaccia per la scelta tra le partite salvate (interfaccer muvt!)
    stampare_partite_salvato(elenco_partite);
    do {
         slot_scelto = scanf("%d",slot_scelto);
        if ((slot_scelto < 0) || (slot_scelto > NUMERO_MASSIMO_PARTITE))
        {
            //stampare messaggio errore
        }
    }while((slot_scelto < 1) || (slot_scelto > NUMERO_MASSIMO_PARTITE);
    return slot_scelto;
}