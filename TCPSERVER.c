#include <stdio.h>      // for printf
#include <stdlib.h>     // for exit() (optional)
#include <string.h>     // for memset (optional)
#include <unistd.h>     // for close
#include <arpa/inet.h>  // for sockaddr_in, htons, inet_ntoa
#include <sys/socket.h> // for socket, bind, listen, accept, send, recv

int main() {
    int sockfd, newsock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Error binding socket");
        return 1;
    }

    if (listen(sockfd, 5) < 0) {
        perror("Error listening on socket");
        return 1;
    }

    printf("Waiting for connection...\n");

    newsock = accept(sockfd, (struct sockaddr *)&client, &len);
    if (newsock < 0) {
        perror("Error accepting connection");
        return 1;
    }

    read(newsock, buffer, sizeof(buffer));
    printf("Message: %s\n", buffer);

    send(newsock, "Hello from server", 17, 0);
    close(newsock);
    close(sockfd);

    return 0;
}

