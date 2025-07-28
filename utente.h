#ifndef UTENTE_H
#define UTENTE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodo_squadra.h"

typedef struct utente* utente;

struct utente {
    char username[15];   		   // Username dell'utente
    char password[9];   		   // Password dell'utente
    lista_squadre squadre;         // Lista di squadre dell'utente  
};


const char* get_username(utente u);

int get_password(utente u, char* password);

int set_username(utente u, const char* username); 

int set_username(utente u, const char* password);

int get_lista_squadre(utente utente_attivo, lista_squadre* head_squadre_utente);

int set_lista_squadre(utente utente_attivo, lista_squadre head_squadre_utente);

int crea_utente(utente* nuovo_utente, const char* username, const char* password); 

int stampa_utente(utente u);

int destroy_utente(utente* utente_da_rimuovere);
#endif 
