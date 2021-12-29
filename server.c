#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hra.h"


typedef struct data {

} DATA;


//void *priebehHry(void *data) {
//    DATA *d = data;
//    int hra = 0;
//    while (hra == 0) {
//        while (koniectahu) {
//            //Caka na signal od ze sa skore aktualizovalo
//        }
//
//        int error = -1;
//        n = read(newsockfd, buffer, 255);
//        if (tah(buffer, 'X') == 1) {
//            error = 1;
//        } else {
//            error = 0;
//        }
//        while (error != 0) {
//            const char *msg = "Zadaj nove cislo";
//            n = write(d->newsockfd, msg, strlen(msg) + 1);
//            n = read(newsockfd, buffer, 255);
//            if (tah(buffer, 'X') == 0) {
//                error = 0;
//            }
//        vypis();
//        if(kontrola()) {
//        break;}
//        printf("Zadaj cislo stlpca");
//        bzero(buffer, 256);
//        fgets(buffer, 255, stdin);
//        if (tah(buffer, 'Y') == 1) {
//            error = 1;
//        } else {
//            error = 0;
//        }
//        while (error != 0) {
//            printf("Zadaj ine cislo \n");
////            scanf("%d",buffer);
//            bzero(buffer, 256);
//            fgets(buffer, 255, stdin);
//            if (tah(buffer, 'X') == 0) {
//                error = 0;
//            }
//        }
//          vypis();
//          if(kontrola()) {
//          break;}
//
//        }
//        vypis();
//    }
//
//
//    hra = 1;
//    //sigranlizovat ze je koniec tahu na prepocitanie skore
//}

//Kory hrac dal viac zenotov vedla seba
//void *skore(void *data) {
// DATA *d = data;
// int hra = 0;
//
//
//
//
//
//
//
//
// Signalizovat koniec aktualizacie skore
// }



//|00000000|
//|00000000|
//|00000000|
//|00000000|
//|0YYYXX00|


int main(int argc, char *argv[]) {
    int sockfd, newsockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    char buffer[256];

    if (argc < 2) {
        fprintf(stderr, "usage %s port\n", argv[0]);
        return 1;
    }
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


    //Vytvorenie thredov a ich joinovanie

    int hrac = 0;
    int a = 0;
    while (hrac == 0) {
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);
        if (n < 0) {
            perror("Error reading from socket");
            return 4;
        }

        printf("Here is the message: %s\n", buffer);
        const char *msg;
        if (a < 1) {
            msg = "ahoj";

        } else if (a == 1) {
            msg = "viac ako 1";
        } else {
            msg = "koniec";
        }
        a++;
        n = write(newsockfd, msg, strlen(msg) + 1);
        if (n < 0) {
            perror("Error writing to socket");
            return 5;
        }
        if (a == 5) {
            hrac = 1;
        }
    }

    close(newsockfd);
    close(sockfd);

    return 0;
}