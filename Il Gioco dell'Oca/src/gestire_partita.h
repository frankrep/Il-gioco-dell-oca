/*
 * gestire_partita.h
 *
 */

#ifndef GESTIRE_PARTITA_H_
#define GESTIRE_PARTITA_H_

#include "partita.h"
#include "vincitore.h"

vincitore gestire_partita (partita* partita_attuale, int * sale);
int confrontare_stringhe(const char stringa_1[], const char stringa_2[]);

#endif /* GESTIRE_PARTITA_H_ */