#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "hra.h"


bool kontrolaVyhry(char **hraciaPlocha, int globalstlpec, int globalriadok) {
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

int tah(int stlpec, char hrac, char **hraciaPlocha) {
    for (int riadky = 5; riadky >= 0; riadky--) {
        if (stlpec - 1 >= 0 && stlpec + 1 <= 7 && riadky - 1 >= 0 && riadky + 1 <= 6) {
            if (hraciaPlocha[stlpec][riadky] == 'O') {
                hraciaPlocha[stlpec][riadky] = hrac;
                return riadky;
            }
        } else {
            return -1;
        }
    }
    return -1;
}

//int skore(char hrac, char **hraciaPlocha) {
//    int pocet1;
//    int pocet2;
//    int pocet3;
//    char pomocnaPlocha[7][6];
//    //Lavo
//    for (int stlpec = 0; stlpec < 7; ++stlpec) {
//        for (int riadok = 0; riadok < 6; ++riadok) {
//            if (pomocnaPlocha[7][6] == "X"){
//
//            }
//        }
//    }
//    if (globalstlpec - 1 >= 0 && hraciaPlocha[globalstlpec - 1][globalriadok] == znak) {
//        counter++;
//        pomocnaStlpec = globalstlpec - 1;
//        for (int i = 1; i < 3; ++i) {
//            if (pomocnaStlpec - 1 >= 0 && hraciaPlocha[pomocnaStlpec - i][globalriadok] == znak) {
//                counter++;
//            }
//        }
//        if (counter == 4) {
//            return true;
//        } else {
//            counter = 1;
//        }
//    }
//    //Pravo
//    if (globalstlpec + 1 <= 6 && hraciaPlocha[globalstlpec + 1][globalriadok] == znak) {
//        counter++;
//        pomocnaStlpec = globalstlpec + 1;
//        for (int i = 1; i < 3; ++i) {
//            if (pomocnaStlpec + 1 <= 6 && hraciaPlocha[pomocnaStlpec + i][globalriadok] == znak) {
//                counter++;
//            }
//        }
//        if (counter == 4) {
//            return true;
//        } else {
//            counter = 1;
//        }
//    }
//    //Hore
//    if (globalriadok - 1 >= 0 && hraciaPlocha[globalstlpec][globalriadok - 1] == znak) {
//        counter++;
//        pomocnaRiadok = globalriadok - 1;
//        for (int i = 1; i < 3; ++i) {
//            if (pomocnaRiadok - 1 >= 0 && hraciaPlocha[globalstlpec][pomocnaRiadok - i] == znak) {
//                counter++;
//            }
//        }
//        if (counter == 4) {
//            return true;
//        } else {
//            counter = 1;
//        }
//    }
//    //Dole
//    if (globalriadok + 1 <= 5 && hraciaPlocha[globalstlpec][globalriadok + 1] == znak) {
//        counter++;
//        pomocnaRiadok = globalriadok + 1;
//        for (int i = 1; i < 3; ++i) {
//            if (pomocnaRiadok + 1 <= 5 && hraciaPlocha[globalstlpec][pomocnaRiadok + i] == znak) {
//                counter++;
//            }
//        }
//        if (counter == 4) {
//            return true;
//        } else {
//            counter = 1;
//        }
//    }
//    //LavoHore
//    if (globalstlpec - 1 >= 0 && globalriadok - 1 >= 0 && hraciaPlocha[globalstlpec - 1][globalriadok - 1] == znak) {
//        counter++;
//        pomocnaRiadok = globalriadok - 1;
//        pomocnaStlpec = globalstlpec - 1;
//        for (int i = 1; i < 3; ++i) {
//            if (pomocnaRiadok - 1 >= 0 && pomocnaStlpec - 1 >= 0 &&
//                hraciaPlocha[pomocnaStlpec - i][pomocnaRiadok - i] == znak) {
//                counter++;
//            }
//        }
//        if (counter == 4) {
//            return true;
//        } else {
//            counter = 1;
//        }
//    }
//    //LavoDole
//    if (globalstlpec - 1 >= 0 && globalriadok + 1 <= 5 && hraciaPlocha[globalstlpec - 1][globalriadok + 1] == znak) {
//        counter++;
//        pomocnaRiadok = globalriadok + 1;
//        pomocnaStlpec = globalstlpec - 1;
//        for (int i = 1; i < 3; ++i) {
//            if (pomocnaRiadok + 1 <= 5 && pomocnaStlpec - 1 >= 0 &&
//                hraciaPlocha[pomocnaStlpec - i][pomocnaRiadok + i] == znak) {
//                counter++;
//            }
//        }
//        if (counter == 4) {
//            return true;
//        } else {
//            counter = 1;
//        }
//
//    }
//    //PravoDole
//    if (globalstlpec + 1 <= 6 && globalriadok + 1 <= 5 && hraciaPlocha[globalstlpec + 1][globalriadok + 1] == znak) {
//        counter++;
//        pomocnaRiadok = globalriadok + 1;
//        pomocnaStlpec = globalstlpec + 1;
//        for (int i = 1; i < 3; ++i) {
//            if (pomocnaRiadok + 1 <= 5 && pomocnaStlpec + 1 <= 6 &&
//                hraciaPlocha[pomocnaStlpec + i][pomocnaRiadok + i] == znak) {
//                counter++;
//            }
//        }
//        if (counter == 4) {
//            return true;
//        } else {
//            counter = 1;
//        }
//    }
//    //PravoHore
//    if (globalstlpec + 1 <= 6 && globalriadok - 1 >= 0 && hraciaPlocha[globalstlpec + 1][globalriadok - 1] == znak) {
//        counter++;
//        pomocnaRiadok = globalriadok - 1;
//        pomocnaStlpec = globalstlpec + 1;
//        for (int i = 1; i < 3; ++i) {
//            if (pomocnaRiadok - 1 >= 0 && pomocnaStlpec + 1 <= 6 &&
//                hraciaPlocha[pomocnaStlpec + i][pomocnaRiadok - i] == znak) {
//                counter++;
//            }
//        }
//        if (counter == 4) {
//            return true;
//        } else {
//            counter = 1;
//        }
//    }
//}

//
//void vypis(char **hraciaPlocha, int socket) {
//    const char *msg;
//    for (int riadok = 0; riadok < 6; ++riadok) {
//        for (int stlpec = 0; stlpec < 7; ++stlpec) {
//            msg =*(*(hraciaPlocha + stlpec) + riadok);
//        }
//        write(socket, msg, strlen(msg) + 1);
//        printf(msg);
//    }
//}
