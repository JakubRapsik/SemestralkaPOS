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


void *klient(void *data) {
    DATA *d = data;
    int hra = 0;
    while (hra == 0) {
        while (koniectahu_klienta) {
            //Caka na signal od servera ze je dalsi tah
        }
        n = read(newsockfd, buffer, 255);
        hra.vypis;
    }


    hra = 1;
    //sigranlizovat ze je koniec tahu klienta
}

void *server(void *data) {
    DATA *d = data;
    int hra = 0;
    while (hra == 0) {
        while (koniectahu_servera) {
            //Caka na signal od klienta ze je na tahu
        }
        printf("Please enter a message: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);

        hra = 1;

        //sigranlizovat koniec tahu
    }
}

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