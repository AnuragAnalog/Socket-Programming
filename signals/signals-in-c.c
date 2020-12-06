#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>

/********* DEFINED CONSTANTS *********/
#define INFINITE        true

/********* FUNCTION DECLARATION *********/
void signal_handle(int sig);

/********* MAIN STARTS HERE *********/
int main()
{
    signal(SIGINT, signal_handle);

    printf("Try to stop me...\n");
    while (INFINITE) ;  // Infinite Loop

    exit(0);
}

/********* FUNCTION DEFINITION *********/
void signal_handle(int sig)
{
    printf("Hahaha.. You can't terminate me with CTRL+C\n");

    return ;
}