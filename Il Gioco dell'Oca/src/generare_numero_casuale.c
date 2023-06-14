//
// Created by Potito Florio on 09/06/2023.
//



#include <stdio.h>
#include "costanti.h"



void caricare_semi (unsigned long long semi[]);
int calcolare_posizione_seme (unsigned long long semi[], int sale);
unsigned long long generare_seme (unsigned long long seme, int sale);
void scrivere_seme (unsigned long long semi[]);
int generare_casuale (unsigned long long seme, int numero_massimo, int numero_minimo);
void creare_file_seme ();



int generare_numero (int numero_massimo, int numero_minimo, int sale) {
    unsigned long long semi [NUMERO_SEMI + 1];
    caricare_semi (semi);
    int posizione_seme = calcolare_posizione_seme (semi, sale);
    semi [posizione_seme] = generare_seme (semi [posizione_seme], sale);
    scrivere_seme (semi);
    int numero_casuale;
    numero_casuale = generare_casuale (semi [posizione_seme], numero_massimo, numero_minimo);
    numero_casuale = generare_casuale ( numero_casuale + sale, numero_massimo, numero_minimo);
    return numero_casuale;
}



void caricare_semi (unsigned long long semi []) {
    FILE * file_seme = fopen (FILE_SEME, "rb");
    if (file_seme == NULL) {
        creare_file_seme ();
        caricare_semi (semi);
    }
    else {
        fread(semi, sizeof (unsigned long long), NUMERO_SEMI + 1, file_seme);
        fclose(file_seme);
    }
    return;
}



int calcolare_posizione_seme (unsigned long long semi[], int sale) {
    semi [0] = generare_seme (semi [0], sale);
    int posizione_seme = generare_casuale (semi [0], FACCIA_MASSIMA_DADO, FACCIA_MINIMA_DADO);
    return posizione_seme;
}



unsigned long long generare_seme (unsigned long long seme, int sale) {
    seme = ( (MOLTIPLICATORE * ( (seme + sale) * seme ) ) + INCREMENTO) % DIVISORE;
    return seme;
}


void scrivere_seme (unsigned long long semi[]) {
    FILE * file_seme = fopen (FILE_SEME, "wb");
    fwrite (semi, sizeof (unsigned long long), NUMERO_SEMI + 1, file_seme);
    fclose (file_seme);
    return;
}



int generare_casuale (unsigned long long seme, int numero_massimo, int numero_minimo) {
    int numero_casuale = (seme % numero_massimo) + numero_minimo;
    return numero_casuale;
}



void creare_file_seme () {
    FILE * file_seme = fopen(FILE_SEME, "wb");
    fwrite(&SEME_INIZIALE_1, sizeof(unsigned long long), 1, file_seme);
    fwrite(&SEME_INIZIALE_1, sizeof(unsigned long long), 1, file_seme);
    fwrite(&SEME_INIZIALE_2, sizeof(unsigned long long), 1, file_seme);
    fwrite(&SEME_INIZIALE_3, sizeof(unsigned long long), 1, file_seme);
    fwrite(&SEME_INIZIALE_4, sizeof(unsigned long long), 1, file_seme);
    fwrite(&SEME_INIZIALE_5, sizeof(unsigned long long), 1, file_seme);
    fwrite(&SEME_INIZIALE_6, sizeof(unsigned long long), 1, file_seme);
    fclose(file_seme);
    return;
}
