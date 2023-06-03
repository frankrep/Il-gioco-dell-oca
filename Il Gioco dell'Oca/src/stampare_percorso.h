#ifndef aiuto_h_
#define aiuto_h_
void stampare_percorso (partita* partita_attuale);
void stampare_parte_superiore_casella ();
void stampare_superiore_sinistra (int numero_colonne, int contatore, int strato);
void stampare_inferiore_sinistra (int numero_colonne, int cotatore, int strato);
void stampare_parte_centrale_incrementeo (int numero_iniziale, int numero_colonne, int strato);
void stampare_parte_centrale_decremento (int numero_iniziale, int numero_colonne, int strato);
void stampare_parte_destra (int numero_colonne, int contatore, int strato, int numero_iniziale);
void stampare_casella(partita* partita_attuale, int numero_casella, int strato);
void stampare_contenuto_casella (partita* partita_attuale, int numero_casella);
void stampare_giocatori_superiori_casella ();
void stampare_giocatori_inferiori_casella ();
#endif /* CASELLA_H_ */