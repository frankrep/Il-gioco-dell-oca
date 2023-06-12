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

void stampare_classifica() {
    vincitore vincitori[NUMERO_MASSIMO_CLASSIFICATI];
    caricare_classifica(vincitori);
    stampare_testo(FILE_CLASSIFICA);
    char nome_vincitore[DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    int indice_vincitori = 0;
    int correttezza_inserimento;
    while (indice_vincitori < NUMERO_MASSIMO_CLASSIFICATI) {
        leggere_nome_vincitore(vincitori[indice_vincitori], nome_vincitore);
        if (nome_vincitore[0] == FINE_STRINGA) {
            printf("%d ", indice_vincitori);
            printf("%s", nome_vincitore);
            printf("%d", leggere_lanci_vincitore(vincitori[indice_vincitori]));
            printf("%d", leggere_lunghezza_percorso_vincitore(vincitori[indice_vincitori]));
        }
        indice_vincitori = indice_vincitori + 1;
    }
    do {
        posizionare_cursore_in_attesa(FILE_CLASSIFICA);
        scanf("%d", &correttezza_inserimento);
        fflush(stdin);
        if (correttezza_inserimento != 0) {
        stampare_messaggio_errore(FILE_CLASSIFICA);
        }
    } while (correttezza_inserimento != 0);
}

void scrivere_classifica(vincitore elenco_vincitori[]) {
    FILE *file_classifica = fopen(FILE_CLASSIFICA_TOP_10, "wb");
    fwrite(elenco_vincitori, sizeof(vincitore), NUMERO_MASSIMO_CLASSIFICATI, file_classifica);
    fclose(file_classifica);
    return;
}