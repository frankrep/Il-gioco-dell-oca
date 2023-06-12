/*
 * gestire_stampa.h
 *
 */

#ifndef GESTIRE_STAMPA_H_
#define GESTIRE_STAMPA_H_

#include "partita.h"

void cancellare_schermata();
void cambiare_colore_testo(int valore_colore);
void posizionare_cursore(int posizione_riga, int posizione_colonna);


void stampare_dadi(const char file_interfaccia[], const int facce_dadi[]);
void stampare_testo(const char file_interfaccia[]);
void stampare_messaggio_errore(const char file_interfaccia[]);
void posizionare_cursore_in_attesa(const char file_interfaccia[]);
void scorrere_righe_file(FILE* file_testo, int numero_righe);
void stampare_dadi_partita(const char file_interfaccia[], partita* partita_attuale);
void stampare_dado(const char file_interfaccia[], int valore_faccia_dado);
void stampare_valore_intero(const char file_interfaccia[], int valore, int posizione_valore);
void stampare_valore_testuale(const char file_interfaccia[], const char stringa[], int posizione_valore);
//void stampare_valore_testuale_colorato(const char file_interfaccia[], const char stringa[], int posizione_valore, int valore_colore);
void stampare_vittoria (const char file_interfaccia[]);
void stampare_intro (const char file_interfaccia[]);
void stampare_interfaccia_percorso(partita* partita_attuale, const char file_interfaccia[]);
void stampare_valore_testuale_centrato(const char file_interfaccia[], const char stringa[], int posizione_valore, int spazio_disponibile);
void stampare_errore_apertura_file(const char file_interfaccia[]);
void stampare_messaggio_valore (const char file_interfaccia[], int posizione_valore);
void stampare_partite_salvate (partita elenco_partite[]);
void stampare_classifica(int * sale);


#endif /* GESTIRE_STAMPA_H_ */
