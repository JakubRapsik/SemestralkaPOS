#include "hra.h"

char hraciaPlocha[7][6];
int globalstlpec = 0;
int globalriadok = 0;


bool kontrolaVyhry() {
    int counter = 1;
    int pomocnaStlpec = 0;
    int pomocnaRiadok = 0;
    char znak = hraciaPlocha[globalstlpec][globalriadok];
    //Lavo
    if (globalstlpec - 1 >= 0 && hraciaPlocha[globalstlpec - 1][globalriadok] == znak) {
        counter++;
        pomocnaStlpec = globalstlpec - 1;
        for (int i = 1; i < 3; ++i) {
            if (pomocnaStlpec - 1 >= 0 && hraciaPlocha[pomocnaStlpec - i][globalriadok] == znak) {
                counter++;
            }
        }
        if (counter == 4) {
            return true;
        } else {
            counter = 1;
        }
    }
    //Pravo
    if (globalstlpec + 1 <= 6 && hraciaPlocha[globalstlpec + 1][globalriadok] == znak) {
        counter++;
        pomocnaStlpec = globalstlpec + 1;
        for (int i = 1; i < 3; ++i) {
            if (pomocnaStlpec + 1 <= 6 && hraciaPlocha[pomocnaStlpec + i][globalriadok] == znak) {
                counter++;
            }
        }
        if (counter == 4) {
            return true;
        } else {
            counter = 1;
        }
    }
    //Hore
    if (globalriadok - 1 >= 0 && hraciaPlocha[globalstlpec][globalriadok - 1] == znak) {
        counter++;
        pomocnaRiadok = globalriadok - 1;
        for (int i = 1; i < 3; ++i) {
            if (pomocnaRiadok - 1 >= 0 && hraciaPlocha[globalstlpec][pomocnaRiadok - i] == znak) {
                counter++;
            }
        }
        if (counter == 4) {
            return true;
        } else {
            counter = 1;
        }
    }
    //Dole
    if (globalriadok + 1 <= 5 && hraciaPlocha[globalstlpec][globalriadok + 1] == znak) {
        counter++;
        pomocnaRiadok = globalriadok + 1;
        for (int i = 1; i < 3; ++i) {
            if (pomocnaRiadok + 1 <= 5 && hraciaPlocha[globalstlpec][pomocnaRiadok + i] == znak) {
                counter++;
            }
        }
        if (counter == 4) {
            return true;
        } else {
            counter = 1;
        }
    }
    //LavoHore
    if (globalstlpec - 1 >= 0 && globalriadok - 1 >= 0 && hraciaPlocha[globalstlpec - 1][globalriadok - 1] == znak) {
        counter++;
        pomocnaRiadok = globalriadok - 1;
        pomocnaStlpec = globalstlpec - 1;
        for (int i = 1; i < 3; ++i) {
            if (pomocnaRiadok - 1 >= 0 && pomocnaStlpec - 1 >= 0 &&
                hraciaPlocha[pomocnaStlpec - i][pomocnaRiadok - i] == znak) {
                counter++;
            }
        }
        if (counter == 4) {
            return true;
        } else {
            counter = 1;
        }
    }
    //LavoDole
    if (globalstlpec - 1 >= 0 && globalriadok + 1 <= 5 && hraciaPlocha[globalstlpec - 1][globalriadok + 1] == znak) {
        counter++;
        pomocnaRiadok = globalriadok + 1;
        pomocnaStlpec = globalstlpec - 1;
        for (int i = 1; i < 3; ++i) {
            if (pomocnaRiadok + 1 <= 5 && pomocnaStlpec - 1 >= 0 &&
                hraciaPlocha[pomocnaStlpec - i][pomocnaRiadok + i] == znak) {
                counter++;
            }
        }
        if (counter == 4) {
            return true;
        } else {
            counter = 1;
        }

    }
    //PravoDole
    if (globalstlpec + 1 <= 6 && globalriadok + 1 <= 5 && hraciaPlocha[globalstlpec + 1][globalriadok + 1] == znak) {
        counter++;
        pomocnaRiadok = globalriadok + 1;
        pomocnaStlpec = globalstlpec + 1;
        for (int i = 1; i < 3; ++i) {
            if (pomocnaRiadok + 1 <= 5 && pomocnaStlpec + 1 <= 6 &&
                hraciaPlocha[pomocnaStlpec + i][pomocnaRiadok + i] == znak) {
                counter++;
            }
        }
        if (counter == 4) {
            return true;
        } else {
            counter = 1;
        }
    }
    //PravoHore
    if (globalstlpec + 1 <= 6 && globalriadok - 1 >= 0 && hraciaPlocha[globalstlpec + 1][globalriadok - 1] == znak) {
        counter++;
        pomocnaRiadok = globalriadok - 1;
        pomocnaStlpec = globalstlpec + 1;
        for (int i = 1; i < 3; ++i) {
            if (pomocnaRiadok - 1 >= 0 && pomocnaStlpec + 1 <= 6 &&
                hraciaPlocha[pomocnaStlpec + i][pomocnaRiadok - i] == znak) {
                counter++;
            }
        }
        if (counter == 4) {
            return true;
        } else {
            counter = 1;
        }
    }
    return false;
}

//int prehladavanie(int stlpec, int riadok , char znak) {
//    int counter = 2;
//    for (int i = 1; i < 3; ++i) {
//        if (stlpec + 1 <= 6 && hraciaPlocha[stlpec + i][riadok] == znak) {
//            counter++;
//        }
//    }
//
//}

int tah(int stlpec, char hrac) {
    for (int riadky = 5; riadky >= 0; riadky--) {
        if (stlpec - 1 >= 0 && stlpec + 1 <= 6 && riadky - 1 >= 0 && riadky + 1 <= 5) {
            if (hraciaPlocha[stlpec][riadky] == 0) {
                hraciaPlocha[stlpec][riadky] = hrac;
                globalriadok = riadky;
                globalstlpec = stlpec;
                return 0;
            }
        } else {
            return 1;
        }
    }
    return 1;
}


