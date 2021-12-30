#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "hra.h"


//bool kontrolaVyhry(char **hraciaPlocha, int globalstlpec, int globalriadok) {
//    int counter = 1;
//    int pomocnaStlpec = 0;
//    int pomocnaRiadok = 0;
//    char znak = hraciaPlocha[globalstlpec][globalriadok];
//    //Lavo
//    if (globalstlpec - 1 >= 0 && hraciaPlocha[globalstlpec - 1][globalriadok] == znak) {
//        counter++;
//        pomocnaStlpec = globalstlpec - 1;
//        for (int i = 1; i < 3; ++i) {
//            if (pomocnaStlpec - i >= 0 && hraciaPlocha[pomocnaStlpec - i][globalriadok] == znak) {
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
//            if (pomocnaStlpec + i <= 6 && hraciaPlocha[pomocnaStlpec + i][globalriadok] == znak) {
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
//            if (pomocnaRiadok - i >= 0 && hraciaPlocha[globalstlpec][pomocnaRiadok - i] == znak) {
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
//            if (pomocnaRiadok + i <= 5 && hraciaPlocha[globalstlpec][pomocnaRiadok + i] == znak) {
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
//            if (pomocnaRiadok - i >= 0 && pomocnaStlpec - i >= 0 &&
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
//            if (pomocnaRiadok + i <= 5 && pomocnaStlpec - i >= 0 &&
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
//            if (pomocnaRiadok + i <= 5 && pomocnaStlpec + i <= 6 &&
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
//            if (pomocnaRiadok - i >= 0 && pomocnaStlpec + i <= 6 &&
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
//    return false;
//}

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
            if (pomocnaStlpec - i >= 0 && hraciaPlocha[pomocnaStlpec - i][globalriadok] == znak) {
                counter++;
            }
        }
    }
    //Pravo
    if (globalstlpec + 1 <= 6 && hraciaPlocha[globalstlpec + 1][globalriadok] == znak) {
        counter++;
        pomocnaStlpec = globalstlpec + 1;
        for (int i = 1; i < 3; ++i) {
            if (pomocnaStlpec + i <= 6 && hraciaPlocha[pomocnaStlpec + i][globalriadok] == znak) {
                counter++;
            }
        }

    }
    if (counter >= 4) {
        return true;
    } else {
        counter = 1;
    }
    //Hore
    if (globalriadok - 1 >= 0 && hraciaPlocha[globalstlpec][globalriadok - 1] == znak) {
        counter++;
        pomocnaRiadok = globalriadok - 1;
        for (int i = 1; i < 3; ++i) {
            if (pomocnaRiadok - i >= 0 && hraciaPlocha[globalstlpec][pomocnaRiadok - i] == znak) {
                counter++;
            }
        }
    }
    //Dole
    if (globalriadok + 1 <= 5 && hraciaPlocha[globalstlpec][globalriadok + 1] == znak) {
        counter++;
        pomocnaRiadok = globalriadok + 1;
        for (int i = 1; i < 3; ++i) {
            if (pomocnaRiadok + i <= 5 && hraciaPlocha[globalstlpec][pomocnaRiadok + i] == znak) {
                counter++;
            }
        }

    }
    if (counter >= 4) {
        return true;
    } else {
        counter = 1;
    }
    //LavoHore
    if (globalstlpec - 1 >= 0 && globalriadok - 1 >= 0 && hraciaPlocha[globalstlpec - 1][globalriadok - 1] == znak) {
        counter++;
        pomocnaRiadok = globalriadok - 1;
        pomocnaStlpec = globalstlpec - 1;
        for (int i = 1; i < 3; ++i) {
            if (pomocnaRiadok - i >= 0 && pomocnaStlpec - i >= 0 &&
                hraciaPlocha[pomocnaStlpec - i][pomocnaRiadok - i] == znak) {
                counter++;
            }
        }
    }
    //PravoDole
    if (globalstlpec + 1 <= 6 && globalriadok + 1 <= 5 && hraciaPlocha[globalstlpec + 1][globalriadok + 1] == znak) {
        counter++;
        pomocnaRiadok = globalriadok + 1;
        pomocnaStlpec = globalstlpec + 1;
        for (int i = 1; i < 3; ++i) {
            if (pomocnaRiadok + i <= 5 && pomocnaStlpec + i <= 6 &&
                hraciaPlocha[pomocnaStlpec + i][pomocnaRiadok + i] == znak) {
                counter++;
            }
        }

    }
    if (counter >= 4) {
        return true;
    } else {
        counter = 1;
    }
    //LavoDole
    if (globalstlpec - 1 >= 0 && globalriadok + 1 <= 5 && hraciaPlocha[globalstlpec - 1][globalriadok + 1] == znak) {
        counter++;
        pomocnaRiadok = globalriadok + 1;
        pomocnaStlpec = globalstlpec - 1;
        for (int i = 1; i < 3; ++i) {
            if (pomocnaRiadok + i <= 5 && pomocnaStlpec - i >= 0 &&
                hraciaPlocha[pomocnaStlpec - i][pomocnaRiadok + i] == znak) {
                counter++;
            }
        }

    }

    //PravoHore
    if (globalstlpec + 1 <= 6 && globalriadok - 1 >= 0 && hraciaPlocha[globalstlpec + 1][globalriadok - 1] == znak) {
        counter++;
        pomocnaRiadok = globalriadok - 1;
        pomocnaStlpec = globalstlpec + 1;
        for (int i = 1; i < 3; ++i) {
            if (pomocnaRiadok - i >= 0 && pomocnaStlpec + i <= 6 &&
                hraciaPlocha[pomocnaStlpec + i][pomocnaRiadok - i] == znak) {
                counter++;
            }
        }

    }
    if (counter >= 4) {
        return true;
    } else {
        counter = 1;
    }
    return false;
}

int tah(int stlpec, char hrac, char **hraciaPlocha) {
    for (int riadky = 5; riadky >= 0; riadky--) {
        if (stlpec >= 0 && stlpec + 1 <= 7) {
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

int skore(char hrac, char **hraciaPlocha) {
    int pocet1 = 0;
    int pocet2 = 0;
    int pocet3 = 0;

    char pomocnaPlocha[7][6];
    for (int stlpec = 0; stlpec < 7; ++stlpec) {
        for (int riadok = 0; riadok < 6; ++riadok) {
            pomocnaPlocha[stlpec][riadok] = hraciaPlocha[stlpec][riadok];
        }
    }
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 6; ++j) {
            int counter = 1;
            int pomocnaRiadok = 0;
            int pomocnaStlpec = 0;
            if(pomocnaPlocha[i][j]!=0){
                //Lavo
                hraciaPlocha[i][j] = 0;
                if (i - 1 >= 0 && hraciaPlocha[i - 1][j] == hrac) {
                    counter++;
                    pomocnaStlpec = i - 1;
                    hraciaPlocha[i - 1][j] = 0;
                    for (int x = 1; x < 3; ++x) {
                        if (pomocnaStlpec - x >= 0 && hraciaPlocha[pomocnaStlpec - x][j] == hrac) {
                            hraciaPlocha[pomocnaStlpec - x][j] = 0;
                            counter++;
                        }
                    }
                }
                //Pravo
                if (i + 1 <= 6 && hraciaPlocha[i + 1][j] == hrac) {
                    hraciaPlocha[i][j] = 0;
                    counter++;
                    pomocnaStlpec = i + 1;
                    hraciaPlocha[i + 1][j] = 0;
                    for (int x = 1; x < 3; ++x) {
                        if (pomocnaStlpec + x <= 6 && hraciaPlocha[pomocnaStlpec + x][j] == hrac) {
                            hraciaPlocha[pomocnaStlpec + x][j] = 0;
                            counter++;
                        }
                    }
                }
                switch (counter){
                    case 1: pocet1++; break;
                    case 2: pocet2++; break;
                    case 3: pocet3++; break;
                    default: break;
                }
                counter = 1;

                //Hore
                if (j - 1 >= 0 && hraciaPlocha[i][j - 1] == hrac) {
                    counter++;
                    pomocnaRiadok = j - 1;
                    hraciaPlocha[i][j - 1] = 0;
                    for (int x = 1; x < 3; ++x) {
                        if (pomocnaRiadok - x >= 0 && hraciaPlocha[i][pomocnaRiadok - x] == hrac) {
                            hraciaPlocha[i][j - x] = 0;
                            counter++;
                        }
                    }
                }
                //Dole
                if (j + 1 <= 5 && hraciaPlocha[i][j + 1] == hrac) {
                    counter++;
                    pomocnaRiadok = j + 1;
                    hraciaPlocha[i][j + 1] = 0;
                    for (int x = 1; x < 3; ++x) {
                        if (pomocnaRiadok + x <= 5 && hraciaPlocha[i][pomocnaRiadok + x] == hrac) {
                            hraciaPlocha[i][j + x] = 0;
                            counter++;
                        }
                    }

                }
                switch (counter){
                    case 1: pocet1++; break;
                    case 2: pocet2++; break;
                    case 3: pocet3++; break;
                    default: break;
                }
                counter = 1;

                if (i - 1 >= 0 && j - 1 >= 0 && hraciaPlocha[i - 1][j - 1] == hrac) {
                    counter++;
                    pomocnaRiadok = i - 1;
                    pomocnaStlpec = j - 1;
                    hraciaPlocha[i  - 1][j - 1] = 0;
                    for (int x = 1; x < 3; ++x) {
                        if (pomocnaRiadok - x >= 0 && pomocnaStlpec - x >= 0 &&
                            hraciaPlocha[pomocnaStlpec - x][pomocnaRiadok - x] == hrac) {
                            hraciaPlocha[i - x][j - x] = 0;
                            counter++;
                        }
                    }
                }
                //PravoDole
                if (i + 1 <= 6 && j + 1 <= 5 && hraciaPlocha[i + 1][j + 1] == hrac) {
                    counter++;
                    pomocnaRiadok = i + 1;
                    pomocnaStlpec = j + 1;
                    hraciaPlocha[i + 1][j + 1] = 0;
                    for (int x = 1; x < 3; ++x) {
                        if (pomocnaRiadok + x <= 5 && pomocnaStlpec + x <= 6 &&
                            hraciaPlocha[pomocnaStlpec + x][pomocnaRiadok + x] == hrac) {
                            hraciaPlocha[i + x][j + x] = 0;
                            counter++;
                        }
                    }

                }
                switch (counter){
                    case 1: pocet1++; break;
                    case 2: pocet2++; break;
                    case 3: pocet3++; break;
                    default: break;
                }
                counter = 1;

                //LavoDole
                if (i - 1 >= 0 && j + 1 <= 5 && hraciaPlocha[i - 1][j + 1] == hrac) {
                    counter++;
                    pomocnaRiadok = j + 1;
                    pomocnaStlpec = i - 1;
                    hraciaPlocha[i - 1][j + 1] = 0;
                    for (int x = 1; x < 3; ++x) {
                        if (pomocnaRiadok + x <= 5 && pomocnaStlpec - x >= 0 &&
                            hraciaPlocha[pomocnaStlpec - x][pomocnaRiadok + x] == hrac) {
                            hraciaPlocha[i - x][j + x] = 0;
                            counter++;
                        }
                    }

                }

                //PravoHore
                if (i + 1 <= 6 && j - 1 >= 0 && hraciaPlocha[i + 1][j - 1] == hrac) {
                    counter++;
                    pomocnaRiadok = j - 1;
                    pomocnaStlpec = i + 1;
                    hraciaPlocha[i + 1][j - 1] = 0;
                    for (int x = 1; x < 3; ++x) {
                        if (pomocnaRiadok - x >= 0 && pomocnaStlpec + x <= 6 &&
                            hraciaPlocha[pomocnaStlpec + x][pomocnaRiadok - x] == hrac) {
                            hraciaPlocha[i + x][j - x] = 0;
                            counter++;
                        }
                    }

                }
                switch (counter){
                    case 1: pocet1++; break;
                    case 2: pocet2++; break;
                    case 3: pocet3++; break;
                    default: break;
                }
            }
        }
    }
    int vysledok = 1 * pocet1 + 4 * pocet2 + 6 * pocet3;
    return vysledok;
}

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
