#include "partita.h"
#include "generare_percorso.h"
#include "casella.h"
#include "costanti.h"



void creare_percorso_con_oche (partita* partita_attuale);
void inserire_casella (partita* partita_attuale, int posizione_percorso);
void creare_casella (casella* casella_attuale, int indice_partita);
void posizionare_caselle_speciali (partita* partita_attuale);
void proporzionare_caselle_speciali (partita* partita_attuale, casella caselle_speciali[]);
int trovare_divisore_massimo_decimale (float valore_reale);
int calcolare_parte_intera_unita (float valore_reale, int divisore);



void generare_percorso (partita* partita_attuale) {
    creare_percorso_con_oche (partita_attuale);
    posizionare_caselle_speciali (partita_attuale);
    return;
}



void creare_percorso_con_oche (partita* partita_attuale) {
    int indice_percorso = 0;
    while ( indice_percorso < leggere_lunghezza_percorso (*partita_attuale)) {
        inserire_casella (partita_attuale, indice_percorso);
        indice_percorso = indice_percorso + 1;
    }
    riempire_restante_percorso(partita_attuale, indice_percorso);
    return;
}



void inserire_casella (partita* partita_attuale, int posizione_percorso) {
    casella casella_attuale;
    creare_casella (&casella_attuale, posizione_percorso);
    scrivere_casella_percorso (partita_attuale, casella_attuale, posizione_percorso);
    return;
}



void creare_casella (casella* casella_attuale, int indice_partita) {
    if (calcolare_resto (indice_partita + 1, DISTANZA_OCHE) != DISTANZA_OCHE) {
        scrivere_carattere_casella (casella_attuale, 0, FINE_STRINGA);
        scrivere_carattere_simbolo (casella_attuale, 0, FINE_STRINGA);
    }
    else {
        scrivere_nome_casella (casella_attuale, NOME_OCA);
        scrivere_simbolo (casella_attuale, SIMBOLO_OCA);
    }
    scrivere_numero_casella (casella_attuale, indice_partita + 1);
    return;
}



void posizionare_caselle_speciali (partita* partita_attuale) {
    casella caselle_speciali [NUMERO_CASELLE_SPECIALI];
    proporzionare_caselle_speciali (partita_attuale, caselle_speciali);
    int indice_speciali = 0;
    while (indice_speciali < NUMERO_CASELLE_SPECIALI - 1) {
        if ( calcolare_resto (leggere_numero_casella (caselle_speciali [indice_speciali] ), DISTANZA_OCHE) == DISTANZA_OCHE){
            scrivere_numero_casella(&caselle_speciali [indice_speciali], leggere_numero_casella (caselle_speciali[indice_speciali]) - 1);
            }
        scrivere_casella_percorso (partita_attuale, caselle_speciali [indice_speciali], leggere_numero_casella (caselle_speciali [indice_speciali] ) - 1);
        indice_speciali = indice_speciali + 1;
    }
    scrivere_casella_percorso (partita_attuale, caselle_speciali [indice_speciali], leggere_numero_casella (caselle_speciali [indice_speciali] ) - 1);
    return;
}



void riempire_restante_percorso (partita* partita_attuale, int indice_ultima_casella) {
    casella casella_attuale;
    scrivere_numero_casella (&casella_attuale, 0);
    scrivere_carattere_casella (&casella_attuale, 0, FINE_STRINGA);
    scrivere_carattere_simbolo (&casella_attuale, 0, FINE_STRINGA);
    while (indice_ultima_casella < DIMENSIONE_MASSIMA_PERCORSO) {
        scrivere_casella_percorso (partita_attuale, casella_attuale, indice_ultima_casella);
        indice_ultima_casella = indice_ultima_casella + 1;
    }
}


void proporzionare_caselle_speciali ( partita* partita_attuale, casella caselle_speciali []) {
    inizializzare_caselle_speciali (caselle_speciali);
    int indice_speciali = 0;
    while (indice_speciali < NUMERO_CASELLE_SPECIALI) {
        scrivere_numero_casella (&caselle_speciali[indice_speciali], calcolare_proporzione (*partita_attuale, leggere_numero_casella (caselle_speciali [indice_speciali]) ) );
        indice_speciali = indice_speciali + 1;
    }
    return;
}



void inizializzare_caselle_speciali (casella caselle_speciali[]) {
    scrivere_nome_casella (&caselle_speciali[0], NOME_PONTE);
    scrivere_simbolo (&caselle_speciali[0], SIMBOLO_PONTE);
    scrivere_numero_casella(&caselle_speciali[0], 6);
    scrivere_nome_casella (&caselle_speciali[1], NOME_LOCANDA);
    scrivere_simbolo (&caselle_speciali[1], SIMBOLO_LOCANDA);
    scrivere_numero_casella(&caselle_speciali[1], 19);
    scrivere_nome_casella (&caselle_speciali[2], NOME_POZZO);
    scrivere_simbolo (&caselle_speciali[2], SIMBOLO_POZZO);
    scrivere_numero_casella(&caselle_speciali[2], 31);
    scrivere_nome_casella (&caselle_speciali[3], NOME_LABIRINTO);
    scrivere_simbolo (&caselle_speciali[3], SIMBOLO_LABIRINTO);
    scrivere_numero_casella(&caselle_speciali[3], 42);
    scrivere_nome_casella (&caselle_speciali[4], NOME_PRIGIONE);
    scrivere_simbolo (&caselle_speciali[4], SIMBOLO_PRIGIONE);
    scrivere_numero_casella(&caselle_speciali[4], 52);
    scrivere_nome_casella (&caselle_speciali[5], NOME_SCHELETRO);
    scrivere_simbolo (&caselle_speciali[5], SIMBOLO_SCHELETRO);
    scrivere_numero_casella(&caselle_speciali[5], 58);
    scrivere_nome_casella (&caselle_speciali[6], NOME_VITTORIA);
    scrivere_simbolo (&caselle_speciali[6], SIMBOLO_VITTORIA);
    scrivere_numero_casella(&caselle_speciali[6], 90);
}



int calcolare_proporzione (partita partita_attuale, int posizione_originale) {
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