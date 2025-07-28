#ifndef GIOCATORE_H    
#define GIOCATORE_H    

#include <stdbool.h>   
#include <stdio.h>     
#include <stdlib.h>    
#include <string.h> 


typedef struct squadra* squadra;
typedef struct nodo_squadra* lista_squadre;


typedef struct giocatore* giocatore;



struct giocatore {
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
    int potenza_giocatore; 		// Calcolata in base alle statistiche

};

int calcola_potenza_giocatore(int pe, int pt, int attacco, int fisico, int controllo, int difesa, int velocita, int resistenza, int grinta);

const char* get_nome_giocatore(giocatore g);

int get_ruolo(giocatore g, char* ruolo);

int get_tipo(giocatore g, char* tipo);

int get_pe(giocatore g);

int get_pt(giocatore g);

int get_attacco(giocatore g);

int get_fisico(giocatore g);

int get_controllo(giocatore g);

int get_difesa(giocatore g);

int get_velocita(giocatore g);

int get_resistenza(giocatore g);

int get_grinta(giocatore g);

int get_tecnica1(giocatore g, char* tecnica1);

int get_tecnica2(giocatore g, char* tecnica2);

int get_tecnica3(giocatore g, char* tecnica3);

int get_tecnica4(giocatore g, char* tecnica4);

int get_potenza_giocatore(giocatore g); 			

int get_titolare(giocatore g);


int set_nome_giocatore(giocatore g, const char* nome_giocatore);

int set_ruolo(giocatore g, const char* ruolo);

int set_tipo(giocatore g, const char* tipo);

int set_pe(giocatore g, int pe);

int set_pt(giocatore g, int pt);

int set_attacco(giocatore g, int attacco);

int set_fisico(giocatore g, int fisico);

int set_controllo(giocatore g, int controllo);

int set_difesa(giocatore g, int difesa);

int set_velocita(giocatore g, int velocita);

int set_resistenza(giocatore g, int resistenza);

int set_grinta(giocatore g, int grinta);

int set_tecnica1(giocatore g, const char* tecnica1);

int set_tecnica2(giocatore g, const char* tecnica2);

int set_tecnica3(giocatore g, const char* tecnica3);

int set_tecnica4(giocatore g, const char* tecnica4);

int set_potenza_giocatore(giocatore g, int potenza_giocatore); 

int set_titolare(giocatore g, int titolare);


giocatore crea_giocatore(giocatore* nuovo_giocatore, const char* nome_giocatore, const char* ruolo, const char* tipo, int pe, int pt, int attacco, int fisico, int 	controllo, int difesa, int velocita, int resistenza, int grinta,  const char* tecnica1, const char* tecnica2, const char* tecnica3, const char* tecnica4, int titolare, int potenza_giocatore); 
   
     
int stampa_giocatore(giocatore g);

int stampa_all_giocatore(giocatore g);

int destroy_giocatore(giocatore* g);


int modifica_giocatore(giocatore* g_da_modificare, char* nome,  char* ruolo, char* tipo, int pe, int pt, int attacco, int fisico, int controllo, int difesa, int velocita, int resistenza, int grinta, char* tecnica1, char* tecnica2, char* tecnica3, char* tecnica4);

int check_titolare(int titolare);

int check_statistica(int statistica);
#endif

