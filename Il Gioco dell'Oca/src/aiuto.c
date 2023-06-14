#include "aiuto.h"
#include "costanti.h"
#include "gestire_stampa.h"
#include "salvare_caricare_partita.h"



int scegliere_aiuto (int * sale);



void chiedere_aiuto (int * sale) {
    int opzione_scelta;
    do {
        opzione_scelta = scegliere_aiuto (sale);
        if (opzione_scelta == 1) {
            stampare_testo (FILE_REGOLE);
            attendere_tasto_zero(FILE_REGOLE, sale);
        } else if (opzione_scelta == 2) {
            stampare_testo (FILE_MANUALE);
            attendere_tasto_zero(FILE_MANUALE, sale);
        }
    } while (opzione_scelta != 0);
    return;
}



int scegliere_aiuto (int * sale) {
    stampare_testo (FILE_MENU_AIUTO);
    int opzione_scelta;
    do {
        verificare_correttezza_inserimento (FILE_MENU_AIUTO, &opzione_scelta, sale);
        if ( (opzione_scelta < 0) || (opzione_scelta > NUMERO_MASSIMO_OPZIONI_AIUTO) ) {
            stampare_messaggio_errore (FILE_MENU_AIUTO);
        }
    } while ( (opzione_scelta < 0 ) || (opzione_scelta > NUMERO_MASSIMO_OPZIONI_AIUTO) );
    return opzione_scelta;
}
