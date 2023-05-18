#include <stlib.h>
#include "casella.h"
#include "giocatore.h"
#include "partita.h"
#include "vincitore.h"
#include "costanti.h"
#include "gestire_partita.h"
vincitore* gestire_partita(partita* partita_attuale){
    if(leggere_turno(partita_attuale) == 0){
        //scelta giocatore iniziale
        *partita_attuale = scegliere_giocatore(partita_attuale);
    }
    do{
        *partita_attuale = cambiare_turno(partita_attuale);
        if(leggere_autorizzazione(leggere_giocatore(partita_attuale,leggere_turno(partita_attuale))) > 0){
            *partita_attuale = gestire_autorizzazione(partita_attuale);
        }
        if(leggere_autorizzazione(leggere_giocatore(partita_attuale,leggere_turno(partita_attuale))) > 0){
            //stampare percorso con l'attesa con l'attesa dell'input
            *partita_attuale = lanciare_dadi(partita_attuale);
            //stampare percorso con i dadi aggiornati e attendere l'input
            *partita_attuale = spostare_giocatore(partita_attuale);
            //stampare percorso con input utente per proseguire con l'effetto
            *partita_attuale = verificare_casella(partita_attuale);
        }   

        }while(leggere_posizione_giocatore(leggere_giocatore(partita_attuale,leggere_turno(partita_attuale))) != leggere_lunghezza_percorso(partita_attuale));
        vincitore* vincitore_partita = inizializzare_vincitore(partita_attuale);
        return vincitore_partita;
}   
partita* scegliere_giocatore(partita* partita_attuale, int PRIMO_DADO){
        int estrazioni[NUMERO_MASSIMO_GIOCATORI];
        int indice_giocatori = 0;
        while(indice_giocatori <= leggere_numero_giocatori(partita_attuale)){
            //stampare scelta_g_iniziale
            //prendere in input la lettura da tastiera per il lancio
            estrazioni[indice_giocatori] = generare_numero(FACCIA_MINIMA_DADO, FACCIA_MASSIMA_DADO);
            //stampa del dado risultante
            //aspetta input da tastiera
            indice_giocatori = indice_giocatori + 1;
        }
        *partita_attuale = scrivere_turno(partita_attuale, trovare_posizione_massimo(estrazioni, leggere_numero_giocatori(partita_attuale)) - 1);
        return partita_attuale;
}
vincitore* inizializzare_vincitore(partita* partita_attuale){
    vincitore* vincitore_partita;
    *vincitore_partita = scrivere_nome_vincitore(vincitore_partita, leggere_nome_giocatore(leggere_giocatore(partita_attuale, leggere_turno(partita_attuale))));
    *vincitore_partita = scrivere_pedina_vincitore(vincitore_partita, leggere_pedina_giocatore(leggere_giocatore(partita_attuale, leggere_turno(partita_attuale))));
    *vincitore_partita = scrivere_lanci_vincitore(vincitore_partita, leggere_lanci_effettuati(leggere_giocatore(partita_attuale, leggere_turno(partita_attuale))));
    *vincitore_partita = scrivere_lunghezza_percorso_vincitore(vincitore_partita, leggere_lunghezza_percorso(partita_attuale));
    return vincitore_partita;
}
int generare_numero(FILE* file_seme,int numero_massimo,int numero_minimo){
    int seme;
    seme = leggere_da_file(int,1,file_seme);
    seme = generare_seme(seme);
    file_seme = scrivere_su_file(int,1,seme);
    int numero_casuale = generare_casuale(seme,numero_massimo,numero_minimo);
    return numero_casuale;
}
int generare_seme(int seme){
    int nuovo_seme = (MOLTIPLICATORE * seme + INCREMENTO) % DIVISORE;
    return nuovo_seme;
}
int generare_casuale(int seme,int numero_massimo,int numero_minimo){
    int numero_casuale = (seme % numero_massimo) + numero_minimo;
    return numero_casuale;
}
int trovare_posizione_massimo(int* valori, int dimensione_valori){
    int indice_valori = 0;
    int massimo = valori[indice_valori];
    int posizione_massimo = indice_valori;
    while(indice_valori < dimensione_valori){
        indice_valori = indice_valori + 1;
        if(massimo < valori[indice_valori]){
            massimo = valori[indice_valori];
            posizione_massimo = indice_valori;
        }
    }
    return posizione_massimo;
}
partita* cambiare_turno(partita* partita_attuale){
    *partita_attuale = scrivere_turno(partita_attuale, leggere_turno(partita_attuale) + 1);
    if(leggere_turno(partita_attuale) > leggere_numero_giocatori(partita_attuale)){
        *partita_attuale = scrivere_turno(partita_attuale, 1);
    }
    return partita_attuale;
}
partita* lanciare_dadi(partita* partita_attuale,int FACCIA_MINIMA_DADO,int FACCIA_MASSIMA_DADO,int NUMERO_DADI){
    int indice_dado = 0;
    int lancio;
    while(indice_dado <= NUMERO_DADI){
        lancio = generare_numero(FACCIA_MINIMA_DADO, FACCIA_MASSIMA_DADO);
        *partita_attuale = scrivere_dadi(partita_attuale, indice_dado, lancio);
        indice_dado = indice_dado + 1;
    }
    return partita_attuale
}
partita* incrementare_lanci_effettuati(partita* partita_attuale){
    giocatore* giocatore_attuale;
    int lanci_effettuati;
    *giocatore_attuale = leggere_giocatore(partita_attuale, leggere_turno(partita_attuale));
    lanci_effettuati = leggere_lanci_effettuati(giocatore_attuale);
    lanci_effettuati = lanci_effettuati + 1;
    *giocatore_attuale = scrivere_lanci_effettuati(giocatore_attuale, lanci_effettuati);
    *partita_attuale = scrivere_giocatore(partita_attuale,giocatore_attuale, leggere_turno(partita_attuale));
    return partita_attuale;
}
partita* incrementare_turno(partita* partita_attuale){
    int turno = leggere_turno(partita_attuale);
    turno = turno + 1;
    if(turno > leggere_numero_giocatori(partita_attuale)){
        turno = 1;
    }
    *partita_attuale = scrivere_turno(partita_attuale, turno);
    return partita_attuale;
}
partita* spostare_giocatore(partita* partita_attuale){
    *partita_attuale = sommare_lancio_posizione(partita_attuale);
    int indice_giocatore = leggere_turno(partita_attuale);
    if (indice_giocatore > leggere_lunghezza_percorso(partita_attuale)){
        *partita_attuale = calcolare_caselle_eccesso(partita_attuale);
    }
    return partita_attuale;
}
partita* sommare_lancio_posizione(partita* partita_attuale){
    giocatore* giocatore_attuale;
    *giocatore_attuale = leggere_posizione_giocatore(leggere_giocatore(partita_attuale), leggere_turno(partita_attuale) + sommare_dadi(partita_attuale));
    *partita_attuale = scrivere_giocatore(partita_attuale, giocatore_attuale, leggere_turno(partita_attuale));
    return partita_attuale;
}
partita* calcolare_caselle_eccesso(partita* partita_attuale){
    giocatore* giocatore_attuale;
    int eccesso = leggere_posizione_giocatore (leggere_giocatore(partita_attuale), leggere_turno(partita_attuale)) - leggere_lunghezza_percorso(partita_attuale);
    *giocatore_attuale = leggere_giocatore(partita_attuale,leggere_turno(partita_attuale));
    *partita_attuale = scrivere_giocatore(partita_attuale, scrivere_posizione_giocatore(giocatore_attuale , leggere_posizione_giocatore(giocatore_attuale) - eccesso), leggere_turno(partita_attuale));
    return partita_attuale;
}
int sommare_dadi(partita* partita_attuale, int NUMERO_DADI){
    int somma_dadi = 0;
    int indice_dado = 0;
    while (indice_dado <= NUMERO_DADI){
        somma_dadi = somma_dadi + leggere_dadi(partita_attuale, indice_dado);
        indice_dado = indice_dado + 1; 
    }
    return somma_dadi;
}
partita* gestire_casella(partita* partita_attuale, char NOME_OCA[],char NOME_PRIGIONE[],char NOME_PONTE[],char NOME_LABIRINTO[],char NOME_LOCANDA[],char NOME_POZZO[],char NOME_SCHELETRO[],char NOME_VITTORIA[],int CASELLA_ARRIVO_SCHELETRO){
    giocatore* giocatore_attuale;
    char nome[DIMENSIONE_MASSIMA_NOME_GIOCATORE];
    do{
        *giocatore_attuale = leggere_giocatore(partita_attuale, leggere_turno(partita_attuale));
        nome = leggere_nome_casella(leggere_percorso(partita_attuale, leggere_posizione_giocatore(giocatore_attuale)));
        if(confrontare_stringhe(nome, NOME_OCA) == TRUE)
        {
            //stampare schermata_oca e aspettare input
            *partita_attuale = gestire_oca(partita_attuale);
        }
        else if(confrontare_stringhe(nome, NOME_PONTE) == TRUE )
        {
            //schermata_ponte e aspettare input
            *partita_attuale = spostare_giocatore(partita_attuale);
        }
        else if (confrontare_stringhe(nome,NOME_LOCANDA) == TRUE )
        {
            //stampare schermata_locanda e aspettare input
            *giocatore_attuale = scrivere_autorizzazione(giocatore_attuale, TURNI_ATTESA_LOCANDA);
            *partita_attuale = scrivere_giocatori(partita_attuale, giocatore_attuale, leggere_turno(partita_attuale));
        }
        else if (confrontare_stringhe(nome,NOME,POZZO) == TRUE )
        {
            //stampare schermata_pozzo e aspettare input
            *partita_attuale = impostare_autorizzazioni(partita_attuale, NOME_POZZO);    
        }
        else if (confrontare_stringhe(nome,NOME_PRIGIONE) == TRUE )
        {
            //stampare schermata_prigione e aspettare input
            *partita_attuale = impostare_autorizzazioni(partita_attuale, NOME_PRIGIONE);
        }
        else if (confrontare_stringhe(nome,NOME_LABIRINTO) == TRUE )
        {
            //stampare schermata_labirinto e aspettare input
            giocatore_attuale = scrivere_posizione_giocatore(giocatore_attuale, calcolare_proporzione(leggere_lunghezza_percorso(partita_attuale), CASELLA_ARRIVO_LABIRINTO))
            while (confrontare_stringhe(leggere_nome_casella(leggere_percorso(partita_attuale, leggere_posizione_giocatore(giocatore_attuale))), FINE_STRINGA) == FALSE )
            {
                *giocatore_attuale = scrivere_posizione_giocatore(giocatore_attuale, leggere_posizione_giocatore(giocatore_attuale) - 1);
            }
            *partita_attuale = scrivere_giocatori(partita_attuale, giocatore_attuale, leggere_turno(partita_attuale));
        }
        else if (confrontare_stringhe(nome,NOME_SCHELETRO) == TRUE )
        {
            //stampare schermata_scheletro e aspettare input
            *giocatore_attuale = scrivere_posizione_giocatore(giocatore_attuale, CASELLA_ARRIVO_SCHELETRO);
            *partita_attuale = scrivere_giocatori(partita_attuale, giocatore_attuale, leggere_turno(partita_attuale));
        }
              //stampare percorso e aspettare input  
    }while(leggere_nome_casella(leggere_percorso(partita_attuale, leggere_posizione_giocatore(giocatore_attuale))) != FINE_STRINGA);
    return partita_attuale;
}
partita* gestore_oca(partita* partita_attuale,int PRIMO_LANCIO_3_6,int PRIMO_LANCIO_4_5,int DADO_MINORE_PRIMO_LANCIO,int DADO_MAGGIORE_PRIMO_LANCIO,int PRIMO_DADO,char FINE_STRINGA){
    giocatore* giocatore_attuale = leggere_giocatore(partita_attuale, leggere_turno(partita_attuale));
    if(leggere_lanci_effettuati(giocatore_attuale) == 1)
    {
        if(leggere_dadi(partita_attuale,PRIMO_DADO) == DADO_MINORE_PRIMO_LANCIO) || ((leggere_dadi(partita_attuale,PRIMO_DADO) == DADO_MAGGIORE_PRIMO_LANCIO))
        {
            *giocatore_attuale = scrivere_posizione_giocatore(giocatore_attuale, calcolare_proporzione(leggere_lunghezza_percorso(partita_attuale), PRIMO_LANCIO_3_6));
        }
        else
        {
            *giocatore_attuale = scrivere_posizione_giocatore(giocatore_attuale, calcolare_proporzione(leggere_lunghezza_percorso(partita_attuale), PRIMO_LANCIO_4_5));
        }
        while(confrontare_stringhe(leggere_nome_casella(leggere_percorso(partita_attuale, leggere_posizione_giocatore(giocatore_attuale))), FINE_STRINGA) == FALSE)
        {
            *giocatore_attuale = scrivere_posizione_giocatore(giocatore_attuale, leggere_posizione_giocatore(giocatore_attuale) - 1);
        }
        *partita_attuale = scrivere_giocatori(partita_attuale, giocatore_attuale, leggere_turno(partita_attuale));
    }
    else
    {
        *partita_attuale = spostare_giocatore(partita_attuale);
    }
    return partita_attuale;
}
partita* impostare_autorizzazioni(partita* partita_attuale, char nome_casella_attuale[]){
    giocatore* giocatore_attuale;
    int indice_giocatore = 0;
    while (indice_giocatore <= leggere_numero_giocatori(partita_attuale)){
        *giocatore_attuale = leggere_giocatore(partita_attuale, indice_giocatore);
        if (confrontare_stringhe (leggere_nome_casella (leggere_percorso (partita_attuale, leggere_posizione_giocatore(giocatore_attuale))), nome_casella_attuale) == TRUE){
            //stampare schermata_liberato e attendere input
            *giocatore_attuale = scrivere_autorizzazione(giocatore_attuale, 0);
            *partita_attuale = scrivere_giocatori(partita_attuale, giocatore_attuale, indice_giocatore);
        }
        indice_gicoatore = indice_giocatore + 1;
    }
    *giocatore_attuale = leggere_giocatore(partita_attuale, leggere_turno(partita_attuale));
    *giocatore_attuale = scrivere_autorizzazione(giocatore_attuale, 1);
    *partita_attuale = scrivere_giocatori(partita_attuale, giocatore_attuale, leggere_turno(partita_attuale));
    return partita_attuale
}
partita* gestire_autorizzazione(partita* partita_attuale, char NOME_LOCANDA[], char NOME_PRIGIONE[], int DADO_MINORE_USCITA_PRIGIONE, int DADO_MAGGIORE_USCITA_PRIGIONE){
    giocatore* giocatore_attuale = leggere_giocatore(partita_attuale, leggere_turno(partita_attuale));
    int autorizzazione = leggere_atuorizzazione(giocatore_attuale);
    if (confrontare_stringhe(leggere_nome_casella(leggere_percorso(partita_attuale, leggere_posizione_giocatore(giocatore_attuale)))) == TRUE){
        *giocatore_attuale = scrivere_autorizzazione(giocatore, leggere_autorizzazione(giocatore_attuale) - 1);
        //stampare schermata_locanda_turno_passato e attende input
    }
    else if(confrontare_Stringhe(leggere_nome_casella(leggere_percorso(partita_attuale,leggere_posizione_giocatore(giocatore_attuale))),NOME_PRIGIONE) == TRUE ){
        //stampare schermata_lancio_dadi_prigione e richiedere input
        *partita_attuale = lanciare_dadi(partita_attuale)
        //stampare schermata_lancio_dadi_prigione con lancio effettuato e richiedere input
        if((sommare_dadi(partita_attauel) == DADO_MINORE_USCITA_PRIGIONE) || (sommare_dadi(partita_attuale) == DADO_MAGGIORE_USCITAPRIGIONE)){
            *giocatore_attuale = scrivere_autorizzazione(giocatore_attuale, 0);
        }
    }
    *partita_attuale = scrivere_giocatore(partita_attuale,giocatore_attuale,leggere_turno(partita_attuale));
    return partita_attuale;
}
int confrontare_stringhe(char stringa_1[],char stringa_2[],char FINE_STRINGA){
    int indice_stringa = 0;
    int esito = 1;
    while(stringa_1[indice_stringa] != FINE_STRINGA){
        if(stringa_1[indice_stringa] != stringa_2[indice_stringa]){
            esito = 0;
        }
        indice_stringa = indice_stringa + 1;
    }
    return esito;
}
