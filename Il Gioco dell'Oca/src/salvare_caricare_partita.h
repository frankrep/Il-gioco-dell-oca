#ifndef SALVARE_CARICARE_PARTITA_H_
#define SALVARE_CARICARE_PARTITA_H_
#include "partita.h"

//da valutare cosa tenere qui o nel file sorgente di caricare e salvare partita
void caricare_partite (partita elenco_partite[]);
void salvare_partita (partita* partita_attuale);
void confermare_scelta (char * risposta);
void stampare_partite_salvate (partita elenco_partite[]);
int selezionare_slot (partita elenco_partite[]);
void scrivere_partite (partita elenco_partite[]);

#endif /* SALVARE_CARICARE_PARTITA_H_ */
