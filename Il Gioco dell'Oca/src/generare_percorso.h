#ifndef GENERARE_PERCORSO_H_
#define GENERARE_PERCORSO_H_

void generare_percorso (partita* partita_attuale);


void creare_percorso_con_oche (partita* partita_attuale);
void inserire_casella (partita* partita_attuale, int posizione_percorso);
void creare_casella (casella* casella_attuale, int indice_partita);
void posizionare_caselle_speciali (partita* partita_attuale);
void proporzionare_caselle_speciali(partita* partita_attuale, casella caselle_speciali[]);


int calcolare_proporzione(partita partita_attuale, int posizione_originale);
int calcolare_parte_intera (float valore_reale);


int trovare_divisore_massimo_decimale (float valore_reale);
int calcolare_parte_intera_unita (float valore_reale, int divisore);


int calcolare_resto (int dividendo, int divisore);

#endif /* GENERARE_PERCORSO_H_ */