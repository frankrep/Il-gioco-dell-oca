/*
 * gestire_stampa.c
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "gestire_stampa.h"
#include "costanti.h"

void stampare_dadi(const char FILE_INTERFACCIA[], const int facce_dadi[]) {
	char carattere_letto;

	FILE *f_interfaccia = NULL;
	if ((f_interfaccia = fopen(FILE_INTERFACCIA, "r")) == NULL) {
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
			int indice_puntini_dado = 0;
			while (indice_puntini_dado < NUMERO_MASSIMO_PUNTINI_FACCIA_DADO) {
				//inserire funzione di conversione
				fscanf (f_interfaccia, "%d ", &posizione_riga);
				carattere_letto = fgetc(f_interfaccia);
				while (carattere_letto != CARATTERE_A_CAPO) {
					carattere_letto = leggere_da_file(FILE_INTERFACCIA);
				}

				fscanf (f_interfaccia, "%d ", &posizione_colonna);
				carattere_letto = fgetc(f_interfaccia);
				while (carattere_letto != CARATTERE_A_CAPO) {
					carattere_letto = fgetc(f_interfaccia);
				}

				posizionare_cursore(posizione_riga, posizione_colonna);             //GOTOXY
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
	} else {
		//GESTIRE FILE NON TROVATO
	}

}

void stampare_testo(const char FILE_DA_STAMPARE[]) {
	int indice_nuova_riga = 0;
	while (indice_nuova_riga < ALTEZZA_SCHERMATA) {
		char simbolo_letto = leggere_da_file(testo);
		printf("%c", simbolo_letto);
		if (simbolo_letto == CARATTERE_A_CAPO) {
			indice_nuova_riga = indice_nuova_riga + 1;
		}
	}
}
