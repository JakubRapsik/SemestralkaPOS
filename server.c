#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "hra.h"


typedef struct data {
    char **hraciaPlocha;
    int *newsockfd;
    int *skoreKlient;
    int *skoreServer;
    int *koniecTahov;
    int *hra;
    int *vyherca;
    pthread_mutex_t *mutex;
    pthread_cond_t *aktualizovaneSkore;
    pthread_cond_t *koniecTahu;
} DATA;


void *priebehHry(void *data) {
    DATA *d = data;
    int riadok = 0;
    int stlpec = 0;
    int counter = 0;
     char pomocnastlpec;
    char pomocnariadok;
    char buffer[256];
    pthread_mutex_lock(d->mutex);
    while (*d->hra == 0) {
        while (*d->koniecTahov == 1) {
            pthread_cond_wait(d->aktualizovaneSkore, d->mutex);
        }
        pthread_mutex_unlock(d->mutex);
        int error = -1;
        bzero(buffer, 256);
        read(*d->newsockfd, buffer, 255);
        stlpec = atoi(buffer);
        stlpec--;
        pthread_mutex_lock(d->mutex);
        riadok = tah(stlpec, 'X', d->hraciaPlocha);
        pthread_mutex_unlock(d->mutex);
        if (riadok == -1) {
            error = 1;
        } else {
            error = 0;
        }
        while (error != 0) {
            bzero(buffer, 256);
            strcpy(buffer, "Zadaj nove cislo\n");
            write(*d->newsockfd, buffer, 255);
            bzero(buffer, 256);
            read(*d->newsockfd, buffer, 255);
            stlpec = atoi(buffer);
            stlpec--;
            pthread_mutex_lock(d->mutex);
            riadok = tah(stlpec, 'X', d->hraciaPlocha);
            pthread_mutex_unlock(d->mutex);
            if (riadok != -1) {
                error = 0;
            }
        }
//      vypis(d->hraciaPlocha,*d->newsockfd);
        pomocnastlpec = stlpec;
        pomocnariadok = riadok;
        bzero(buffer, 256);
        buffer[0] = pomocnastlpec;
        buffer[1] = pomocnariadok;
        buffer[2] = 'X';
        write(*d->newsockfd, buffer, 255);
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                printf("%c ", *(*(d->hraciaPlocha + j) + i));
            }
            printf("\n");
        }
        printf("\n------------------------------------\n");

        if (kontrolaVyhry(d->hraciaPlocha, stlpec, riadok)) {
            *d->vyherca = 0;
            *d->hra = 1;
        }
        if (*d->hra == 0) {
            pthread_mutex_unlock(d->mutex);
            printf("Zadaj cislo stlpca\n");
            bzero(buffer, 256);
            fgets(buffer, 255, stdin);
            stlpec = atoi(buffer);
            stlpec--;
            pthread_mutex_lock(d->mutex);
            riadok = tah(stlpec, 'Y', d->hraciaPlocha);
            pthread_mutex_unlock(d->mutex);
            if (riadok == -1) {
                error = 1;
            } else {
                error = 0;
                counter++;
            }
            while (error != 0) {
                printf("Zadaj ine cislo \n");
                bzero(buffer, 256);
                fgets(buffer, 255, stdin);
                stlpec = atoi(buffer);
                stlpec--;
                pthread_mutex_lock(d->mutex);
                riadok = tah(stlpec, 'Y', d->hraciaPlocha);
                pthread_mutex_unlock(d->mutex);
                if (riadok != -1) {
                    error = 0;
                    counter++;
                }
            }
//          vypis(d->hraciaPlocha,*d->newsockfd);
            pomocnastlpec = stlpec;
            pomocnariadok = riadok;
            bzero(buffer, 256);
            buffer[0] = pomocnastlpec;
            buffer[1] = pomocnariadok;
            buffer[2] = 'Y';
            write(*d->newsockfd, buffer, 255);
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 7; j++) {
                    printf("%c ", *(*(d->hraciaPlocha + j) + i));
                }
                printf("\n");

            }
            printf("\n------------------------------------\n");
            pthread_mutex_lock(d->mutex);
            *d->koniecTahov = *d->koniecTahov + 1;
            if (kontrolaVyhry(d->hraciaPlocha, stlpec, riadok)) {
                *d->vyherca = 1;
                *d->hra = 1;
            }
            if (counter == 21) {
                *d->hra = 2;
            }
        }
        *d->koniecTahov = 1;
        pthread_cond_signal(d->koniecTahu);
    }
    pthread_mutex_unlock(d->mutex);
    //Pridane prinf na vyhodnotenie
}

//Kory hrac dal viac zenotov vedla seba
void *skoreHry(void *data) {
    DATA *d = data;
    int s1 = 0;
    int s2 = 0;
    while (*d->hra == 0) {
        pthread_mutex_lock(d->mutex);
        while (*d->koniecTahov == 0) {

            pthread_cond_wait(d->koniecTahu, d->mutex);
        }
        *d->skoreKlient = skore('X', d->hraciaPlocha);
        *d->skoreServer = skore('Y', d->hraciaPlocha);
        pthread_mutex_unlock(d->mutex);
        printf("Skore uprava\n");
        s1 = *d->skoreKlient;
        s2 = *d->skoreServer;
        printf("x skore %d\n",s1);
        printf("y skore %d\n",s2);
        pthread_mutex_lock(d->mutex);
        *d->koniecTahov = 0;
        pthread_mutex_unlock(d->mutex);
        pthread_cond_signal(d->aktualizovaneSkore);
    }
}



//|00000000|
//|00000000|
//|00000000|
//|00000000|
//|00000000|


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage %s port\n", argv[0]);
        return 1;
    }

    // dynamically create an array of pointers of size `m`
    char **arr = (char **) malloc(7 * sizeof(char *));

    // dynamically allocate memory of size `n` for each row
    for (int r = 0; r < 7; r++) {
        arr[r] = (char *) malloc(6 * sizeof(char));
    }

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 6; j++) {
            arr[i][j] = 'O';
        }
    }


    int sockfd, newsockfd;
    int skoreKlient = 0;
    int skoreServer = 0;
    int koniectahov = 0;
    int hra = 0;
    int vyherca = -1;
    socklen_t cli_len;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    char buffer[256];


    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error binding socket address");
        return 2;
    }

    listen(sockfd, 5);
    cli_len = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
    if (newsockfd < 0) {
        perror("ERROR on accept");
        return 3;
    }
    //Koniec pripojovania

    pthread_t priebehhry, skore;

    pthread_mutex_t mutex;
    pthread_cond_t aktualneSkore, koniecTahov;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&aktualneSkore, NULL);
    pthread_cond_init(&koniecTahov, NULL);

    DATA dataSpol = {arr, &newsockfd, &skoreKlient, &skoreServer, &koniectahov, &hra, &vyherca, &mutex,
                     &aktualneSkore,
                     &koniecTahov};

    pthread_create(&priebehhry, NULL, &priebehHry, &dataSpol);
    pthread_create(&skore, NULL, &skoreHry, &dataSpol);

    pthread_join(priebehhry, NULL);
    pthread_join(skore, NULL);

    if (*dataSpol.hra == 1) {
        const char *msg;
        const int *msg2;
        if (*dataSpol.vyherca == 0) {
            msg = "Vyhral Hrac X pretoze ma styri rovnake v rade \n";
            write(newsockfd, msg, strlen(msg) + 1);
            msg = "Jeho skore bolo: ";
            write(newsockfd, msg, strlen(msg) + 1);
            msg2 = dataSpol.skoreKlient;
            write(newsockfd, msg2, 3);
            printf("Vyhral Hrac X pretoze ma styri rovnake v rade \n");
            printf("Jeho skore bolo %d\n", *dataSpol.skoreKlient);
        }
        if (*dataSpol.vyherca == 1) {
            msg = "Vyhral Hrac Y pretoze ma styri rovnake v rade \n";
            write(newsockfd, msg, strlen(msg) + 1);
            msg = "Jeho skore bolo: ";
            write(newsockfd, msg, strlen(msg) + 1);
            printf("Vyhral Hrac Y pretoze ma styri rovnake v rade\n");
            printf("Jeho skore bolo %d\n", *dataSpol.skoreServer);
        }
        msg = "koniec";
        write(newsockfd, msg, strlen(msg) + 1);
    }
    if (*dataSpol.hra == 2) {
        printf("Remiza hra bola rozhodnuta na body\n");
        if (*dataSpol.skoreServer > *dataSpol.skoreKlient) {
            printf("Vyhral Hrac Y na body\n");
            printf("Jeho skore bolo %d\n", *dataSpol.skoreServer);
        } else {
            printf("Vyhral Hrac X na body\n");
            printf("Jeho skore bolo %d\n", *dataSpol.skoreKlient);
        }
    }
    //Vytvorenie thredov a ich joinovanie
    //create a join
    //Finalny vypis

//    int hrac = 0;
//    int a = 0;
//    while (hrac == 0) {
//        bzero(buffer, 256);
//        n = read(newsockfd, buffer, 255);
//        if (n < 0) {
//            perror("Error reading from socket");
//            return 4;
//        }
//
//        printf("Here is the message: %s\n", buffer);
//        const char *msg;
//        if (a < 1) {
//            msg = "ahoj";
//
//        } else if (a == 1) {
//            msg = "viac ako 1";
//        } else {
//            msg = "koniec";
//        }
//        a++;
//        n = write(newsockfd, msg, strlen(msg) + 1);
//        if (n < 0) {
//            perror("Error writing to socket");
//            return 5;
//        }
//        if (a == 5) {
//            hrac = 1;
//        }
//    }

    for (int i = 0; i < 7; i++) {
        free(arr[i]);
    }
    free(arr);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&koniecTahov);
    pthread_cond_destroy(&aktualneSkore);
    close(newsockfd);
    close(sockfd);


    return 0;
}