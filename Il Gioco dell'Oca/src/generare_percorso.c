#include <stdlib.h>
#include <stdio.h>
#include "partita.h"
#include "generare_percorso.h"
#include "casella.h"
#include "costanti.h"

void generare_percorso (partita* partita_attuale) {
    creare_percorso_con_oche (partita_attuale);
    posizionare_caselle_speciali (partita_attuale);
    return;
}

void creare_percorso_con_oche (partita* partita_attuale) {
    int indice_percorso = 0;
    while ( indice_percorso < leggere_lunghezza_percorso (*partita_attuale) ) {
        inserire_casella (partita_attuale, indice_percorso);
        indice_percorso = indice_percorso + 1;
    }
    return;
}

void inserire_casella (partita* partita_attuale, int posizione_percorso) {
    casella casella_attuale;
    creare_casella (&casella_attuale, posizione_percorso);
    scrivere_casella_percorso (partita_attuale, casella_attuale, posizione_percorso);
    return;
}

void creare_casella (casella* casella_attuale, int indice_partita) {
    if ( calcolare_resto (indice_partita, DISTANZA_OCHE) != DISTANZA_OCHE ) {
        scrivere_carattere_casella (casella_attuale, 0, FINE_STRINGA);
        scrivere_carattere_simbolo (casella_attuale, FINE_STRINGA);
    }
    else {
        scrivere_nome_casella (casella_attuale, NOME_OCA );
        scrivere_simbolo (casella_attuale, simbolo_della_casella_oca);  <-----aggiungere costante
    }
    scrivere_numero_casella (casella_attuale, indice_partita);
    return;
}

void posizionare_caselle_speciali (partita* partita_attuale) {
    casella caselle_speciali [NUMERO_CASELLE_SPECIALI];
    proporzionare_caselle_speciali (partita_attuale, caselle_speciali);
    int indice_speciali = 0;
    while (indice_speciali < NUMERO_CASELLE_SPECIALI) {
        scrivere_casella_percorso (partita_attuale, caselle_speciali[indice_speciali], leggere_numero_casella (caselle_speciali [indice_speciali] ) );
        indice_speciali = indice_speciali + 1;
    }
    return;
}

void proporzionare_caselle_speciali(partita* partita_attuale, casella caselle_speciali[]) {
    FILE * file_caselle_speciali = fopen("file_caselle_speciali.bin", "rb");
    fread(caselle_speciali, sizeof(casella), NUMERO_CASELLE_SPECIALI, file_caselle_speciali);

    int indice_speciali = 0;
    while(indice_speciali < NUMERO_CASELLE_SPECIALI) {
        caselle_speciali [indice_speciali] = scrivere_numero_casella ( caselle_speciali [indice_speciali], calcolare_proporzione( *partita_attuale, leggere_numero_casella (caselle_speciali [indice_speciali] ) ) );
        indice_speciali = indice_speciali + 1;
    }
    return;
}

int calcolare_proporzione(partita partita_attuale, int posizione_originale) {
    float valore_proporzione = ( ( leggere_lunghezza_percorso (partita_attuale) * posizione_originale) / DIMENSIONE_MASSIMA_PERCORSO);
    int posizione_ricavata = calcolare_parte_intera (valore_proporzione);
    return posizione_ricavata;
}
int calcolare_parte_intera (float valore_reale) {
    int parte_intera_numero = 0;
    int divisore = trovare_divisore_massimo_decimale (valore_reale);
    while (divisore >= 1) {
        int parte_intera_cifra = calcolare_parte_intera_unita (valore_reale, divisore);
        parte_intera_numero = parte_intera_numero + (parte_intera_cifra * divisore);
        valore_reale = valore_reale - (parte_intera_cifra * divisore);
        divisore = divisore / BASE;
    }
    return parte_intera_numero;
}
int trovare_divisore_massimo_decimale (float valore_reale) {
    int divisore = 1;
    while ( (valore_reale / divisore) >= BASE) {
        divisore = divisore * BASE;
    }
    return divisore;
}
int calcolare_parte_intera_unita (float valore_reale, int divisore) {
    float cifra_del_numero = valore_reale / divisore;
    int parte_intera = 0;
    while (cifra_del_numero >= UNITA) {
        cifra_del_numero = cifra_del_numero - UNITA;
        parte_intera = parte_intera + UNITA;
    }
    return parte_intera;
}

int calcolare_resto (int dividendo, int divisore) {
    int resto = dividendo;
    while (resto > divisore) {
        resto = resto - divisore;
    }
    return resto;
}