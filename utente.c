#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include "utente.h"  




//////  GETTER e SETTER  //////
const char* get_username(utente u){
	if (u == NULL) 
        return NULL;

    return u->username;
}

int get_password(utente u, char* password){
	if (u == NULL) 
        return 1;
        
    strcpy(password, u->password);
    return 0;
}

int set_username(utente u, const char* username){
	if (u == NULL) 
        return 1;
        
    strcpy(u->username, username); //copio username in u->username
    return 0;
}

int set_password(utente u, const char* password){
	if (u == NULL)
	    return 1;
	    
	strcpy(u->password, password); 
	return 0;
}

                                                                                  
int crea_utente(utente* nuovo_utente, const char* username, const char* password){
    *nuovo_utente = (utente)malloc(sizeof(struct utente));  

    if (*nuovo_utente == NULL) 
        return 1;
        
    else{
		set_username(*nuovo_utente, username);
		set_password(*nuovo_utente, password);
		// Inizializza la lista delle squadre a NULL
        (*nuovo_utente)->squadre = NULL; 
		}
	return 0;
}


//stampa l'utente attivo al momento dell'accesso
int stampa_utente(utente u){
	if(u==NULL)
		return 1;
	char username[15];
	strcpy(username, get_username(u));
	printf("Utente attualmente attivo: %s\n", username);
	return 0;
}




//da sistemare la questione dell'eliminazione delle squadre e dei giocatori dell'utente
int destroy_utente(utente* u) {
    if (*u == NULL){
    	return 1;
    }
    else{
    	destroy_lista_squadre(&((*u)->squadre));
    	free(*u);
    	*u = NULL;
    	return 0;
    }
}



int get_lista_squadre(utente utente_attivo, lista_squadre* head_squadre_utente){
	if(utente_attivo==NULL){
		return 1;
	}
	else{
		*head_squadre_utente = utente_attivo->squadre;
		return 0;
	}	
}

int set_lista_squadre(utente utente_attivo, lista_squadre head_squadre_utente){
	if(utente_attivo==NULL){
    	return 1;
    }
    else{
    	utente_attivo->squadre= head_squadre_utente;
    }
    return 0;
}







	
