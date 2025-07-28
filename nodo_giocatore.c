#include <stdbool.h>   
#include <stdio.h>     
#include <stdlib.h>    
#include <string.h> 
#include "nodo_giocatore.h"
#include "squadra.h"

int crea_lista_giocatori(lista_giocatori* head_giocatori){
	*head_giocatori=NULL;
	return 0;
}


int destroy_lista_giocatori(lista_giocatori* head){
	int errore = 0; //flag per tracciare errori
    
    while (*head != NULL) {
        lista_giocatori current = *head;
        *head = (*head)->next;

        if (destroy_giocatore(&(current->n_giocatore)) != 0) {
            errore = 1; //segnala un errore, ma continua a liberare i nodi
        }
        free(current); //libera il nodo indipendentemente dall'errore
    }

    *head = NULL; //evito dagling pointers
    return errore; 

}


int aggiungi_giocatore(lista_giocatori* head, giocatore nuovo_giocatore, squadra* squadra_attiva){
	if (squadra_attiva == NULL) {
		printf("Errore: la squadra attiva non è valida.\n");
		return 1;
	}
	lista_giocatori nodo_g = (lista_giocatori)malloc(sizeof(struct nodo_giocatore));
	if (nodo_g == NULL) {
		return 1; //errore nell'allocazione della memoria
	}
	
	//QUANDO AGGIUNGO IL GIOCATORE DEVO RICORDARMI DI AGGIORNARE:
	//Potenza_squadra, numero di giocatori, numero di titolari e numero di riserve
	int potenza_giocatore = get_potenza_giocatore(nuovo_giocatore);
	int res=calcola_potenza_squadra(squadra_attiva, potenza_giocatore);
	if ( res == 1) {
		printf("Errore nel calcolo della potenza della squadra, la squadra è null\n");
	} else if (res == -1) {
		printf("Errore nel calcolo della potenza della squadra, potenza <= 0\n");
	}
	set_num_giocatori(*squadra_attiva, get_num_giocatori(*squadra_attiva)+1);
	if(get_titolare(nuovo_giocatore)==1){
		set_num_titolari(*squadra_attiva, get_num_titolari(*squadra_attiva)+1);
	}
	else if(get_titolare(nuovo_giocatore)==0){
		set_num_panchina(*squadra_attiva, get_num_panchina(*squadra_attiva)+1);
	} 
	
	nodo_g->n_giocatore = nuovo_giocatore;
	nodo_g->next = *head;
	*head = nodo_g;

	return 0;
}

int stampa_lista_giocatori(lista_giocatori head){
	if(head== NULL)
		return 1;
	printf("Giocatori attualmente in squadra:\n\n");
	for(lista_giocatori l=head; l!=NULL; l=l->next ){
		stampa_giocatore(l->n_giocatore);
	}
	return 0;
}


int check_nome_g(lista_giocatori head, char* nome){
	while(head!=NULL){
		if(strcmp(get_nome_giocatore(head->n_giocatore), nome)==0)
			return 1;
		else
			head=head->next;
	}
	return 0;

}

int rimuovi_giocatore(lista_giocatori* head,  const char* nome_giocatore){
	lista_giocatori current = *head; //all'inizio il nodo corrente è la testa stessa
    lista_giocatori previous = NULL;
    if (current == NULL) {
        return -1;
    }
    //se current->next non è NULL AND se verifico che il nodo in current non ha lo stesso nome del nome che ho inserito io
    //Appena la trova e arriva a current->next ==NULL, per il while current sarà NULL e il ciclo si ferma
    while (current != NULL && strcmp(get_nome_giocatore(current->n_giocatore), nome_giocatore) != 0) {
        previous = current;
        current = current->next;
    }
    //Il giocatore non è nella lista
    if (current == NULL) {
    	return 1;
    }
    
    destroy_giocatore(&(current->n_giocatore));
    
    //se previous == NULL e current non era null allora il nodo da rimuovere è il primo della lista
    if (previous == NULL) {
    	//quindi aggiorno la testa della lista per puntare al nodo successivo
    	*head = current->next;
    } 
    //se nè previous nè current erano null allora il nodo da rimuovere è intermedio o finale
    else {
    	//faccio in modo che il nodo precedente punti al nodo che era puntato precedentemente dal nodo da rimuovere
    	previous->next = current->next;
    }
   
    free(current); 
    return 0;

}

int stampa_titolari(lista_giocatori head) {
    if (head == NULL) {
        return 1; 
    }
    while (head != NULL) {
        if (head->n_giocatore != NULL && get_titolare(head->n_giocatore) == 1) {
            stampa_giocatore(head->n_giocatore);
        }
        head = head->next; 
    }
    return 0;
}

int stampa_riserve(lista_giocatori head) {
    if (head == NULL) {
        return 1; 
    }
    while (head != NULL) {
        if (head->n_giocatore != NULL && get_titolare(head->n_giocatore) == 0) {
            stampa_giocatore(head->n_giocatore);
        }
        head = head->next; 
    }
    return 0;
}



giocatore cerca_giocatore(lista_giocatori head, const char* nome_giocatore_da_cercare){
	if(head==NULL){
	}
	while (head != NULL){
		if(strcmp(get_nome_giocatore(head->n_giocatore), nome_giocatore_da_cercare)==0){
			return head->n_giocatore; 
		} 
		else
			head = head->next; 
	}
	return NULL;
}




