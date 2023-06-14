#include <stdio.h>
#include "costanti.h"
#include "partita.h"
#include "giocatore.h"
#include "stampare_percorso.h"
#include "generare_percorso.h"
#include "gestire_stampa.h"


void stampare_percorso (partita* partita_attuale) {
    
    //Stampa il titolo del percorso
    stampare_parte_superiore_casella ();
    
    int indice_riga_tabellone_superiore = 0; //L'indice della riga, costituita da caselle, del tabellone, a partire dall'alto

    int indice_riga_tabellone_inferiore = ALTEZZA_TABELLONE; //L'indice della riga, costituita da caselle, del tabellone, a partire dal basso
    
    int colonne_parte_sinistra = 0; //Il numero di caselle da stampare nella parte sinistra del tabellone

    int colonne_parte_destra = 0; //Il numero di caselle da stampare nella parte destra del tabellone
    
    int ultima_casella_stampata; //Indica il numero dell'ultima casella stampata

    int meta_righe = calcolare_parte_intera (ALTEZZA_TABELLONE / 2); //Il numero della riga centrale, costituita da caselle, del tabellone


    //Mentre il tabellone non è ancora stato stampato per intero
    while (indice_riga_tabellone_superiore < ALTEZZA_TABELLONE) {
        
        int indice_altezza_disegno = 1; //L'indice che indica la riga, costituita da caratteri, di una casella che si sta stampando 

        //Mentre la casella non è stata stampata per intero
        while (indice_altezza_disegno <= ALTEZZA_DISEGNO_CASELLA) {
            ultima_casella_stampata = 0;

            //Verifica se ci sono colonne nella parte sinistra del tabellone da stampare, in tal caso le stampa
            if (colonne_parte_sinistra > 0) {

                //Verifica che non si è superata la metà del tabellone, in tal caso chiama la funzione per la stampa delle caselle della parte superiore sinistra del tabellone . . .
                if ( indice_riga_tabellone_superiore < (meta_righe + 1) ) {
                    ultima_casella_stampata = stampare_superiore_sinistra (partita_attuale, colonne_parte_sinistra, 0, indice_altezza_disegno);
                } 
                else { //. . . altrimenti chiama la funzione per la stampa delle caselle della parte inferiore sinistra del tabellone
                    ultima_casella_stampata = stampare_inferiore_sinistra (partita_attuale, colonne_parte_sinistra, 0, indice_altezza_disegno);
                }
            }

            //Verifica che non si è superata la metà del tabellone, in tal caso chiama la funzione per la stampa delle caselle della parte superiore centrale del tabellone . . .
            if ( indice_riga_tabellone_superiore <= (meta_righe - 1) ) {
                ultima_casella_stampata = stampare_parte_centrale_incremento ( partita_attuale, ultima_casella_stampata, (LARGHEZZA_TABELLONE - colonne_parte_destra - colonne_parte_sinistra), indice_altezza_disegno );
            }
            else { //. . . altrimenti chiama la funzione per la stampa delle caselle della parte inferiore sinistra del tabellone
                ultima_casella_stampata = stampare_parte_centrale_decremento ( partita_attuale, ultima_casella_stampata - ( ALTEZZA_TABELLONE - ( 2 * (colonne_parte_sinistra) ) ), (LARGHEZZA_TABELLONE - colonne_parte_destra - colonne_parte_sinistra), indice_altezza_disegno );
            }
            if (colonne_parte_destra > 0) {
                if ( indice_riga_tabellone_superiore <= (meta_righe - 1) ) {
                    stampare_parte_destra (partita_attuale, colonne_parte_destra, ultima_casella_stampata, 0, indice_altezza_disegno);
                }
                else {
                    stampare_parte_destra (partita_attuale, colonne_parte_destra - 1, ultima_casella_stampata, 0, indice_altezza_disegno);
                }
            }

            printf ("%c", CONTORNO_LATERALE_CASELLA); fflush (stdout);
            printf ("%c", CARATTERE_A_CAPO); fflush (stdout);

            indice_altezza_disegno = indice_altezza_disegno + 1;
        }


        if ( indice_riga_tabellone_superiore < (indice_riga_tabellone_inferiore - 1) ) {
            colonne_parte_sinistra = colonne_parte_sinistra + 1;
            colonne_parte_destra = colonne_parte_destra + 1;
        } else if ( indice_riga_tabellone_superiore > (indice_riga_tabellone_inferiore - 1) ) {
            colonne_parte_sinistra = colonne_parte_sinistra - 1;
            colonne_parte_destra = colonne_parte_destra - 1;
        }

        indice_riga_tabellone_superiore = indice_riga_tabellone_superiore + 1;
        indice_riga_tabellone_inferiore = indice_riga_tabellone_inferiore - 1;
    }
    return;
}

void stampare_parte_superiore_casella () {

    printf ("%s", TITOLO_PERCORSO);
    fflush (stdout);
    printf ("%c", CARATTERE_A_CAPO);
    fflush (stdout);
    return;
}

int stampare_superiore_sinistra (partita* partita_attuale, int numero_colonne, int contatore, int strato) {

    int ultima_casella_stampata = ( ( LARGHEZZA_TABELLONE - ( 1 + ( 2 * ( numero_colonne - contatore - 1 ) ) ) ) * 2 )  + ( ( ALTEZZA_TABELLONE - ( 1 + ( 2 * ( numero_colonne - contatore - 1 ) ) ) ) * 2 );

    if ( (numero_colonne - contatore) > 1 ) {
        ultima_casella_stampata = ultima_casella_stampata + stampare_superiore_sinistra (partita_attuale, numero_colonne, contatore + 1, strato);
    }
    stampare_casella (partita_attuale, ultima_casella_stampata - contatore, strato);
    return ultima_casella_stampata;
}

int stampare_inferiore_sinistra (partita* partita_attuale, int numero_colonne, int contatore, int strato) {
    int ultima_casella_stampata = ( (LARGHEZZA_TABELLONE - ( 1 + ( 2 * ( numero_colonne - contatore - 1 ) ) ) ) * 2 )  + ( ( ALTEZZA_TABELLONE - ( 1 + ( 2 * ( numero_colonne - contatore - 1 ) ) ) ) * 2 );

    if ( (numero_colonne - contatore) > 1 ) {
        ultima_casella_stampata = ultima_casella_stampata + stampare_inferiore_sinistra (partita_attuale, numero_colonne, contatore + 1, strato);
    }
    stampare_casella ( partita_attuale, ultima_casella_stampata  - ( ALTEZZA_TABELLONE - ( 2 * ( numero_colonne - contatore ) ) ) + contatore, strato );
    return ultima_casella_stampata;
}

int stampare_parte_destra (partita* partita_attuale, int numero_colonne, int numero_iniziale, int contatore, int strato) {
    int ultima_casella_stampata = numero_iniziale;
    while (contatore < numero_colonne) {
        ultima_casella_stampata = ultima_casella_stampata - ( ( ( LARGHEZZA_TABELLONE + ALTEZZA_TABELLONE ) * 2 ) - ( 3 * 2 ) - ( 4 * 2 * ( numero_colonne - contatore - 1 ) ) );
        stampare_casella ( partita_attuale, ( ultima_casella_stampata + contatore + 1 ), strato );
        contatore = contatore + 1;
    }
    return ultima_casella_stampata;
}

int stampare_parte_centrale_incremento (partita* partita_attuale, int valore_iniziale, int numero_colonne, int strato) {
    int i = 0;
    while (i < numero_colonne) {
        valore_iniziale = valore_iniziale + 1;
        stampare_casella (partita_attuale, valore_iniziale, strato);
        i = i + 1;
    }
    return valore_iniziale;
}

int stampare_parte_centrale_decremento (partita* partita_attuale, int valore_iniziale, int numero_colonne, int strato) {
    int i = 0;
    while (i <= numero_colonne) {
        valore_iniziale = valore_iniziale - 1;
        stampare_casella (partita_attuale, valore_iniziale, strato);
        i = i + 1;
    }
    return valore_iniziale;
}

void stampare_casella (partita* partita_attuale, int ultima_casella_stampata, int strato) {
    if (strato == 1) {
        printf ("%c", CONTORNO_LATERALE_CASELLA);
        stampare_giocatori_superiori_casella (partita_attuale, ultima_casella_stampata);
    } else if (strato == 2) {
        printf ("%c", CONTORNO_LATERALE_CASELLA);
        stampare_contenuto_casella (partita_attuale,ultima_casella_stampata);
    } else if (strato == 3) {
        printf ("%c", CONTORNO_LATERALE_CASELLA);
        stampare_giocatori_inferiori_casella (partita_attuale,ultima_casella_stampata);
    }
    return;
}



void stampare_contenuto_casella (partita* partita_attuale, int numero_casella) {
    if ( ( leggere_numero_casella ( leggere_casella_percorso (*partita_attuale, numero_casella - 1) ) <= leggere_lunghezza_percorso (*partita_attuale) ) && ( leggere_numero_casella ( leggere_casella_percorso (*partita_attuale, numero_casella - 1) ) > 0 ) ) {
        if ( leggere_carattere_casella ( leggere_casella_percorso (*partita_attuale, numero_casella - 1) , 0 ) == FINE_STRINGA ) {
            printf ("%c", CARATTERE_SPAZIO);
            printf ("%d", leggere_numero_casella ( leggere_casella_percorso (*partita_attuale, numero_casella - 1) ) );
            if ( leggere_numero_casella ( leggere_casella_percorso (*partita_attuale, numero_casella - 1) ) < NUMERO_CIFRE ) {
                printf ("%c", CARATTERE_SPAZIO);
            }
            printf ("%c", CARATTERE_SPAZIO);
        } 
        else {
            char simbolo [DIMENSIONE_MASSIMA_SIMBOLO_CASELLA];
            leggere_simbolo ( leggere_casella_percorso (*partita_attuale, numero_casella - 1), simbolo );
            printf ("%s", simbolo);
            fflush (stdout);
        }
    } 
    else {
        printf ("%s", SIMBOLO_VUOTO);
    }
    return;
}



//Stampa i giocatori nella parte superirore di una casella
void stampare_giocatori_superiori_casella (partita* partita_attuale, int numero_casella) {
    if ( leggere_posizione_giocatore ( leggere_giocatore ( *partita_attuale, POSIZIONE_GIOCATORE_1 ) ) == numero_casella ) {
        cambiare_colore_testo ( COLORI_GIOCATORI [POSIZIONE_GIOCATORE_1] );
        printf ( "%c", leggere_pedina_giocatore ( leggere_giocatore ( *partita_attuale, POSIZIONE_GIOCATORE_1 ) ) );
        cambiare_colore_testo (COLORE_PRINCIPALE_SCHERMATA);
    }
    else {
        printf ("%c", CARATTERE_SPAZIO);
    }
    int indice_spazio = 1;
    while ( indice_spazio <= (SPAZIO_DISPONIBILE_CASELLA - NUMERO_GIOCATORI_STRATO_CASELLA) ) {
        printf ("%c", CARATTERE_SPAZIO);
        indice_spazio = indice_spazio + 1;
    }
    if ( leggere_posizione_giocatore (leggere_giocatore ( *partita_attuale, POSIZIONE_GIOCATORE_2 ) ) == numero_casella ) {
        cambiare_colore_testo ( COLORI_GIOCATORI [POSIZIONE_GIOCATORE_2] );
        printf ( "%c", leggere_pedina_giocatore ( leggere_giocatore ( *partita_attuale, POSIZIONE_GIOCATORE_2 ) ) );
        cambiare_colore_testo (COLORE_PRINCIPALE_SCHERMATA);
    }
    else {
        printf ("%c", CARATTERE_SPAZIO);
    }
    return;
}



//Stampa i giocatori nella parte inferiore di una casella
void stampare_giocatori_inferiori_casella (partita* partita_attuale, int numero_casella) {
    if ( leggere_pedina_giocatore ( leggere_giocatore ( *partita_attuale, POSIZIONE_GIOCATORE_3 ) ) != FINE_STRINGA ) {
        if ( leggere_posizione_giocatore ( leggere_giocatore ( *partita_attuale, POSIZIONE_GIOCATORE_3 ) ) == numero_casella ) {
            cambiare_colore_testo ( COLORI_GIOCATORI [POSIZIONE_GIOCATORE_3] );
            printf( "%c", leggere_pedina_giocatore ( leggere_giocatore ( *partita_attuale, POSIZIONE_GIOCATORE_3 ) ) );
            cambiare_colore_testo (COLORE_PRINCIPALE_SCHERMATA);
        } 
        else {
            printf ("%c", CONTORNO_INFERIORE_CASELLA);                  
        }           
    }
    else {
        printf ("%c", CONTORNO_INFERIORE_CASELLA);
    }
    int indice_spazio = 1;
    while ( indice_spazio <= (SPAZIO_DISPONIBILE_CASELLA - NUMERO_GIOCATORI_STRATO_CASELLA ) ) {
        printf ("%c", CONTORNO_INFERIORE_CASELLA);
        indice_spazio = indice_spazio + 1;
    }
    if ( leggere_pedina_giocatore ( leggere_giocatore ( *partita_attuale, POSIZIONE_GIOCATORE_4 ) ) != FINE_STRINGA ) {
        if ( leggere_posizione_giocatore( leggere_giocatore ( *partita_attuale, POSIZIONE_GIOCATORE_4 ) ) == numero_casella) {
            cambiare_colore_testo ( COLORI_GIOCATORI [POSIZIONE_GIOCATORE_4] );
            printf ( "%c", leggere_pedina_giocatore ( leggere_giocatore ( *partita_attuale, POSIZIONE_GIOCATORE_4 ) ) );
            cambiare_colore_testo (COLORE_PRINCIPALE_SCHERMATA);
        } 
        else {
            printf ("%c", CONTORNO_INFERIORE_CASELLA);
        }
    }
    else {
        printf ("%c", CONTORNO_INFERIORE_CASELLA);
    }
    return;
}