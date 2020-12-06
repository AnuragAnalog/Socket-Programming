#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/********* DEFINED CONSTANTS *********/
#define MAX         80
#define IPMAX       16
#define INFINITE    true
#define SA struct   sockaddr

/********* FUNCTION DECLARATIONS ********/
void chat_server(int sockfd);
void print_message(char *message, bool is_error);

/********* MAIN STARTS HERE *********/
int main(int argc, char **argv)
{
    int        sockfd, connfd, len, port;
    struct sockaddr_in  servaddr, cli;

    if (argc != 2)
    {
        fprintf(stderr, "Syntax: %s <port>", argv[0]);
        exit(1);
    }

    port = atoi(argv[1]);

    // Create the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        print_message("[Server]: Socket Cannot be created\n", true);
        exit(2);
    }
    else
    {
        print_message("[Server]: Socket successfully created..\n", false);
    }
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    // Binding the socket to server
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        print_message("[Server]: Socket Binding failed..\n", true);
        exit(3);
    }
    else
    {
        print_message("[Server]: Socket successfully binded..\n", false);
    }
    
    // Server listening
    if ((listen(sockfd, 5)) != 0)
    {
        print_message("[Server]: Listening Failed..\n", true);
        exit(4);
    }
    else
    {
        print_message("[Server]: Server listening..\n", false);
    }
    len = sizeof(cli);

    connfd = accept(sockfd, (SA *)&cli, &len); 
    if (connfd < 0)
    {
        print_message("[Server]: server acccept failed...\n", true); 
        exit(0); 
    } 
    else
    {
        print_message("[Server]: Server acccept the client...\n", false);   
    }

    chat_server(connfd); 
    
    exit(0);
}

/********* FUNCTION DEFINITIONS ********/
void chat_server(int sockfd)
{
    int        i, j;
    char       info[MAX];

    while (INFINITE)
    {
        j = 0;
        bzero(info, MAX);
   
        read(sockfd, info, sizeof(info)); 
        printf("[Client]: %s\n", info);

        if (strncmp("bye", info, 3) == 0)
        {
            printf("[Server]: Okay bye client..\n");
            continue;
        }

        write(sockfd, info, sizeof(info));
        bzero(info, MAX);
    }

    return ;
}

void print_message(char *message, bool is_error)
{
    if (is_error)
    {
        fprintf(stderr, "%s", message);
    }
    else
    {
        printf("%s", message);
    }

    return ;
}