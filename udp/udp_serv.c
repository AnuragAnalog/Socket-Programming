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
void getinfo(int sockfd);
void strrev(char *str, int len);

/********* MAIN STARTS HERE *********/
int main(int argc, char **argv)
{
    int 		sockfd;
    char 		buff[MAXLEN];
    struct 		sockaddr_in serverAddress, clientAddress;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(errno);
    }

    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("Socket Bind failed");
        exit(errno);
    }

    while (INFINITE)
    {
        getinfo(sockfd);
    }

    exit(0);
}

/********* FUNCTION DEFINITIONS *********/
void getinfo(int sockfd)
{
    int len, n;
    char buff[MAXLEN];
    struct sockaddr_in clientAddress;

    memset(&clientAddress, 0, sizeof(clientAddress));

    len = sizeof(clientAddress);

    n = recvfrom(sockfd, (char *)buff, MAXLEN, MSG_WAITALL, (struct sockaddr *)&clientAddress, &len);
    buff[n] = '\0';
    printf("[Client]: %s\n", buff);
    strrev(buff);
    printf("[Server]: %s\n", buff);
    sendto(sockfd, (const char *)buff, strlen(buff), MSG_CONFIRM, (const struct sockaddr *)&clientAddress, len);

    return;
}

void strrev(char *str, int len)
{
    int 		i, j;
    char 		temp;
    for (i = 0, j = len -1; i < j; ++i, --j)
	{
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }

	return ;
}