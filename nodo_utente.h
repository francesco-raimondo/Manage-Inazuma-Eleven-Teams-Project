#ifndef NODO_UTENTE_H
#define NODO_UTENTE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utente.h"


typedef struct nodo_utente* lista_utenti; 

struct nodo_utente {
    utente n_utente;            	// puntatore alla struct utente
    lista_utenti next;             // Puntatore al prossimo nodo
};

int crea_lista_utenti(lista_utenti* head_utenti); 

utente cerca_utente(lista_utenti head, const char* username);

int aggiungi_utente(lista_utenti* head, utente nuovo_utente);

//questa richiamerà rimuovi_squadra, destroy_lista_squadre
int rimuovi_utente(lista_utenti* head, const char* nome);

int destroy_lista_utenti(lista_utenti* head);

void stampa_lista_utenti(lista_utenti head);

int check_username(lista_utenti head, char* username);

//ritorna l'utente attivo se l'accesso è stato effettuato, altrimenti NULL
utente accesso(lista_utenti head_utenti, char* username, char* password);

int salva_su_file(lista_utenti head_utenti);

void carica_da_file(lista_utenti* head_utenti);
#endif
