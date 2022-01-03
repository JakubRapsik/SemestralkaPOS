#include "hra.h"


bool kontrolaVyhry(char **hraciaPlocha, int globalstlpec, int globalriadok) {
    int counter = 1;
    int pomocnaStlpec;
    int pomocnaRiadok;
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

//int skore(char hrac, char **hraciaPlocha) {
//    int pocet1 = 0;
//    int pocet2 = 0;
//    int pocet3 = 0;
//
//    char pomocnaPlocha[7][6];
//    for (int stlpec = 0; stlpec < 7; ++stlpec) {
//        for (int riadok = 0; riadok < 6; ++riadok) {
//            pomocnaPlocha[stlpec][riadok] = hraciaPlocha[stlpec][riadok];
//        }
//    }
//    for (int i = 0; i < 7; ++i) {
//        for (int j = 0; j < 6; ++j) {
//            int pomocnaRiadok = 0;
//            int pomocnaStlpec = 0;
//            if(pomocnaPlocha[i][j]==hrac){
//                int counter = 1;
//                pomocnaPlocha[i][j] = 'O';
//                //Lavo
//                if (i - 1 >= 0 && pomocnaPlocha[i - 1][j] == hrac) {
//                    counter++;
//                    pomocnaStlpec = i - 1;
//                    pomocnaPlocha[i - 1][j] = 'O';
//                    for (int x = 1; x < 3; ++x) {
//                        if (pomocnaStlpec - x >= 0 && pomocnaPlocha[pomocnaStlpec - x][j] == hrac) {
//                            pomocnaPlocha[pomocnaStlpec - x][j] = 'O';
//                            counter++;
//                        }
//                    }
//                }
//                //Pravo
//                if (i + 1 <= 6 && pomocnaPlocha[i + 1][j] == hrac) {
//                    counter++;
//                    pomocnaStlpec = i + 1;
//                    pomocnaPlocha[i + 1][j] = 'O';
//                    for (int x = 1; x < 3; ++x) {
//                        if (pomocnaStlpec + x <= 6 && pomocnaPlocha[pomocnaStlpec + x][j] == hrac) {
//                            pomocnaPlocha[pomocnaStlpec + x][j] = 'O';
//                            counter++;
//                        }
//                    }
//                }
//                if (counter == 1){pocet1++; continue;}
//                if (counter == 2){pocet2++; continue;}
//                if (counter == 3){pocet3++; continue;}
//                counter = 1;
//
//                //Hore
//                if (j - 1 >= 0 && pomocnaPlocha[i][j - 1] == hrac) {
//                    counter++;
//                    pomocnaRiadok = j - 1;
//                    pomocnaPlocha[i][j - 1] = 'O';
//                    for (int x = 1; x < 3; ++x) {
//                        if (pomocnaRiadok - x >= 0 && pomocnaPlocha[i][pomocnaRiadok - x] == hrac) {
//                            pomocnaPlocha[i][j - x] = 'O';
//                            counter++;
//                        }
//                    }
//                }
//                //Dole
//                if (j + 1 <= 5 && pomocnaPlocha[i][j + 1] == hrac) {
//                    counter++;
//                    pomocnaRiadok = j + 1;
//                    pomocnaPlocha[i][j + 1] = 'O';
//                    for (int x = 1; x < 3; ++x) {
//                        if (pomocnaRiadok + x <= 5 && pomocnaPlocha[i][pomocnaRiadok + x] == hrac) {
//                            pomocnaPlocha[i][j + x] = 'O';
//                            counter++;
//                        }
//                    }
//
//                }
//                if (counter == 1){pocet1++; continue;}
//                if (counter == 2){pocet2++; continue;}
//                if (counter == 3){pocet3++; continue;}
//                counter = 1;
//
//                if (i - 1 >= 0 && j - 1 >= 0 && pomocnaPlocha[i - 1][j - 1] == hrac) {
//                    counter++;
//                    pomocnaRiadok = i - 1;
//                    pomocnaStlpec = j - 1;
//                    pomocnaPlocha[i  - 1][j - 1] = 'O';
//                    for (int x = 1; x < 3; ++x) {
//                        if (pomocnaRiadok - x >= 0 && pomocnaStlpec - x >= 0 &&
//                            pomocnaPlocha[pomocnaStlpec - x][pomocnaRiadok - x] == hrac) {
//                            pomocnaPlocha[i - x][j - x] = 'O';
//                            counter++;
//                        }
//                    }
//                }
//                //PravoDole
//                if (i + 1 <= 6 && j + 1 <= 5 && pomocnaPlocha[i + 1][j + 1] == hrac) {
//                    counter++;
//                    pomocnaRiadok = i + 1;
//                    pomocnaStlpec = j + 1;
//                    pomocnaPlocha[i + 1][j + 1] = 'O';
//                    for (int x = 1; x < 3; ++x) {
//                        if (pomocnaRiadok + x <= 5 && pomocnaStlpec + x <= 6 &&
//                            pomocnaPlocha[pomocnaStlpec + x][pomocnaRiadok + x] == hrac) {
//                            pomocnaPlocha[i + x][j + x] = 'O';
//                            counter++;
//                        }
//                    }
//
//                }
//                if (counter == 1){pocet1++; continue;}
//                if (counter == 2){pocet2++; continue;}
//                if (counter == 3){pocet3++; continue;}
//                counter = 1;
//
//                //LavoDole
//                if (i - 1 >= 0 && j + 1 <= 5 && pomocnaPlocha[i - 1][j + 1] == hrac) {
//                    counter++;
//                    pomocnaRiadok = j + 1;
//                    pomocnaStlpec = i - 1;
//                    pomocnaPlocha[i - 1][j + 1] = 'O';
//                    for (int x = 1; x < 3; ++x) {
//                        if (pomocnaRiadok + x <= 5 && pomocnaStlpec - x >= 0 &&
//                            pomocnaPlocha[pomocnaStlpec - x][pomocnaRiadok + x] == hrac) {
//                            pomocnaPlocha[i - x][j + x] = 'O';
//                            counter++;
//                        }
//                    }
//
//                }
//
//                //PravoHore
//                if (i + 1 <= 6 && j - 1 >= 0 && pomocnaPlocha[i + 1][j - 1] == hrac) {
//                    counter++;
//                    pomocnaRiadok = j - 1;
//                    pomocnaStlpec = i + 1;
//                    pomocnaPlocha[i + 1][j - 1] = 'O';
//                    for (int x = 1; x < 3; ++x) {
//                        if (pomocnaRiadok - x >= 0 && pomocnaStlpec + x <= 6 &&
//                            pomocnaPlocha[pomocnaStlpec + x][pomocnaRiadok - x] == hrac) {
//                            pomocnaPlocha[i + x][j - x] = 'O';
//                            counter++;
//                        }
//                    }
//
//                }
//                if (counter == 1){pocet1++; continue;}
//                if (counter == 2){pocet2++; continue;}
//                if (counter == 3){pocet3++; continue;}
//            }
//        }
//    }
//    int vysledok = 1 * pocet1 + 4 * pocet2 + 6 * pocet3;
//    return vysledok;
//}

int skore(char hrac, char **hraciaPlocha) {
    int pocet1 = 0;
    int pocet2 = 0;
    int pocet3 = 0;
    int pocet4 = 0;
    int pocet5 = 0;
    int pocet6 = 0;
    int pocet7 = 0;

    int pomocnaRiadok;
    int pomocnaStlpec;
    int pocetP;
    int pocetD;
    int pocetPD;
    char pomocnaPlocha[7][6];
    for (int stlpec = 0; stlpec < 7; ++stlpec) {
        for (int riadok = 0; riadok < 6; ++riadok) {
            pomocnaPlocha[stlpec][riadok] = hraciaPlocha[stlpec][riadok];
        }
    }
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 6; ++j) {
            pocetP = 0;
            pocetD = 0;
            pocetPD = 0;
            if(pomocnaPlocha[i][j]==hrac){
                pomocnaPlocha[i][j] = 'O';
                //Pravo
                if (i + 1 <= 6 && pomocnaPlocha[i + 1][j] == hrac) {
                    pomocnaStlpec = i + 1;
                    pocetP++;
                    for (int x = 1; x < 6; ++x) {
                        if (pomocnaStlpec + x <= 6 && pomocnaPlocha[pomocnaStlpec + x][j] == 'O'){
                            break;
                        }

                        if (pomocnaStlpec + x <= 6 && pomocnaPlocha[pomocnaStlpec + x][j] == hrac) {
                            pocetP++;
                        }

                    }
                }

                //Dole
                if (j + 1 <= 5 && pomocnaPlocha[i][j + 1] == hrac) {
                    pocetD++;
                    pomocnaRiadok = j + 1;
                    for (int x = 1; x < 6; ++x) {
                        if  (pomocnaRiadok + x <= 5 && pomocnaPlocha[i][pomocnaRiadok + x] == 'O'){
                            break;
                        }

                        if (pomocnaRiadok + x <= 5 && pomocnaPlocha[i][pomocnaRiadok + x] == hrac) {
                            pocetD++;
                        }
                    }

                }

                //PravoDole
                if (i + 1 <= 6 && j + 1 <= 5 && pomocnaPlocha[i + 1][j + 1] == hrac) {
                    pocetPD++;
                    pomocnaRiadok = i + 1;
                    pomocnaStlpec = j + 1;
                    for (int x = 1; x < 6; ++x) {
                        if(pomocnaRiadok + x <= 5 && pomocnaStlpec + x <= 6 &&
                           pomocnaPlocha[pomocnaStlpec + x][pomocnaRiadok + x] == 'O'){
                            break;
                        }

                        if (pomocnaRiadok + x <= 5 && pomocnaStlpec + x <= 6 &&
                            pomocnaPlocha[pomocnaStlpec + x][pomocnaRiadok + x] == hrac) {
                            pocetPD++;
                        }
                    }

                }

                if(pocetD == pocetPD && pocetD == pocetP){
                    for (int x = 1; x <= pocetD; ++x) {
                        pomocnaPlocha[i][j + x] = 'O';
                    }
                    switch (pocetD) {
                        case 0: pocet1++;break;
                        case 1: pocet2++;break;
                        case 2: pocet3++;break;
                        case 3: pocet4++;break;
                        case 4: pocet5++;break;
                        case 5: pocet6++;break;
                        case 6: pocet7++;break;
                        default: ;
                    }
                }

                if(pocetD > pocetPD && pocetD > pocetP){
                    for (int x = 1; x <= pocetD; ++x) {
                        pomocnaPlocha[i][j + x] = 'O';
                    }
                    switch (pocetD) {
                        case 0: pocet1++;break;
                        case 1: pocet2++;break;
                        case 2: pocet3++;break;
                        case 3: pocet4++;break;
                        case 4: pocet5++;break;
                        case 5: pocet6++;break;
                        case 6: pocet7++;break;
                        default: ;
                    }
                }
                if(pocetPD > pocetD && pocetPD > pocetP){
                    for (int x = 1; x <= pocetPD; ++x) {
                        pomocnaPlocha[i + x][j + x] = 'O';
                    }
                    switch (pocetPD) {
                        case 0: pocet1++;break;
                        case 1: pocet2++;break;
                        case 2: pocet3++;break;
                        case 3: pocet4++;break;
                        case 4: pocet5++;break;
                        case 5: pocet6++;break;
                        case 6: pocet7++;break;
                        default: ;
                    }

                }
                if(pocetP > pocetPD && pocetP > pocetD){
                    for (int x = 1; x <= pocetP; ++x) {
                        pomocnaPlocha[i + x][j] = 'O';
                    }
                    switch (pocetP) {
                        case 0: pocet1++;break;
                        case 1: pocet2++;break;
                        case 2: pocet3++;break;
                        case 3: pocet4++;break;
                        case 4: pocet5++;break;
                        case 5: pocet6++;break;
                        case 6: pocet7++;break;
                        default: ;
                    }
                }

                if(pocetP > pocetPD && pocetP == pocetD){
                    for (int x = 1; x <= pocetP; ++x) {
                        pomocnaPlocha[i + x][j] = 'O';
                    }
                    switch (pocetP) {
                        case 0: pocet1++;break;
                        case 1: pocet2++;break;
                        case 2: pocet3++;break;
                        case 3: pocet4++;break;
                        case 4: pocet5++;break;
                        case 5: pocet6++;break;
                        case 6: pocet7++;break;
                        default: ;
                    }
                }
                if(pocetP == pocetPD && pocetP > pocetD){
                    for (int x = 1; x <= pocetP; ++x) {
                        pomocnaPlocha[i + x][j] = 'O';
                    }
                    switch (pocetP) {
                        case 0: pocet1++;break;
                        case 1: pocet2++;break;
                        case 2: pocet3++;break;
                        case 3: pocet4++;break;
                        case 4: pocet5++;break;
                        case 5: pocet6++;break;
                        case 6: pocet7++;break;
                        default: ;
                    }
                }



                if(pocetD > pocetPD && pocetD == pocetP){
                    for (int x = 1; x <= pocetD; ++x) {
                        pomocnaPlocha[i][j + x] = 'O';
                    }
                    switch (pocetD) {
                        case 0: pocet1++;break;
                        case 1: pocet2++;break;
                        case 2: pocet3++;break;
                        case 3: pocet4++;break;
                        case 4: pocet5++;break;
                        case 5: pocet6++;break;
                        case 6: pocet7++;break;
                        default: ;
                    }
                }
                if(pocetD == pocetPD && pocetD > pocetP){
                    for (int x = 1; x <= pocetD; ++x) {
                        pomocnaPlocha[i][j + x] = 'O';
                    }
                    switch (pocetD) {
                        case 0: pocet1++;break;
                        case 1: pocet2++;break;
                        case 2: pocet3++;break;
                        case 3: pocet4++;break;
                        case 4: pocet5++;break;
                        case 5: pocet6++;break;
                        case 6: pocet7++;break;
                        default: ;
                    }
                }


                if(pocetPD > pocetD && pocetPD == pocetP){
                    for (int x = 1; x <= pocetPD; ++x) {
                        pomocnaPlocha[i + x][j + x] = 'O';
                    }
                    switch (pocetPD) {
                        case 0: pocet1++;break;
                        case 1: pocet2++;break;
                        case 2: pocet3++;break;
                        case 3: pocet4++;break;
                        case 4: pocet5++;break;
                        case 5: pocet6++;break;
                        case 6: pocet7++;break;
                        default: ;
                    }
                }
                if(pocetPD == pocetD && pocetPD > pocetP){
                    for (int x = 1; x <= pocetPD; ++x) {
                        pomocnaPlocha[i + x][j + x] = 'O';
                    }
                    switch (pocetPD) {
                        case 0: pocet1++;break;
                        case 1: pocet2++;break;
                        case 2: pocet3++;break;
                        case 3: pocet4++;break;
                        case 4: pocet5++;break;
                        case 5: pocet6++;break;
                        case 6: pocet7++;break;
                        default: ;
                    }
                }
            }
        }
    }
    int vysledok = 1 * pocet1 + 4 * pocet2 + 6 * pocet3 +
            8 * pocet4 + 10 * pocet5 + 12 * pocet6 + 14 * pocet7;
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
