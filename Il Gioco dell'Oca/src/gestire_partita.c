/*
 * gestire_partita.c
 *
 */

#include <stdio.h>
#include <string.h>
#include "casella.h"
#include "giocatore.h"
#include "partita.h"
#include "vincitore.h"
#include "costanti.h"
#include "gestire_partita.h"
#include "generare_numero_casuale.h"
#include "generare_percorso.h"
#include "gestire_stampa.h"
#include "stampare_percorso.h"
#include "salvare_caricare_partita.h"
#include "aiuto.h"



void scegliere_giocatore_iniziale (partita* partita_attuale, int * sale);
vincitore inizializzare_vincitore (partita* partita_attuale, int * sale);
int trovare_posizione_massimo (const int valori[], int dimensione_valori);
void cambiare_turno (partita* partita_attuale);
void lanciare_dadi (partita* partita_attuale, int sale);
void incrementare_lanci_effettuati (partita* partita_attuale);
void spostare_giocatore (partita* partita_attuale);
void sommare_lancio_posizione (partita* partita_attuale);
void calcolare_caselle_eccesso (partita* partita_attuale);
int sommare_dadi (partita partita_attuale);
void verificare_casella (partita* partita_attuale, int * sale);
void gestire_oca (partita* partita_attuale);
void impostare_autorizzazioni (partita* partita_attuale, const char nome_casella_attuale[]);
void gestire_autorizzazione (partita* partita_attuale, int * sale);
int scegliere_opzione_menu_di_pausa (int * sale);
int gestire_menu_di_pausa (partita* partita_attuale, int * sale);
void azzerare_vincitore (vincitore* vincitore_attuale);
int verificare_nomi_speciali (partita* partita_attuale);
void gestire_nome_speciale (partita* partita_attuale, int indice_nome_speciale, int* seme);


/*
gestire_partita: 
si occupa della gestione di una partita inizializzata, ovvero di una partita avente i campi
numero_giocatori, lunghezza_percorso, percorso, giocatori inizializzati

restituisce il vincitore della partita gestita

se si esce dalla partita prima che questa termini, verrà restituito un vincitore avente il campo
nome_vincitore inizializzato a FINE_STRINGA
*/
vincitore gestire_partita (partita* partita_attuale, int * sale) {
    int indietro;
    char scelta;
    vincitore vincitore_partita;
    //Verifica il turno della partita per vedere se la partita non è iniziata
    if ( leggere_turno (*partita_attuale) == TURNO_PARTITA_NON_INIZIATA ) {
        scegliere_giocatore_iniziale (partita_attuale, sale);
    }
    int nome_speciale = verificare_nomi_speciali (partita_attuale);
    if (nome_speciale == -1) {
        do {
            cambiare_turno (partita_attuale);
            if ( leggere_autorizzazione (leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) ) ) > AUTORIZZATO_A_LANCIARE_DADI) {
                gestire_autorizzazione (partita_attuale, sale);
            }

        //Verifica che il giocatore di turno sia autorizzato a lanciare i dadi
        if (leggere_autorizzazione (leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) ) ) == AUTORIZZATO_A_LANCIARE_DADI) {
            stampare_interfaccia_percorso (partita_attuale, FILE_PERCORSO);
            do {

                //Stampa l'opzione del menu di gioco per lanciare i dadi
                stampare_messaggio_valore (FILE_PERCORSO, SECONDO_VALORE);
                do {
                    inserire_simbolo (FILE_PERCORSO, &scelta, sale);
                    if ( (scelta != TASTO_LANCIO_DADI_MAIUSCOLO) && (scelta != TASTO_LANCIO_DADI_MINUSCOLO) && (scelta != TASTO_MENU_MAIUSCOLO) && (scelta != TASTO_MENU_MINUSCOLO) ) {
                        stampare_messaggio_errore(FILE_PERCORSO);
                    }
                } while ( (scelta != TASTO_LANCIO_DADI_MAIUSCOLO) && (scelta != TASTO_LANCIO_DADI_MINUSCOLO) && (scelta != TASTO_MENU_MAIUSCOLO) && (scelta != TASTO_MENU_MINUSCOLO) );

                if ( (scelta == TASTO_LANCIO_DADI_MAIUSCOLO) || (scelta == TASTO_LANCIO_DADI_MINUSCOLO) ) {
                    lanciare_dadi (partita_attuale, *sale);
                    incrementare_lanci_effettuati (partita_attuale);
                    stampare_dadi_partita (FILE_PERCORSO, partita_attuale);
                    do {

                        //Stampa l'opzione del menu di gioco per far avanzare la pedina
                        stampare_messaggio_valore (FILE_PERCORSO, TERZO_VALORE);
                        do {
                            inserire_simbolo(FILE_PERCORSO, &scelta, sale);
                            if ( (scelta != TASTO_AVANZAMENTO_MAIUSCOLO) && (scelta != TASTO_AVANZAMENTO_MINUSCOLO) && (scelta != TASTO_MENU_MAIUSCOLO) && (scelta != TASTO_MENU_MINUSCOLO) ) {
                                stampare_messaggio_errore(FILE_PERCORSO);
                            }
                        } while ( (scelta != TASTO_AVANZAMENTO_MAIUSCOLO) && (scelta != TASTO_AVANZAMENTO_MINUSCOLO) && (scelta != TASTO_MENU_MAIUSCOLO) && (scelta != TASTO_MENU_MINUSCOLO) );

                        //Verifica se si è premuto il tasto avanza
                        if ( (scelta == TASTO_AVANZAMENTO_MAIUSCOLO) || (scelta == TASTO_AVANZAMENTO_MINUSCOLO) ) {
                            spostare_giocatore (partita_attuale);

                            //Stampa il percorso con la pedina spostata
                            stampare_interfaccia_percorso (partita_attuale, FILE_PERCORSO);
                            posizionare_cursore_in_attesa (FILE_PERCORSO);
                            fgetc (stdin);
                            fflush (stdin);
                            *sale = *sale + 1;
                            verificare_casella (partita_attuale, sale);
                            stampare_interfaccia_percorso (partita_attuale, FILE_PERCORSO);
                            posizionare_cursore_in_attesa (FILE_PERCORSO);
                            //Stampa il messaggio per passare il turno al giocatore successivo

                            if ( ( leggere_posizione_giocatore (leggere_giocatore (*partita_attuale, leggere_turno(*partita_attuale) ) ) ) != leggere_lunghezza_percorso (*partita_attuale) ) {
                                stampare_schermata_cambio_turno (*partita_attuale);
                                attendere_tasto_zero (FILE_CAMBIO_TURNO, sale);
                            }
                        }
                        else {
                            indietro = gestire_menu_di_pausa (partita_attuale, sale);
                            stampare_interfaccia_percorso (partita_attuale, FILE_PERCORSO);
                        }
                    } while (indietro == 1);
                }
                else {
                    indietro = gestire_menu_di_pausa (partita_attuale, sale);
                    stampare_interfaccia_percorso (partita_attuale, FILE_PERCORSO);
                }
            } while (indietro == 1);

        }

        } while (leggere_posizione_giocatore (leggere_giocatore(*partita_attuale, leggere_turno(*partita_attuale) ) ) !=
                 leggere_lunghezza_percorso (*partita_attuale) && (indietro != 0));

        //Verifica se un giocatore ha vinto oppure se si desidera tornare indietro

        if ( leggere_posizione_giocatore (leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) ) ) == leggere_lunghezza_percorso (*partita_attuale) ) {
            vincitore_partita = inizializzare_vincitore (partita_attuale, sale);
        } 
        else {
            azzerare_vincitore (&vincitore_partita);
        }
    } 
    else {
        gestire_nome_speciale (partita_attuale, nome_speciale, sale);
        azzerare_vincitore (&vincitore_partita);
    }

    return vincitore_partita;
}



int gestire_menu_di_pausa (partita* partita_attuale, int * sale) {
    char uscita;
    int scelta;
    do {
        scelta = scegliere_opzione_menu_di_pausa (sale);
        if (scelta == 2) {
            salvare_partita (partita_attuale, sale);
        } else if (scelta == 3) {
                chiedere_aiuto (sale);
            } else if (scelta == 0) {
                    stampare_testo (FILE_RICHIESTA_USCITA);
                    attendere_simbolo_risposta (FILE_RICHIESTA_USCITA, &uscita, sale);
                }
    } while ( (scelta != 1) && (uscita != RISPOSTA_AFFERMATIVA_MAIUSCOLO) && (uscita != RISPOSTA_AFFERMATIVA_MINUSCOLO) );
    return scelta;
}




int scegliere_opzione_menu_di_pausa (int * sale) {
    int scelta;
    stampare_testo (FILE_MENU_DI_PAUSA);
    do {
        verificare_correttezza_inserimento (FILE_MENU_DI_PAUSA, &scelta, sale);
        if ( (scelta < 0) || (scelta > NUMERO_MASSIMO_OPZIONE_PAUSA) ) {
            stampare_messaggio_errore (FILE_MENU_DI_PAUSA);
        }
    } while ( (scelta < 0) || (scelta > NUMERO_MASSIMO_OPZIONE_PAUSA) );
    return scelta;
}



void scegliere_giocatore_iniziale (partita* partita_attuale, int * sale) {
    char scelta;
    int estrazioni [NUMERO_MASSIMO_GIOCATORI];
    int indice_giocatori = 0;
    char nome_giocatore [DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    while (indice_giocatori < leggere_numero_giocatori (*partita_attuale) ) {
        stampare_testo (FILE_SCELTA_G_INIZIALE);
        leggere_nome_giocatore (leggere_giocatore (*partita_attuale,indice_giocatori), nome_giocatore);
        //Stampa il nome del giocatore centrato nella schermata del lancio dei dadi
        stampare_valore_testuale_centrato (FILE_SCELTA_G_INIZIALE, nome_giocatore, PRIMO_VALORE, DIMENSIONE_MASSIMA_NOME_GIOCATORE);
        do{
            inserire_simbolo (FILE_SCELTA_G_INIZIALE, &scelta, sale);
            if( (scelta != TASTO_CONFERMA) && (scelta != TASTO_LANCIO_DADI_MAIUSCOLO) && (scelta != TASTO_LANCIO_DADI_MINUSCOLO) ) {
                stampare_messaggio_errore(FILE_SCELTA_G_INIZIALE);
            }
        } while ( (scelta != TASTO_CONFERMA) && (scelta != TASTO_LANCIO_DADI_MAIUSCOLO) && (scelta != TASTO_LANCIO_DADI_MINUSCOLO) );

        estrazioni [indice_giocatori] = generare_numero (FACCIA_MASSIMA_DADO, FACCIA_MINIMA_DADO, *sale);
        stampare_dado (FILE_SCELTA_G_INIZIALE, estrazioni [indice_giocatori]);
        posizionare_cursore_in_attesa (FILE_SCELTA_G_INIZIALE);
        inserire_simbolo (FILE_SCELTA_G_INIZIALE, &scelta, sale);
        indice_giocatori = indice_giocatori + 1;
    }
    scrivere_turno (partita_attuale, trovare_posizione_massimo (estrazioni, leggere_numero_giocatori (*partita_attuale)) - 1);
    return;
}



vincitore inizializzare_vincitore (partita* partita_attuale, int * sale) {
    //Converte il vincitore della partita
    vincitore vincitore_partita;
    char nome_vincitore [DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    leggere_nome_giocatore (leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale)), nome_vincitore);
    scrivere_nome_vincitore (&vincitore_partita, nome_vincitore);
    scrivere_pedina_vincitore (&vincitore_partita, leggere_pedina_giocatore (leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) ) ) );
    scrivere_lanci_vincitore (&vincitore_partita, leggere_lanci_effettuati (leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) ) ) );
    scrivere_lunghezza_percorso_vincitore (&vincitore_partita, leggere_lunghezza_percorso (*partita_attuale) );
    cancellare_schermata ();
    stampare_vittoria (FILE_VITTORIA_NOMI);
    char nome_giocatore [DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    leggere_nome_giocatore (leggere_giocatore ( *partita_attuale, leggere_turno (*partita_attuale) ), nome_giocatore);
    //Stampa il nome del vincitore colorato e centrato sulla raffigurazione della coppa
    cambiare_colore_testo (COLORI_GIOCATORI [leggere_turno (*partita_attuale)] );
    stampare_valore_testuale_centrato (FILE_VITTORIA_NOMI, nome_vincitore, PRIMO_VALORE, DIMENSIONE_MASSIMA_NOME_GIOCATORE);
    cambiare_colore_testo (COLORE_PRINCIPALE_SCHERMATA);
    attendere_tasto_zero (FILE_VITTORIA_NOMI, sale);
    //Stampa la schermata dei crediti
    stampare_testo(FILE_CREDITI);
    attendere_tasto_zero (FILE_CREDITI, sale);
    return vincitore_partita;
}



void azzerare_vincitore (vincitore* vincitore_attuale) {
    scrivere_carattere_nome_vincitore (vincitore_attuale, 0, FINE_STRINGA);
    scrivere_pedina_vincitore (vincitore_attuale, 0);
    scrivere_lanci_vincitore (vincitore_attuale, 0);
    scrivere_lunghezza_percorso_vincitore (vincitore_attuale, 0);
    scrivere_punteggio (vincitore_attuale, 0.0);
    return;
}



int trovare_posizione_massimo (const int valori[], int dimensione_valori) {
    int indice_valori = 0;
    int massimo = valori [indice_valori];
    int posizione_massimo = indice_valori;
    while (indice_valori < dimensione_valori - 1) {
        indice_valori = indice_valori + 1;
        if (massimo < valori [indice_valori]) {
            massimo = valori [indice_valori];
            posizione_massimo = indice_valori;
        }
    }
    return posizione_massimo;
}



void cambiare_turno (partita* partita_attuale) {
    scrivere_turno (partita_attuale, leggere_turno (*partita_attuale) + 1);
    if ( leggere_turno (*partita_attuale) >= leggere_numero_giocatori (*partita_attuale) ) {
        scrivere_turno (partita_attuale, 0);
    }
    return;
}



void lanciare_dadi (partita* partita_attuale, int sale) {
    int indice_dado = 0;
    int lancio;
    while (indice_dado < NUMERO_DADI) {
        scanf("%d", &lancio);
        //lancio = generare_numero (FACCIA_MASSIMA_DADO, FACCIA_MINIMA_DADO, sale);
        scrivere_dadi (partita_attuale, lancio, indice_dado);
        indice_dado = indice_dado + 1;
    }
    return;
}



void incrementare_lanci_effettuati (partita* partita_attuale) {
    giocatore giocatore_attuale;
    int lanci_effettuati;
    giocatore_attuale = leggere_giocatore ( *partita_attuale, leggere_turno (*partita_attuale) );
    lanci_effettuati = leggere_lanci_effettuati (giocatore_attuale);
    lanci_effettuati = lanci_effettuati + 1;
    scrivere_lanci_effettuati (&giocatore_attuale, lanci_effettuati);
    scrivere_giocatore ( partita_attuale, giocatore_attuale, leggere_turno (*partita_attuale) );
    return;
}



void spostare_giocatore (partita* partita_attuale) {
    sommare_lancio_posizione (partita_attuale);
    if ( leggere_posizione_giocatore (leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) ) ) > leggere_lunghezza_percorso (*partita_attuale) ) {
        calcolare_caselle_eccesso (partita_attuale);
    }
    return;
}



void sommare_lancio_posizione (partita* partita_attuale) {
    giocatore giocatore_attuale = leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) );
    scrivere_posizione_giocatore (&giocatore_attuale, leggere_posizione_giocatore (giocatore_attuale) + sommare_dadi (*partita_attuale) );
    scrivere_giocatore ( partita_attuale, giocatore_attuale, leggere_turno (*partita_attuale) );
    return;
}



void calcolare_caselle_eccesso (partita* partita_attuale){
    giocatore giocatore_attuale;
    giocatore_attuale = leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) );
    int eccesso = leggere_posizione_giocatore (giocatore_attuale ) - leggere_lunghezza_percorso (*partita_attuale);
    scrivere_posizione_giocatore (&giocatore_attuale, leggere_lunghezza_percorso (*partita_attuale) - eccesso);
    scrivere_giocatore (partita_attuale, giocatore_attuale, leggere_turno (*partita_attuale) );
    return;
}



int sommare_dadi (partita partita_attuale) {
    int somma_dadi = 0;
    int indice_dado = 0;
    while (indice_dado < NUMERO_DADI) {
        somma_dadi = somma_dadi + leggere_dadi (partita_attuale, indice_dado);
        indice_dado = indice_dado + 1;
    }
    return somma_dadi;
}



void verificare_casella (partita* partita_attuale, int * sale) {
    giocatore giocatore_attuale;
    char nome_casella [DIMENSIONE_MASSIMA_NOME_CASELLA];
    do{
        giocatore_attuale = leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) );
        leggere_nome_casella (leggere_casella_percorso (*partita_attuale, leggere_posizione_giocatore (giocatore_attuale) - 1), nome_casella);
        if (confrontare_stringhe (nome_casella, NOME_OCA) == VERO) {
            stampare_testo (FILE_SCHERMATA_OCA);
            attendere_tasto_zero (FILE_SCHERMATA_OCA, sale);
            gestire_oca (partita_attuale);
        } else if (confrontare_stringhe (nome_casella, NOME_PONTE) == VERO) {
            stampare_testo (FILE_SCHERMATA_PONTE);
            attendere_tasto_zero (FILE_SCHERMATA_PONTE, sale);
            spostare_giocatore (partita_attuale);
        } else if (confrontare_stringhe(nome_casella, NOME_LOCANDA) == VERO) {
            stampare_testo(FILE_SCHERMATA_LOCANDA);
            attendere_tasto_zero (FILE_SCHERMATA_LOCANDA, sale);
            scrivere_autorizzazione (&giocatore_attuale, TURNI_ATTESA_LOCANDA);
            scrivere_giocatore ( partita_attuale, giocatore_attuale, leggere_turno (*partita_attuale) );
        } else if (confrontare_stringhe (nome_casella, NOME_POZZO) == VERO) {
            stampare_testo (FILE_SCHERMATA_POZZO);
            attendere_tasto_zero (FILE_SCHERMATA_POZZO, sale);
            impostare_autorizzazioni (partita_attuale, NOME_POZZO);
        } else if (confrontare_stringhe (nome_casella, NOME_PRIGIONE) == VERO) {
            stampare_testo (FILE_SCHERMATA_PRIGIONE);
            attendere_tasto_zero (FILE_SCHERMATA_PRIGIONE, sale);
            impostare_autorizzazioni (partita_attuale, NOME_PRIGIONE);
        } else if (confrontare_stringhe (nome_casella, NOME_LABIRINTO) == VERO) {
            scrivere_posizione_giocatore (&giocatore_attuale, calcolare_proporzione (*partita_attuale, CASELLA_ARRIVO_LABIRINTO) );
            leggere_nome_casella (leggere_casella_percorso (*partita_attuale, leggere_posizione_giocatore (giocatore_attuale) - 1), nome_casella);
            while (nome_casella[0] != FINE_STRINGA){
                leggere_nome_casella (leggere_casella_percorso (*partita_attuale, leggere_posizione_giocatore (giocatore_attuale) - 1), nome_casella);
                scrivere_posizione_giocatore (&giocatore_attuale, leggere_posizione_giocatore (giocatore_attuale) - 1);
            }
            scrivere_giocatore (partita_attuale, giocatore_attuale, leggere_turno (*partita_attuale) );
            stampare_testo (FILE_SCHERMATA_LABIRINTO);
            stampare_valore_intero(FILE_SCHERMATA_LABIRINTO, leggere_posizione_giocatore(giocatore_attuale), PRIMO_VALORE);
            attendere_tasto_zero (FILE_SCHERMATA_LABIRINTO, sale);
        } else if (confrontare_stringhe (nome_casella, NOME_SCHELETRO) == VERO ) {
            stampare_testo (FILE_SCHERMATA_SCHELETRO);
            attendere_tasto_zero(FILE_SCHERMATA_SCHELETRO, sale);
            scrivere_posizione_giocatore (&giocatore_attuale, CASELLA_ARRIVO_SCHELETRO);
            scrivere_giocatore (partita_attuale, giocatore_attuale, leggere_turno (*partita_attuale) );
        }
        //stampare percorso e aspettare input
        giocatore_attuale = leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) );
        leggere_nome_casella(leggere_casella_percorso (*partita_attuale, leggere_posizione_giocatore (giocatore_attuale) - 1), nome_casella);
    } while ( (nome_casella [0] != FINE_STRINGA) && (leggere_autorizzazione (giocatore_attuale) == 0) && (leggere_posizione_giocatore (giocatore_attuale) != leggere_lunghezza_percorso (*partita_attuale) ) );
    return;
}



void gestire_oca (partita* partita_attuale) {
    giocatore giocatore_attuale = leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) );
    if (leggere_lanci_effettuati (giocatore_attuale) == 1) {
        if ( (leggere_dadi (*partita_attuale, PRIMO_DADO) == DADO_MINORE_PRIMO_LANCIO) || (leggere_dadi (*partita_attuale, PRIMO_DADO) == DADO_MAGGIORE_PRIMO_LANCIO) ) {
            scrivere_posizione_giocatore (&giocatore_attuale, calcolare_proporzione (*partita_attuale, PRIMO_LANCIO_3_6) );
        }
        else {
            scrivere_posizione_giocatore (&giocatore_attuale, calcolare_proporzione (*partita_attuale, PRIMO_LANCIO_4_5) );
        }
        char nome_casella [DIMENSIONE_MASSIMA_NOME_CASELLA];
        leggere_nome_casella (leggere_casella_percorso (*partita_attuale, leggere_posizione_giocatore (giocatore_attuale) - 1), nome_casella);
        while (nome_casella [0] != FINE_STRINGA) {
            leggere_nome_casella (leggere_casella_percorso (*partita_attuale, leggere_posizione_giocatore (giocatore_attuale) - 1), nome_casella);
            scrivere_posizione_giocatore (&giocatore_attuale, leggere_posizione_giocatore (giocatore_attuale) - 1);
        }
        scrivere_giocatore (partita_attuale, giocatore_attuale, leggere_turno (*partita_attuale) );
    }
    else {
        spostare_giocatore (partita_attuale);
    }
    return;
}



void impostare_autorizzazioni (partita* partita_attuale, const char nome_casella_attuale []) {
    giocatore giocatore_attuale;
    int indice_giocatore = 0;
    while ( indice_giocatore < leggere_numero_giocatori (*partita_attuale) ) {
        giocatore_attuale = leggere_giocatore (*partita_attuale, indice_giocatore);
        char nome_casella [DIMENSIONE_MASSIMA_NOME_CASELLA];
        leggere_nome_casella (leggere_casella_percorso (*partita_attuale, leggere_posizione_giocatore (giocatore_attuale) - 1), nome_casella);
        if (confrontare_stringhe (nome_casella, nome_casella_attuale) == VERO) {
            scrivere_autorizzazione (&giocatore_attuale, AUTORIZZATO_A_LANCIARE_DADI);
            scrivere_giocatore (partita_attuale, giocatore_attuale, indice_giocatore);
        }
        indice_giocatore = indice_giocatore + 1;
    }
    giocatore_attuale = leggere_giocatore (*partita_attuale, leggere_turno (*partita_attuale) );
    scrivere_autorizzazione (&giocatore_attuale, 1);
    scrivere_giocatore (partita_attuale, giocatore_attuale, leggere_turno (*partita_attuale) );
    return;
}



void gestire_autorizzazione (partita* partita_attuale, int * sale) {
    giocatore giocatore_attuale = leggere_giocatore ( *partita_attuale, leggere_turno (*partita_attuale) );
    char nome_casella [DIMENSIONE_MASSIMA_NOME_CASELLA];
    leggere_nome_casella (leggere_casella_percorso (*partita_attuale, leggere_posizione_giocatore (giocatore_attuale) - 1), nome_casella);

    //Se il giocatore si trova sulla casella locanda, decrementa l'autorizzazione di 1
    if (confrontare_stringhe (nome_casella, NOME_LOCANDA) == VERO) {
        //Stampa la schermata della locanda che mostra il turno passato e attende l'input dell'utente
        stampare_testo (FILE_SCHERMATA_LOCANDA_TURNO_PASSATO);
        stampare_valore_intero (FILE_SCHERMATA_LOCANDA_TURNO_PASSATO, leggere_autorizzazione (giocatore_attuale), PRIMO_VALORE);
        attendere_tasto_zero(FILE_SCHERMATA_LOCANDA_TURNO_PASSATO, sale);
        scrivere_autorizzazione (&giocatore_attuale, leggere_autorizzazione (giocatore_attuale) - 1);
    } else if (confrontare_stringhe (nome_casella, NOME_PRIGIONE) == VERO) { //Se il giocatore si trova sulla casella prigione, lancia i dadi
        //Stampa la schermata della prigione che mostra il lancio dei dadi e attende l'input dell'utente
        stampare_testo (FILE_SCHERMATA_LANCIO_DADI_PRIGIONE);

        char scelta;
        do {
            inserire_simbolo (FILE_SCHERMATA_LANCIO_DADI_PRIGIONE, &scelta, sale);
            if ( (scelta != TASTO_LANCIO_DADI_MAIUSCOLO) && (scelta != TASTO_LANCIO_DADI_MINUSCOLO) ) {
                stampare_messaggio_errore (FILE_SCHERMATA_LANCIO_DADI_PRIGIONE);
            }
        } while ( (scelta != TASTO_LANCIO_DADI_MAIUSCOLO) && (scelta != TASTO_LANCIO_DADI_MINUSCOLO) );

        lanciare_dadi (partita_attuale, *sale);


        //Stampa la schermata della prigione che mostra il lancio dei dadi con il lancio effettuato e richiedere l'input dell'utente
        stampare_dadi_partita (FILE_SCHERMATA_LANCIO_DADI_PRIGIONE, partita_attuale);

        do {
            inserire_simbolo (FILE_SCHERMATA_LANCIO_DADI_PRIGIONE, &scelta, sale);
            if ( (scelta != TASTO_AVANZAMENTO_MAIUSCOLO) && (scelta != TASTO_AVANZAMENTO_MINUSCOLO) ) {
                stampare_messaggio_errore (FILE_SCHERMATA_LANCIO_DADI_PRIGIONE);
            }
        } while ( (scelta != TASTO_AVANZAMENTO_MAIUSCOLO) && (scelta != TASTO_AVANZAMENTO_MINUSCOLO) );

        //Se la somma dei dadi coincide con quella per l'uscita dalla prigione
        if ( (sommare_dadi (*partita_attuale) == DADO_MINORE_USCITA_PRIGIONE) || (sommare_dadi (*partita_attuale) == DADO_MAGGIORE_USCITA_PRIGIONE) ) {
            //Stampa la schermata dell'uscita di prigione
            stampare_testo (FILE_SCHERMATA_LIBERATO);
            attendere_tasto_zero(FILE_SCHERMATA_LIBERATO, sale);
            scrivere_autorizzazione (&giocatore_attuale, AUTORIZZATO_A_LANCIARE_DADI);
        }
    } else if (confrontare_stringhe (nome_casella, NOME_POZZO) == VERO) {//Se il giocatore si trova sulla casella pozzo
        //Stampa la schermata che ricorda al giocatore che si trova nel pozzo
        stampare_testo (FILE_SCHERMATA_PERM_POZZO);
        attendere_tasto_zero(FILE_SCHERMATA_PERM_POZZO, sale);
    }
    scrivere_giocatore ( partita_attuale, giocatore_attuale, leggere_turno (*partita_attuale) );
    return;
}

int confrontare_stringhe (const char stringa_1 [], const char stringa_2 []) {
    int indice_stringa = 0;
    int esito = VERO;
    while ((stringa_2 [indice_stringa] != FINE_STRINGA) && (esito == VERO) ) {
        if (stringa_2 [indice_stringa] != stringa_1 [indice_stringa]) {
            esito = FALSO;
        }
        indice_stringa = indice_stringa + 1;
    }
    return esito;
}


int verificare_nomi_speciali (partita* partita_attuale) {
    char nome_giocatore[DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    int giocatore_con_nome_speciale = -1;
    int indice_nomi_speciali;
    int indice_giocatori = 0;
    while ( (indice_giocatori < leggere_numero_giocatori (*partita_attuale) ) && (giocatore_con_nome_speciale == -1) ) {
        leggere_nome_giocatore (leggere_giocatore (*partita_attuale, indice_giocatori), nome_giocatore);
        strlwr(nome_giocatore);
        indice_nomi_speciali = 0;
        while ( (indice_nomi_speciali < NUMERO_NOMI_SPECIALI) && (giocatore_con_nome_speciale == -1) ) {
            if ( (confrontare_stringhe (nome_giocatore, NOMI_SPECIALI[indice_nomi_speciali]) == VERO) && (giocatore_con_nome_speciale == -1) ) {
                giocatore_con_nome_speciale = indice_giocatori;
            }
            indice_nomi_speciali = indice_nomi_speciali + 1;
        }
        indice_giocatori = indice_giocatori + 1;
    }
    return giocatore_con_nome_speciale;
}



void gestire_nome_speciale (partita* partita_attuale, int indice_nome_speciale, int * sale) {
    stampare_testo(FILE_EASTEREGG1);
    attendere_tasto_zero(FILE_EASTEREGG1, sale);

    stampare_testo(FILE_EASTEREGG2);
    attendere_tasto_zero(FILE_EASTEREGG2, sale);

    stampare_vittoria (FILE_VITTORIA_NOMI);
    char nome_giocatore [DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    leggere_nome_giocatore (leggere_giocatore (*partita_attuale, indice_nome_speciale), nome_giocatore);
    //Stampa il nome del vincitore colorato e centrato sulla raffigurazione della coppa
    cambiare_colore_testo (VIOLETTO);
    stampare_valore_testuale_centrato (FILE_VITTORIA_NOMI, nome_giocatore, PRIMO_VALORE, DIMENSIONE_MASSIMA_NOME_GIOCATORE);
    cambiare_colore_testo (COLORE_PRINCIPALE_SCHERMATA);
    attendere_tasto_zero (FILE_VITTORIA_NOMI, sale);

    stampare_testo(FILE_CREDITI);
    attendere_tasto_zero(FILE_CREDITI, sale);
    cancellare_schermata ();
    return;
}