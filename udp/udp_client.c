#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/********* DEFINED CONSTANTS *********/
#define PORT 8080
#define MAXLEN 1024
#define INFINITE true

/********* FUNCTION DECLARATIONS *********/
void sendinfo(int sockfd, struct sockaddr_in *serverAddress);

/********* MAIN STARTS HERE *********/
int main(int argc, char **argv)
{
    int 		sockfd;
    struct 		sockaddr_in serverAddress;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(errno);
    }

    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    sendinfo(sockfd, &serverAddress);

    exit(0);
}

/********* FUNCTION DEFINITION *********/
void sendinfo(int sockfd, struct sockaddr_in *serverAddress)
{
    int 		n, len;
    char 	buff[MAXLEN];

    while (INFINITE)
    {
        printf("[Client]: ");
        scanf("%s", buff);
        sendto(sockfd, (const char *)buff, strlen(buff), MSG_CONFIRM, (const struct sockaddr *)serverAddress, sizeof(*serverAddress));

        n = recvfrom(sockfd, (char *)buff, MAXLEN,
                     MSG_WAITALL, (struct sockaddr *)serverAddress,
                     &len);
        buff[n] = '\0';
        printf("[Server]: %s\n", buff);
    }

    close(sockfd);

	return ;
}