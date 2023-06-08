#include <stdlib.h>
#include <stdio.h>
#include "aiuto.h"
#include "costanti.h"
#include "gestire_stampa.h"

void chiedere_aiuto (int opzione_scelta) {
    opzione_scelta = scegliere_aiuto ();
    if (opzione_scelta == 1)
    {
        stampare_testo(FILE_REGOLE);
    }
    else if (opzione_scelta == 2)
    {
        stampare_testo(FILE_MANUALE);
    }
}
int scegliere_aiuto () {
    printf("file_menu_aiuto");
    int opzione_scelta;
    do
    {
         scanf("%d", &opzione_scelta);
         if ((opzione_scelta < 0) || (opzione_scelta > NUMERO_MASSIMO_OPZIONI_AIUTO))
         {
            stampare_messaggio_errore(FILE_MENU_AIUTO);
         }
    }while((opzione_scelta < 0 ) || (opzione_scelta > NUMERO_MASSIMO_OPZIONI_AIUTO));
    return opzione_scelta;
}
