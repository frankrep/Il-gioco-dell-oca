#include "partita.h"
#include "stampare_percorso.h"
#include <stdio.h>
#include <stdlib.h>

void stampare_percorso (partita* partita_attuale) {
    stampare_parte_superiore_casella();
    int indice_riga_superiore = 0;
    int colonne_parte_sinistra;
    while (indice_riga_superiore <= ALTEZZA_TABELLONE)
    {
        int indice_altezza_disegno = 0;
        while (indice_altezza_disegno <= ALTEZZA_DISEGNO_TABELLA)
        {
            if (colonne_parte_sinistra > 0)
            {
                if (indice_riga_superiore < (meta_righe +1))
                {
                    ultima_casella_stampata = stampare_superiore_sinistra(partita_attuale, colonne_parte_sinistra, 0);
                }
                else
                {
                    ultima_casella_stampata = stampare_inferiore_sinistra(partita_attuale,colonne_parte_sinistra, 0);
                }
            }
            if (indice_riga_superiore <= (meta_righe -1))
            {
                ultima_casella_stampata = stampare_parte_centrale_incremento(partita_attuale, ultima_casella_stampata, (LARGHEZZA_TABELLONE - colonne_parte_destra - colonne_parte_sinistra));
            }
            else 
            {
                stampare_parte_centrale_decremento(partita_attuale, ultima_casella_stampata - (ALTEZZA_TABELLONE - (2 * (colonne_parte_sinistra))), (LARGHEZZA_TABELLONE - colonne_parte_destra - colonne_parte_sinistra));
            }
            if (colonne_parte_destra > 0)
            {
                if (indice_riga_superiore <= (meta_righe -1))
                {
                    stampare_parte_destra(partita_attuale, colonne_parte_destra, ultima_casella_stampata, 0);
                }
                else
                {
                    
                }
            }
        }
    }
}