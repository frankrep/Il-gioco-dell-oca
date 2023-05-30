#ifndef classifica_h_
#define classifica_h_
FILE* aggiornare_classifica_top_10 (vincitore* vincitore_partita);
vincitore* spostamento_destra_vincitori (vincitore* vincitori[], int posizione_inserimento,vincitore* vincitore_partita);
vincitore* caricare_classifica ();
void stampare_classifica();
#endif /* classifica_h_ *