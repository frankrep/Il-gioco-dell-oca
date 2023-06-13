#ifndef GENERARE_PERCORSO_H_
#define GENERARE_PERCORSO_H_

void generare_percorso (partita* partita_attuale);
int calcolare_proporzione (partita partita_attuale, int posizione_originale);
int calcolare_parte_intera (float valore_reale);
int calcolare_resto (int dividendo, int divisore);
void inizializzare_caselle_speciali (casella caselle_speciali[]);
void riempire_restante_percorso (partita* partita_attuale, int indice_ultima_casella);

#endif /* GENERARE_PERCORSO_H_ */