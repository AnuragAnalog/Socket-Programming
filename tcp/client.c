#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>

/********* DEFINED CONSTANTS *********/
#define MAX         80
#define IPMAX       16
#define INFINITE    true
#define SA struct   sockaddr

/********* FUNCTION DECLARATIONS ********/
void chat_client(int sockfd);
void print_message(char *message, bool is_error);

/********* MAIN STARTS HERE *********/
int main(int argc, char **argv)
{
    int                     port, sockfd, connfd;
    char                    *serv_addr = NULL;
    struct sockaddr_in      servaddr, cli;

    if (argc != 2)
    {
        fprintf(stderr, "Syntax: %s <port>", argv[0]);
        exit(1);
    }

    port = atoi(argv[1]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Create a socket
    if (sockfd == -1)
    {
        print_message("[Client]: Cannot create a socket\n", true);
        exit(2);
    }
    else
    {
        print_message("[Client]: Socket Created Successfully\n", false);
    }
    
    // Assign Server Port and IP
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(port);

    // Connect to Server
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) != 0)
    {
        print_message("[Client]: Sorry, Coundn't connect with the server....\n", false);
        exit(3);
    }
    else
    {
        print_message("[Client]: Connection with Server Established\n", true);
    }
    
    chat_client(sockfd);

    close(sockfd); // Closing the Socket

    exit(0);
}

/********* FUNCTION DEFINITIONS ********/
void chat_client(int sockfd)
{
    int        n;
    char       info[MAX];

    while (INFINITE)
    { 
        bzero(info, sizeof(info)); 
        printf("[Client]: "); 
        n = 0; 
        while ((info[n++] = getchar()) != '\n');

        write(sockfd, info, sizeof(info)); 
        bzero(info, sizeof(info));

        read(sockfd, info, sizeof(info)); 
        printf("[Server]: %s\n", info);
 
        if ((strncmp(info, "bye", 3)) == 0)
        { 
            printf("[Client]: I am going bye...\n"); 
            break;
        }
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