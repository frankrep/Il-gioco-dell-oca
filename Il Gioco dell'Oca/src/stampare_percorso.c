#include <stdio.h>
#include "costanti.h"
#include "partita.h"
#include "giocatore.h"
#include "gestire_partita.h"
#include "stampare_percorso.h"
#include "generare_percorso.h"
#include "gestire_stampa.h"

void stampare_interfaccia_percorso(partita* partita_attuale, const char file_interfaccia[]){
    cancellare_schermata();
    stampare_percorso(partita_attuale);
    FILE *f_interfaccia = NULL;
    if ((f_interfaccia = fopen(file_interfaccia, "r")) != NULL) {
        int indice_carattere = 0;
        while (indice_carattere < (LUNGHEZZA_SCHERMATA * (ALTEZZA_SCHERMATA - ALTEZZA_MENU_INTERFACCIA_PERCORSO))) {
            fgetc(f_interfaccia);
            indice_carattere = indice_carattere + 1;
        }
        char simbolo_letto;
        int indice_altezza_menu = 0;
        while (indice_altezza_menu < ALTEZZA_MENU_INTERFACCIA_PERCORSO) {
            simbolo_letto = fgetc(f_interfaccia);
            printf("%c", simbolo_letto);
            if (simbolo_letto == CARATTERE_A_CAPO) {
                indice_altezza_menu = indice_altezza_menu + 1;
            }
        }
        fclose(f_interfaccia);
    } else {
        printf("%s", ERRORE_FILE_NON_TROVATO);
        fflush(stdout);
        printf("%c", CARATTERE_SPAZIO);
        fflush(stdout);
        printf("%s", file_interfaccia);
        fflush(stdout);
    }
    stampare_dadi_partita(file_interfaccia, partita_attuale);
}

void stampare_percorso(partita* partita_attuale) {

    stampare_parte_superiore_casella();

    int indice_riga_superiore = 0;
    int indice_riga_inferiore = ALTEZZA_TABELLONE;
    int colonne_parte_sinistra = 0;
    int colonne_parte_destra = 0;
    int ultima_casella_stampata;

    int meta_righe = calcolare_parte_intera(ALTEZZA_TABELLONE / 2);

    while (indice_riga_superiore < ALTEZZA_TABELLONE)
    {
        int indice_altezza_disegno = 1;
        while (indice_altezza_disegno <= ALTEZZA_DISEGNO_CASELLA) {
            ultima_casella_stampata = 0;
            if(colonne_parte_sinistra > 0){
                if (indice_riga_superiore < (meta_righe + 1))
                {
                    ultima_casella_stampata = stampare_superiore_sinistra(partita_attuale, colonne_parte_sinistra, 0, indice_altezza_disegno);
                }else{
                    ultima_casella_stampata = stampare_inferiore_sinistra(partita_attuale, colonne_parte_sinistra, 0, indice_altezza_disegno);
                }

            }

            if (indice_riga_superiore <= (meta_righe - 1))
            {
                ultima_casella_stampata = stampare_parte_centrale_incremento(partita_attuale, ultima_casella_stampata, (LARGHEZZA_TABELLONE - colonne_parte_destra - colonne_parte_sinistra), indice_altezza_disegno);
            }else{
                ultima_casella_stampata = stampare_parte_centrale_decremento(partita_attuale, ultima_casella_stampata - (ALTEZZA_TABELLONE - (2 * (colonne_parte_sinistra))), (LARGHEZZA_TABELLONE - colonne_parte_destra - colonne_parte_sinistra), indice_altezza_disegno);
            }

            if(colonne_parte_destra > 0){
                if (indice_riga_superiore <= (meta_righe - 1)){
                    stampare_parte_destra(partita_attuale, colonne_parte_destra, ultima_casella_stampata, 0, indice_altezza_disegno);
                }else{
                    stampare_parte_destra(partita_attuale, colonne_parte_destra - 1, ultima_casella_stampata, 0, indice_altezza_disegno);
                }
            }

            printf("%c", CONTORNO_LATERALE_CASELLA); fflush(stdout);
            printf("%c", CARATTERE_A_CAPO); fflush(stdout);

            indice_altezza_disegno = indice_altezza_disegno + 1;
        }


        if (indice_riga_superiore < (indice_riga_inferiore-1))
        {
            colonne_parte_sinistra = colonne_parte_sinistra + 1;
            colonne_parte_destra = colonne_parte_destra + 1;
        }else if (indice_riga_superiore > (indice_riga_inferiore - 1)) {
            colonne_parte_sinistra = colonne_parte_sinistra - 1;
            colonne_parte_destra = colonne_parte_destra - 1;
        }

        indice_riga_superiore = indice_riga_superiore + 1;
        indice_riga_inferiore = indice_riga_inferiore - 1;
    }

}

void stampare_parte_superiore_casella() {

    printf("%s", TITOLO_PERCORSO);
    fflush(stdout);
    printf("%c", CARATTERE_A_CAPO);
    fflush(stdout);

}

int stampare_superiore_sinistra(partita* partita_attuale, int numero_colonne, int contatore, int strato){

    int ultima_casella_stampata = ((LARGHEZZA_TABELLONE - (1 + (2 * (numero_colonne - contatore - 1)))) * 2)  + ((ALTEZZA_TABELLONE - (1 + (2 * (numero_colonne - contatore - 1)))) * 2);

    if ((numero_colonne - contatore) > 1)
    {
        ultima_casella_stampata = ultima_casella_stampata + stampare_superiore_sinistra(partita_attuale, numero_colonne, contatore + 1, strato);
    }

    stampare_casella(partita_attuale, ultima_casella_stampata - contatore, strato);
    return ultima_casella_stampata;
}

int stampare_inferiore_sinistra(partita* partita_attuale, int numero_colonne, int contatore, int strato){
//il problema è qui perchè il numero che si sottrae sta nella stampa, non nel dato
    int ultima_casella_stampata = ((LARGHEZZA_TABELLONE - (1 + (2 * (numero_colonne - contatore - 1)))) * 2)  + ((ALTEZZA_TABELLONE - (1 + (2 * (numero_colonne - contatore - 1)))) * 2);

    if ((numero_colonne - contatore) > 1)
    {
        ultima_casella_stampata = ultima_casella_stampata + stampare_inferiore_sinistra(partita_attuale, numero_colonne, contatore + 1, strato);
    }

    stampare_casella(partita_attuale, ultima_casella_stampata  - (ALTEZZA_TABELLONE - (2 * (numero_colonne - contatore))) + contatore, strato);
    return ultima_casella_stampata;
}

int stampare_parte_destra(partita* partita_attuale, int numero_colonne, int numero_iniziale, int contatore, int strato){

    int ultima_casella_stampata = numero_iniziale;


    while(contatore < numero_colonne){
        ultima_casella_stampata = ultima_casella_stampata - (((LARGHEZZA_TABELLONE + ALTEZZA_TABELLONE) * 2) - (3 * 2) - (4 * 2 * (numero_colonne - contatore - 1)));
        stampare_casella(partita_attuale, (ultima_casella_stampata + contatore + 1), strato);
        contatore = contatore + 1;
    }

    return ultima_casella_stampata;
}

int stampare_parte_centrale_incremento(partita* partita_attuale, int valore_iniziale, int numero_colonne, int strato){
    int i = 0;
    while (i < numero_colonne)
    {
        valore_iniziale = valore_iniziale + 1;
        stampare_casella(partita_attuale, valore_iniziale, strato);
        i = i + 1;
    }
    return valore_iniziale;
}

int stampare_parte_centrale_decremento(partita* partita_attuale, int valore_iniziale, int numero_colonne, int strato){
    int i = 0;
    while (i <= numero_colonne)
    {
        valore_iniziale = valore_iniziale - 1;
        stampare_casella(partita_attuale, valore_iniziale, strato);
        i = i + 1;
    }
    return valore_iniziale;
}

void stampare_casella(partita* partita_attuale, int ultima_casella_stampata, int strato) {
    if (strato == 1) {
        printf("%c", CONTORNO_LATERALE_CASELLA);
        stampare_giocatori_superiori_casella(partita_attuale, ultima_casella_stampata);
    } else if (strato == 2) {
        printf("%c", CONTORNO_LATERALE_CASELLA);
        stampare_contenuto_casella(partita_attuale,ultima_casella_stampata);
    } else if (strato == 3) {
        printf("%c", CONTORNO_LATERALE_CASELLA);
        stampare_giocatori_inferiori_casella(partita_attuale,ultima_casella_stampata);
    }
}


void stampare_contenuto_casella(partita* partita_attuale, int numero_casella) {
    if((leggere_numero_casella(leggere_casella_percorso(*partita_attuale, numero_casella - 1)) <= leggere_lunghezza_percorso(*partita_attuale)) && (leggere_numero_casella(leggere_casella_percorso(*partita_attuale, numero_casella - 1)) > 0)){
        if (leggere_carattere_casella(leggere_casella_percorso(*partita_attuale, numero_casella - 1), 0) == FINE_STRINGA){
            printf("%c", CARATTERE_SPAZIO);
            printf("%d", leggere_numero_casella(leggere_casella_percorso(*partita_attuale, numero_casella - 1)));
            if(leggere_numero_casella(leggere_casella_percorso(*partita_attuale, numero_casella - 1)) < NUMERO_CIFRE) {
                printf("%c", CARATTERE_SPAZIO);
            }
            printf("%c", CARATTERE_SPAZIO);
        } else {
            char simbolo[DIMENSIONE_MASSIMA_SIMBOLO_CASELLA];
            leggere_simbolo(leggere_casella_percorso(*partita_attuale, numero_casella - 1), simbolo);
            printf("%s", simbolo);
            fflush(stdout);
        }
    }else{
        printf("%s", SIMBOLO_VUOTO);
    }

}


void stampare_giocatori_superiori_casella(partita* partita_attuale, int numero_casella) {
    if (leggere_posizione_giocatore(leggere_giocatore(*partita_attuale, POSIZIONE_GIOCATORE_1)) == numero_casella) {
        printf("%c", leggere_pedina_giocatore(leggere_giocatore(*partita_attuale, POSIZIONE_GIOCATORE_1)));
    }else {
        printf("%c", CARATTERE_SPAZIO);
    }
    int indice_spazio = 1;
    while (indice_spazio <= (SPAZIO_DISPONIBILE_CASELLA - NUMERO_GIOCATORI_STRATO_CASELLA)) {
        printf("%c", CARATTERE_SPAZIO);
        indice_spazio = indice_spazio + 1;
    }
    if (leggere_posizione_giocatore(leggere_giocatore(*partita_attuale, POSIZIONE_GIOCATORE_2)) == numero_casella) {
        printf("%c", leggere_pedina_giocatore(leggere_giocatore(*partita_attuale, POSIZIONE_GIOCATORE_2)));
    }else {
        printf("%c", CARATTERE_SPAZIO);
    }
}


void stampare_giocatori_inferiori_casella(partita* partita_attuale, int numero_casella) {
    if (leggere_pedina_giocatore(leggere_giocatore(*partita_attuale, POSIZIONE_GIOCATORE_3)) == FINE_STRINGA) {
        if (leggere_posizione_giocatore(leggere_giocatore(*partita_attuale, POSIZIONE_GIOCATORE_3)) == numero_casella) {
            printf("%c", leggere_pedina_giocatore(leggere_giocatore(*partita_attuale, POSIZIONE_GIOCATORE_3)));
        } else {
            printf("%c", CONTORNO_INFERIORE_CASELLA);
        }
    }else {
        printf("%c", CONTORNO_INFERIORE_CASELLA);
    }
    int indice_spazio = 1;
    while (indice_spazio <= (SPAZIO_DISPONIBILE_CASELLA - NUMERO_GIOCATORI_STRATO_CASELLA)){
        printf("%c", CONTORNO_INFERIORE_CASELLA);
        indice_spazio = indice_spazio + 1;
    }
    if (leggere_pedina_giocatore(leggere_giocatore(*partita_attuale, POSIZIONE_GIOCATORE_4)) == FINE_STRINGA) {
        if (leggere_posizione_giocatore(leggere_giocatore(*partita_attuale, POSIZIONE_GIOCATORE_4)) == numero_casella) {
            printf("%c", leggere_pedina_giocatore(leggere_giocatore(*partita_attuale, POSIZIONE_GIOCATORE_4)));
        } else {
            printf("%c", CONTORNO_INFERIORE_CASELLA);
        }
    }else {
        printf("%c", CONTORNO_INFERIORE_CASELLA);
    }

}