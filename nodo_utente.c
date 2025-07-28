#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include "nodo_utente.h"  



int crea_lista_utenti(lista_utenti* head_utenti){
    *head_utenti = NULL;
    return 0;
}

utente cerca_utente(lista_utenti head, const char* username){
	while (head != NULL){
		if(strcmp(get_username(head->n_utente), username)==0){
			return head->n_utente; 
		} 
		else
			head = head->next; 
	}
	return NULL;
}

int check_username(lista_utenti head, char* username){
	while(head!=NULL){
		if(strcmp(get_username(head->n_utente), username)==0)
			return 1;
		else
			head=head->next;
	}
	return 0;

}


int aggiungi_utente(lista_utenti* head, utente nuovo_utente) {
    lista_utenti nodo_u = (lista_utenti)malloc(sizeof(struct nodo_utente));
    if (nodo_u == NULL) {
        return 1; // Errore nell'allocazione della memoria
    }

    nodo_u->n_utente = nuovo_utente;
    nodo_u->next = *head;
    *head = nodo_u;

    return 0;
}


void stampa_lista_utenti(lista_utenti head){ 
	printf("\nSTAMPO LISTA DEGLI UTENTI:\n");
	for(lista_utenti l=head; l!=NULL; l=l->next ){
		char password[9];
		get_password(l->n_utente,password);
		printf("Username: %s, Password: %s\n", get_username(l->n_utente), password);

	}
}


utente accesso(lista_utenti head_utenti, char* username, char* password){
	while (head_utenti != NULL){
		char tmp_password[9];
		get_password(head_utenti->n_utente, tmp_password);
		if((strcmp(get_username(head_utenti->n_utente), username)==0) && (strcmp(tmp_password, password)==0))
			return head_utenti->n_utente;  //restituisco il puntatore all'utente attivo
		else
			head_utenti = head_utenti->next;  //altrimenti vado al nodo successivo
	}
	//sono arrivato alla fine della lista quindi l'utente non esiste
	return NULL;
}


int destroy_lista_utenti(lista_utenti* head) {
    int errore = 0; //Flag per tracciare errori
    
    while (*head != NULL) {
        lista_utenti current = *head;
        *head = (*head)->next;

        if (destroy_utente(&(current->n_utente)) != 0) {
            errore = 1; // Segnala un errore, ma continua a liberare i nodi
        }
        free(current); // Libera il nodo indipendentemente dall'errore
    }

    *head = NULL; //Evito dagling pointers
    return errore; 
}



int salva_su_file(lista_utenti head_utenti){
	FILE* file = fopen("squadre_inazuma.txt", "w"); 
    if (file == NULL) {
        return 1;
    }else{
    	lista_utenti temp_head_utenti = head_utenti;
    	while(temp_head_utenti!=NULL){ //scorro tutta la lista degli utenti
    		char password[9]; 
    		get_password(temp_head_utenti->n_utente, password);
    		fprintf(file, "Username:%s,%s\n", get_username(temp_head_utenti->n_utente), password);
            
            lista_squadre head_squadre = NULL;
            get_lista_squadre(temp_head_utenti->n_utente, &head_squadre); //assegno a head_squadre il puntatore alla lista delle squadre dell'utente corrente
            lista_squadre temp_head_squadre = head_squadre; 
            while(temp_head_squadre!=NULL){
				char nome[30];
				char allenatore[20];
				int num_giocatori=0;
				int num_titolari=0;
				int num_panchina=0;
				int potenza_squadra=0;
				
				strcpy(nome, get_nome_squadra(temp_head_squadre->n_squadra));
				get_allenatore(temp_head_squadre->n_squadra, allenatore);
				num_giocatori = get_num_giocatori(temp_head_squadre->n_squadra);
				num_titolari = get_num_titolari(temp_head_squadre->n_squadra);
				num_panchina = get_num_panchina(temp_head_squadre->n_squadra);
				potenza_squadra = get_potenza_squadra(temp_head_squadre->n_squadra);
				
            	fprintf(file,
            			"Squadra:%s,%s,%d,%d,%d,%d\n", 
            			nome, allenatore, num_giocatori, num_titolari, num_panchina, potenza_squadra);
            	


            	lista_giocatori head_giocatori=NULL;
            	get_lista_giocatori(temp_head_squadre->n_squadra, &head_giocatori); //assegno a head_gioatori il puntatore alla lista dei giocatori
            	lista_giocatori temp_head_giocatori = head_giocatori;
            	while(temp_head_giocatori!=NULL){
        		    char nome_giocatore[20];         
					char ruolo[20]; 
					char tipo[20];  
					int pe, pt;
					int attacco, fisico, controllo, difesa, velocita, resistenza, grinta;        
					char tecnica1[20];
					char tecnica2[20];
					char tecnica3[20];
					char tecnica4[20];
					int titolare;    		  
					int potenza_giocatore;
					
					strcpy(nome_giocatore, get_nome_giocatore(temp_head_giocatori->n_giocatore));
					get_ruolo(temp_head_giocatori->n_giocatore, ruolo);
					get_tipo(temp_head_giocatori->n_giocatore, tipo);
					pe=get_pe(temp_head_giocatori->n_giocatore);
					pt=get_pt(temp_head_giocatori->n_giocatore);
					attacco=get_attacco(temp_head_giocatori->n_giocatore);
					fisico=get_fisico(temp_head_giocatori->n_giocatore);
					controllo=get_controllo(temp_head_giocatori->n_giocatore);
					difesa=get_difesa(temp_head_giocatori->n_giocatore);
					velocita=get_velocita(temp_head_giocatori->n_giocatore);
					resistenza=get_resistenza(temp_head_giocatori->n_giocatore);
					grinta=get_grinta(temp_head_giocatori->n_giocatore);
					get_tecnica1(temp_head_giocatori->n_giocatore, tecnica1);
					if (strlen(tecnica1) == 0) {
						strcpy(tecnica1, "----");
					}
					get_tecnica2(temp_head_giocatori->n_giocatore, tecnica2);
					if (strlen(tecnica2) == 0) {
						strcpy(tecnica2, "----");
					}
					get_tecnica3(temp_head_giocatori->n_giocatore, tecnica3);
					if (strlen(tecnica3) == 0) {
						strcpy(tecnica3, "----");
					}
					get_tecnica4(temp_head_giocatori->n_giocatore, tecnica4);
					if (strlen(tecnica4) == 0) {
						strcpy(tecnica4, "----");
					}
					titolare=get_titolare(temp_head_giocatori->n_giocatore);
					potenza_giocatore=get_potenza_giocatore(temp_head_giocatori->n_giocatore);
					
					fprintf(file,
							"Giocatore:%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%s,%d,%d\n",
							nome_giocatore, ruolo, tipo, pe, pt, attacco, fisico, controllo, 
							difesa, velocita, resistenza, grinta, tecnica1, tecnica2, tecnica3, 
							tecnica4, titolare, potenza_giocatore);
					//passo al giocatore successivo
					temp_head_giocatori = temp_head_giocatori->next;
            	}
				//passo alla squadra successiva
				temp_head_squadre = temp_head_squadre->next;
            }
            //passo all' utente successivo
			temp_head_utenti = temp_head_utenti->next;
    	}
    	fclose(file);
    	return 0;	
    } 
}

void carica_da_file(lista_utenti* head_utenti){
	FILE* file = fopen("squadre_inazuma.txt", "r");
    if (file == NULL) {
        file = fopen("squadre_inazuma.txt", "w");
        if (file == NULL) {
            printf("Errore nella creazione del file\n");
            return;
        }
        fclose(file);
        return; //torna al chiamante, poiché non ci sono dati da caricare
    }
    //lista_utenti temp_head_utenti = NULL;
    utente ultimo_utente = NULL;
	squadra ultima_squadra=NULL;
	giocatore ultimo_giocatore=NULL;
	
    char line[256];
    char username[15]="";   		   
    char password[9]="";
    while (fgets(line, sizeof(line), file)) { //così line conterrebbe: 'Username:e,r\n'
        line[strcspn(line, "\n")] = 0; //così line contiene: 'Username:e,r'
        
        if (strncmp(line, "Username:", 9) == 0){ //Questa funzione confronta i primi 9 caratteri di line con la stringa "Username:".
			sscanf(line + 9, "%14[^,],%7[^,\n]", username, password);  
			ultimo_utente=cerca_utente(*head_utenti, username);
			//se cerca_utente restituisce NULL allora l'utent_corrente non è stato trovato allora non esiste ancora nella lista. Lo creiamo e lo aggiungiamo.
			if(ultimo_utente==NULL){
				crea_utente(&ultimo_utente,username,password);
				aggiungi_utente(head_utenti, ultimo_utente);
				ultimo_utente=cerca_utente(*head_utenti, username);
			}

		}else{
			if (strncmp(line, "Squadra:", 8) == 0){
				lista_squadre squadre_ultimo_utente=NULL;

				char nome[30]="";
				char allenatore[20]="";
				int num_giocatori;
				int num_titolari;
				int num_panchina;
				int potenza_squadra;
				

		        int valori=sscanf(line +8, 
								   "%29[^,],%19[^,],%d,%d,%d,%d",
						           nome, allenatore, &num_giocatori, &num_titolari, &num_panchina, &potenza_squadra);
                
                if (valori != 6) {
		            printf("Errore nel recupero dei valori della squadra dal file\n");
		            destroy_lista_utenti(head_utenti);  // Libera la memoria allocata
		            fclose(file);
		            return;
		        }
		        
                //prendo la lista
				get_lista_squadre(ultimo_utente, &squadre_ultimo_utente);
				crea_squadra(&ultima_squadra, nome, allenatore);    
                aggiungi_squadra(&squadre_ultimo_utente, ultima_squadra); 
                set_lista_squadre(ultimo_utente, squadre_ultimo_utente);
                
			
			
			}
			if (strncmp(line, "Giocatore:", 10) == 0){
				lista_giocatori giocatori_ultima_squadra=NULL;
				
				char nome_giocatore[20]="";         
				char ruolo[20]=""; 
				char tipo[20]="";  
				int pe, pt;
				int attacco, fisico, controllo, difesa, velocita, resistenza, grinta;        
				char tecnica1[20]="";
				char tecnica2[20]="";
				char tecnica3[20]="";
				char tecnica4[20]="";
				int titolare; 
				int potenza_giocatore;
				

				int valori= sscanf(line + 10, "%19[^,],%19[^,],%19[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%19[^,],%19[^,],%19[^,],%19[^,],%d,%d",
								 nome_giocatore, ruolo, tipo, &pe, &pt, &attacco, &fisico, &controllo, &difesa, &velocita, &resistenza, &grinta,
								 tecnica1, tecnica2, tecnica3, tecnica4, &titolare, &potenza_giocatore);
				
				if (valori != 18) {
		            printf("Errore nel recupero dei valori del giocatore dal file\n");
		            destroy_lista_utenti(head_utenti);  // Libera la memoria allocata
		            fclose(file);
		            return;
		        }
		        
		        //prendo la lista
				get_lista_giocatori(ultima_squadra, &giocatori_ultima_squadra);
				crea_giocatore(&ultimo_giocatore, nome_giocatore, ruolo, tipo, pe, pt, attacco, fisico, 	
							   controllo,difesa, velocita,	resistenza, grinta,  tecnica1,  
							   tecnica2, tecnica3, tecnica4, titolare, potenza_giocatore);    
                
                aggiungi_giocatore(&giocatori_ultima_squadra, ultimo_giocatore, &ultima_squadra);
                set_lista_giocatori(ultima_squadra, giocatori_ultima_squadra);
			}	
		}
	}							  	
	fclose(file);
}













