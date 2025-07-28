#ifndef NODO_SQUADRA_H
#define NODO_SQUADRA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "squadra.h"

typedef struct utente* utente;
typedef struct nodo_utente* lista_utenti; 

typedef struct nodo_squadra* lista_squadre;

struct nodo_squadra{
	squadra n_squadra;
	lista_squadre next;
};


int aggiungi_squadra(lista_squadre* head, squadra nuova_squadra); 

squadra cerca_squadra(lista_squadre head, const char* nome_squadra_da_cercare);

int rimuovi_squadra(lista_squadre* head, const char* nome_squadra);

int destroy_lista_squadre(lista_squadre* head);

int stampa_lista_squadre(lista_squadre head);

squadra seleziona_squadra(lista_squadre head_squadre, char* nome_squadra);

int check_nome_s(lista_squadre head, char* nome_squadra); 
#endif
