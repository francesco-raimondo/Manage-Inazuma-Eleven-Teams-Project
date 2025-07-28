#!/bin/bash

if [ "$1" == "clean" ]; then
    rm -f *.o
    rm -f squadre_inazuma
else
    gcc -c -g squadre_inazuma.c -o squadre_inazuma.o
    gcc -c -g utente.c -o utente.o
    gcc -c -g nodo_utente.c -o nodo_utente.o
    gcc -c -g squadra.c -o squadra.o
    gcc -c -g nodo_squadra.c -o nodo_squadra.o
    gcc -c -g giocatore.c -o giocatore.o
    gcc -c -g nodo_giocatore.c -o nodo_giocatore.o

    gcc -g -o squadre_inazuma squadre_inazuma.o utente.o nodo_utente.o squadra.o nodo_squadra.o giocatore.o nodo_giocatore.o
fi

