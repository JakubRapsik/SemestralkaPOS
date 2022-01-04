

#ifndef SEMESTRALKASERVER_HRA_H
#define SEMESTRALKASERVER_HRA_H


#include <stdbool.h>

int tah(int stlpec, char hrac, char **hraciaPlocha);

bool kontrolaVyhry(char **hraciaPlocha, int globalstlpec, int globalriadok);

int skore(char hrac, char **hraciaPlocha);

#endif //SEMESTRALKASERVER_HRA_H


