#ifndef GESTIRE_PARTITA_H_
#define GESTIRE_PARTITA_H_

vincitore* gestire_partita(partita* partita_attuale);
partita* scegliere_giocatore(partita* partita_attuale, int PRIMO_DADO);
vincitore* inizializzare_vincitore(partita* partita_attuale);
int generare_numero(FILE* file_seme,int numero_massimo,int numero_minimo);
int generare_seme(int seme);
int generare_casuale(int seme,int numero_massimo,int numero_minimo);
int trovare_posizione_massimo(int* valori, int dimensione_valori);
partita* cambiare_turno(partita* partita_attuale);
partita* lanciare_dadi(partita* partita_attuale,int FACCIA_MINIMA_DADO,int FACCIA_MASSIMA_DADO,int NUMERO_DADI);
partita* incrementare_lanci_effettuati(partita* partita_attuale);
partita* incrementare_turno(partita* partita_attuale);
partita* spostare_giocatore(partita* partita_attuale);
partita* sommare_lancio_posizione(partita* partita_attuale);
partita* calcolare_caselle_eccesso(partita* partita_attuale);
int sommare_dadi(partita* partita_attuale, int NUMERO_DADI);
partita* gestire_casella(partita* partita_attuale, char NOME_OCA[],char NOME_PRIGIONE[],char NOME_PONTE[],char NOME_LABIRINTO[],char NOME_LOCANDA[],char NOME_POZZO[],char NOME_SCHELETRO[],char NOME_VITTORIA[],int CASELLA_ARRIVO_SCHELETRO);
partita* gestore_oca(partita* partita_attuale,int PRIMO_LANCIO_3_6,int PRIMO_LANCIO_4_5,int DADO_MINORE_PRIMO_LANCIO,int DADO_MAGGIORE_PRIMO_LANCIO,int PRIMO_DADO,char FINE_STRINGA);
partita* impostare_autorizzazioni(partita* partita_attuale, char nome_casella_attuale[]);
partita* gestire_autorizzazione(partita* partita_attuale, char NOME_LOCANDA[], char NOME_PRIGIONE[], int DADO_MINORE_USCITA_PRIGIONE, int DADO_MAGGIORE_USCITA_PRIGIONE);
int confrontare_stringhe(char stringa_1[],char stringa_2[],char FINE_STRINGA);
#endif /* CASELLA_H_ */