#ifndef NODO_GIOCATORE_H    
#define NODO_GIOCATORE_H    

#include <stdbool.h>   
#include <stdio.h>     
#include <stdlib.h>    
#include <string.h> 
#include "giocatore.h"

typedef struct nodo_giocatore* lista_giocatori;

struct nodo_giocatore {
	giocatore n_giocatore;
	lista_giocatori next;   //puntatore al prossimo nodo della lista giocatori
};



int aggiungi_giocatore(lista_giocatori* head, giocatore nuovo_giocatore, squadra* squadra_attiva);

giocatore cerca_giocatore(lista_giocatori head, const char* nome_giocatore);

int rimuovi_giocatore(lista_giocatori* head,  const char* nome_giocatore);

int destroy_lista_giocatori(lista_giocatori* head);

int stampa_lista_giocatori(lista_giocatori head);

giocatore* seleziona_giocatore(lista_giocatori head_giocatori, char* nome_giocatore);

int check_nome_g(lista_giocatori head, char* nome); 

int stampa_titolari(lista_giocatori head);

int stampa_riserve(lista_giocatori head);

#endif
