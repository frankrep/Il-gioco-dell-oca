#ifndef STAMPARE_PERCORSO_H_
#define STAMPARE_PERCORSO_H_

void stampare_percorso(partita* partita_attuale);
void stampare_parte_superiore_casella();
int stampare_superiore_sinistra(partita* partita_attuale, int numero_colonne, int contatore, int strato);
int stampare_inferiore_sinistra(partita* partita_attuale, int numero_colonne, int contatore, int strato);
int stampare_parte_destra(partita* partita_attuale, int numero_colonne, int numero_iniziale, int contatore, int strato);
int stampare_parte_centrale_incremento(partita* partita_attuale, int valore_iniziale, int numero_colonne, int strato);
int stampare_parte_centrale_decremento(partita* partita_attuale, int valore_iniziale, int numero_colonne, int strato);
void stampare_casella(partita* partita_attuale, int ultima_casella_stampata, int strato);
void stampare_contenuto_casella(partita* partita_attuale, int numero_casella);
void stampare_giocatori_superiori_casella(partita* partita_attuale, int numero_casella);
void stampare_giocatori_inferiori_casella(partita* partita_attuale, int numero_casella);

#endif /* STAMPARE_PERCORSO_H_ */