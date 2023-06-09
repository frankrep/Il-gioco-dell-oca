cmake_minimum_required(VERSION 3.25)
project(Il_Gioco_dell_Oca C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(Il_Gioco_dell_Oca
        src/aiuto.c
        src/aiuto.h
        src/casella.c
        src/casella.h
        src/classifica.c
        src/classifica.h
        src/costanti.h
        src/generare_percorso.c
        src/generare_percorso.h
        src/gestire_partita.c
        src/gestire_partita.h
        src/gestire_stampa.c
        src/gestire_stampa.h
        src/giocatore.c
        src/giocatore.h
        src/inizializzare_partita.c
        src/inizializzare_partita.h
        src/partita.c
        src/partita.h
        src/principale.c
        src/salvare_caricare_partita.c
        src/salvare_caricare_partita.h
        src/stampare_percorso.c
        src/stampare_percorso.h
        src/vincitore.c
        src/vincitore.h
        src/generare_numero_casuale.c
        src/generare_numero_casuale.h
        )
