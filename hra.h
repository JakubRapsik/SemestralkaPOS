

#ifndef SEMESTRALKASERVER_HRA_H
#define SEMESTRALKASERVER_HRA_H


#include <stdbool.h>

int prehladavanie(int stlpec, int riadok, char znak);

int tah(int stlpec, char hrac, char **hraciaPlocha);

void vypis(char *b, int socket);

bool kontrolaVyhry(char **hraciaPlocha, int globalstlpec, int globalriadok);

int skore(char hrac, char **hraciaPlocha);

#endif //SEMESTRALKASERVER_HRA_H


