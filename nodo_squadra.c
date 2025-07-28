#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include "nodo_squadra.h"  



int aggiungi_squadra(lista_squadre* head, squadra nuova_squadra){
	lista_squadre nodo_s;
	if ((*head)==NULL){
		nodo_s = (lista_squadre)malloc(sizeof(struct nodo_squadra));
		nodo_s->n_squadra = nuova_squadra;
		nodo_s->next = NULL;
		*head = nodo_s; 
	}
	else{
		nodo_s = (lista_squadre)malloc(sizeof(struct nodo_squadra));
		nodo_s->n_squadra = nuova_squadra;
		nodo_s->next=(*head);
		(*head)=nodo_s; 
	}
	return 0;
}


int check_nome_s(lista_squadre head, char* nome_squadra){
	while(head!=NULL){
		if(strcmp(get_nome_squadra(head->n_squadra), nome_squadra)==0)
			return 1;
		else
			head=head->next;
	}
	return 0;
}


int stampa_lista_squadre(lista_squadre head){
	if(head==NULL)
		return 1;
	for(lista_squadre l=head; l!=NULL; l=l->next ){
		stampa_squadra(l->n_squadra);
	}
	return 0;
}


int destroy_lista_squadre(lista_squadre* head) {
   int errore = 0; //flag per tracciare errori
    
    while (*head != NULL) {
        lista_squadre current = *head;
        *head = (*head)->next;

        if (destroy_squadra(&(current->n_squadra)) != 0) {
            errore = 1; //segnala un errore, ma continua a liberare i nodi
        }
        free(current); //libera il nodo indipendentemente dall'errore
    }

    *head = NULL; //evito dagling pointers
    return errore; 
}


squadra cerca_squadra(lista_squadre head, const char* nome_squadra_da_cercare){
	while (head != NULL){
		if(strcmp(get_nome_squadra(head->n_squadra), nome_squadra_da_cercare)==0){
			return head->n_squadra; 
		} 
		else
			head = head->next; 
	}
	return NULL;
}


int rimuovi_squadra(lista_squadre* head, const char* nome_squadra){
	lista_squadre current = *head; //all'inizio il nodo corrente è la testa stessa
    lista_squadre previous = NULL;
    if (current == NULL) {
        return 1;
    }
    //se current->next non è NULL AND se verifico che il nodo in current non ha lo stesso nome del nome che ho inserito io
    //Appena la trova e arriva a current->next ==NULL, per il while current sarà NULL e il ciclo si ferma
    while (current != NULL && strcmp(get_nome_squadra(current->n_squadra), nome_squadra) != 0) {
        previous = current;
        current = current->next;
    }
    //la squadra non è nella lista 
    if (current == NULL) {
    	return 1;
    }
    
     destroy_squadra(&(current->n_squadra));
    
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
