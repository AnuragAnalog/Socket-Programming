#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/********* MAIN STARTS HERE *********/
int main(void)
{
    int          i, j;
    pid_t        child_pid;

    child_pid = fork();

    if (child_pid != 0)
    {
        for (i = 0; i < 5; i++)
        {
            printf("I am Child Process, with PID %d\n", (int) child_pid);
            usleep(50);
        }
    }
    else
    {
        for (j = 0; j < 5; j++)
        {
            printf("I am Parent Process, with PID %d\n", (int) getpid());
            usleep(50);
        }
    }

    exit(0);
}