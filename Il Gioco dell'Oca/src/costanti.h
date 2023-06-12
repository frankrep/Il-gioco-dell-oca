/*
 * costanti.h
 *
 */

#ifndef COSTANTI_H_
#define COSTANTI_H_


#define DIMENSIONE_MASSIMA_PERCORSO 90
#define DIMENSIONE_MINIMA_PERCORSO 50
#define NUMERO_MASSIMO_GIOCATORI 4
#define NUMERO_MINIMO_GIOCATORI 2
#define FACCIA_MINIMA_DADO 1
#define FACCIA_MASSIMA_DADO 6
#define NUMERO_DADI 2
#define DISTANZA_OCHE 9
#define NUMERO_CASELLE_SPECIALI 7
#define PRIMO_DADO 0
#define NUMERO_MASSIMO_CARATTERI_SIMBOLO 5
#define ALTEZZA_DISEGNO_CASELLA 3
#define LARGHEZZA_DISEGNO_CASELLA 5
#define SPAZIO_DISPONIBILE_CASELLA 4
#define LARGHEZZA_TABELLONE 15
#define ALTEZZA_TABELLONE 6
#define PRIMO_LANCIO_3_6 38
#define PRIMO_LANCIO_4_5 76
#define DADO_MINORE_PRIMO_LANCIO 3
#define DADO_MAGGIORE_PRIMO_LANCIO 6
#define TURNI_ATTESA_LOCANDA 3
#define CASELLA_ARRIVO_LABIRINTO 33
#define CASELLA_ARRIVO_SCHELETRO 1
#define DADO_MINORE_USCITA_PRIGIONE 5
#define DADO_MAGGIORE_USCITA_PRIGIONE 7
#define DIMENSIONE_MINIMA_NOME_PARTITA 3
#define DIMENSIONE_MASSIMA_NOME_PARTITA 13
#define DIMENSIONE_MINIMA_NOME_GIOCATORE 3
#define DIMENSIONE_MASSIMA_NOME_GIOCATORE 19
#define DIMENSIONE_MASSIMA_NOME_CASELLA 10
#define NUMERO_MASSIMO_PARTITE 5
#define NUMERO_MASSIMO_CLASSIFICATI 10
#define NUMERO_SEMI 6
static const unsigned long long SEME_INIZIALE_1 = 123456789;
static const unsigned long long SEME_INIZIALE_2 = 543210987;
static const unsigned long long SEME_INIZIALE_3 = 876543210;
static const unsigned long long SEME_INIZIALE_4 = 135792468;
static const unsigned long long SEME_INIZIALE_5 = 987654321;
static const unsigned long long SEME_INIZIALE_6 = 246813579;
static const unsigned long long MOLTIPLICATORE = 6364136223846793005ULL;
static const unsigned long long INCREMENTO = 1442695040888963407ULL;
static const unsigned long long DIVISORE = 9223372036854775808ULL;
#define BASE 10
#define UNITA 1


#define NUMERO_MASSIMO_CARATTERI_PERCORSO 256
#define CARATTERE_SPAZIO ' '
#define NUMERO_MASSIMO_OPZIONI_PRINCIPALE  4
#define NUMERO_MASSIMO_OPZIONE_PAUSA 3
#define NUMERO_MASSIMO_OPZIONI_AIUTO  2
#define POSIZIONE_GIOCATORE_1 0
#define POSIZIONE_GIOCATORE_2 1
#define POSIZIONE_GIOCATORE_3 2
#define POSIZIONE_GIOCATORE_4 3
#define NUMERO_GIOCATORI_STRATO_CASELLA 2
#define LUNGHEZZA_SCHERMATA 80
#define ALTEZZA_SCHERMATA 25
#define ALTEZZA_MENU_INTERFACCIA_PERCORSO 6
#define ALTEZZA_TITOLO_GRANDE 8
#define RISPOSTA_AFFERMATIVA_MAIUSCOLO 'S'
#define RISPOSTA_AFFERMATIVA_MINUSCOLO 's'
#define RISPOSTA_NEGATIVA_MAIUSCOLO 'N'
#define RISPOSTA_NEGATIVA_MINUSCOLO 'n'
#define FALSO 0
#define VERO 1
#define FINE_FILE EOF
#define DIMENSIONE_MASSIMA_SIMBOLO_CASELLA 5
#define SPIAZZAMENTO_DADO 19
#define NUMERO_MASSIMO_PUNTINI_FACCIA_DADO 7
#define NUMERO_CIFRE 10
#define SPIAZZAMENTO_MESSAGGIO_ERRORE 2
#define SPIAZZAMENTO_STAMPA_VALORI 5
#define SPIAZZAMENTO_SINGOLO_VALORE 2

//Caratteri per scelta opzioni menu
#define TASTO_LANCIO_DADI_MINUSCOLO 'l'
#define TASTO_LANCIO_DADI_MAIUSCOLO 'L'
#define TASTO_MENU_MINUSCOLO 'm'
#define TASTO_MENU_MAIUSCOLO 'M'
#define TASTO_AVANZAMENTO_MINUSCOLO 'a'
#define TASTO_AVANZAMENTO_MAIUSCOLO 'A'
#define TASTO_SALVATAGGIO_MINUSCOLO 's'
#define TASTO_SALVATAGGIO_MAIUSCOLO 'S'
#define TASTO_INDIETRO '0'


//COLORI SCHERMATA
#define COLORE_PRINCIPALE_SCHERMATA 15
#define NERO 0
#define BLU 1
#define VERDE 2
#define AZZURRO 3
#define ROSSO 4
#define VIOLA 5
#define ARANCIO 6
#define GRIGIO_MOLTO_CHIARO 7
#define GRIGIO 8
#define BLU_OCEANO 9
#define VERDE_FLUO 10
#define CELESTE 11
#define ROSSO_PALLIDO 12
#define VIOLETTO 13
#define GIALLINO 14
#define BIANCO 15


static const char ERRORE_FILE_NON_TROVATO[LUNGHEZZA_SCHERMATA + 1] = "ERRORE! FILE NON TROVATO \0";
static const char FINE_STRINGA = '\0';
static const char CARATTERE_A_CAPO = '\n';
static const char STRINGA_VUOTA[1] = "\0";
static const char NOME_GIOCATORE_INDIETRO [2] = "0\0";
static const char PEDINE_DISPONIBILI[NUMERO_MASSIMO_GIOCATORI] = "#$%&";
static const char NOME_OCA[DIMENSIONE_MASSIMA_NOME_CASELLA] = "OCA\0";
static const char NOME_PRIGIONE[DIMENSIONE_MASSIMA_NOME_CASELLA] = "PRIGIONE\0";
static const char NOME_PONTE[DIMENSIONE_MASSIMA_NOME_CASELLA] = "PONTE\0";
static const char NOME_LABIRINTO[DIMENSIONE_MASSIMA_NOME_CASELLA] = "LABIRINTO\0";
static const char NOME_LOCANDA[DIMENSIONE_MASSIMA_NOME_CASELLA] = "LOCANDA\0";
static const char NOME_POZZO[DIMENSIONE_MASSIMA_NOME_CASELLA] = "POZZO\0";
static const char NOME_SCHELETRO[DIMENSIONE_MASSIMA_NOME_CASELLA] = "SCHELETRO\0";
static const char NOME_VITTORIA[DIMENSIONE_MASSIMA_NOME_CASELLA] = "VITTORIA\0";
static const char SIMBOLO_PONTE[DIMENSIONE_MASSIMA_SIMBOLO_CASELLA] = " == \0";
static const char SIMBOLO_PRIGIONE[DIMENSIONE_MASSIMA_SIMBOLO_CASELLA] = "[#] \0";
static const char SIMBOLO_LABIRINTO[DIMENSIONE_MASSIMA_SIMBOLO_CASELLA] = " @  \0";
static const char SIMBOLO_VITTORIA[DIMENSIONE_MASSIMA_SIMBOLO_CASELLA] = " W  \0";
static const char SIMBOLO_POZZO[DIMENSIONE_MASSIMA_SIMBOLO_CASELLA] = "(O) \0";
static const char SIMBOLO_SCHELETRO[DIMENSIONE_MASSIMA_SIMBOLO_CASELLA] = " xx \0";
static const char SIMBOLO_OCA[DIMENSIONE_MASSIMA_SIMBOLO_CASELLA] = " O  \0";
static const char SIMBOLO_LOCANDA[DIMENSIONE_MASSIMA_SIMBOLO_CASELLA] = " ^^ \0";
static const char SIMBOLO_VUOTO[DIMENSIONE_MASSIMA_SIMBOLO_CASELLA] = "    \0";
static const char TITOLO_PERCORSO[LUNGHEZZA_SCHERMATA + 1] = " ___________________________<IL GIOCO DELL'OCA>____________________________ \0";
static const char CONTORNO_LATERALE_CASELLA = '|';
static const char CONTORNO_SUPERIORE_CASELLA = '_';
static const char CONTORNO_INFERIORE_CASELLA = '_';
static const char CARATTERE_PUNTO_FACCIA_DADO = '*';
static const char CARATTERE_PUNTO_INTERROGATIVO = '?';
static const char CARATTERE_COPPA = '$';
static const char CARATTERE_BECCO = '8';
static const char CARATTERE_SFONDO = '_';
static const char FILE_CASELLE_SPECIALI [NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_caselle_speciali.bin";
static const char FILE_CLASSIFICA_TOP_10 [NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_classifica_top_10.bin";
static const char FILE_CLASSIFICA[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_classifica.txt";
static const char FILE_CREDITI[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\crediti.txt";
static const char FILE_SEME [NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\filebin\\seme.bin";
static const char FILE_MENU_AIUTO[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_menu_aiuto.txt";
static const char FILE_MANUALE[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_manuale.txt";
static const char FILE_MENU_REGOLAMENTO[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_menu_regolamento.txt";
static const char FILE_PERCORSO[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_percorso.txt";
static const char FILE_REGOLE[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_regole.txt";
static const char FILE_MENU_CARICA_PARTITA[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_menu_carica_partita.txt";
static const char FILE_SCELTA_G_INIZIALE[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_scelta_g_iniziale.txt";
static const char FILE_SCELTA_LUNG_PERCO[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_scelta_lung_perco.txt";
static const char FILE_SCELTA_N_GIOCATORI[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_scelta_n_giocatori.txt";
static const char FILE_SCELTA_NOMI_GIOCATORI[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_scelta_nomi_giocatori.txt";
static const char FILE_MENU_PRINCIPALE[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_menu_principale.txt";
static const char FILE_SCELTA_NOME_PARTITA[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_scelta_nome_partita.txt";
static const char FILE_SCELTA_SLOT_SALVARE_PARTITA[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_scelta_slot_salvare_partita.txt";
static const char FILE_DETTAGLI_PARTITA[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_dettagli_partita.txt";
static const char FILE_VITTORIA_NOMI[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_vittoria_nomi.txt";
static const char FILE_INTRO[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_intro.txt";
static const char FILE_EASTEREGG1[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_easteregg1.txt";
static const char FILE_EASTEREGG2[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_easteregg2.txt";
static const char FILE_SALVATAGGIO [NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_salvataggio.bin";
static const char FILE_SCHERMATA_LABIRINTO[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_schermata_labirinto.txt";
static const char FILE_SCHERMATA_LANCIO_DADI_PRIGIONE[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_schermata_lancio_dadi_prigione.txt";
static const char FILE_SCHERMATA_LIBERATO[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_schermata_liberato.txt";
static const char FILE_SCHERMATA_LOCANDA_TURNO_PASSATO[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_schermata_locanda_turno_passato.txt";
static const char FILE_SCHERMATA_LOCANDA[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_schermata_locanda.txt";
static const char FILE_SCHERMATA_OCA[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_schermata_oca.txt";
static const char FILE_SCHERMATA_PERM_POZZO[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_schermata_perm_pozzo.txt";
static const char FILE_SCHERMATA_PONTE[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_schermata_ponte.txt";
static const char FILE_SCHERMATA_POZZO[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_schermata_pozzo.txt";
static const char FILE_SCHERMATA_PRIGIONE[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_schermata_prigione.txt";
static const char FILE_SCHERMATA_SCHELETRO[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_schermata_scheletro.txt";
static const char FILE_CONFERMA_INSERIMENTO[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_conferma_inserimento.txt";
static const char FILE_CONFERMA_SALVATAGGIO[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_conferma_salvataggio.txt";
static const char FILE_RICHIESTA_C_INSERIMENTO[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_richiesta_c_inserimento.txt";
static const char FILE_RICHIESTA_C_SALVATAGGIO[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_richiesta_c_salvataggio.txt";
static const char FILE_STAMPE[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\stampe.txt";
static const char FILE_MESSAGGI_ERRORE[NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_stampe.txt";
static const char FILE_MENU_DI_PAUSA [NUMERO_MASSIMO_CARATTERI_PERCORSO] = "..\\src\\interfacce\\file_menu_di_gioco.txt";






#endif /* COSTANTI_H_ */
