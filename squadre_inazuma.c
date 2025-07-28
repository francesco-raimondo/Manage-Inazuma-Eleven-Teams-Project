#include <stdbool.h>   
#include <stdio.h>     
#include <stdlib.h>    
#include <string.h> 
#include "nodo_utente.h"
#include "utente.h"
#include "giocatore.h"

int valida_input(char* stringa){
	if (stringa == NULL || strlen(stringa) == 0){
		    return 0; 
		}
	return 1; 
}


int main() {
	lista_utenti head_utenti=NULL;
	utente utente_attivo=NULL;
	lista_squadre squadre_utente_attivo=NULL; 
	squadra squadra_attiva=NULL;
	lista_giocatori giocatori_squadra_attiva=NULL;
	giocatore nuovo_giocatore=NULL;
	int val = 0; //serve per la validazione delle stringhe
	
	carica_da_file(&head_utenti);
	//stampa_lista_utenti(head_utenti);

	
    
	printf("\n---  BENVENUTO NEL PROGRAMMA DI GESTIONE DELLE SQUADRE DI INAZUMA ELEVEN  ---");
	int scelta= -1;
	char username[15];
	char password[9];
	do{
		printf("\n1. Accedi\n");
		printf("2. Registrati\n");
		printf("0. Esci\n");
        scanf("%d", &scelta);
        getchar(); // Rimuove il newline lasciato da scanf
        switch(scelta){
        	case 1:
				//ACCESSO DELL'UTENTE   
				do{     	
					printf("\nAccedi Inserendo il tuo username:\n");
					fgets(username, sizeof(username), stdin);
					username[strcspn(username, "\n")] = '\0';
					
					
		    		printf("\nInserisci la password:\n");
					fgets(password, sizeof(password), stdin);
					password[strcspn(password, "\n")] = '\0';
					
		    		utente_attivo=accesso(head_utenti, username, password);
		    		
					if (utente_attivo == NULL) {
		                printf("\nCredenziali errate. Riprova.\n");
		            }
	            }while(utente_attivo==NULL);
				
				// ACCESSO RIUSCITO
                printf("\nAccesso effettuato con username: %s\n", get_username(utente_attivo)); 
            	
            	///////////////                                    ////////////////
				///////////////   SI PASSA AL MENU DELLE SQUADRE   ////////////////
				///////////////                                    ////////////////
				
				
				int scelta2=-1;
				
				do{
					
					printf("\n---  GESTIONE DELLE SQUADRE  ---");
					printf("\n1. Crea squadra\n");
					printf("2. Visualizza squadre\n");
					printf("0. Indietro\n");
					scanf("%d", &scelta2);
					getchar(); // Rimuove il newline lasciato da scanf
					switch(scelta2){
						case 1:
							//INSERIMENTO DEL NOME E DELL'ALLENATORE DELLA SQUADRA
							char nome[30]="";
							char allenatore[20]="";
							int squadra_esistente=0;
							do {
								val = 0; 
					
								while (val == 0) {
									printf("\nInserisci il nome della squadra:\n");
									fgets(nome, sizeof(nome), stdin);
									nome[strcspn(nome, "\n")] = '\0';
									
									//controlla se l'input è valido
									if (valida_input(nome) == 0) {
										printf("Errore, devi inserire almeno un carattere\n");
									} else {
										val = 1; //se l'input è valido, esci dal ciclo
									}
								}
								
								if (get_lista_squadre(utente_attivo, &squadre_utente_attivo) == 1) {
									printf("Errore nel getter della lista delle squdre dell'utente attivo, l'utente è NULL\n");
								}
								squadra_esistente = check_nome_s(squadre_utente_attivo, nome);
								if (squadra_esistente == 1) {
									printf("\nEsiste già una squadra con questo nome, riprova\n");
								}
								
							} while (squadra_esistente == 1);
							
							
							
							val = 0; 
							while (val == 0) {
								printf("\nInserisci l'allenatore:\n");
								fgets(allenatore, sizeof(allenatore), stdin);
								allenatore[strcspn(allenatore, "\n")] = '\0';
								
								//controlla se l'input è valido
								if (valida_input(allenatore) == 0) {
									printf("Errore, devi inserire almeno un carattere\n");
								} else {
									val = 1; // Se l'input è valido, esci dal ciclo
								}
							}
							
							//CREAZIONE DELLA SQUADRA
							squadra_attiva=crea_squadra(&squadra_attiva, nome, allenatore);
							if(squadra_attiva==NULL){
								printf("Errore nella creazione della squadra\n");
							}
							
                            //AGGIUNTA DELA SQUADRA
                            if (get_lista_squadre(utente_attivo, &squadre_utente_attivo) == 1) {
								printf("Errore nel getter della lista delle squdre dell'utente attivo, l'utente è NULL\n");
							}
							if(aggiungi_squadra(&(squadre_utente_attivo), squadra_attiva)==1){
								printf("Errore nell'aggiunta della squadra");
							}
							//sincronizzo la lista locale con il campo `utente_attivo->squadre`
							if(set_lista_squadre(utente_attivo, squadre_utente_attivo)==1){
								printf("Errore nella sincronizzazione della lista delle squadre\n");
							}
							
							//STAMPO LA SQUADRA AGGIUNTA
							if(stampa_squadra(squadra_attiva)==1){
								printf("Errore nella stampa della squadra\n");
							}

							
							///////////////                                           ////////////////
							///////////////            AGGIUNTA DEI GIOCATORI         ////////////////
							///////////////                                           ////////////////
							int scelta4=-1;

							
							do{
								
								printf("\n1. Aggiungi giocatore\n");
								printf("0. Indietro\n");
								scanf("%d", &scelta4);
								getchar();
								switch(scelta4){
									case 1:
										
										//DICHIARAZIONE E INIZIALIZZAZIONE VARIABILI PER IL GIOCATORE
										char nome_giocatore[20];         
										char ruolo[20]; 
										char tipo[20];  
										int pe=0; int pt=0;
										int attacco=0; int fisico=0; int controllo=0; int difesa=0; int velocita=0; int resistenza=0; int grinta=0;        
										char tecnica1[20];
										char tecnica2[20];
										char tecnica3[20];
										char tecnica4[20];
										int titolare=-1;    			//0: panchinaro,   1: titolare   
										int potenza_giocatore=0; 		// Calcolata in base alle statistiche
										
										int res=0;
									
										
										//PRIMA VERIFICO SE LA SQUADRA È COMPLETA
										if(is_complete(squadra_attiva)==1){
											printf("Errore, la squadra è già completa\n");
											continue;
										}
										
										//CREAZIONE DEL GIOCATORE
										printf("\nInserisci nome e cognome del giocatore:\n");
										fgets(nome_giocatore, sizeof(nome_giocatore), stdin);
										nome_giocatore[strcspn(nome_giocatore, "\n")] = '\0';
										if(valida_input(nome_giocatore)==0){
											printf("Errore, inserisci almeno un carattere\n");
											continue;
										}
										else{
											if (get_lista_giocatori(squadra_attiva, &giocatori_squadra_attiva) == 1) {
												printf("Errore nel getter della lista dei giocatori della squadra attiva, la squadra è NULL\n");
											}
											
											if(check_nome_g(giocatori_squadra_attiva, nome_giocatore)==1){
												printf("Esiste già un giocatore con questo nome, riprova\n");
												continue;
											}
										}
										
										
										while( (res==0 || (res==1 && check_titolare(titolare)==1)) || (titolare==1 && get_num_titolari(squadra_attiva)==11) || 
											  (titolare==0 && get_num_panchina(squadra_attiva)==5) ){
											printf("\nVuoi che il giocatore sia un Titolare o vuoi metterlo in Panchina? (0: panchina, 1: titolare)\n");
											res=scanf("%d", &titolare);
											getchar();
											if(res==0 || (res==1 && check_titolare(titolare)==1)){
												printf("Valore non valido:\nInserisci 1 per un giocatore titolare, 0 per un giocatore in panchina\n");	
											}
											if(titolare==1 && get_num_titolari(squadra_attiva)==11){
												printf("Errore, nella squadra ci sono già 11 titolari\n");
												continue;
											}
											else if(titolare==0 && get_num_panchina(squadra_attiva)==5){
												printf("Errore, la panchina della squadra è già al completo\n");
												continue;
											}	
										}
										
										val=0;
										while (val == 0) {
											printf("\nInserisci il ruolo del giocatore:\n");
											fgets(ruolo, sizeof(ruolo), stdin);
											ruolo[strcspn(ruolo, "\n")] = '\0';
											
											//controlla se l'input è valido
											if (valida_input(ruolo) == 0) {
												printf("Errore, devi inserire almeno un carattere\n");
											} else {
												val = 1; 
											}
										}
										
										val=0;
										while (val == 0) {
											printf("\nInserisci il tipo del giocatore:\n");
											fgets(tipo, sizeof(tipo), stdin);
											tipo[strcspn(tipo, "\n")] = '\0';
											
											//controlla se l'input è valido
											if (valida_input(tipo) == 0) {
												printf("Errore, devi inserire almeno un carattere\n");
											} else {
												val = 1; 
											}
										}
										
										
										while(res==0 || (res==1 && check_statistica(pe)==0)){
											printf("\nInserisci i Punti Tecnica (PE) del giocatore:\n");
											res=scanf("%d", &pe);
											getchar();
											if(res==0 || (res==1 && check_statistica(pe)==0)){
												printf("Valore non valido:\nInserisci un numero intero positivo\n");	
											}
										}
										
										
										while(res==0 || (res==1 && check_statistica(pt)==0)){
											printf("\nInserisci i Punti Tecnica (PT) del giocatore:\n");
											res=scanf("%d", &pt);
											getchar();
											if(res==0 || (res==1 && check_statistica(pt)==0)){
												printf("Valore non valido:\nInserisci un numero intero positivo\n");	
											}
										}
										
										
										while(res==0 || (res==1 && check_statistica(attacco)==0)){
											printf("\nInserisci il livello di Attacco del giocatore:\n");
											res=scanf("%d", &attacco);
											getchar();
											if(res==0 || (res==1 && check_statistica(attacco)==0)){
												printf("Valore non valido:\nInserisci un numero intero positivo\n");	
											}
										}

										while(res==0 || (res==1 && check_statistica(fisico)==0)){
											printf("\nInserisci il livello di Fisico del giocatore:\n");
											res=scanf("%d", &fisico);
											getchar();
											if(res==0 || (res==1 && check_statistica(fisico)==0)){
												printf("Valore non valido:\nInserisci un numero intero positivo\n");	
											}
										}
										
										while(res==0 || (res==1 && check_statistica(controllo)==0)){
											printf("\nInserisci il livello di Controllo del giocatore:\n");
											res=scanf("%d", &controllo);
											getchar();
											if(res==0 || (res==1 && check_statistica(controllo)==0)){
												printf("Valore non valido:\nInserisci un numero intero positivo\n");	
											}
										}
										
										while(res==0 || (res==1 && check_statistica(difesa)==0)){
											printf("\nInserisci il livello di Difesa del giocatore:\n");
											res=scanf("%d", &difesa);
											getchar();
											if(res==0 || (res==1 && check_statistica(difesa)==0)){
												printf("Valore non valido:\nInserisci un numero intero positivo\n");	
											}
										}
										
										while(res==0 || (res==1 && check_statistica(velocita)==0)){
											printf("\nInserisci il livello di Velocita del giocatore:\n");
											res=scanf("%d", &velocita);
											getchar();
											if(res==0 || (res==1 && check_statistica(velocita)==0)){
												printf("Valore non valido:\nInserisci un numero intero positivo\n");	
											}
										}

										while(res==0 || (res==1 && check_statistica(resistenza)==0)){
											printf("\nInserisci il livello di Resistenza del giocatore:\n");
											res=scanf("%d", &resistenza);
											getchar();
											if(res==0 || (res==1 && check_statistica(resistenza)==0)){
												printf("Valore non valido:\nInserisci un numero intero positivo\n");	
											}
										}
										
										while(res==0 || (res==1 && check_statistica(grinta)==0)){
											printf("\nInserisci il livello di Grinta del giocatore:\n");
											res=scanf("%d", &grinta);
											getchar();
											if(res==0 || (res==1 && check_statistica(grinta)==0)){
												printf("Valore non valido:\nInserisci un numero intero positivo\n");	
											}
										}
										
										printf("\nTECNICHE SPECIALI: (se non vuoi aggiungere una tecnica premi direttamente 'invio')\n");
										printf("\nInserisci la prima tecnica speciale (premi 'invio' per non aggiungerla):\n");
										fgets(tecnica1, sizeof(tecnica1), stdin);
										tecnica1[strcspn(tecnica1, "\n")] = '\0';
										
										printf("\nInserisci la seconda tecnica speciale (premi 'invio' per non aggiungerla):\n");
										fgets(tecnica2, sizeof(tecnica2), stdin);
										tecnica2[strcspn(tecnica2, "\n")] = '\0';
										
										printf("\nInserisci la terza tecnica speciale (premi 'invio' per non aggiungerla):\n");
										fgets(tecnica3, sizeof(tecnica3), stdin);
										tecnica3[strcspn(tecnica3, "\n")] = '\0';
										
										printf("\nInserisci la quarta tecnica speciale (premi 'invio' per non aggiungerla):\n");
										fgets(tecnica4, sizeof(tecnica4), stdin);
										tecnica4[strcspn(tecnica4, "\n")] = '\0';
										
										//CALCOLO LA POTENZA
										potenza_giocatore=calcola_potenza_giocatore(pe,pt,attacco,fisico,controllo,difesa,velocita,resistenza,grinta);
                              			
                              			//AVVIO LA CREAZIONE
                              			nuovo_giocatore=crea_giocatore(&nuovo_giocatore, nome_giocatore, ruolo, tipo, pe, pt, attacco, fisico, 	
                              											controllo,difesa, velocita,	resistenza, grinta,  tecnica1,  
                              											tecnica2, tecnica3, tecnica4, titolare, potenza_giocatore);

										if(nuovo_giocatore==NULL){
											printf("Errore nella creazione del giocatore");
										}

										if(stampa_all_giocatore(nuovo_giocatore)==1){
											printf("Errore nella stampa del giocatore");
										}
										
										//AGGIUNTA DEL GIOCATORE ALLA SQUADRA ATTIVA
										if (get_lista_giocatori(squadra_attiva, &giocatori_squadra_attiva) == 1) {
											printf("Errore nel getter della lista dei giocatori della squadra attiva, la squadra è NULL\n");
										}
										if(aggiungi_giocatore(&(giocatori_squadra_attiva), nuovo_giocatore, &squadra_attiva)==1){
											printf("Errore nell'aggiunta della squadra\n");
										}
										if(set_lista_giocatori(squadra_attiva, giocatori_squadra_attiva)==1){
											printf("Errore nella sincronizzazione della lista dei giocatori\n");
										}
										break;
									case 0:
										break;
									default:
										printf("\nOpzione non valida! Riprova.\n");
								}
								
								
							}while(scelta4!=0);
							
							break;
						case 2:
							///////////////                                           ////////////////
							///////////////   SI PASSA ALLA SELEZIONE DELLE SQUADRE   ////////////////
							///////////////                                           ////////////////
							int scelta3=-1;
							do{
								printf("\n\n---  LE TUE SQUADRE  ---\n");
								if (get_lista_squadre(utente_attivo, &squadre_utente_attivo) == 1) {
									printf("Errore nel getter della lista delle squdre dell'utente attivo, l'utente è NULL\n");
								}
								if(stampa_lista_squadre(squadre_utente_attivo)==1)
									printf("Nessuna squadra disponibile, torna indietro per crearne una nuova\n");
								printf("\n1. Seleziona squadra\n");
								printf("2. Cancella squadra\n");
								printf("0. Indietro\n");
								scanf("%d", &scelta3);
								getchar();
								switch(scelta3){
									case 1:
										char s_da_cercare[30];
										printf("\nInserisci il nome della squadra da selezionare:\n");
										fgets(s_da_cercare, sizeof(s_da_cercare), stdin);
										s_da_cercare[strcspn(s_da_cercare, "\n")] = 0;
										
										
										//STAMPA DELLA SQUADRA CON TUTTI I SUOI GIOCATORI
										if (get_lista_squadre(utente_attivo, &squadre_utente_attivo) == 1) {
											printf("Errore nel getter della lista delle squdre dell'utente attivo, l'utente è NULL\n");
										}
										squadra_attiva=cerca_squadra(squadre_utente_attivo, s_da_cercare);
										if (squadra_attiva == NULL) {
											printf("Errore, squadra non trovata\n");
											continue;
										} else if (squadra_attiva != NULL){
											if (stampa_all_squadra(squadra_attiva) == 1) {
												printf("Questa squadra non contiene nessun giocatore\n");
											}
										}

										///////////////                                           ////////////////
										///////////////   SI PASSA ALLA MODIFICA DELLA SQUADRA    ////////////////
										///////////////                                           ////////////////
										int scelta4=-1;
										do{
											printf("\n\n---  MODIFICA DELLA SQUADRA  ---\n");
											printf("\n1. Seleziona giocatore\n");
											printf("2. Aggiungi giocatore\n");
											printf("3. Rimuovi giocatore\n");
											printf("4. Promuovi riserva a titolare\n");
											printf("5. Metti titolare in panchina\n");
											printf("6. Cambia l'allenatore\n");
											printf("7. Cambia nome alla squadra\n");
											printf("0. Indietro\n");
											
											scanf("%d", &scelta4);
											getchar();
											switch(scelta4){
												case 1:
													///////////////                                           ////////////////
													///////////////   SI PASSA ALLA MODIFICA DEL GIOCATORE    ////////////////
													///////////////                                           ////////////////
													int scelta6=-1;
													char nome_giocatore_attivo[20];
													giocatore giocatore_attivo;
													
													printf("\nInserisci nome e cognome del giocatore da selezionare:\n");
													fgets(nome_giocatore_attivo, sizeof(nome_giocatore_attivo), stdin);
													nome_giocatore_attivo[strcspn(nome_giocatore_attivo, "\n")] = '\0';
													
													if (get_lista_giocatori(squadra_attiva, &giocatori_squadra_attiva) == 1) {
														printf("Errore nel getter della lista dei giocatori della squadra attiva, la squadra è NULL\n");
													}
													giocatore_attivo=cerca_giocatore(giocatori_squadra_attiva, nome_giocatore_attivo);
													if(giocatore_attivo==NULL){
														printf("Errore, il giocatore non esiste\n");
														continue;
													}
													do{
														printf("\n---  MODIFICA DEL GIOCATORE  ---\n");
														stampa_all_giocatore(giocatore_attivo);
														printf("\n\nCosa vuoi modificare del giocatore?");
														printf("\n1. Modifica statistiche\n");
														printf("2. Modifica nome\n");
														printf("3. Modifica ruolo\n");
														printf("4. Modifica tipo\n");
														printf("5. Modifica tecniche speciali\n");
														printf("0. Indietro\n");
														scanf("%d", &scelta6);
														getchar();
														switch(scelta6){
															case 1:
																int input=-1;
																int res=0;
																while(input!=0){
																	int pe=0; int pt=0;
																	int attacco=0; int fisico=0; int controllo=0; int difesa=0; 
																	int velocita=0; int resistenza=0; int grinta=0; 
																	//quale statistica vuoi cambiare?
																	printf("\nQuale statistica del giocatore vuoi cambiare?");
																	printf("\n1. Punti Energia (PE)\n");
																	printf("2. Punti Tecnica (PT)\n");
																	printf("3. Attacco\n");
																	printf("4. Fisico\n");
																	printf("5. Controllo\n");
																	printf("6. Difesa\n");
																	printf("7. Velocità\n");
																	printf("8. Resistenza\n");
																	printf("9. Grinta\n");
																	printf("0. Indietro\n");
																	scanf("%d", &input);
																	getchar();
																	switch(input){
																		case 1:
																			printf("\nHai scelto 'Punti Energia (PE)'.\n");
																			printf("PE attuali di %s: '%d'", get_nome_giocatore(giocatore_attivo), get_pe(giocatore_attivo));
																			while(res==0 || (res==1 && check_statistica(pe)==0)){
																				printf("\nInserisci i PE del giocatore:\n");
																				res=scanf("%d", &pe);
																				getchar();
																				if(res==0 || (res==1 && check_statistica(pe)==0)){
																					printf("Valore non valido:\nInserisci un numero intero positivo\n");	
																				}
																			}
																			if(set_pe(giocatore_attivo,pe)==1){
																				printf("Errore nella modifica dei PE del giocatore\n");
																			}
																			printf("Modifica effettuata con successo!\n");
																			break;
																		case 2:
																			printf("\nHai scelto 'Punti Tecnica (PT)'.\n");
																			printf("PT attuali di %s: '%d'", get_nome_giocatore(giocatore_attivo), get_pt(giocatore_attivo));
																			while(res==0 || (res==1 && check_statistica(pt)==0)){
																				printf("\nInserisci i PT del giocatore:\n");
																				res=scanf("%d", &pt);
																				getchar();
																				if(res==0 || (res==1 && check_statistica(pt)==0)){
																					printf("Valore non valido:\nInserisci un numero intero positivo\n");	
																				}
																			}
																			if(set_pt(giocatore_attivo,pt)==1){
																				printf("Errore nella modifica dei PT del giocatore\n");
																			}
																			printf("Modifica effettuata con successo!\n");
																			break;
																		
																		case 3:
																			printf("\nHai scelto 'Attacco'.\n");
																			printf("Il livello di attacco attuale di %s è: %d", get_nome_giocatore(giocatore_attivo), get_attacco(giocatore_attivo));
																			while(res==0 || (res==1 && check_statistica(attacco)==0)){
																				printf("\nInserisci il livello di Attacco del giocatore:\n");
																				res=scanf("%d", &attacco);
																				getchar();
																				if(res==0 || (res==1 && check_statistica(attacco)==0)){
																					printf("Valore non valido:\nInserisci un numero intero positivo\n");	
																				}
																			}
																			if(set_attacco(giocatore_attivo,attacco)==1){
																				printf("Errore nella modifica del livello di Attacco del giocatore\n");
																			}
																			printf("Modifica effettuata con successo!\n");
																			break;
																		case 4:
																			printf("\nHai scelto 'Fisico'.\n");
																			printf("Il livello di Fisico attuale di %s è: %d", get_nome_giocatore(giocatore_attivo), get_fisico(giocatore_attivo));
																			while(res==0 || (res==1 && check_statistica(fisico)==0)){
																				printf("\nInserisci il livello di Fisico del giocatore:\n");
																				res=scanf("%d", &fisico);
																				getchar();
																				if(res==0 || (res==1 && check_statistica(fisico)==0)){
																					printf("Valore non valido:\nInserisci un numero intero positivo\n");	
																				}
																			}
																			if(set_fisico(giocatore_attivo,fisico)==1){
																				printf("Errore nella modifica del livello di Fisico del giocatore\n");
																			}
																			printf("Modifica effettuata con successo!\n");
																			break;
																		case 5:
																			printf("\nHai scelto 'Controllo'.\n");
																			printf("Il livello di Controllo attuale di %s è: %d", get_nome_giocatore(giocatore_attivo), get_controllo(giocatore_attivo));
																			while(res==0 || (res==1 && check_statistica(controllo)==0)){
																				printf("\nInserisci il livello di Controllo del giocatore:\n");
																				res=scanf("%d", &controllo);
																				getchar();
																				if(res==0 || (res==1 && check_statistica(controllo)==0)){
																					printf("Valore non valido:\nInserisci un numero intero positivo\n");	
																				}
																			}
																			if(set_controllo(giocatore_attivo,controllo)==1){
																				printf("Errore nella modifica del livello di Controllo del giocatore\n");
																			}
																			printf("\nModifica effettuata con successo!\n");
																			break;
																		case 6:
																			printf("\nHai scelto 'Difesa'.\n");
																			printf("Il livello di Difesa attuale di %s è: %d", get_nome_giocatore(giocatore_attivo), get_difesa(giocatore_attivo));
																			while(res==0 || (res==1 && check_statistica(difesa)==0)){
																				printf("\nInserisci il livello di Difesa del giocatore:\n");
																				res=scanf("%d", &difesa);
																				getchar();
																				if(res==0 || (res==1 && check_statistica(difesa)==0)){
																					printf("Valore non valido:\nInserisci un numero intero positivo\n");	
																				}
																			}
																			if(set_difesa(giocatore_attivo,difesa)==1){
																				printf("Errore nella modifica del livello di Difesa del giocatore\n");
																			}
																			printf("\nModifica effettuata con successo!\n");
																			break;
																		case 7:
																			printf("\nHai scelto 'Velocità'.\n");
																			printf("Il livello di Velocità attuale di %s è: %d", get_nome_giocatore(giocatore_attivo), get_velocita(giocatore_attivo));
																			while(res==0 || (res==1 && check_statistica(velocita)==0)){
																				printf("\nInserisci il livello di Velocità del giocatore:\n");
																				res=scanf("%d", &velocita);
																				getchar();
																				if(res==0 || (res==1 && check_statistica(velocita)==0)){
																					printf("Valore non valido:\nInserisci un numero intero positivo\n");	
																				}
																			}
																			if(set_velocita(giocatore_attivo,velocita)==1){
																				printf("Errore nella modifica del livello di Velocità del giocatore\n");
																			}
																			printf("\nModifica effettuata con successo!\n");
																			break;
																		case 8:
																			printf("\nHai scelto 'Resistenza'.\n");
																			printf("Il livello di Resistenza attuale di %s è: %d", get_nome_giocatore(giocatore_attivo), get_resistenza(giocatore_attivo));
																			while(res==0 || (res==1 && check_statistica(resistenza)==0)){
																				printf("\nInserisci il livello di Resistenza del giocatore:\n");
																				res=scanf("%d", &resistenza);
																				getchar();
																				if(res==0 || (res==1 && check_statistica(resistenza)==0)){
																					printf("Valore non valido:\nInserisci un numero intero positivo\n");	
																				}
																			}
																			if(set_resistenza(giocatore_attivo,resistenza)==1){
																				printf("Errore nella modifica del livello di Resistenza del giocatore\n");
																			}
																			printf("\nModifica effettuata con successo!\n");
																			break;
																		case 9:
																			printf("\nHai scelto 'Grinta'.\n");
																			printf("Il livello di Grinta attuale di %s è: %d", get_nome_giocatore(giocatore_attivo), get_grinta(giocatore_attivo));
																			while(res==0 || (res==1 && check_statistica(grinta)==0)){
																				printf("\nInserisci il livello di Grinta del giocatore:\n");
																				res=scanf("%d", &grinta);
																				getchar();
																				if(res==0 || (res==1 && check_statistica(grinta)==0)){
																					printf("Valore non valido:\nInserisci un numero intero positivo\n");	
																				}
																			}
																			if(set_grinta(giocatore_attivo,grinta)==1){
																				printf("Errore nella modifica del livello di Grinta del giocatore\n");
																			}
																			printf("\nModifica effettuata con successo!\n");
																			break;
																		case 0:
																		    //ricarico i valori aggiornati
																			pe = get_pe(giocatore_attivo);
																			pt = get_pt(giocatore_attivo);
																			attacco = get_attacco(giocatore_attivo);
																			fisico = get_fisico(giocatore_attivo);
																			controllo = get_controllo(giocatore_attivo);
																			difesa = get_difesa(giocatore_attivo);
																			velocita = get_velocita(giocatore_attivo);
																			resistenza = get_resistenza(giocatore_attivo);
																			grinta = get_grinta(giocatore_attivo);

																			//ricalcolo la potenza del giocatore
																			int potenza_giocatore=0; 
																			potenza_giocatore=calcola_potenza_giocatore(pe, pt, attacco, fisico, controllo,  
difesa, velocita, resistenza, grinta);
																			if(potenza_giocatore==1){
																				printf("Errore nel ricalcolo della potenza del giocatore\n");						 
																			}
																			if (set_potenza_giocatore(giocatore_attivo, potenza_giocatore) == 1) {
																				printf("Errore nel setter della potenza del giocatore modificato\n");
																			}
																			break;
																		default:
																			printf("Opzione non disponibile, riprova\n");	
																	}
																}
																break;
															
															case 2:
																char nome_da_cambiare[20];
																printf("\nNome attuale del giocatore: '%s'\n", get_nome_giocatore(giocatore_attivo));
																		
																printf("\nInserisci il nuovo nome del giocatore:\n");
																fgets(nome_da_cambiare, sizeof(nome_da_cambiare), stdin);
																nome_da_cambiare[strcspn(nome_da_cambiare, "\n")] = '\0';
																if(valida_input(nome_da_cambiare)==0){
																	printf("Errore, inserisci almeno un carattere\n");
																	continue;
																}
																else{
																	if (get_lista_giocatori(squadra_attiva, &giocatori_squadra_attiva) == 1) {
																		printf("Errore nel getter della lista dei giocatori della squadra attiva\n");
																	}
																	
																	if(check_nome_g(giocatori_squadra_attiva, nome_da_cambiare)==1){
																		printf("Esiste già un giocatore con questo nome, riprova\n");
																		continue;
																	}
																}
																
																if(set_nome_giocatore(giocatore_attivo, nome_da_cambiare)==1){
																	printf("Errore nella modifica del nome del giocatore\n");
																}
																printf("\nModifica del nome del giocatore avvenuta con successo!\n");
																printf("\nNome attuale del giocatore: '%s'\n", get_nome_giocatore(giocatore_attivo));
																break;
															
															case 3:
																char ruolo_da_cambiare[20];
																get_ruolo(giocatore_attivo,ruolo_da_cambiare);
																printf("\nRuolo attuale di %s: '%s'\n", get_nome_giocatore(giocatore_attivo), ruolo_da_cambiare);
																		
																val=0;
																while (val == 0) {
																	printf("\nInserisci il nuovo ruolo del giocatore:\n");
																	fgets(ruolo_da_cambiare, sizeof(ruolo_da_cambiare), stdin);
																	ruolo_da_cambiare[strcspn(ruolo_da_cambiare, "\n")] = '\0';
																	
																	//controlla se l'input è valido
																	if (valida_input(ruolo_da_cambiare) == 0) {
																		printf("Errore, devi inserire almeno un carattere\n");
																	} else {
																		val = 1; 
																	}
																}
																
																if(set_ruolo(giocatore_attivo, ruolo_da_cambiare)==1){
																	printf("Errore nella modifica del ruolo del giocatore\n");
																}
																printf("\nModifica del ruolo del giocatore avvenuta con successo!\n");
																printf("\nRuolo attuale di %s: '%s'\n", get_nome_giocatore(giocatore_attivo), ruolo_da_cambiare);
																break;
															
															case 4:
																char tipo_da_cambiare[20];
																get_tipo(giocatore_attivo,tipo_da_cambiare);
																printf("\nAttualmente %s è di tipo: '%s'\n", get_nome_giocatore(giocatore_attivo), tipo_da_cambiare);
																		
																val=0;
																while (val == 0) {
																	printf("\nInserisci il nuovo tipo del giocatore:\n");
																	fgets(tipo_da_cambiare, sizeof(tipo_da_cambiare), stdin);
																	tipo_da_cambiare[strcspn(tipo_da_cambiare, "\n")] = '\0';
																	
																	//controlla se l'input è valido
																	if (valida_input(tipo_da_cambiare) == 0) {
																		printf("Errore, devi inserire almeno un carattere\n");
																	} else {
																		val = 1; 
																	}
																}
																
																if(set_tipo(giocatore_attivo, tipo_da_cambiare)==1){
																	printf("Errore nella modifica del tipo del giocatore\n");
																}
																printf("\nModifica del tipo del giocatore avvenuta con successo!\n");
																printf("\nAttualmente %s è di tipo: '%s'\n", get_nome_giocatore(giocatore_attivo), tipo_da_cambiare);
																break;
																
															case 5:
																char tecnica1[20];
																char tecnica2[20];
																char tecnica3[20];
																char tecnica4[20];
																get_tecnica1(giocatore_attivo, tecnica1);
																get_tecnica2(giocatore_attivo, tecnica2);
																get_tecnica3(giocatore_attivo, tecnica3);
																get_tecnica4(giocatore_attivo, tecnica4);
																
																printf("\nModifica delle tecniche speciali:\n");
																
																printf("\nLa prima tecnica speciale è: %s\n", tecnica1);
																printf("Inserisci la nuova tecnica speciale (premi 'invio' per non aggiungerla):\n");
																fgets(tecnica1, sizeof(tecnica1), stdin);
																tecnica1[strcspn(tecnica1, "\n")] = '\0';
																set_tecnica1(giocatore_attivo, tecnica1);
																
																printf("\nLa seconda tecnica speciale è: %s\n", tecnica2);
																printf("Inserisci la nuova tecnica speciale (premi 'invio' per non aggiungerla):\n");
																fgets(tecnica2, sizeof(tecnica2), stdin);
																tecnica2[strcspn(tecnica2, "\n")] = '\0';
																set_tecnica2(giocatore_attivo, tecnica2);
																
																printf("\nLa terza tecnica speciale è: %s\n", tecnica3);
																printf("Inserisci la nuova tecnica speciale (premi 'invio' per non aggiungerla):\n");
																fgets(tecnica3, sizeof(tecnica3), stdin);
																tecnica3[strcspn(tecnica3, "\n")] = '\0';
																set_tecnica3(giocatore_attivo, tecnica3);
																
																printf("\nLa quarta tecnica speciale è: %s\n", tecnica4);
																printf("Inserisci la nuova tecnica speciale (premi 'invio' per non aggiungerla):\n");
																fgets(tecnica4, sizeof(tecnica4), stdin);
																tecnica4[strcspn(tecnica4, "\n")] = '\0';
																set_tecnica4(giocatore_attivo, tecnica4);
																break;
															case 0:
																break;
															default:
																printf("Opzione non valida, riprova");
														}
														
													
													}while(scelta6!=0);
													
													break;
												case 2:
													
													//DICHIARAZIONE E INIZIALIZZAZIONE VARIABILI PER IL GIOCATORE
													char nome_giocatore[20];         
													char ruolo[20]; 
													char tipo[20];  
													int pe=0; int pt=0;
													int attacco=0; int fisico=0; int controllo=0; int difesa=0; int velocita=0; int resistenza=0; 
													int grinta=0;                                                                                            
													char tecnica1[20];
													char tecnica2[20];
													char tecnica3[20];
													char tecnica4[20];
													int titolare=-1;    			//0: panchinaro,   1: titolare   
													int potenza_giocatore=0; 		// Calcolata in base alle statistiche
													int res=0;
													giocatore nuovo_giocatore;
													
													//PRIMA VERIFICO SE LA SQUADRA È COMPLETA
													if(is_complete(squadra_attiva)==1){
														printf("Errore, la squadra è già completa\n");
														continue;
													}
													
													//CREAZIONE DEL GIOCATORE
													printf("\nInserisci nome e cognome del giocatore:\n");
													fgets(nome_giocatore, sizeof(nome_giocatore), stdin);
													nome_giocatore[strcspn(nome_giocatore, "\n")] = '\0';
													if(valida_input(nome_giocatore)==0){
														printf("Errore, inserisci almeno un carattere\n");
														continue;
													}
													else{
														if (get_lista_giocatori(squadra_attiva, &giocatori_squadra_attiva) == 1) {
															printf("Errore nel getter della lista dei giocatori della squadra attiva, la squadra è NULL\n");
														}
														
														if(check_nome_g(giocatori_squadra_attiva, nome_giocatore)==1){
															printf("Esiste già un giocatore con questo nome, riprova\n");
															continue;
														}
													}
													
													
													
													while( (res==0 || (res==1 && check_titolare(titolare)==1)) || (titolare==1 && 
														 get_num_titolari(squadra_attiva)==11) || (titolare==0 && get_num_panchina(squadra_attiva)==5) ){
														printf("\nVuoi che il giocatore sia un Titolare o vuoi metterlo in Panchina? (0: panchina, 1: titolare)\n");
														res=scanf("%d", &titolare);
														getchar();
														if(res==0 || (res==1 && check_titolare(titolare)==1)){
															printf("Valore non valido:\nInserisci 1 per un giocatore titolare, 0 per un giocatore in panchina\n");	
														}
														if(titolare==1 && get_num_titolari(squadra_attiva)==11){
															printf("Errore, nella squadra ci sono già 11 titolari\n");
															continue;
														}
														else if(titolare==0 && get_num_panchina(squadra_attiva)==5){
															printf("Errore, la panchina della squadra è già al completo\n");
															continue;
														}	
													}
													

													val=0;
													while (val == 0) {
														printf("\nInserisci il ruolo del giocatore:\n");
														fgets(ruolo, sizeof(ruolo), stdin);
														ruolo[strcspn(ruolo, "\n")] = '\0';
														
														//controlla se l'input è valido
														if (valida_input(ruolo) == 0) {
															printf("Errore, devi inserire almeno un carattere\n");
														} else {
															val = 1; 
														}
													}
													
													val=0;
													while (val == 0) {
														printf("\nInserisci il tipo del giocatore:\n");
														fgets(tipo, sizeof(tipo), stdin);
														tipo[strcspn(tipo, "\n")] = '\0';
														
														//controlla se l'input è valido
														if (valida_input(tipo) == 0) {
															printf("Errore, devi inserire almeno un carattere\n");
														} else {
															val = 1; 
														}
													}
													
													
													while(res==0 || (res==1 && check_statistica(pe)==0)){
														printf("\nInserisci i Punti Tecnica (PE) del giocatore:\n");
														res=scanf("%d", &pe);
														getchar();
														if(res==0 || (res==1 && check_statistica(pe)==0)){
															printf("Valore non valido:\nInserisci un numero intero positivo\n");	
														}
													}
													
													
													while(res==0 || (res==1 && check_statistica(pt)==0)){
														printf("\nInserisci i Punti Tecnica (PT) del giocatore:\n");
														res=scanf("%d", &pt);
														getchar();
														if(res==0 || (res==1 && check_statistica(pt)==0)){
															printf("Valore non valido:\nInserisci un numero intero positivo\n");	
														}
													}
													
													
													while(res==0 || (res==1 && check_statistica(attacco)==0)){
														printf("\nInserisci il livello di Attacco del giocatore:\n");
														res=scanf("%d", &attacco);
														getchar();
														if(res==0 || (res==1 && check_statistica(attacco)==0)){
															printf("Valore non valido:\nInserisci un numero intero positivo\n");	
														}
													}

													while(res==0 || (res==1 && check_statistica(fisico)==0)){
														printf("\nInserisci il livello di Fisico del giocatore:\n");
														res=scanf("%d", &fisico);
														getchar();
														if(res==0 || (res==1 && check_statistica(fisico)==0)){
															printf("Valore non valido:\nInserisci un numero intero positivo\n");	
														}
													}
													
													while(res==0 || (res==1 && check_statistica(controllo)==0)){
														printf("\nInserisci il livello di Controllo del giocatore:\n");
														res=scanf("%d", &controllo);
														getchar();
														if(res==0 || (res==1 && check_statistica(controllo)==0)){
															printf("Valore non valido:\nInserisci un numero intero positivo\n");	
														}
													}
													
													while(res==0 || (res==1 && check_statistica(difesa)==0)){
														printf("\nInserisci il livello di Difesa del giocatore:\n");
														res=scanf("%d", &difesa);
														getchar();
														if(res==0 || (res==1 && check_statistica(difesa)==0)){
															printf("Valore non valido:\nInserisci un numero intero positivo\n");	
														}
													}
													
													while(res==0 || (res==1 && check_statistica(velocita)==0)){
														printf("\nInserisci il livello di Velocita del giocatore:\n");
														res=scanf("%d", &velocita);
														getchar();
														if(res==0 || (res==1 && check_statistica(velocita)==0)){
															printf("Valore non valido:\nInserisci un numero intero positivo\n");	
														}
													}

													while(res==0 || (res==1 && check_statistica(resistenza)==0)){
														printf("\nInserisci il livello di Resistenza del giocatore:\n");
														res=scanf("%d", &resistenza);
														getchar();
														if(res==0 || (res==1 && check_statistica(resistenza)==0)){
															printf("Valore non valido:\nInserisci un numero intero positivo\n");	
														}
													}
													
													while(res==0 || (res==1 && check_statistica(grinta)==0)){
														printf("\nInserisci il livello di Grinta del giocatore:\n");
														res=scanf("%d", &grinta);
														getchar();
														if(res==0 || (res==1 && check_statistica(grinta)==0)){
															printf("Valore non valido:\nInserisci un numero intero positivo\n");	
														}
													}
													
													printf("\nTECNICHE SPECIALI: (se non vuoi aggiungere una tecnica premi direttamente 'invio')\n");
													printf("\nInserisci la prima tecnica speciale (premi 'invio' per non aggiungerla):\n");
													fgets(tecnica1, sizeof(tecnica1), stdin);
													tecnica1[strcspn(tecnica1, "\n")] = '\0';

													
													printf("\nInserisci la seconda tecnica speciale (premi 'invio' per non aggiungerla):\n");
													fgets(tecnica2, sizeof(tecnica2), stdin);
													tecnica2[strcspn(tecnica2, "\n")] = '\0';
													
													printf("\nInserisci la terza tecnica speciale (premi 'invio' per non aggiungerla):\n");
													fgets(tecnica3, sizeof(tecnica3), stdin);
													tecnica3[strcspn(tecnica3, "\n")] = '\0';
													
													printf("\nInserisci la quarta tecnica speciale (premi 'invio' per non aggiungerla):\n");
													fgets(tecnica4, sizeof(tecnica4), stdin);
													tecnica4[strcspn(tecnica4, "\n")] = '\0';
													
													//CALCOLO LA POTENZA
												    potenza_giocatore=calcola_potenza_giocatore(pe,pt,attacco,fisico,controllo,difesa,velocita,resistenza,
												                      grinta);
						                  			
						                  			//AVVIO LA CREAZIONE
						                  			nuovo_giocatore=crea_giocatore(&nuovo_giocatore, nome_giocatore, ruolo, tipo, pe, pt, attacco, fisico, 	
						                  											controllo,difesa, velocita,	resistenza, grinta,  tecnica1,  
						                  											tecnica2, tecnica3, tecnica4, titolare, potenza_giocatore);

													if(nuovo_giocatore==NULL){
														printf("Errore nella creazione del giocatore");
													}

													if(stampa_all_giocatore(nuovo_giocatore)==1){
														printf("Errore nella stampa del giocatore");
													}
													
													//AGGIUNTA DEL GIOCATORE ALLA SQUADRA ATTIVA
													if (get_lista_giocatori(squadra_attiva, &giocatori_squadra_attiva) == 1) {
														printf("Errore nel getter della lista dei giocatori della squadra attiva, la squadra è NULL\n");
													}
													if(aggiungi_giocatore(&(giocatori_squadra_attiva), nuovo_giocatore, &squadra_attiva)==1){
														printf("Errore nell'aggiunta della squadra\n");
													}
													if(set_lista_giocatori(squadra_attiva, giocatori_squadra_attiva)==1){
														printf("Errore nella sincronizzazione della lista dei giocatori\n");
													}
													
													break;
												case 3:
													//////// RIMOZIONE DI UN GIOCATORE DALLA SQUADRA ///////
													printf("\nInserisci il nome del giocatore da rimuovere dalla squadra:\n");
													fgets(nome_giocatore, sizeof(nome_giocatore), stdin);
													nome_giocatore[strcspn(nome_giocatore, "\n")] = 0;
													
													if (get_lista_giocatori(squadra_attiva, &giocatori_squadra_attiva) == 1) {
														printf("Errore nel getter della lista dei giocatori della squadra attiva, la squadra è NULL\n");
													}
													
													//AGGIORNARE I DATI DELLA SQUADRA
													giocatore giocatore_da_rimuovere=cerca_giocatore(giocatori_squadra_attiva, nome_giocatore);

													int pot_g_da_rimuovere= get_potenza_giocatore(giocatore_da_rimuovere);
													set_potenza_squadra(squadra_attiva, (get_potenza_squadra(squadra_attiva))-pot_g_da_rimuovere);
													
													if(get_titolare(giocatore_da_rimuovere)==0){
														set_num_panchina(squadra_attiva, get_num_panchina(squadra_attiva)-1);
													}
													else if(get_titolare(giocatore_da_rimuovere)==1){
														set_num_titolari(squadra_attiva, get_num_titolari(squadra_attiva)-1);
													}
													set_num_giocatori(squadra_attiva, get_num_giocatori(squadra_attiva)-1);
													
													
													int a=rimuovi_giocatore(&(giocatori_squadra_attiva), nome_giocatore);
													if(a==-1){
														printf("Errore nella rimozione del giocatore dalla squadra: Il giocatore non esiste\n");
														continue;
													}else if(a==1){
														printf("Errore nella rimozione del giocatore dalla squadra\n");
														continue;
													}
													
													if(set_lista_giocatori(squadra_attiva, giocatori_squadra_attiva)==1){
														printf("Errore nella sincronizzazione della lista dei giocatori\n");
													}
													printf("\nGiocatore rimosso con successo!\n");
													break;
												
												case 4:
													//PROMOZIONE DA RISERVA A TITOLARE
													//inserisco il nome della riserva
													giocatore giocatore_riserva;
													char nome_riserva[30];
													
													printf("\nInserisci il nome del giocatore in panchina da promuovere:\n");
													fgets(nome_riserva, sizeof(nome_riserva), stdin);
													nome_riserva[strcspn(nome_riserva, "\n")] = '\0';
													//lo cerco e lo restituisco
													if (get_lista_giocatori(squadra_attiva, &giocatori_squadra_attiva) == 1) {
														printf("Errore nel getter della lista dei giocatori della squadra attiva, la squadra è NULL\n");
													}
													giocatore_riserva=cerca_giocatore(giocatori_squadra_attiva, nome_riserva);
													//Prima controllo se il giocatore esiste
													if(giocatore_riserva==NULL){
														printf("Errore nella ricerca del giocatore in panchina, il giocatore non esiste\n");
														continue;
													} else{
														//Se esiste controllo se è già un titolare
														if(get_titolare(giocatore_riserva)==1){
															printf("Errore, il giocatore inserito è già un titolare\n");
															continue;//Se non è un titolare allora controllo se ci sono già 11 titolari
														}else if(get_titolare(giocatore_riserva)==0){ 
															//Controllo se ci sono già 11 titolari
															if(get_num_titolari(squadra_attiva)<11){
																//Se non ci sono già 11 titolari allora modifico semplicemente il campo "titolare da 0 a 1"
																//e aggiorno i valori di num_panchina e i num_titolari
																set_titolare(giocatore_riserva,1);
																set_num_titolari(squadra_attiva, get_num_titolari(squadra_attiva)+1);
																set_num_panchina(squadra_attiva, get_num_panchina(squadra_attiva)-1);
																printf("Promozione avvenuta con successo!\n");
															} else if(get_num_titolari(squadra_attiva)==11){
																//Se ci sono già 11 titolari allora devo effettuare uno scambio
																printf("In squadra ci sono già 11 titolari,\n");
																printf("Vuoi scambiare un titolare con la riserva? (1: Si / 0: torna indietro)\n");
																int scelta5=-1;
																scanf("%d", &scelta5);
																getchar();
																switch(scelta5){
																	case 1:
																		giocatore giocatore_titolare;
																		char nome_titolare[30];
																		if (get_lista_giocatori(squadra_attiva, &giocatori_squadra_attiva) == 1) {
																			printf("Errore nel getter della lista dei giocatori della squadra attiva\n");
																		}
																		if(stampa_titolari(giocatori_squadra_attiva)==1){
																			printf("Errore nella stampa dei titolari\n");
																		}
																		printf("\nInserisci il nome del titolare da sostituire:\n");
																		fgets(nome_titolare, sizeof(nome_titolare), stdin);
																		nome_titolare[strcspn(nome_titolare, "\n")] = 0;
																		
																		//lo cerco e lo restituisco
																		if (get_lista_giocatori(squadra_attiva, &giocatori_squadra_attiva) == 1) {
																			printf("Errore nel getter della lista dei giocatori della squadra attiva\n");
																		}
																		giocatore_titolare=cerca_giocatore(giocatori_squadra_attiva, nome_titolare);
																		if(giocatore_titolare==NULL){
																			printf("Errore nella ricerca del giocatore titolare, il giocatore non esiste\n");
																			continue;
																		}
																		set_titolare(giocatore_riserva,1); //setto la riserva a titolare
																		set_titolare(giocatore_titolare,0); //setto il titolare a riserva
																		printf("Promozione e sostituzione avvenute con successo!\n");
																		break;	
																											
																	case 0:
																		//torno indietro
																		break;
																	default:
																		printf("Opzione non valida, riprova\n");		
																}													
															} else if(get_num_titolari(squadra_attiva)>11){ 
																//per sicurezza controllo se il numero di titolari è maggiore di 11
																printf("Errore grave, numero di titolari oltre il massimo\n");
																return 1;
															}
														}	
													}
													break;
												
												case 5:
													//METTO UN TITOLARE IN PANCHINA
													//inserisco il nome del titolare
													giocatore giocatore_titolare;
													char nome_titolare[30];
													
													printf("\nInserisci il nome del giocatore titolare da mettere in panchina:\n");
													fgets(nome_titolare, sizeof(nome_titolare), stdin);
													nome_titolare[strcspn(nome_titolare, "\n")] = '\0';
													//lo cerco e lo restituisco
													if (get_lista_giocatori(squadra_attiva, &giocatori_squadra_attiva) == 1) {
														printf("Errore nel getter della lista dei giocatori della squadra attiva\n");
													}
													giocatore_titolare=cerca_giocatore(giocatori_squadra_attiva, nome_titolare);
													
													//Prima controllo se il giocatore esiste
													if(giocatore_titolare==NULL){
														printf("Errore nella ricerca del giocatore titolare, il giocatore non esiste\n");
														continue;
													} else{
														//Se esiste controllo se è già una riserva
														if(get_titolare(giocatore_titolare)==0){
															printf("Errore, il giocatore inserito è già in panchina\n");
															continue;//Se non è in panchina allora controllo se ci sono già 5 giocatori in panchina
														}else if(get_titolare(giocatore_titolare)==1){ 
															//Controllo se ci sono già 5 giocatori in panchina
															if(get_num_panchina(squadra_attiva)<5){
																//Se non ci sono già 5 in panchina allora modifico semplicemente il campo "titolare da 1 a 0"
																//e aggiorno i valori di num_panchina e i num_titolari
																set_titolare(giocatore_titolare,0);
																set_num_titolari(squadra_attiva, get_num_titolari(squadra_attiva)-1);
																set_num_panchina(squadra_attiva, get_num_panchina(squadra_attiva)+1);
																printf("Il giocatore ora è in panchina!\n");
															} else if(get_num_panchina(squadra_attiva)==5){
																//Se ci sono già 5 in panchina allora devo effettuare uno scambio
																printf("In squadra ci sono già 5 giocatori in panchina,\n");
																printf("Vuoi scambiare un giocatore in panchina con un titolare? (1: Si / 0: torna indietro)\n");
																int scelta5=-1;
																scanf("%d", &scelta5);
																getchar();
																switch(scelta5){
																	case 1:
																		giocatore giocatore_riserva;
																		char nome_riserva[30];
																		if (get_lista_giocatori(squadra_attiva, &giocatori_squadra_attiva) == 1) {
																			printf("Errore nel getter della lista dei giocatori della squadra attiva\n");
																		}
																		if(stampa_riserve(giocatori_squadra_attiva)==1){
																			printf("Errore nella stampa delle riserve\n");
																		}
																		printf("\nInserisci il nome del giocatore in panchina da sostituire:\n");
																		fgets(nome_riserva, sizeof(nome_riserva), stdin);
																		nome_riserva[strcspn(nome_riserva, "\n")] = 0;
																		
																		//lo cerco e lo restituisco
																		if (get_lista_giocatori(squadra_attiva, &giocatori_squadra_attiva) == 1) {
																			printf("Errore nel getter della lista dei giocatori della squadra attiva\n");
																		}
																		giocatore_riserva=cerca_giocatore(giocatori_squadra_attiva, nome_riserva);
																		if(giocatore_riserva==NULL){
																			printf("Errore nella ricerca del giocatore in, il giocatore non esiste\n");
																			continue;
																		}
																		set_titolare(giocatore_riserva,1); //setto la riserva a titolare
																		set_titolare(giocatore_titolare,0); //setto il titolare a riserva
																		printf("Retrocessione e sostituzione avvenute con successo!\n");
																		break;	
																											
																	case 0:
																		//torno indietro
																		break;
																	default:
																		printf("Opzione non valida, riprova\n");		
																}													
															} else if(get_num_titolari(squadra_attiva)>11){ 
																//per sicurezza controllo se il numero di titolari è maggiore di 11
																printf("Errore grave, numero di titolari oltre il massimo\n");
																return 1;
															}
														}	
													}
													break;
												
												case 6:
													char allenatore[20];
													get_allenatore(squadra_attiva,allenatore);
													printf("\nAllenatore attuale della squadra '%s': %s\n", get_nome_squadra(squadra_attiva), 
															allenatore);
															
													val = 0; 
													while (val == 0) {
														printf("\nInserisci il nuovo allenatore della squadra:\n");
														fgets(allenatore, sizeof(allenatore), stdin);
														allenatore[strcspn(allenatore, "\n")] = '\0';
														
														//controlla se l'input è valido
														if (valida_input(allenatore) == 0) {
															printf("Errore, devi inserire almeno un carattere\n");
														} else {
															val = 1; // Se l'input è valido, esci dal ciclo
														}
													}
													
													if(set_allenatore(squadra_attiva, allenatore)==1){
														printf("Errore nella modifica dell'allenatore\n");
													}
													printf("\nModifica dell'allenatore avvenuta con successo!\n");
													printf("\nAllenatore attuale della squadra '%s': %s\n\n", get_nome_squadra(squadra_attiva), 
															allenatore);	
													break;
												case 7:
													char nome[30];
													printf("\nNome attuale della squadra: '%s'\n", get_nome_squadra(squadra_attiva));		
													
													squadra_esistente=0;
													do {
														val = 0; 
											
														while (val == 0) {
															printf("\nInserisci il nome della squadra:\n");
															fgets(nome, sizeof(nome), stdin);
															nome[strcspn(nome, "\n")] = '\0';
															
															//controlla se l'input è valido
															if (valida_input(nome) == 0) {
																printf("Errore, devi inserire almeno un carattere\n");
															} else {
																val = 1; //se l'input è valido, esci dal ciclo
															}
														}
														
														if (get_lista_squadre(utente_attivo, &squadre_utente_attivo) == 1) {
															printf("Errore nel getter della lista delle squdre dell'utente attivo, l'utente è NULL\n");
														}
														squadra_esistente = check_nome_s(squadre_utente_attivo, nome);
														if (squadra_esistente == 1) {
															printf("\nEsiste già una squadra con questo nome, riprova\n");
														}
														
													} while (squadra_esistente == 1);
													
													
													if(set_nome_squadra(squadra_attiva, nome)==1){
														printf("Errore nella modifica del nome della squadra\n");
													}
													printf("\nModifica del nome della squadra avvenuta con successo!\n");
													printf("\nNome attuale della squadra: '%s'\n", get_nome_squadra(squadra_attiva));		
													break;
												case 0:
													break;
												default:
													printf("\nOpzione non valida! Riprova.\n");
											}	
										}while(scelta4!=0);
										break;
									
									case 2:
										printf("\nInserisci il nome della squadra da cancellare:\n");
										fgets(nome, sizeof(nome), stdin);
										nome[strcspn(nome, "\n")] = 0;
										if (get_lista_squadre(utente_attivo, &squadre_utente_attivo) == 1) {
											printf("Errore nel getter della lista delle squdre dell'utente attivo, l'utente è NULL\n");
										}
										if(rimuovi_squadra(&(squadre_utente_attivo), nome)==1){
											printf("Errore nella rimozione della squadra\n");
											continue;
										}
										//sincronizzo la lista locale con il campo `utente_attivo->squadre`
										if(set_lista_squadre(utente_attivo, squadre_utente_attivo)==1){
											printf("Errore nella sincronizzazione della lista delle squadre\n");
										} 
										printf("\nSquadra rimossa con successo!\n");
										break;
									
									case 0:
										break;
									default:
										printf("\nOpzione non valida! Riprova.\n");
								}		
							}while(scelta3!=0);
							break;
						
						case 0:
							//INDIETRO
						    printf("\n---  BENVENUTO NEL PROGRAMMA DI GESTIONE DELL SQUADRE DI INAZUMA ELEVEN  ---");	
							break;
						default:
							printf("\nOpzione non valida! Riprova.\n");
						}
				}while(scelta2!=0);
        	break;	
        	
        	case 2:
        		//REGISTRAZIONE
				int username_esistente = 0; 
				do {
					val = 0; 
					
					while (val == 0) {
						printf("\nRegistrati Inserendo il tuo username:\n");
						fgets(username, sizeof(username), stdin);
						username[strcspn(username, "\n")] = '\0';
						
						//controlla se l'input è valido
						if (valida_input(username) == 0) {
							printf("Errore, devi inserire almeno un carattere\n");
						} else {
							val = 1; // Se l'input è valido, esci dal ciclo
						}
					}

					//verifica se l'username è già esistente
					username_esistente = check_username(head_utenti, username);
					
					//se username è già esistente, avvisa l'utente
					if (username_esistente == 1) {
						printf("\nUsername già esistente, riprova\n");
					}
					else{
						printf("\nInserisci la password (max 8 caratteri):\n");
						fgets(password, sizeof(password), stdin);
						password[strcspn(password, "\n")] = '\0';
					
					}

				} while (username_esistente == 1); //continua a chiedere finché l'username non è unico
				
				
				//CREAZIONE DELL'UTENTE
        		if(crea_utente(&utente_attivo,username,password)==1){
        			printf("Errore nella creazione dell'utente\n");
        		}
        		else{
        			printf("\nUtente creato con successo, Username: %s\n", get_username(utente_attivo));
        		}                         
   		
				//AGGIUNTA DELL'UTENTE ALLA LISTA
        		if (aggiungi_utente(&head_utenti, utente_attivo)==1){
        			printf("Errore nell'aggiunta dell'utente\n");
        		}
        		//printf("\nLista degli utenti registrati:\n");
        		//stampa_lista_utenti(head_utenti);
        		break;
        	
        	case 0:
        		//SALVO TUTTO SU FILE:
        		
        		if(salva_su_file(head_utenti)==1){
        			printf("Errore nel salvataggio su file dei dati del programma\n");
        		}
        		
        		//LIBERO LA MEMORIA
        		if(destroy_lista_utenti(&head_utenti)==1){
        			printf("Errore nella deallocazione della lista degli utenti\n");
        		}
                printf("\nUscita dal programma in corso...\n");
        		break;
        	
        	 default:
                printf("\nOpzione non valida! Riprova.\n");
             }
     
	}while(scelta!=0);
	return 0;	
}	


