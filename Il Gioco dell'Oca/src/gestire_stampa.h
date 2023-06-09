/*
 * gestire_stampa.h
 *
 */

#ifndef GESTIRE_STAMPA_H_
#define GESTIRE_STAMPA_H_

void stampare_dadi(const char file_interfaccia[], const int facce_dadi[]);
void stampare_testo(const char file_interfaccia[]);
void stampare_messaggio_errore(const char file_interfaccia[]);
void posizionare_cursore(int posizione_riga, int posizione_colonna);
void posizionare_cursore_in_attesa(const char file_interfaccia[]);
void scorrere_righe_file(FILE* file_testo, int numero_righe);

#endif /* GESTIRE_STAMPA_H_ */
