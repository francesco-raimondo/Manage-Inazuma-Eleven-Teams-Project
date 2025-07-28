#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include "squadra.h"  

//////  GETTER e SETTER //////
const char* get_nome_squadra(squadra s) {
    if(s==NULL){
    	return NULL;
    }
    else{
    	return s->nome;
    }   	
}

int get_allenatore(squadra s, char* allenatore) {
    if (s == NULL)
        return 1;
        
    strcpy(allenatore, s->allenatore); 
    return 0;
}

int get_num_giocatori(squadra s) {
    if (s == NULL)
        return -1; 
    
    return s->num_giocatori;
}

int get_num_titolari(squadra s) {
    if (s == NULL)
        return -1;
        
    return s->num_titolari;
}

int get_num_panchina(squadra s) {
    if (s == NULL)
        return -1;
        
    return s->num_panchina;
}

int get_potenza_squadra(squadra s) {
    if (s == NULL)
        return -1;
        
    return s->potenza_squadra;
}


int set_nome_squadra(squadra s, const char* nome_squadra) {
    if (s == NULL)
        return 1;
        
    strcpy(s->nome, nome_squadra); 
    return 0;
}

int set_allenatore(squadra s, const char* allenatore) {
    if (s == NULL)
        return 1;
        
    strcpy(s->allenatore, allenatore); 
    return 0;
}

int set_num_giocatori(squadra s, int num_giocatori) {
    if (s == NULL || num_giocatori < 0)
        return 1;
        
    s->num_giocatori = num_giocatori;
    return 0;
}

int set_num_titolari(squadra s, int num_titolari) {
    if (s == NULL || num_titolari < 0)
        return 1;
        
    s->num_titolari = num_titolari;
    return 0;
}

int set_num_panchina(squadra s, int num_panchina) {
    if (s == NULL || num_panchina < 0)
        return 1;
        
    s->num_panchina = num_panchina;
    return 0;
}

int set_potenza_squadra(squadra s, int potenza_squadra) {
    if (s == NULL || potenza_squadra < 0)
        return 1;
        
    s->potenza_squadra = potenza_squadra;
    return 0;
}



squadra crea_squadra(squadra* nuova_squadra, const char* nome, const char* allenatore){
	*nuova_squadra = (squadra)malloc(sizeof(struct squadra));
	if (*nuova_squadra== NULL)
		return NULL;
	else{
		set_nome_squadra(*nuova_squadra, nome);
		set_allenatore(*nuova_squadra, allenatore);
		set_num_giocatori(*nuova_squadra, 0);
		set_num_titolari(*nuova_squadra, 0);
		set_num_panchina(*nuova_squadra, 0);
		set_potenza_squadra(*nuova_squadra, 0);
		//inizializza la lista dei giocatori a NULL
        (*nuova_squadra)->giocatori = NULL; 
		
	}
	return *nuova_squadra;


}

int stampa_all_squadra(squadra s){
	if(s==NULL)
		return -1;
	stampa_squadra(s);
	if(stampa_lista_giocatori(s->giocatori)==1)
		return 1;
	return 0;
}




int stampa_squadra(squadra s){
	if(s==NULL)
		return 1;
	char nome[30];
    char allenatore[20];
    int num_panchina;
    int num_titolari;
    int potenza_squadra;
    strcpy(nome, get_nome_squadra(s));
    get_allenatore(s,allenatore);
    num_panchina=get_num_panchina(s);
    num_titolari=get_num_titolari(s);
    potenza_squadra=get_potenza_squadra(s);
    printf("\n\n--> Squadra: '%s'\n", nome);
	printf("    Allenatore: %s  |  Num. di titolari: %d  |   Num. di riserve: %d  |   Potenza della squadra: %d   ", allenatore, num_titolari, num_panchina, potenza_squadra);
	if(is_complete(s)==1)
		printf("|  Stato: COMPLETA\n\n");
	else
		printf("|  Stato: NON COMPLETA\n\n");
	printf("\n\n");
	return 0;
}




int calcola_potenza_squadra(squadra* squadra_attiva, int potenza_giocatore_aggiunto){
	if(squadra_attiva==NULL){
		return 1;
	}
	else if(potenza_giocatore_aggiunto<=0){
		return -1;
	}
	else {
        ((*squadra_attiva)->potenza_squadra) += potenza_giocatore_aggiunto;
        return 0;
    }
}

int is_complete(squadra squadra_attiva){
	if(get_num_giocatori(squadra_attiva)==16)
		return 1;
	else
		return 0;
}


int destroy_squadra(squadra* s) {
    if (*s == NULL) {
        return 1;  //la squadra è già nulla
    }
	else{
		destroy_lista_giocatori(&((*s)->giocatori));

		//libera la memoria della struttura squadra
		free(*s);
		*s = NULL;  //evita dangling pointer
		return 0;
	}   
}

int get_lista_giocatori(squadra squadra_attiva, lista_giocatori* head_giocatori_della_squadra){
	if(squadra_attiva==NULL){
		return 1;
	}
	else{
		*head_giocatori_della_squadra = squadra_attiva->giocatori;
		return 0;
	}	
}

int set_lista_giocatori(squadra squadra_attiva, lista_giocatori head_giocatori_della_squadra){
	if(squadra_attiva==NULL){
    	return 1;
    }
    else{
    	squadra_attiva->giocatori= head_giocatori_della_squadra;
    }
    return 0;
	
}



