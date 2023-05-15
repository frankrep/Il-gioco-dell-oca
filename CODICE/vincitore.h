#ifndef VINCITORE_H_
#define VINCITORE_H_

typedef struct
{
    char* nome_vincitore;
    char pedina_vincitore;
    int lunghezza_percorso_vincitore;
    int lanci_vincitore;
}casella;

void scrivere_nome_vincitore(vincitore* vincitore_attuale, char* nome);
char* leggere_nome_vincitore(vincitore* vincitore_attuale);
void scrivere_pedina_vincitore(vincitore* vincitore_attuale, char pedina);
char leggere_pedina_vincitore(vincitore* vincitore_attuale);
void scrivere_lunghezza_percorso_vincitore(vincitore* vincitore_attuale,int lunghezza);
int leggere_lunghezza_percorso_vincitore(vincitore* vincitore_attuale);
void scrivere_lanci_vincitore(vincitore* vincitore_attuale,int lanci);
int leggere_lanci_vincitore(vincitore* vincitore_attuale);

#endif /* VINCITORE_H_ */