

#ifndef SEMESTRALKASERVER_HRA_H
#define SEMESTRALKASERVER_HRA_H


#include <stdbool.h>

int prehladavanie(int stlpec,int riadok, char znak);

int tah(int stlpec, char hrac);

void vypis(char *b, int socket);

bool kontrolaVyhry();

#endif //SEMESTRALKASERVER_HRA_H


