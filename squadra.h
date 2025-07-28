#ifndef SQUADRA_H
#define SQUADRA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodo_giocatore.h"


typedef struct utente* utente;
typedef struct nodo_utente* lista_utenti; 


typedef struct squadra* squadra;

struct squadra{
    char nome[30];
    char allenatore[20];
    int num_giocatori;
    int num_titolari;
    int num_panchina;
    lista_giocatori giocatori;  // Lista dei giocatori nella squadra
    int potenza_squadra;
};



const char* get_nome_squadra(squadra s);

int get_allenatore(squadra s, char* allenatore);

int get_num_giocatori(squadra s);

int get_num_titolari(squadra s);

int get_num_panchina(squadra s);

int get_potenza_squadra(squadra s);


int set_nome_squadra(squadra s, const char* nome_squadra);

int set_allenatore(squadra s, const char* allenatore);

int set_num_giocatori(squadra s, int num_giocatori);

int set_num_titolari(squadra s, int num_titolari);

int set_num_panchina(squadra s, int num_panchina);

int set_potenza_squadra(squadra s, int potenza_squadra);


int get_lista_giocatori(squadra squadra_attiva, lista_giocatori* head_giocatori_della_squadra);

int set_lista_giocatori(squadra squadra_attiva, lista_giocatori head_giocatori_della_squadra);

squadra crea_squadra(squadra* nuova_squadra, const char* nome, const char* allenatore); 

int stampa_squadra(squadra squadra_attiva); 

int stampa_all_squadra(squadra squadra_attiva); 

int destroy_squadra(squadra* squadra_da_rimuovere);

int is_complete(squadra squadra_attiva);  	//0: non completa,   1: completa

int calcola_potenza_squadra(squadra* squadra_attiva, int potenza_giocatore_aggiunto);
#endif


