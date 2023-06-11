#include <stdlib.h>
#include <stdio.h>
#include "aiuto.h"
#include "costanti.h"
#include "gestire_stampa.h"
//prova commit da cclone
void chiedere_aiuto () {
    int opzione_scelta;
    do {
        opzione_scelta = scegliere_aiuto();
        int torna_indietro = 1;
        if (opzione_scelta == 1) {
            stampare_testo(FILE_REGOLE);
            do {
                posizionare_cursore_in_attesa(FILE_REGOLE);
                scanf("%d", &torna_indietro);
                fflush(stdin);
                if (torna_indietro != 0) {
                    stampare_messaggio_errore(FILE_REGOLE);
                }
            } while (torna_indietro != 0);
            system("cls");
        } else if (opzione_scelta == 2) {
            stampare_testo(FILE_MANUALE);
            do {
                posizionare_cursore_in_attesa(FILE_MANUALE);
                scanf("%d", &torna_indietro);
                fflush(stdin);
                if (torna_indietro != 0) {
                    stampare_messaggio_errore(FILE_MANUALE);
                }
            }while (torna_indietro != 0);
            system("cls");
        }
    } while(opzione_scelta != 0);
    return ;
}

int scegliere_aiuto () {
    stampare_testo(FILE_MENU_AIUTO);
    int opzione_scelta;
    do {
         posizionare_cursore_in_attesa(FILE_MENU_AIUTO);
         scanf("%d", &opzione_scelta);
         fflush(stdin);
         if ((opzione_scelta < 0) || (opzione_scelta > NUMERO_MASSIMO_OPZIONI_AIUTO))
         {
            stampare_messaggio_errore(FILE_MENU_AIUTO);
         }
    }while((opzione_scelta < 0 ) || (opzione_scelta > NUMERO_MASSIMO_OPZIONI_AIUTO));
    system("cls");
    return opzione_scelta;
}
