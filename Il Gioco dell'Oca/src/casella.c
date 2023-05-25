#include "casella.h"
#include <stdlib.h>
void scrivere_nome_casella(casellla* casella_attuale, char nome_da_inserire[]){
    casella_attuale->nome_casella = nome_da_inserire;
}
char* leggere_nome_casella(casella* casella_attuale){
    char* nome_letto = casella_attuale->nome_casella;
    return nome_letto;
}
void scrivere_numero_casella(casella* casella_attuale, int numero_casella_da_inserire){
    casella_attuale->numero_casella = numero_casella_da_inserire;
}
int leggere_numero_casella(casella* casella_attuale){
    int numero_casella_letto = casella_attuale->numero_casella;
    return numero_casella_letto;
}
void scrivere_file_interfaccia(casella* casella_attuale, char file[]){
    casella_attuale->file_interfaccia = file;
}
char* leggere_file_interfaccia(casella* casella_attuale){
    char* file = casella_attuale->file_interfaccia;
    return file;
}
void scrivere_simbolo(casella* casella_attuale, char simbolo_da_inserire[]){
    casella_attuale->simbolo = simbolo_da_inserire;
}
char* leggere_simbolo(casella* casella_attuale){
    char* simbolo_letto = casella_attuale->simbolo;
    return simbolo_letto;
} 