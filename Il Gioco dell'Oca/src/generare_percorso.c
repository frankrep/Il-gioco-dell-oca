#include <stdlib.h>
#include "partita.h"
#include "generare_percorso.h"
#include "casella.h"
#include "costanti.h"

void generare_percorso (partita* partita_attuale) {
    creare_percorso_con_oche(partita_attuale);
    posizionare_caselle_speciali(partita_attuale);
    return;
}

void creare_percorso_con_oche(partita* partita_attuale) {
    int indice_percorso = 0;
    while(indice_percorso < leggere_numero_casella(partita_attuale)) {
        partita_attuale = inserire_casella(partita_attuale, indice_percorso);
        indice_percorso = indice_percorso + 1;
    }
}
void inserire_casella(partita* partita_attuale, int posizione_percorso) {
    casella* casella_attuale = creare_casella(posizione_percorso);
    *partita_attuale = scrivere_casella_percorso(partita_attuale, casella_attuale, posizione_percorso);
}
casella* creare_casella(int indice_partita, FILE* file_oca) {
    casella* casella_attuale;
    if (calcolare_resto(indice_partita) == FALSE ){
        *casella_attuale = leggere_da_file(casella, 1, file_oca);
    }
    else
    {
        *casella_attuale = scrivere_nome_casella(casella_attuale);
        *casella_attuale = scrivere_simbolo(casella_attuale);
    }
    *casella_attuale = scrivere_numero_casella(casella_attuale, indice_partita);
    return casella_attuale;
}
partita* posizionare_caselle_speciali(partita* partita_attuale) {
    casella* caselle_speciali = proporzionare_caselle_speciali(partita_attuale);
    int indice_speciali = 0;
    while(indice_speciali <= NUMERO_CASELLE_SPECIALI) {
        *partita_attuale = scrivere_casella_percorso(partita_attuale, caselle_speciali[indice_speciali], indice_speciali);
        indice_speciali = indice_speciali + 1;
    }
    return partita_attuale;
}
casella* proporzionare_caselle_speciali(partita* partita_attuale, FILE* file_caselle_speciali) {
    casella* caselle_speciali = leggere_da_file(casella, NUMERO_CASELLE_SPECIALI, file_caselle_speciali);
    int indice_speciali = 0;
    while(indice_speciali <= NUMERO_CASELLE_SPECIALI){
        caselle_speciali[indice_speciali] = scrivere_numero_casella(caselle_speciali[indice_speciali], calcolare_proporzione(partita_attuale, leggere_numero_casella(caselle_speciali[indice_speciali])));
        indice_speciali = indice_speciali + 1;
    }
    return caselle_speciali;
}
int calcolare_proporzione(partita* partita_attuale, int posizione_originale) {
    float valore_proporzione = ((leggere_lunghezza_percorso(partita_attuale) * posizione_originale) / DIMENSIONE_MASSIMA_PERCORSO);
    int posizione_ricavata = calcolare_parte_intera(valore_proporzione);
    return posizione_ricavata;
}
int calcolare_parte_intera(float valore_reale) {
    float numero = valore_reale;
    int parte_intera_numero = 0;
    int divisore = trovare_divisore_decimale(numero);
    while(divisore >= 1){
        int parte_intera_cifra = calcolare_parte_intera_unita(numero, divisore);
        parte_intera_numero = parte_intera_numero + (parte_intera_cifra * divisore);
        numero = numero - (parte_intera_cifra * divisore);
        divisore = divisore / BASE;
    }
    return parte_intera_numero;
}
int trovare_divisore_decimale(float numero) {
    int divisore = 1;
    while((numero/divisore) >= BASE){
        divisore = divisore * BASE;
    }
    return divisore;
}
int calcolare_parte_intera_unita(float numero, int divisore) {
    float cifra_del_numero = numero/divisore;
    int parte_intera = 0;
    while(cifra_del_numero >= UNITA){
        cifra_del_numero = cifra_del_numero - UNITA;
        parte_intera = parte_intera + UNITA;
    }
    return parte_intera;
}