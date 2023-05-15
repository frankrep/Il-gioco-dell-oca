#ifndef CASELLA_H_
#define CASELLA_H_

typedef struct
{
    char* nome_casella;
    int numero_casella;
    char* percorso_file;
    char* simbolo;
}casella;

void scrivere_nome_casella(casellla* casella_attuale,char* nome_da_inserire);
char* leggere_nome_casella(casella* casella_attuale);
void scrivere_numero_casella(casella* casella_attuale,int numero_casella_da_inserire);
int leggere_numero_casella(casella* casella_attuale);
void scrivere_percorso_file(casella* casella_attuale,char percorso_file_generale);
char* leggere_percorso_file(casella* casella_attuale);
void scrivere_simbolo(casella* casella_attuale, char* simbolo_da_inserire);
char* leggere_simbolo(casella* casella_attuale);
#endif /* CASELLA_H_ */