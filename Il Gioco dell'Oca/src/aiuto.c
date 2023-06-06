#include <stdlib.h>
#include <stdio.h>
#include "aiuto.h"
#include "costanti.h"
void chiedere_aiuto (int opzione_scelta) {
    opzione_scelta = scegliere_aiuto ();
    if (opzione_scelta == 1)
    {
        stampare_da_file(file_regole);
    }
    else if (opzione_scelta == 2)
    {
        stampare_da_file(file_manuale);
    }
}
int scegliere_aiuto () {
    printf("file_menu_aiuto");
    int opzione_scelta;
    do
    {
         scanf("%d",&opzione_scelta);
         if ((opzione_scelta < 0) || (opzione_scelta > NUMERO_MASSIMO_OPZIONI_AIUTO))
         {
            stampare_messaggio_errore(file_menu_aiuto);
         }
    }while((opzione_scelta < 0 ) || (opzione_scelta > NUMERO_MASSIMO_OPZIONI_AIUTO));
    return opzione_scelta;
}
