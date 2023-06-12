/*
 * gestire_stampa.c
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "gestire_stampa.h"
#include "costanti.h"
#include "stampare_percorso.h"
#include "inizializzare_partita.h"
#include "generare_percorso.h"


void stampare_dadi_partita(const char file_interfaccia[], partita* partita_attuale){
    int dadi_da_stampare[NUMERO_DADI];
    int indice_dadi = 0;
    while (indice_dadi < NUMERO_DADI){
        dadi_da_stampare[indice_dadi] = leggere_dadi(*partita_attuale, indice_dadi);
        indice_dadi = indice_dadi + 1;
    }
    stampare_dadi(file_interfaccia, dadi_da_stampare);
    return;
}


void stampare_dado(const char file_interfaccia[], int valore_faccia_dado){
    int dadi_da_stampare[NUMERO_DADI];
    dadi_da_stampare[0] = valore_faccia_dado;
    int indice_dadi = 1;
    while (indice_dadi < NUMERO_DADI){
        dadi_da_stampare[indice_dadi] = 0;
        indice_dadi = indice_dadi + 1;
    }
    stampare_dadi(file_interfaccia, dadi_da_stampare);
    return;
}


void stampare_dadi(const char file_interfaccia[], const int facce_dadi[]) {

	FILE *f_interfaccia = fopen(file_interfaccia, "r");
	if (f_interfaccia != NULL) {
        scorrere_righe_file(f_interfaccia, ALTEZZA_SCHERMATA + SPIAZZAMENTO_DADO);
		int posizione_riga;
		int posizione_colonna;
        int indice_puntini_dado;
		int indice_dadi = 0;
		while ((facce_dadi[indice_dadi] != 0) && (indice_dadi < NUMERO_DADI)) {
            indice_puntini_dado = 1;
			while (indice_puntini_dado <= NUMERO_MASSIMO_PUNTINI_FACCIA_DADO) {
				fscanf(f_interfaccia, "%d ", &posizione_riga);
                scorrere_righe_file(f_interfaccia, 1);
				fscanf(f_interfaccia, "%d ", &posizione_colonna);
                scorrere_righe_file(f_interfaccia, 1);
				posizionare_cursore(posizione_riga, posizione_colonna);
				if (indice_puntini_dado == 1) {
					if (facce_dadi[indice_dadi] == 6
							|| (facce_dadi[indice_dadi] == 5)
							|| (facce_dadi[indice_dadi] == 4)) {
						printf("%c", CARATTERE_PUNTO_FACCIA_DADO); fflush(stdin);
					} else {
						printf("%c", CARATTERE_SPAZIO); fflush(stdin);
					}
				} else if (indice_puntini_dado == 2) {
					if (facce_dadi[indice_dadi] == 6) {
						printf("%c", CARATTERE_PUNTO_FACCIA_DADO);
					} else {
						printf("%c", CARATTERE_SPAZIO); fflush(stdin);
					}
				} else if (indice_puntini_dado == 3) {
					if (facce_dadi[indice_dadi] == 6
                            || (facce_dadi[indice_dadi] == 5)
							|| (facce_dadi[indice_dadi] == 4)
							|| (facce_dadi[indice_dadi] == 3)
                            || (facce_dadi[indice_dadi] == 2)) {
						printf("%c", CARATTERE_PUNTO_FACCIA_DADO); fflush(stdin);
					} else {
						printf("%c", CONTORNO_INFERIORE_CASELLA); fflush(stdin);
					}
				} else if (indice_puntini_dado == 4) {
					if (facce_dadi[indice_dadi] == 5
							|| (facce_dadi[indice_dadi] == 3)
							|| (facce_dadi[indice_dadi] == 1)) {
						printf("%c", CARATTERE_PUNTO_FACCIA_DADO); fflush(stdin);
					} else if((facce_dadi[indice_dadi] == 6)
                              || (facce_dadi[indice_dadi] == 4)
                              || (facce_dadi[indice_dadi] == 2)){
                        printf("%c", CARATTERE_SPAZIO); fflush(stdin);
                    }else{
                        printf("%c", CARATTERE_PUNTO_INTERROGATIVO); fflush(stdin);
                    }
				} else if (indice_puntini_dado == 5) {
					if (facce_dadi[indice_dadi] == 6
							|| (facce_dadi[indice_dadi] == 5)
							|| (facce_dadi[indice_dadi] == 4)
							|| (facce_dadi[indice_dadi] == 3)
							|| (facce_dadi[indice_dadi] == 2)) {
						printf("%c", CARATTERE_PUNTO_FACCIA_DADO); fflush(stdin);
					} else {
						printf("%c", CARATTERE_SPAZIO); fflush(stdin);
					}
				} else if (indice_puntini_dado == 6) {
					if (facce_dadi[indice_dadi] == 6) {
						printf("%c", CARATTERE_PUNTO_FACCIA_DADO); fflush(stdin);
					} else {
						printf("%c", CARATTERE_SPAZIO); fflush(stdin);
					}
				} else if (indice_puntini_dado == 7) {
					if ((facce_dadi[indice_dadi] == 6)
							|| (facce_dadi[indice_dadi] == 5)
							|| (facce_dadi[indice_dadi] == 4)) {
						printf("%c", CARATTERE_PUNTO_FACCIA_DADO); fflush(stdin);
					} else {
						printf("%c", CONTORNO_INFERIORE_CASELLA); fflush(stdin);
					}
				}
				indice_puntini_dado = indice_puntini_dado + 1;
			}
			indice_dadi = indice_dadi + 1;
		}
		fclose(f_interfaccia);
	} else {
		printf("%s", ERRORE_FILE_NON_TROVATO); fflush(stdin);
		fflush(stdout);
		printf("%c", CARATTERE_SPAZIO); fflush(stdin);
		fflush(stdout);
		printf("%s", file_interfaccia); fflush(stdin);
		fflush(stdout);
	}
    return;
}

void stampare_testo (const char file_interfaccia[]) {

	FILE * f_interfaccia = fopen(file_interfaccia, "r");
	if (f_interfaccia != NULL) {
		char simbolo_letto;
		int indice_nuova_riga = 0;
		while (indice_nuova_riga < ALTEZZA_SCHERMATA) {
			simbolo_letto = fgetc(f_interfaccia);
			printf("%c", simbolo_letto); fflush(stdin);
			if (simbolo_letto == CARATTERE_A_CAPO) {
				indice_nuova_riga = indice_nuova_riga + 1;
			}
		}
		fclose(f_interfaccia);
	} else {
		printf("%s", ERRORE_FILE_NON_TROVATO); fflush(stdin);
		fflush(stdout);
		printf("%c", CARATTERE_SPAZIO); fflush(stdin);
		fflush(stdout);
		printf("%s", file_interfaccia); fflush(stdin);
		fflush(stdout);
	}
    return;
}

void stampare_messaggio_errore (const char file_interfaccia[]) {
	FILE *f_interfaccia = fopen(file_interfaccia, "r");
	if (f_interfaccia != NULL) {
        scorrere_righe_file(f_interfaccia, ALTEZZA_SCHERMATA + SPIAZZAMENTO_MESSAGGIO_ERRORE);
		int posizione_riga;
		int posizione_colonna;
		int codice_messaggio_errore;
		fscanf(f_interfaccia, "%d ", &posizione_riga);
        scorrere_righe_file(f_interfaccia, 1);
		fscanf(f_interfaccia, "%d ", &posizione_colonna);
        scorrere_righe_file(f_interfaccia, 1);
		fscanf(f_interfaccia, "%d ", &codice_messaggio_errore);
		fclose(f_interfaccia);


		posizionare_cursore(posizione_riga, posizione_colonna);
		FILE *f_messaggi_errore = fopen(FILE_MESSAGGI_ERRORE, "r");
		if (f_messaggi_errore != NULL) {
            scorrere_righe_file(f_interfaccia, codice_messaggio_errore - 1);
			char messaggio_errore[LUNGHEZZA_SCHERMATA + 1];
            fgets(messaggio_errore, (LUNGHEZZA_SCHERMATA + 1),f_messaggi_errore);
			fclose(f_messaggi_errore);
			printf("%s", messaggio_errore);
			fflush(stdin);
		} else {
			printf("%s", ERRORE_FILE_NON_TROVATO);
			fflush(stdin);
			printf("%c", CARATTERE_SPAZIO);
			fflush(stdin);
			printf("%s", FILE_MESSAGGI_ERRORE);
			fflush(stdin);
		}

	} else {
		printf("%s", ERRORE_FILE_NON_TROVATO);
		fflush(stdin);
		printf("%c", CARATTERE_SPAZIO);
		fflush(stdin);
		printf("%s", file_interfaccia);
		fflush(stdin);
	}
    return;
}

void posizionare_cursore(int posizione_riga, int posizione_colonna) {
	COORD coord;
	coord.X = posizione_colonna;
	coord.Y = posizione_riga - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    return;
}

void posizionare_cursore_in_attesa(const char file_interfaccia[]) {
	FILE *f_interfaccia = fopen(file_interfaccia, "r");
	if ( f_interfaccia != NULL ) {
        scorrere_righe_file(f_interfaccia, ALTEZZA_SCHERMATA);
		int posizione_riga;
		int posizione_colonna;
		fscanf (f_interfaccia, "%d ", &posizione_riga);
        scorrere_righe_file(f_interfaccia, 1);
		fscanf (f_interfaccia, "%d ", &posizione_colonna);
		posizionare_cursore (posizione_riga, posizione_colonna);
		fclose(f_interfaccia);
	} else {
		printf ("%s", ERRORE_FILE_NON_TROVATO); fflush(stdin);
		fflush (stdout);
		printf ("%c", CARATTERE_SPAZIO); fflush(stdin);
		fflush (stdout);
		printf ("%s", file_interfaccia); fflush(stdin);
		fflush (stdout);
	}
    return;
}


void scorrere_righe_file(FILE* file_testo, int numero_righe){
    char riga_letta [LUNGHEZZA_SCHERMATA + 1];
    int indice_riga = 0;
    while (indice_riga < numero_righe) {
        fgets(riga_letta, LUNGHEZZA_SCHERMATA + 1, file_testo);
        indice_riga = indice_riga + 1;
    }
    return;
}


void cancellare_schermata () {
    system("cls");
    return;
}


void stampare_valore_intero(const char file_interfaccia[], int valore, int posizione_valore){
    FILE *f_interfaccia = fopen(file_interfaccia, "r");
    if (f_interfaccia != NULL) {
        scorrere_righe_file(f_interfaccia, ALTEZZA_SCHERMATA + SPIAZZAMENTO_STAMPA_VALORI + ((posizione_valore - 1) * SPIAZZAMENTO_SINGOLO_VALORE));
        int posizione_riga;
        int posizione_colonna;
        fscanf (f_interfaccia, "%d ", &posizione_riga);
        scorrere_righe_file(f_interfaccia, 1);
        fscanf (f_interfaccia, "%d ", &posizione_colonna);
        posizionare_cursore (posizione_riga, posizione_colonna);
        printf("%d", valore); fflush(stdin);
    fclose(f_interfaccia);
    } else {
    printf ("%s", ERRORE_FILE_NON_TROVATO); fflush(stdin);
    fflush (stdout);
    printf ("%c", CARATTERE_SPAZIO); fflush(stdin);
    fflush (stdout);
    printf ("%s", file_interfaccia); fflush(stdin);
    fflush (stdout);
    }
    return;
}





void stampare_valore_testuale(const char file_interfaccia[], const char stringa[], int posizione_valore){
    FILE *f_interfaccia = fopen(file_interfaccia, "r");
    if (f_interfaccia != NULL) {
        scorrere_righe_file(f_interfaccia, ALTEZZA_SCHERMATA + SPIAZZAMENTO_STAMPA_VALORI + ((posizione_valore - 1) * SPIAZZAMENTO_SINGOLO_VALORE));
        int posizione_riga;
        int posizione_colonna;
        fscanf (f_interfaccia, "%d ", &posizione_riga);
        scorrere_righe_file(f_interfaccia, 1);
        fscanf (f_interfaccia, "%d ", &posizione_colonna);
        posizionare_cursore (posizione_riga, posizione_colonna);
        printf("%s", stringa); fflush(stdin);
        fclose(f_interfaccia);
    } else {
        printf ("%s", ERRORE_FILE_NON_TROVATO); fflush(stdin);
        fflush (stdout);
        printf ("%c", CARATTERE_SPAZIO); fflush(stdin);
        fflush (stdout);
        printf ("%s", file_interfaccia); fflush(stdin);
        fflush (stdout);
    }
    return;
}


void stampare_valore_testuale_centrato(const char file_interfaccia[], const char stringa[], int posizione_valore, int spazio_disponibile){
    FILE *f_interfaccia = fopen(file_interfaccia, "r");
    if (f_interfaccia != NULL) {
        scorrere_righe_file(f_interfaccia, ALTEZZA_SCHERMATA + SPIAZZAMENTO_STAMPA_VALORI + ((posizione_valore - 1) * SPIAZZAMENTO_SINGOLO_VALORE));
        int posizione_riga;
        int posizione_colonna;
        fscanf (f_interfaccia, "%d ", &posizione_riga);
        scorrere_righe_file(f_interfaccia, 1);
        fscanf (f_interfaccia, "%d ", &posizione_colonna);
        posizionare_cursore (posizione_riga, posizione_colonna);
        int lunghezza_stringa = calcolare_lunghezza_stringa(stringa);
        int spazio_rimanente = spazio_disponibile - lunghezza_stringa;
        int spaziatura_iniziale = calcolare_parte_intera(spazio_rimanente / 2);
        while(spaziatura_iniziale > 0){
            printf("%c", CARATTERE_SPAZIO);
            spaziatura_iniziale = spaziatura_iniziale - 1;
        }
        printf("%s", stringa); fflush(stdin);
        fclose(f_interfaccia);
    } else {
        printf ("%s", ERRORE_FILE_NON_TROVATO); fflush(stdin);
        fflush (stdout);
        printf ("%c", CARATTERE_SPAZIO); fflush(stdin);
        fflush (stdout);
        printf ("%s", file_interfaccia); fflush(stdin);
        fflush (stdout);
    }
    return;
}


/*void stampare_valore_testuale_colorato(const char file_interfaccia[], const char stringa[], int posizione_valore, int valore_colore){
    cambiare_colore_testo(valore_colore);
    stampare_valore_testuale(file_interfaccia, stringa, posizione_valore);
    cambiare_colore_testo(COLORE_PRINCIPALE_SCHERMATA);
}*/



void stampare_vittoria (const char file_interfaccia[]) {

    FILE * f_interfaccia = fopen(file_interfaccia, "r");
    if (f_interfaccia != NULL) {
        char simbolo_letto;
        int indice_nuova_riga = 0;
        while (indice_nuova_riga < ALTEZZA_SCHERMATA) {
            simbolo_letto = fgetc(f_interfaccia);
            if(simbolo_letto == CARATTERE_COPPA){
                cambiare_colore_testo(ARANCIO);
            }
            printf("%c", simbolo_letto); fflush(stdin);
            if(simbolo_letto == CARATTERE_COPPA){
                cambiare_colore_testo(COLORE_PRINCIPALE_SCHERMATA);
            }
            if (simbolo_letto == CARATTERE_A_CAPO) {
                indice_nuova_riga = indice_nuova_riga + 1;
            }
        }
        fclose(f_interfaccia);
    } else {
        printf("%s", ERRORE_FILE_NON_TROVATO); fflush(stdin);
        fflush(stdout);
        printf("%c", CARATTERE_SPAZIO); fflush(stdin);
        fflush(stdout);
        printf("%s", file_interfaccia); fflush(stdin);
        fflush(stdout);
    }
    return;
}


void stampare_intro (const char file_interfaccia[]) {

    FILE * f_interfaccia = fopen(file_interfaccia, "r");
    if (f_interfaccia != NULL) {
        char simbolo_letto;
        int indice_nuova_riga = 0;
        cambiare_colore_testo(VERDE_FLUO);
        while (indice_nuova_riga < ALTEZZA_TITOLO_GRANDE) {
            simbolo_letto = fgetc(f_interfaccia);
            printf("%c", simbolo_letto); fflush(stdin);
            if (simbolo_letto == CARATTERE_A_CAPO) {
                indice_nuova_riga = indice_nuova_riga + 1;
            }
        }
        while (indice_nuova_riga < ALTEZZA_SCHERMATA) {
            simbolo_letto = fgetc(f_interfaccia);
            if(simbolo_letto == CARATTERE_BECCO){
                cambiare_colore_testo(ARANCIO);
            }else if (simbolo_letto == CARATTERE_SFONDO){
                cambiare_colore_testo(CELESTE);
            }
            printf("%c", simbolo_letto); fflush(stdin);
            if(simbolo_letto == CARATTERE_BECCO){
                cambiare_colore_testo(COLORE_PRINCIPALE_SCHERMATA);
            }else if (simbolo_letto == CARATTERE_SFONDO){
                cambiare_colore_testo(COLORE_PRINCIPALE_SCHERMATA);
            }
            if (simbolo_letto == CARATTERE_A_CAPO) {
                indice_nuova_riga = indice_nuova_riga + 1;
            }
        }
        fclose(f_interfaccia);
    } else {
        printf("%s", ERRORE_FILE_NON_TROVATO); fflush(stdin);
        fflush(stdout);
        printf("%c", CARATTERE_SPAZIO); fflush(stdin);
        fflush(stdout);
        printf("%s", file_interfaccia); fflush(stdin);
        fflush(stdout);
    }
    return;
}


void cambiare_colore_testo(int valore_colore){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, valore_colore);
    return;
}




void stampare_interfaccia_percorso(partita* partita_attuale, const char file_interfaccia[]){
    cancellare_schermata();
    stampare_percorso(partita_attuale);
    FILE *f_interfaccia = NULL;
    if ((f_interfaccia = fopen(file_interfaccia, "r")) != NULL) {
        scorrere_righe_file(f_interfaccia, ALTEZZA_SCHERMATA - ALTEZZA_MENU_INTERFACCIA_PERCORSO);
        char simbolo_letto;
        int indice_altezza_menu = 0;
        while (indice_altezza_menu < ALTEZZA_MENU_INTERFACCIA_PERCORSO) {
            simbolo_letto = fgetc(f_interfaccia);
            printf("%c", simbolo_letto);
            if (simbolo_letto == CARATTERE_A_CAPO) {
                indice_altezza_menu = indice_altezza_menu + 1;
            }
        }
        scorrere_righe_file(f_interfaccia, SPIAZZAMENTO_STAMPA_VALORI);
        int posizione_riga;
        int posizione_colonna;
        fscanf (f_interfaccia, "%d ", &posizione_riga);
        scorrere_righe_file(f_interfaccia, 1);
        fscanf (f_interfaccia, "%d ", &posizione_colonna);
        posizionare_cursore (posizione_riga, posizione_colonna);
        char nome_giocatore[DIMENSIONE_MASSIMA_NOME_GIOCATORE];
        leggere_nome_giocatore(leggere_giocatore(*partita_attuale, leggere_turno(*partita_attuale)), nome_giocatore);
        cambiare_colore_testo(COLORI_GIOCATORI[leggere_turno(*partita_attuale)]);
        printf("%18s", nome_giocatore);
        cambiare_colore_testo(COLORE_PRINCIPALE_SCHERMATA);
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
    return;
}