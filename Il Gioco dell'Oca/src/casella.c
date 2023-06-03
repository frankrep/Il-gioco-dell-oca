#include "casella.h"
#include <stdlib.h>
void scrivere_carattere_casella(casella* casella_attuale, int posizione, char simbolo) {
    casella_attuale->nome_casella[posizione] = simbolo;
    return;
}
char leggere_carattere_casella(casella* casella_attuale, int posizione) {
    char simbolo = casella_attuale->nome_casella[posizione];
    return simbolo;
}
void scrivere_numero_casella(casella* casella_attuale, int numero_casella_da_inserire){
    casella_attuale->numero_casella = numero_casella_da_inserire;
}
int leggere_numero_casella(casella* casella_attuale){
    int numero_casella_letto = casella_attuale->numero_casella;
    return numero_casella_letto;
}
void scrivere_simbolo(casella* casella_attuale, char simbolo_da_inserire[]){
    casella_attuale->simbolo = simbolo_da_inserire;
}
char* leggere_simbolo(casella* casella_attuale){
    char* simbolo_letto = casella_attuale->simbolo;
    return simbolo_letto;
}

void scrivere_nome_casella (casella* casella_attuale, char nome_da_inserire[]) {
    int indice_nome = 0;
    while(nome_da_inserire[indice_nome] != FINE_STRINGA){
        scrivere_carattere_casella(casella_attuale, nome_da_inserire[indice_nome], indice_nome);
        indice_nome = indice_nome + 1;
    }
    return;
}

void leggere_nome_casella (casella* casella_attuale, char nome_letto[]) {
    int indice_nome = 0;
    while(leggere_carattere_casella (casella_attuale, indice_nome) != FINE_STRINGA){
        nome_letto[indice_nome] = leggere_carattere_casella(casella_attuale, indice_nome);
        indice_nome = indice_nome + 1;
    }
    return;
}




