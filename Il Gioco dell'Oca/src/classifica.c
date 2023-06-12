#include <stdio.h>
#include <stdlib.h>
#include "classifica.h"
#include "costanti.h"
#include "gestire_partita.h"
#include "gestire_stampa.h"


void aggiornare_classifica_top_10(vincitore vincitore_partita) {
    vincitore vincitori[NUMERO_MASSIMO_CLASSIFICATI];
    caricare_classifica(vincitori);
    int inserito = FALSO;
    int indice_vincitori = 0;
    int rateo_vincitore_partita = leggere_lanci_vincitore(vincitore_partita) / leggere_lunghezza_percorso_vincitore(vincitore_partita);
    while (indice_vincitori < NUMERO_MASSIMO_CLASSIFICATI) {
        int rateo_classificato = leggere_lanci_vincitore(vincitori[indice_vincitori]) / leggere_lunghezza_percorso_vincitore(vincitori[indice_vincitori]);
        if ((rateo_vincitore_partita <= rateo_classificato) && (inserito != VERO)) {
            spostamento_destra_vincitori(vincitori, indice_vincitori, vincitore_partita);
            inserito = 1;
        }
        indice_vincitori = indice_vincitori + 1;
    }
    scrivere_classifica(vincitori);

    return;
}

void spostamento_destra_vincitori(vincitore vincitori[], int posizione_inserimento, vincitore vincitore_partita) {
    int indice_vincitori = NUMERO_MASSIMO_CLASSIFICATI;
    while (indice_vincitori >= posizione_inserimento) {
        vincitori[indice_vincitori] = vincitori[indice_vincitori - 1];
        indice_vincitori = indice_vincitori - 1;
    }
    vincitori[posizione_inserimento] = vincitore_partita;
    return;
}

void caricare_classifica(vincitore vincitori[]) {
    FILE *file_classifica = NULL;
    if ((file_classifica = fopen(FILE_CLASSIFICA_TOP_10, "r")) == NULL) {
        fread(vincitori, sizeof(vincitore), NUMERO_MASSIMO_CLASSIFICATI, file_classifica);
        fclose(file_classifica);
    } else {
        printf("%s", ERRORE_FILE_NON_TROVATO);
        fflush(stdout);
        printf("%c", CARATTERE_SPAZIO);
        fflush(stdout);
        printf("%s", FILE_CLASSIFICA_TOP_10);
        fflush(stdout);
    }
    return;
}


void scrivere_classifica(vincitore elenco_vincitori[]) {
    FILE *file_classifica = fopen(FILE_CLASSIFICA_TOP_10, "wb");
    fwrite(elenco_vincitori, sizeof(vincitore), NUMERO_MASSIMO_CLASSIFICATI, file_classifica);
    fclose(file_classifica);
    return;
}