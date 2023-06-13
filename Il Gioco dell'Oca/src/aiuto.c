#include <stdlib.h>
#include <stdio.h>
#include "aiuto.h"
#include "costanti.h"
#include "gestire_stampa.h"



int scegliere_aiuto (int * sale);



void chiedere_aiuto (int * sale) {
    int opzione_scelta;
    do {
        opzione_scelta = scegliere_aiuto (sale);
        int torna_indietro = 1;
        if (opzione_scelta == 1) {
            stampare_testo(FILE_REGOLE);
            do {
                posizionare_cursore_in_attesa(FILE_REGOLE);
                scanf("%d", &torna_indietro);
                fflush(stdin);
                *sale = *sale + 1;
                if (torna_indietro != 0) {
                    stampare_messaggio_errore(FILE_REGOLE);
                }
            } while (torna_indietro != 0);
        }
        else if (opzione_scelta == 2) {
            stampare_testo(FILE_MANUALE);
            do {
                posizionare_cursore_in_attesa(FILE_MANUALE);
                scanf("%d", &torna_indietro);
                fflush(stdin);
                *sale = *sale + 1;
                if (torna_indietro != 0) {
                    stampare_messaggio_errore(FILE_MANUALE);
                }
            }while (torna_indietro != 0);
        }
        cancellare_schermata();
    } while(opzione_scelta != 0);
    return ;
}

int scegliere_aiuto (int * sale) {
    cancellare_schermata();
    stampare_testo(FILE_MENU_AIUTO);
    int opzione_scelta;
    do {
        posizionare_cursore_in_attesa(FILE_MENU_AIUTO);
        scanf("%d", &opzione_scelta);
        fflush(stdin);
        *sale = *sale + 1;
        if ((opzione_scelta < 0) || (opzione_scelta > NUMERO_MASSIMO_OPZIONI_AIUTO))
        {
            stampare_messaggio_errore(FILE_MENU_AIUTO);
        }
    } while ( (opzione_scelta < 0 ) || (opzione_scelta > NUMERO_MASSIMO_OPZIONI_AIUTO) );
    return opzione_scelta;
}
