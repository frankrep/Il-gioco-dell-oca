#include "inizializzare_partita.h"
#include "partita.h"
#include "giocatore.h"
#include "vincitore.h"
#include "costanti.h"
#include "casella.h"
#include <stdlib.h>
partita* inizializzare_giocatori(partita* partita_attuale){
    *partita_attuale = richiedere_numero_caselle(partita_attuale);
    *partita_attuale = inizializzare_numero_giocatori(partita_attuale);
    *partita_attuale = inizializzare_nomi_giocatori(partita_attuale);
    *partita_attuale = inizializzare_pedine_giocatori(partita_attuale);
    return partita_attuale;
}
partita* richiedere_numero_caselle(partita* partita_attuale){
    //stampare richiesta
    do{
        int dimensione_percorso = scanf("%d", &dimensione_percorso);
        if ((dimensione_percorso < DIMENSIONE_MINIMA_PERCORSO) || (dimensione_percorso > DIMENSIONE_MASSIMA_PERCORSO))
        {
            //stampare messaggio errore
        }
    }while((dimensione_percorso < DIMENSIONE_MINIMA_PERCORSO) || (dimensione_percorso > DIMENSIONE_MASSIMA_PERCORSO));
    *partita_attuale = scrivere_lunghezza_percorso(partita_attuale, dimensione_percorso);
    return partita_attuale;
}
partita* inizializzare_numero_giocatori(partita* partita_attuale){
    //stampare messaggio richiesta
    do{
        int numero_partecipanti = scanf("%d", &numero_partecipanti);
        if ((numero_partecipanti < NUMERO_MINIMO_GIOCATORI) || (numero_partecipanti > NUMERO_MASSIMO_GIOCATORI))
        {
            //stampare messaggio errore
        }
    }wbile((numero_partecipanti < NUMERO_MINIMO_GIOCATORI) || (numero_partecipanti > NUMERO_MASSIMO_GIOCATORI));
    *partita_attuale = scrivere_numero_giocatori (partita_attuale, numero_partecipanti);
    return partita_attuale;
}
partita* inizializzare_nomi_giocatori(partita* partita_attuale){
    int indice_giocatori = 0;
    while (indice_giocatori <= leggere_numero_giocatori(partita_attuale))
    {
        //stampare richiesta
        *partita_attuale = scrivere_giocatori(partita_attuale, scrivere_nome_giocatore(leggere_giocatori(partita_attuale, indice_giocatori), inserire_stringa(DIMENSIONE_MINIMA_NOME_GIOCATORE, DIMENSIONE_MASSIMA_NOME_GIOCATORE)), indice_giocatori);
        indice_giocatori = indice_giocatori + 1;
    }
    return partita_attuale;
}
char* inserire_stringa(int dimensione_minima_stringa, int dimensione_massima_stringa){
    int indice_stringa = 0;
    int terminato = 0;
    char stringa[dimensione_massima_stringa];
    while ( (indice_stringa < dimensione_massima_stringa) && (terminato == FALSE) && (indice_stringa < dimensione_minima_stringa) )
    {
        char carattere = scanf("%c", &carattere);
        if(carattere != CARATTERE_A_CAPO)
        {
            stringa[indice_stringa] = carattere;
            indice_stringa = indice_stringa + 1;
        }
        esle if (indice_Stringa <= dimensione_minima_stringa)
        {
            //stampare messaggio errore minimo caratteri richiesti
        }
         else 
         {
            terminato = TRUE;
         }
    }
    stringa[indice_stringa] = FINE_STRINGA;
    return stringa;
}
partita* inizializzare_pedine_giocatori(partita* partita_attuale){
    int indice_pedine = 0;
    do{
        *partita_attuale = scrivere_giocatore(partita_attuale,scrivere_pedina(leggere_giocatore(partita_attuale,indice_pedine),PEDINE_DISPONIBILI[indice_pedine]),indice_pedine);
        indice_pedine = indice_pedine + 1;
    }(indice_pedine <= leggere_numero_giocatori(partita_attuale));
    return partita_attuale;
}