#include <stdio.h>
#include <stdlib.h>
#include "partita.h"
#include "stampare_percorso.h"
#include "costanti.h"

void stampare_percorso (partita* partita_attuale) {
    stampare_parte_superiore_casella();
    int indice_riga_superiore = 1;
    int indice_riga_inferiore;
    int colonne_parte_sinistra;
    int colonne_parte_destra;
    int ultima_casella_stampata;
    while (indice_riga_superiore <= ALTEZZA_TABELLONE)
    {
        int indice_altezza_disegno = 1;
        while (indice_altezza_disegno <= ALTEZZA_DISEGNO_CASELLA)
        {
            if (colonne_parte_sinistra > 0)
            {
                if (indice_riga_superiore < (meta_righe +1))
                {
                    ultima_casella_stampata = stampare_superiore_sinistra(partita_attuale, colonne_parte_sinistra, 0);
                }
                else
                {
                    ultima_casella_stampata = stampare_inferiore_sinistra(partita_attuale,colonne_parte_sinistra, 0);
                }
            }
            if (indice_riga_superiore <= (meta_righe -1))
            {
                ultima_casella_stampata = stampare_parte_centrale_incremento(partita_attuale, ultima_casella_stampata, (LARGHEZZA_TABELLONE - colonne_parte_destra - colonne_parte_sinistra));
            }
            else 
            {
                stampare_parte_centrale_decremento(partita_attuale, ultima_casella_stampata - (ALTEZZA_TABELLONE - (2 * (colonne_parte_sinistra))), (LARGHEZZA_TABELLONE - colonne_parte_destra - colonne_parte_sinistra));
            }
            if (colonne_parte_destra > 0)
            {
                if (indice_riga_superiore <= (meta_righe -1))
                {
                    stampare_parte_destra(partita_attuale, colonne_parte_destra, ultima_casella_stampata, 0);
                }
                else
                {
                    stampare_parte_destra(partita_attuale, colonne_parte_destra - 1, ultima_casella_stampata, 0);
                }
            }
            if (indice_riga_superiore < (indice_riga_inferiore -1))
            {
                colonne_parte_sinistra = colonne_parte_sinistra + 1;
                colonne_parte_destra = colonne_parte_destra + 1;
            }
            else if (indice_riga_superiore > (indice_riga_inferiore -1))
            {
                colonne_parte_sinistra = colonne_parte_sinistra - 1;
                colonne_parte_destra = colonne_parte_destra - 1;
            }
            printf("%c",CARATTERE_A_CAPO);
            indice_riga_superiore = indice_riga_superiore + 1;
            indice_riga_inferiore = indice_riga_inferiore - 1;

            indice_altezza_disegno = indice_altezza_disegno + 1;
        }
    }
}

void stampare_parte_superiore_casella () {

    int indice_caselle_disegnate = 1;
    int indice_larghezza_disegno;
    while (indice_caselle_disegnate <= LARGHEZZA_TABELLONE)
    {
        printf ("%c", CARATTERE_SPAZO);
        while (indice_larghezza_disegno <= SPAZIO_DISPONIBILE_CASELLA)
        {
            printf("%c", CONTORNO_SUPERIORE_CASELLA);
            indice_larghezza_disegno = indice_larghezza_disegno + 1;
        }
        printf ("%c", CARATTERE_SPAZIO);
        indice_caselle_disegnate = indice_caselle_disegnate + 1;
    }
    printf("%c", CARATTERE_A_CAPO);
}

void stampare_superiore_sinistra (int numero_colonne, int contatore, int strato) {

    int ultima_casella_stampata = ((LARGHEZZA_TABELLONE - (1 + (2 * (numero_colonne - contatore - 1)))) * 2)  + ((ALTEZZA_TABELLONE - (1 + (2 * (numero_colonne - contatore - 1)))) * 2);
    if ((numero_colonne - contatore) > 1)
    {
        ultima_casella_stampata = ultima_casella_stampata + stampare_superiore_sinistra(numero_colonne, contatore + 1, strato);
    }
    stampare_casella((ultima_casella_stampata - contatore), strato);
}

void stampare_inferiore_sinistra (int numero_colonne, int cotatore, int strato) {
    int ultima_casella_stampata = ((LARGHEZZA_TABELLONE - (1 + (2 * (numero_colonne - contatore - 1)))) * 2)  + ((ALTEZZA_TABELLONE - (1 + (2 * (numero_colonne - contatore - 1)))) * 2);
    if ((numero_colonne - contatore) > 1)
    {
        ultima_casella_stampata = ultima_casella_stampata + stampare_inferiore_sinistra(numero_colonne, contatore + 1);
    }
    stampare_casella((ultima_casella_stampata  - (ALTEZZA_TABELLONE - (2 * (numero_colonne - contatore))) + contatore), strato);
}

void stampare_parte_centrale_incrementeo (int numero_iniziale, int numero_colonne, int strato) {
    int ultima_casella_stampata = numero_iniziale;
    int indice_colonna = 0;
    while (indice_colonna < numero_colonne)
    {
         ultima_casella_stampata = ultima_casella_stampata + 1;
         stampare_casella(ultima_casella_stampata);
         indice_colonna = indice_colonna + 1;
    }
}

void stampare_parte_centrale_decremento (int numero_iniziale, int numero_colonne, int strato) {
    int ultima_casella_stampata = numero_iniziale;
    int indice_colonna = 0;
    while (indice_colonna <= numero_colonne)
    {
    ultima_casella_stampata = ultima_casella_stampata - 1
    stampare_casella(ultima_casella_stampata, strato)
    indice_colonna = indice_colonna + 1
    }
}

void stampare_parte_destra (int numero_colonne, int contatore, int strato, int numero_iniziale) {
    int ultima_casella_stampata = numero_iniziale;
    while (contatore < numero_colonne)
    {
    ultima_casella_stampata = ultima_casella_stampata - (((LARGHEZZA_TABELLONE + ALTEZZA_TABELLONE) * 2) - (3 * 2) - (4 * 2 * (numero_colonne - contatore - 1)));
    stampare_casella((ultima_casella_stampata + contatore + 1), strato);
    contatore = contatore + 1;
    }
}

void stampare_casella(partita* partita_attuale, int numero_casella, int strato) {
    if (strato == 1)
    {
        printf("%c",CONTORNO_LATERALE_CASELLA);
        stampare_giocatori_superiori_casella(partita_attuale, numero_casella);
        printf("%c",CONTORNO_LATERALE_CASELLA);
    }
    else if (strato == 2)
    {
        printf("%c",CONTORNO_LATERALE_CASELLA);
        stampare_contenuto_casella(partita_attuale);
        printf("%c",CONTORNO_LATERALE_CASELLA);
    }
    else if (strato == 3)
    {
        printf(CONTORNO_LATERALE_CASELLA);
        stampare_giocatori_inferiori_casella(partita_attuale, numero_casella);
        printf(CONTORNO_LATERALE_CASELLA);
    }
}

void stampare_contenuto_casella (partita* partita_attuale, int numero_casella) {
    if (confrontare_stringhe(leggere_simbolo(leggere_casella_percorso(partita_attuale, numero_casella)), FINE_STRINGA) = VERO)
    {
        printf("%c", CARATTERE_SPAZIO);
        printf("%d",leggere_numero_casella(leggere_casella_percorso(partita_attuale, numero_casella)));
        printf("%c", CARATTERE_SPAZIO);
    }
    else 
    {
        printf("%s",leggere_simbolo(leggere_casella_percorso(partita_attuale, numero_casella)));
    }
}

void stampare_giocatori_superiori_casella () {
    int indice_spazio;
    if (leggere_posizione_giocatore(leggere_giocatore(partita_attuale, POSIZIONE_GIOCATORE_1)) == numero_casella)
    {
        printf ("%c",leggere_pedina_giocatore(leggere_giocatore(partita_attuale, POSIZIONE_GIOCATORE_1)));
    }
    indice_spazio = 1;
    while (indice_spazio <= (SPAZIO_DISPONIBILE_CASELLA - NUMERO_GIOCATORI_STRATO_CASELLA))
    {
        printf("%c", CARATTERE_SPAZIO);
        indice_spazio = indice_spazio + 1;
    }
    if (leggere_posizione_giocatore(leggere_giocatore(partita_attuale, POSIZIONE_GIOCATORE_2)) == numero_casella)
    {
        printf ("%c",leggere_pedina_giocatore(leggere_giocatore(partita_attuale, POSIZIONE_GIOCATORE_2)));
    }
}

void stampare_giocatori_inferiori_casella () {
    int indice_spazio;
    if (confrontare_stringhe(leggere_pedina_giocatore(leggere_giocatore(partita_attuale, POSIZIONE_GIOCATORE_3)), FINE_STRINGA) == VERO)
    {
        printf("%c",leggere_pedina_giocatore(leggere_giocatore(partita_attuale, CONTORNO_INFERIORE_CASELLA)));
    }
    else
    {
        printf("%c",leggere_pedina_giocatore(leggere_giocatore(partita_attuale, POSIZIONE_GIOCATORE_3)));
    }
    indice_spazio = 1;
    while (indice_spazio <= (SPAZIO_DISPONIBILE_CASELLA - NUMERO_GIOCATORI_STRATO_CASELLA));
    {
        printf("%c",CONTORNO_INFERIORE_CASELLA);
        indice_spazio = indice_spazio + 1;
    }
    if (confrontare_stringhe(leggere_pedina_giocatore(leggere_giocatore(partita_attuale, POSIZIONE_GIOCATORE_4)), FINE_STRINGA) == VERO)
    {
        pritnf("%c",leggere_pedina_giocatore(leggere_giocatore(partita_attuale, CONTORNO_INFERIORE_CASELLA)));
    }
    else
    {
        prtinf("%c",leggere_pedina_giocatore(leggere_giocatore(partita_attuale, POSIZIONE_GIOCATORE_4)));
    }
}




