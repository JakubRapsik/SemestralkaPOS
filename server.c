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

void vypis(char stlpec, char riadok, char hrac, char **hraciaPlocha, int socket) {

    char buffer[256];
    bzero(buffer, 256);
    buffer[0] = stlpec;
    buffer[1] = riadok;
    buffer[2] = hrac;
    write(socket, buffer, 255);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%c ", *(*(hraciaPlocha + j) + i));
        }
        printf("\n");
    }
    printf("------------------------------------\n");
    printf("1 2 3 4 5 6 7 \n");
    printf("------------------------------------\n");
}

void *priebehHry(void *data) {
    DATA *d = data;
    int riadok;
    int stlpec;
    int counter = 0;
    int s1;
    int s2;
    int n;
    char pomocnastlpec;
    char pomocnariadok;
    char buffer[256];
    pthread_mutex_lock(d->mutex);
    while (*d->hra == 0) {
        while (*d->koniecTahov == 1) {
            pthread_cond_wait(d->aktualizovaneSkore, d->mutex);
            pthread_mutex_unlock(d->mutex);
            s1 = *d->skoreKlient;
            s2 = *d->skoreServer;
            printf("x skore %d\n", s1);
            printf("y skore %d", s2);
            printf("\n------------------------------------\n");
            bzero(buffer, 256);
            buffer[0] = s1;
            buffer[1] = s2;
            write(*d->newsockfd, buffer, 255);
            pthread_mutex_lock(d->mutex);
        }
        pthread_mutex_unlock(d->mutex);
        int error;
        bzero(buffer, 256);
        n = read(*d->newsockfd, buffer, 255);
        if (n <= 0) {
            printf("Hrac sa odpojil hra skoncila");
            *d->hra = 5;
        } else {
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
                strcpy(buffer, "Zadaj nove cislo: ");
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
            pomocnastlpec = stlpec;
            pomocnariadok = riadok;
            pthread_mutex_lock(d->mutex);
            vypis(pomocnastlpec, pomocnariadok, 'X', d->hraciaPlocha, *d->newsockfd);
            if (kontrolaVyhry(d->hraciaPlocha, stlpec, riadok)) {
                pthread_mutex_unlock(d->mutex);
                *d->vyherca = 0;
                *d->hra = 1;
                if (recv(*d->newsockfd, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT) == 0) {
                    printf("Hrac sa odpojil hra skoncila");
                    *d->hra = 5;
                } else {
                    bzero(buffer, 256);
                    strcpy(buffer, "koniec");
                    write(*d->newsockfd, buffer, 255);
                }
            } else {
                pthread_mutex_unlock(d->mutex);
                if (recv(*d->newsockfd, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT) == 0) {
                    printf("Hrac sa odpojil hra skoncila");
                    *d->hra = 5;
                } else {
                    bzero(buffer, 256);
                    strcpy(buffer, "pokracuje");
                    write(*d->newsockfd, buffer, 255);
                }
            }
            if (*d->hra == 0) {
                printf("Zadaj cislo stlpca: ");
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
                    printf("Zadaj ine cislo: ");
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
                pomocnastlpec = stlpec;
                pomocnariadok = riadok;
                pthread_mutex_lock(d->mutex);
                vypis(pomocnastlpec, pomocnariadok, 'Y', d->hraciaPlocha, *d->newsockfd);
                if (kontrolaVyhry(d->hraciaPlocha, stlpec, riadok)) {
                    pthread_mutex_unlock(d->mutex);
                    *d->vyherca = 1;
                    *d->hra = 1;
                    if (recv(*d->newsockfd, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT) == 0) {
                        printf("Hrac sa odpojil hra skoncila");
                        *d->hra = 5;
                    } else {
                        bzero(buffer, 256);
                        strcpy(buffer, "koniec");
                        write(*d->newsockfd, buffer, 255);
                    }
                } else if (counter == 21) {
                    pthread_mutex_unlock(d->mutex);
                    *d->hra = 2;
                    if (recv(*d->newsockfd, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT) == 0) {
                        printf("Hrac sa odpojil hra skoncila");
                        *d->hra = 5;
                    } else {
                        bzero(buffer, 256);
                        strcpy(buffer, "koniec");
                        write(*d->newsockfd, buffer, 255);
                    }
                } else {
                    pthread_mutex_unlock(d->mutex);
                    if (recv(*d->newsockfd, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT) == 0) {
                        printf("Hrac sa odpojil hra skoncila");
                        *d->hra = 5;
                    } else {
                        bzero(buffer, 256);
                        strcpy(buffer, "pokracuje");
                        write(*d->newsockfd, buffer, 255);
                    }
                }
            }

        }
        pthread_mutex_lock(d->mutex);
        *d->koniecTahov = 1;
        pthread_cond_signal(d->koniecTahu);
    }
    pthread_mutex_unlock(d->mutex);
}

void *skoreHry(void *data) {
    DATA *d = data;
    while (*d->hra == 0) {
        pthread_mutex_lock(d->mutex);
        while (*d->koniecTahov == 0) {

            pthread_cond_wait(d->koniecTahu, d->mutex);
        }
        *d->skoreKlient = skore('X', d->hraciaPlocha);
        *d->skoreServer = skore('Y', d->hraciaPlocha);
        *d->koniecTahov = 0;
        pthread_mutex_unlock(d->mutex);
        pthread_cond_signal(d->aktualizovaneSkore);
    }
}

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
        if (*dataSpol.vyherca == 0) {
            bzero(buffer, 256);
            buffer[0] = 'X';
            buffer[1] = *dataSpol.skoreKlient;
            write(newsockfd, buffer, 255);
            printf("Vyhral Hrac X pretoze ma styri rovnake v rade \n");
            printf("Jeho skore bolo %d\n", *dataSpol.skoreKlient);
        }
        if (*dataSpol.vyherca == 1) {
            bzero(buffer, 256);
            buffer[0] = 'Y';
            buffer[1] = *dataSpol.skoreKlient;
            write(newsockfd, buffer, 255);
            printf("Vyhral Hrac Y pretoze ma styri rovnake v rade\n");
            printf("Jeho skore bolo %d\n", *dataSpol.skoreServer);
        }
    }
    if (*dataSpol.hra == 2) {
        bzero(buffer, 256);
        buffer[0] = 'R';
        buffer[1] = *dataSpol.skoreServer;
        buffer[2] = *dataSpol.skoreKlient;
        printf("Remiza hra bola rozhodnuta na body\n");
        if (*dataSpol.skoreServer > *dataSpol.skoreKlient) {
            printf("Vyhral Hrac Y na body\n");
            printf("Jeho skore bolo %d\n", *dataSpol.skoreServer);
        } else {
            printf("Vyhral Hrac X na body\n");
            printf("Jeho skore bolo %d\n", *dataSpol.skoreKlient);
        }
    }
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

