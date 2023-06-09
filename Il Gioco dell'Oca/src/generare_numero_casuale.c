//
// Created by Potito Florio on 09/06/2023.
//



#include <stdio.h>
#include "costanti.h"



void caricare_seme (long long * seme);
long long generare_seme (long long seme);
void scrivere_seme (long long * seme);
long int generare_casuale (int seme, int numero_massimo, int numero_minimo);
void creare_file_seme ();



int generare_numero (int numero_massimo, int numero_minimo) {
    long long seme;
    caricare_seme (&seme);
    seme = generare_seme (seme);
    scrivere_seme (&seme);
    long int numero_casuale = generare_casuale (seme, numero_massimo, numero_minimo);
    return numero_casuale;
}



void caricare_seme (long long * seme) {
    FILE * file_seme = fopen(FILE_SEME, "rb");
    if (file_seme == NULL) {
        creare_file_seme();
        caricare_seme(seme);
    }
    else {
        fread(seme, sizeof(long long), 1, file_seme);
        fclose(file_seme);
    }
    return;
}



long long generare_seme (long long seme) {
    long long nuovo_seme = (MOLTIPLICATORE * seme + INCREMENTO) % DIVISORE;
    return nuovo_seme;
}



void scrivere_seme (long long * seme) {
    FILE * file_seme = fopen (FILE_SEME, "wb");
    fwrite(seme, sizeof(long long), 1, file_seme);
    fclose (file_seme);
    return;
}



long int generare_casuale (int seme, int numero_massimo, int numero_minimo) {
    long int numero_casuale = (seme % numero_massimo) + numero_minimo;
    return numero_casuale;
}



void creare_file_seme () {
    FILE * file_seme = fopen(FILE_SEME, "wb");
    fwrite((const long long *) SEME_INIZIALE, sizeof(int), 1, file_seme);
    fclose(file_seme);
    return;
}