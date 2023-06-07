#include <stdio.h>
#include <stdlib.h>
#include "costanti.h"
#include "vincitore.h"
#include "gestire_partita.h"
FILE* aggiornare_classifica_top_10 (vincitore* vincitore_partita){
    vincitore vincitori[NUMERO_MASSIMO_CLASSIFICATI] = caricare_classifica(FILE_CLASSIFICA_TOP_10);
    int inserito = VERO;
    int indice_vincitori = 1;
    int rateo_vincitore_partita = leggere_numero_lanci_vincitore(vincitore_partita) / leggere_lunghezza_percorso_vincitore(*vincitore_partita);
    while (indice_vincitori <= NUMERO_MASSIMO_CLASSIFICATI) {
        int rateo_classificato = leggere_numero_lanci_vincitore(vincitori[indice_vincitori]) /leggere_lunghezza_percorso_vincitore(vincitori[indice_vincitori]); 
        if ( (rateo_vincitore_partita <= rateo_classificato) && (inserito != 1) ) {
            vincitori = spostamento_destra_vincitori(vincitori, indice_vincitori, vincitore_partita);
            inserito = 1;
        }
        indice_vincitori = indice_vincitori +1;
    }
    indice_vincitori = 1;
    while (indice_vincitori <= NUMERO_MASSIMO_CLASSIFICATI){
        FILE_CLASSIFICA_TOP_10 = scrivere_su_file(FILE_CLASSIFICA_TOP_10, vincitori[indice_vincitori]);
        indice_vincitori = indice_vincitori + 1;
    }
    return FILE_CLASSIFICA_TOP_10;
}

vincitore* spostamento_destra_vincitori (vincitore* vincitori[], int posizione_inserimento,vincitore* vincitore_partita) {
    int indice_vincitori = NUMERO_MASSIMO_CLASSIFICATI;
    while(indice_vincitori >= posizione_inserimento) {
        vincitori[indice_vincitori] = vincitori[indice_vincitori -1];
        indice_vincitori = indice_vincitori -1;
    }
    vincitori[posizione_inserimento] = vincitore_partita;
    return vincitori;
}
vincitore* caricare_classifica () {
    int indice_vincitore = 1;
    vincitore vincitori[NUMERO_MASSIMO_CLASSIFICATI];
    while(indice_vincitore <= NUMERO_MASSIMO_CLASSIFICATI) {
        vincitori[indice_vincitore] = leggere_da_file(FILE_CLASSIFICA_TOP_10);
        indice_vincitore = indice_vincitore + 1;
    }
    return vincitori;
}

void stampare_classifica() {
    vincitore vincitori[NUMERO_MASSIMO_CLASSIFICATI] = caricare_classifica(FILE_CLASSIFICA_TOP_10);
    stampare_testo(FILE_CLASSIFICA);
    int indice_vincitori = 1;
    while(indice_vincitori <= NUMERO_MASSIMO_CLASSIFICATI) {
        if (confrontare_stringhe(leggere_nome_vincitore(vincitori[indice_vincitori]), FINE_STRINGA)) {
            printf("%d ", indice_vincitori);
            printf("%s", leggere_nome_vincitore(vincitori[indice_vincitori]));
            printf("%d", leggere_numero_lanci_vincitore(vincitori[indice_vincitori]));
            printf("%d", leggere_lunghezza_percorso_vincitore(vincitori[indice_vincitori]));
        }
    }
}
