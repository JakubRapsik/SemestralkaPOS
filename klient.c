#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

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

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        return 1;
    }

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
    int hra = 0;
    char stlpec;
    char riadok;
    char hrac;
    while (1) {
        if (strcmp(koniec, buffer) == 0) {
            hra = 1;
            printf("tu");
            break;
        }
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

    }

    close(sockfd);
    return 0;
}
