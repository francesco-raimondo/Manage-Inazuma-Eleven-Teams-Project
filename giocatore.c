#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include "giocatore.h" 


int calcola_potenza_giocatore(int pe, int pt, int attacco, int fisico, int controllo, int difesa, int velocita, int resistenza, int grinta){
	if (pe < 0 || pt < 0 || attacco < 0 || fisico < 0 || controllo < 0 ||
        difesa < 0 || velocita < 0 || resistenza < 0 || grinta < 0) {
        return 1; 
    }

    float peso_pe = 1.0;
    float peso_pt = 1.2;
    float peso_attacco = 1.5;
    float peso_fisico = 1.1;
    float peso_controllo = 1.3;
    float peso_difesa = 1.2;
    float peso_velocita = 1.4;
    float peso_resistenza = 1.0;
    float peso_grinta = 0.9;

    float potenza = (pe * peso_pe) +
                    (pt * peso_pt) +
                    (attacco * peso_attacco) +
                    (fisico * peso_fisico) +
                    (controllo * peso_controllo) +
                    (difesa * peso_difesa) +
                    (velocita * peso_velocita) +
                    (resistenza * peso_resistenza) +
                    (grinta * peso_grinta);

    return (int)potenza; 
}


const char* get_nome_giocatore(giocatore g) {
    if (g == NULL)
        return NULL;
    return g->nome_giocatore;
}

int get_ruolo(giocatore g, char* ruolo) {
    if (g == NULL)
        return 1;
    strcpy(ruolo, g->ruolo);
    return 0;
}

int get_tipo(giocatore g, char* tipo) {
    if (g == NULL)
        return 1;
    strcpy(tipo, g->tipo);
    return 0;
}

int get_pe(giocatore g) {
    if (g == NULL)
        return -1;
    return g->pe;
}

int get_pt(giocatore g) {
    if (g == NULL)
        return -1;
    return g->pt;
}

int get_attacco(giocatore g) {
    if (g == NULL)
        return -1;
    return g->attacco;
}

int get_fisico(giocatore g) {
    if (g == NULL)
        return -1;
    return g->fisico;
}

int get_controllo(giocatore g) {
    if (g == NULL)
        return -1;
    return g->controllo;
}

int get_difesa(giocatore g) {
    if (g == NULL)
        return -1;
    return g->difesa;
}

int get_velocita(giocatore g) {
    if (g == NULL)
        return -1;
    return g->velocita;
}

int get_resistenza(giocatore g) {
    if (g == NULL)
        return -1;
    return g->resistenza;
}

int get_grinta(giocatore g) {
    if (g == NULL)
        return -1;
    return g->grinta;
}

int get_tecnica1(giocatore g, char* tecnica1) {
    if (g == NULL)
        return 1;
    strcpy(tecnica1, g->tecnica1);
    return 0;
}

int get_tecnica2(giocatore g, char* tecnica2) {
    if (g == NULL)
        return 1;
    strcpy(tecnica2, g->tecnica2);
    return 0;
}

int get_tecnica3(giocatore g, char* tecnica3) {
    if (g == NULL)
        return 1;
    strcpy(tecnica3, g->tecnica3);
    return 0;
}

int get_tecnica4(giocatore g, char* tecnica4) {
    if (g == NULL)
        return 1;
    strcpy(tecnica4, g->tecnica4);
    return 0;
}

int get_potenza_giocatore(giocatore g) {
    if (g == NULL)
        return -1;
    return g->potenza_giocatore;
}

int get_titolare(giocatore g){
	if (g == NULL)
        return -1;
    return g->titolare;
}




int set_nome_giocatore(giocatore g, const char* nome_giocatore) {
    if (g == NULL)
        return 1;
    strcpy(g->nome_giocatore, nome_giocatore);
    return 0;
}

int set_ruolo(giocatore g, const char* ruolo) {
    if (g == NULL)
        return 1;
    strcpy(g->ruolo, ruolo);
    return 0;
}

int set_tipo(giocatore g, const char* tipo) {
    if (g == NULL)
        return 1;
    strcpy(g->tipo, tipo);
    return 0;
}

int set_pe(giocatore g, int pe) {
    if (g == NULL)
        return 1;
    g->pe = pe;
    return 0;
}

int set_pt(giocatore g, int pt) {
    if (g == NULL)
        return 1;
    g->pt = pt;
    return 0;
}

int set_attacco(giocatore g, int attacco) {
    if (g == NULL)
        return 1;
    g->attacco = attacco;
    return 0;
}

int set_fisico(giocatore g, int fisico) {
    if (g == NULL)
        return 1;
    g->fisico = fisico;
    return 0;
}

int set_controllo(giocatore g, int controllo) {
    if (g == NULL)
        return 1;
    g->controllo = controllo;
    return 0;
}

int set_difesa(giocatore g, int difesa) {
    if (g == NULL)
        return 1;
    g->difesa = difesa;
    return 0;
}

int set_velocita(giocatore g, int velocita) {
    if (g == NULL)
        return 1;
    g->velocita = velocita;
    return 0;
}

int set_resistenza(giocatore g, int resistenza) {
    if (g == NULL)
        return 1;
    g->resistenza = resistenza;
    return 0;
}

int set_grinta(giocatore g, int grinta) {
    if (g == NULL)
        return 1;
    g->grinta = grinta;
    return 0;
}

int set_tecnica1(giocatore g, const char* tecnica1) {
    if (g == NULL)
		return 1;
    if (strlen(tecnica1) == 0) {
		strcpy(g->tecnica1, "----");
	}
	else{
    	strcpy(g->tecnica1, tecnica1);
    }
    return 0;
}

int set_tecnica2(giocatore g, const char* tecnica2) {
    if (g == NULL)
		return 1;
	if (strlen(tecnica2) == 0) {
		strcpy(g->tecnica2, "----");
	}
	else{
 		strcpy(g->tecnica2, tecnica2);
    }
    return 0;
}

int set_tecnica3(giocatore g, const char* tecnica3) {
    if (g == NULL)
        return 1;
    if (strlen(tecnica3) == 0) {
		strcpy(g->tecnica3, "----");
	}
	else{
    	strcpy(g->tecnica3, tecnica3);
    }
    return 0;
}

int set_tecnica4(giocatore g, const char* tecnica4) {
    if (g == NULL)
        return 1;
    if (strlen(tecnica4) == 0) {
		strcpy(g->tecnica4, "----");
	}
	else{
    	strcpy(g->tecnica4, tecnica4);
    }
    return 0;
}

int set_potenza_giocatore(giocatore g, int potenza_giocatore) {
    if (g == NULL || potenza_giocatore < 0)
        return 1;
    g->potenza_giocatore = potenza_giocatore;
    return 0;
}

int set_titolare(giocatore g, int titolare) {
    if (g == NULL)
        return 1;
    g->titolare = titolare;
    return 0;
}





giocatore crea_giocatore(giocatore* nuovo_giocatore, const char* nome_giocatore, const char* ruolo, const char* tipo, int pe, int pt,
                       int attacco, int fisico, int controllo, int difesa, int velocita, int resistenza, int grinta, 
                       const char* tecnica1, const char* tecnica2, const char* tecnica3, const char* tecnica4, int titolare, int potenza_giocatore){
                       
	*nuovo_giocatore = (giocatore)malloc(sizeof(struct giocatore));
	if (*nuovo_giocatore== NULL)
		return NULL;    
	else{
		set_nome_giocatore(*nuovo_giocatore, nome_giocatore);
		set_ruolo(*nuovo_giocatore, ruolo);
		set_tipo(*nuovo_giocatore, tipo);
		set_pe(*nuovo_giocatore, pe);
		set_pt(*nuovo_giocatore, pt);
		set_attacco(*nuovo_giocatore, attacco);
		set_fisico(*nuovo_giocatore, fisico);
		set_controllo(*nuovo_giocatore, controllo);
		set_difesa(*nuovo_giocatore, difesa);
		set_velocita(*nuovo_giocatore, velocita);
		set_resistenza(*nuovo_giocatore, resistenza);
		set_grinta(*nuovo_giocatore, grinta);
		set_tecnica1(*nuovo_giocatore, tecnica1);
		set_tecnica2(*nuovo_giocatore, tecnica2);
		set_tecnica3(*nuovo_giocatore, tecnica3);
		set_tecnica4(*nuovo_giocatore, tecnica4);
		set_titolare(*nuovo_giocatore, titolare);
		set_potenza_giocatore(*nuovo_giocatore, potenza_giocatore);
		return *nuovo_giocatore;
	}        
 
}   
         
int stampa_all_giocatore(giocatore g){
	if(g==NULL)
			return 1;
	char nome_giocatore[20];         
    char ruolo[20]; 
    char tipo[20];  
    int pe, pt;
    int attacco, fisico, controllo, difesa, velocita, resistenza, grinta;        
    char tecnica1[20];
    char tecnica2[20];
    char tecnica3[20];
    char tecnica4[20];
    int titolare;    			//0: panchinaro,   1: titolare   
    int potenza_giocatore;
     
	strcpy(nome_giocatore, get_nome_giocatore(g));
	get_ruolo(g,ruolo);
	get_tipo(g,tipo);
	pe=get_pe(g);
	pt=get_pt(g);
	attacco=get_attacco(g);
	fisico=get_fisico(g);
	controllo=get_controllo(g);
	difesa=get_difesa(g);
	velocita=get_velocita(g);
	resistenza=get_resistenza(g);
	grinta=get_grinta(g);
	get_tecnica1(g,tecnica1);
	get_tecnica2(g,tecnica2);
	get_tecnica3(g,tecnica3);
	get_tecnica4(g,tecnica4);
	titolare=get_titolare(g);
	potenza_giocatore=get_potenza_giocatore(g);
	
	printf("\n-> %s\n", nome_giocatore);
	printf("   Ruolo: %s   |   Tipo: %s   |   Potenza: %d   |", ruolo, tipo, potenza_giocatore);
	if(titolare==1)
		printf("   Stato: titolare\n");
	else
		printf("   Stato: in panchina\n");	
	printf("\nStatistiche:\n");
	printf("  Punti Energia (PE): %d\n", pe);
	printf("  Punti Tecnica (PT): %d\n", pt);
    printf("  Attacco: %d\n", attacco);
    printf("  Fisico: %d\n", fisico);
    printf("  Controllo: %d\n", controllo);
    printf("  Difesa: %d\n", difesa);
    printf("  Velocità: %d\n", velocita);
    printf("  Resistenza: %d\n", resistenza);
    printf("  Grinta: %d\n", grinta);
    
    printf("\nTecniche speciali:\n");
    printf("1) %s\n", g->tecnica1);
    printf("2) %s\n", g->tecnica2);
    printf("3) %s\n", g->tecnica3);
    printf("4) %s\n", g->tecnica4);
	return 0;
	
}

int stampa_giocatore(giocatore g){
	if(g==NULL)
			return 1;
	char nome_giocatore[20];         
    char ruolo[20]; 
    char tipo[20];
	int titolare;    			//0: panchinaro,   1: titolare   
    int potenza_giocatore;
    
    strcpy(nome_giocatore, get_nome_giocatore(g));
	get_ruolo(g,ruolo);
	get_tipo(g,tipo);
    titolare=get_titolare(g);
	potenza_giocatore=get_potenza_giocatore(g);
    
	printf("-> %s\n", nome_giocatore);
	printf("   Ruolo: %s   |   Tipo: %s   |   Potenza: %d   |", ruolo, tipo, potenza_giocatore);
	if(titolare==1)
		printf("   Stato: titolare\n");
	else
		printf("   Stato: in panchina\n");
	printf("\n");
	return 0;
}


int check_titolare(int titolare) {
   if (titolare != 0 && titolare != 1) {
       return 1; 
   }
   return 0; 
}



int check_statistica(int statistica){
	 return statistica > 0; //restituisce 1 se è positivo, 0 altrimenti
}



int destroy_giocatore(giocatore* g){
    if (*g == NULL){
    	return 1;
    }
    else{
    	free(*g);
    	*g = NULL;
    	return 0;
    }
}
