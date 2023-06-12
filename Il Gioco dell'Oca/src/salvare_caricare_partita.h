#ifndef SALVARE_CARICARE_PARTITA_H_
#define SALVARE_CARICARE_PARTITA_H_
#include "partita.h"

//da valutare cosa tenere qui o nel file sorgente di caricare e salvare partita
void caricare_partite (partita elenco_partite[]);
void salvare_partita (partita* partita_attuale, int * sale);
void confermare_scelta (char * risposta, int * sale);
int selezionare_slot (partita elenco_partite[], int * sale, const char file_interfaccia[]);

#endif /* SALVARE_CARICARE_PARTITA_H_ */
