#ifndef classifica_h_
#define classifica_h_

#include "vincitore.h"

void aggiornare_classifica_top_10 (vincitore vincitore_partita);
void spostamento_destra_vincitori (vincitore vincitori[], int posizione_inserimento, vincitore vincitore_partita);
void caricare_classifica (vincitore vincitori[]);
void scrivere_classifica (vincitore elenco_vincitori[]);
void creare_classifica_vuota(vincitore vincitori[]);

#endif /* classifica_h_ */