/*
 * gestire_stampa.c
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "gestire_stampa.h"
#include "costanti.h"

void stampare_dadi(const char file_interfaccia[], const int facce_dadi[]) {
	char carattere_letto;

	FILE *f_interfaccia = NULL;
	if ((f_interfaccia = fopen(file_interfaccia, "r")) == NULL) {
		int indice_carattere = 0;
		while (indice_carattere < (LUNGHEZZA_SCHERMATA * ALTEZZA_SCHERMATA)) {
			fgetc(f_interfaccia);
			indice_carattere = indice_carattere + 1;
		}
		int indice_riga = 0;
		while (indice_riga < SPIAZZAMENTO_DADO) {
			carattere_letto = fgetc(f_interfaccia);
			if (carattere_letto == CARATTERE_A_CAPO) {
				indice_riga = indice_riga + 1;
			}
		}
		int posizione_riga;
		int posizione_colonna;
		int indice_dadi = 0;
		while (facce_dadi[indice_dadi] != 0 || (indice_dadi < NUMERO_DADI)) {
			int indice_puntini_dado = 1;
			while (indice_puntini_dado <= NUMERO_MASSIMO_PUNTINI_FACCIA_DADO) {
				//inserire funzione di conversione
				fscanf(f_interfaccia, "%d ", &posizione_riga);
				carattere_letto = fgetc(f_interfaccia);
				while (carattere_letto != CARATTERE_A_CAPO) {
					carattere_letto = fgetc(f_interfaccia);
				}

				fscanf(f_interfaccia, "%d ", &posizione_colonna);
				carattere_letto = fgetc(f_interfaccia);
				while (carattere_letto != CARATTERE_A_CAPO) {
					carattere_letto = fgetc(f_interfaccia);
				}

				posizionare_cursore(posizione_riga, posizione_colonna);
				if (indice_puntini_dado == 1) {
					if (facce_dadi[indice_dadi] == 6
							|| (facce_dadi[indice_dadi] == 5)
							|| (facce_dadi[indice_dadi] == 4)) {
						printf("%c", CARATTERE_PUNTO_FACCIA_DADO);
					} else {
						printf("%c", CARATTERE_SPAZIO);
					}
				} else if (indice_puntini_dado == 2) {
					if (facce_dadi[indice_dadi] == 6) {
						printf("%c", CARATTERE_PUNTO_FACCIA_DADO);
					} else {
						printf("%c", CARATTERE_SPAZIO);
					}
				} else if (indice_puntini_dado == 3) {
					if (facce_dadi[indice_dadi] == 6
							|| (facce_dadi[indice_dadi] == 5)
							|| (facce_dadi[indice_dadi] == 4)) {
						printf("%c", CARATTERE_PUNTO_FACCIA_DADO);
					} else {
						printf("%c", CARATTERE_SPAZIO);
					}
				} else if (indice_puntini_dado == 4) {
					if (facce_dadi[indice_dadi] == 5
							|| (facce_dadi[indice_dadi] == 3)
							|| (facce_dadi[indice_dadi] == 1)) {
						printf("%c", CARATTERE_PUNTO_FACCIA_DADO);
					} else {
						printf("%c", CARATTERE_SPAZIO);
					}
				} else if (indice_puntini_dado == 5) {
					if (facce_dadi[indice_dadi] == 6
							|| (facce_dadi[indice_dadi] == 5)
							|| (facce_dadi[indice_dadi] == 4)
							|| (facce_dadi[indice_dadi] == 3)
							|| (facce_dadi[indice_dadi] == 2)) {
						printf("%c", CARATTERE_PUNTO_FACCIA_DADO);
					} else {
						printf("%c", CARATTERE_SPAZIO);
					}
				} else if (indice_puntini_dado == 6) {
					if (facce_dadi[indice_dadi] == 6) {
						printf("%c", CARATTERE_PUNTO_FACCIA_DADO);
					} else {
						printf("%c", CARATTERE_SPAZIO);
					}
				} else if (indice_puntini_dado == 7) {
					if (facce_dadi[indice_dadi] == 6
							|| (facce_dadi[indice_dadi] == 5)
							|| (facce_dadi[indice_dadi] == 4)) {
						printf("%c", CARATTERE_PUNTO_FACCIA_DADO);
					} else {
						printf("%c", CARATTERE_SPAZIO);
					}
				}
				indice_puntini_dado = indice_puntini_dado + 1;
			}
			indice_dadi = indice_dadi + 1;
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

}

void stampare_testo (const char file_interfaccia[]) {

	FILE * f_interfaccia = fopen(file_interfaccia, "r");
	if (f_interfaccia != NULL) {
		char simbolo_letto;
		int indice_nuova_riga = 0;
		while (indice_nuova_riga < ALTEZZA_SCHERMATA) {
			simbolo_letto = fgetc(f_interfaccia);
			printf("%c", simbolo_letto);
			if (simbolo_letto == CARATTERE_A_CAPO) {
				indice_nuova_riga = indice_nuova_riga + 1;
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

}

void stampare_messaggio_errore(const char file_interfaccia[]) {
	FILE *f_interfaccia = NULL;
	if ((f_interfaccia = fopen(file_interfaccia, "r")) == NULL) {
		char carattere_letto;
		int indice_carattere = 0;
		while (indice_carattere < (LUNGHEZZA_SCHERMATA * ALTEZZA_SCHERMATA)) {
			fgetc(f_interfaccia);
			indice_carattere = indice_carattere + 1;
		}
		int indice_riga = 0;
		while (indice_riga < SPIAZZAMENTO_MESSAGGIO_ERRORE) {
			carattere_letto = fgetc(f_interfaccia);
			if (carattere_letto == CARATTERE_A_CAPO) {
				indice_riga = indice_riga + 1;
			}
		}
		int posizione_riga;
		int posizione_colonna;
		int codice_messaggio_errore;
		fscanf(f_interfaccia, "%d ", &posizione_riga);
		carattere_letto = fgetc(f_interfaccia);
		while (carattere_letto != CARATTERE_A_CAPO) {
			carattere_letto = fgetc(f_interfaccia);
		}
		fscanf(f_interfaccia, "%d ", &posizione_colonna);
		carattere_letto = fgetc(f_interfaccia);
		while (carattere_letto != CARATTERE_A_CAPO) {
			carattere_letto = fgetc(f_interfaccia);
		}
		fscanf(f_interfaccia, "%d ", &codice_messaggio_errore);
		carattere_letto = fgetc(f_interfaccia);
		while (carattere_letto != CARATTERE_A_CAPO) {
			carattere_letto = fgetc(f_interfaccia);
		}
		fclose(f_interfaccia);

		posizionare_cursore(posizione_riga, posizione_colonna);
		FILE *f_messaggi_errore = NULL;
		if ((f_messaggi_errore = fopen(FILE_MESSAGGI_ERRORE, "r")) == NULL) {
			char messaggio_errore[LUNGHEZZA_SCHERMATA + 1];

			indice_riga = 0;
			while (indice_riga < codice_messaggio_errore) {
				fgets(messaggio_errore, (LUNGHEZZA_SCHERMATA + 1),f_messaggi_errore);
			}
			fclose(f_messaggi_errore);
			printf("%s", messaggio_errore);
			fflush(stdout);
		} else {
			printf("%s", ERRORE_FILE_NON_TROVATO);
			fflush(stdout);
			printf("%c", CARATTERE_SPAZIO);
			fflush(stdout);
			printf("%s", FILE_MESSAGGI_ERRORE);
			fflush(stdout);
		}

	} else {
		printf("%s", ERRORE_FILE_NON_TROVATO);
		fflush(stdout);
		printf("%c", CARATTERE_SPAZIO);
		fflush(stdout);
		printf("%s", file_interfaccia);
		fflush(stdout);
	}
}

void posizionare_cursore(int asse_x, int asse_y) {
	COORD coord;
	coord.X = asse_x;
	coord.Y = asse_y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void posizionare_cursore_in_attesa(const char file_interfaccia[]) {
	FILE *f_interfaccia = NULL;
	if ((f_interfaccia = fopen(file_interfaccia, "r")) == NULL) {
		char carattere_letto;
		int indice_carattere = 0;
		while (indice_carattere < (LUNGHEZZA_SCHERMATA * ALTEZZA_SCHERMATA)) {
			fgetc(f_interfaccia);
			indice_carattere = indice_carattere + 1;
		}
		int posizione_riga;
		int posizione_colonna;
		fscanf(f_interfaccia, "%d ", &posizione_riga);
		carattere_letto = fgetc(f_interfaccia);
		while (carattere_letto != CARATTERE_A_CAPO) {
			carattere_letto = fgetc(f_interfaccia);
		}
		fscanf(f_interfaccia, "%d ", &posizione_colonna);
		carattere_letto = fgetc(f_interfaccia);
		while (carattere_letto != CARATTERE_A_CAPO) {
			carattere_letto = fgetc(f_interfaccia);
		}
		posizionare_cursore(posizione_riga, posizione_colonna);
	} else {
		printf("%s", ERRORE_FILE_NON_TROVATO);
		fflush(stdout);
		printf("%c", CARATTERE_SPAZIO);
		fflush(stdout);
		printf("%s", file_interfaccia);
		fflush(stdout);
	}
}
