#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        return 1;
    }
    char arr[7][6];

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 6; j++) {
            arr[i][j] = 'O';
        }
    }
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char koniec[] = "koniec";
    char buffer[256];
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "Error, no such host\n");
        return 2;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char *) server->h_addr,
            (char *) &serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(atoi(argv[2]));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 3;
    }

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error connecting to socket");
        return 4;
    }
    char stlpec;
    char riadok;
    char hrac;
    int skore1;
    int skore2;
    while (1) {

        printf("Zadajte cislo stplca kde padne zeton: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);

        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {
            perror("Chyba pri poslati spravy na server");
            return 5;
        }
        int zadane = 0;
        while (zadane != 1) {
            bzero(buffer, 256);
            n = read(sockfd, buffer, 255);
            if (n < 0) {
                perror("Chyba pri prijmani spravi zo servera");
                return 6;
            }
            if (buffer[4] != 0) {
                printf("%s\n", buffer);
                bzero(buffer, 256);
                fgets(buffer, 255, stdin);
                write(sockfd, buffer, strlen(buffer));

            } else {
                stlpec = buffer[0];
                riadok = buffer[1];
                hrac = buffer[2];

                *(*(arr + stlpec) + riadok) = hrac;

                for (int i = 0; i < 6; i++) {
                    for (int j = 0; j < 7; j++) {
                        printf("%c ", *(*(arr + j) + i));
                    }
                    printf("\n");
                }
                zadane = 1;
            }

        }


        printf("\n------------------------------------\n");

        bzero(buffer, 256);
        read(sockfd, buffer, 255);
        if (strcmp(koniec, buffer) == 0) {
            break;
        }

        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0) {
            perror("Chyba pri prijmani spravi zo servera");
            return 6;
        }
        stlpec = buffer[0];
        riadok = buffer[1];
        hrac = buffer[2];

        *(*(arr + stlpec) + riadok) = hrac;

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                printf("%c ", *(*(arr + j) + i));
            }
            printf("\n");
        }
        printf("\n------------------------------------\n");
        //skore

        bzero(buffer, 256);
        read(sockfd, buffer, 255);
        if (strcmp(koniec, buffer) == 0) {
            break;
        }

        bzero(buffer, 256);
        read(sockfd, buffer, 255);
        skore1 = buffer[0];
        skore2 = buffer[1];
        printf("x skore %d\n", skore1);
        printf("y skore %d\n", skore2);

    }
    bzero(buffer, 256);
    read(sockfd, buffer, 255);

    if (buffer[0] == 'X') {
        printf("Vyhral Hrac X pretoze ma styri rovnake v rade \n");
        printf("Jeho skore bolo %d\n", buffer[1]);
    }
    if (buffer[0] == 'Y') {
        printf("Vyhral Hrac Y pretoze ma styri rovnake v rade \n");
        printf("Jeho skore bolo %d\n", buffer[1]);
    }
    if (buffer[0] == 'R') {
        printf("Remiza hra bola rozhodnuta na body\n");
        if (buffer[1] > buffer[2]) {
            printf("Vyhral Hrac Y na body\n");
            printf("Jeho skore bolo %d\n", buffer[1]);
        } else {
            printf("Vyhral Hrac X na body\n");
            printf("Jeho skore bolo %d\n", buffer[2]);
        }
    }

    close(sockfd);
    return 0;
}