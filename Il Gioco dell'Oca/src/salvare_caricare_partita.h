#ifndef "salvare_caricare_partita.h"
#define "salvare_caricare_partita.h"
parita caricare_partite ();
FILE* salvare_partita (partita* partita_attuale, int slot_scelto) ;
void stampare_partite_salvato(partita* elenco_partite) ;
int selezionare_slot (partita* elenco_partite);
#endif // "salvare_caricare_partita.h"