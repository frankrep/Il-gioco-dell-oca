#ifndef GENERARE_PERCORSO_H_
#define GENERARE_PERCORSO_H_

partita* generare_percorso(partita* partita_attuale);
partita* creare_percorso_con_oche(partita* partita_attaule);
partita* inserire_casella(partita* partita_attuale, int posizione_percorso);
casella* creare_casella(FILE* file_oca, int posizione_percorso);
partita* posizionare_caselle_speciali(partita* partita_attuale);
casella* proporzionare_caselle_speciali(partita* partita_attuale,FILE* file_caselle_speciali);
int calcolare_proporzione(partita* partita_attuale, int posizione_originale);
int calcolare_parte_intera(float valore_reale);
int trovare_divisore_decimale(float numero);
int calcolare_parte_intera_unita(float numero, int divisore);
#endif /* GENERARE_PERCORSO_H_ */