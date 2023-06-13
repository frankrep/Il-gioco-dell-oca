#ifndef SALVARE_CARICARE_PARTITA_H_
#define SALVARE_CARICARE_PARTITA_H_
#include "partita.h"

void caricare_partite (partita elenco_partite[]);
void salvare_partita (partita* partita_attuale, int * sale);
int selezionare_slot (partita elenco_partite[], int * sale, const char file_interfaccia[]);
void inserire_simbolo (const char interfaccia [], char * simbolo, int * sale);
void attendere_simbolo_risposta (const char interfaccia [], char * risposta, int * sale);
void attendere_tasto_zero (const char interfaccia [], int * sale);
void verificare_correttezza_inserimento (const char file_interfaccia [], int * input, int * sale);
void attendere_tasto_zero (const char interfaccia [], int * sale);

#endif /* SALVARE_CARICARE_PARTITA_H_ */
