#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/********* MAIN STARTS HERE *********/
int main(void)
{
    pid_t      child_pid;

    printf("My PID is %d, (parent(shell) PID is %d)\n", (int) getpid(), (int) getppid());

    child_pid = fork();

    if (child_pid != 0)
    {
        printf("[Parent]: My Child's Id is %d\n", child_pid);
    }
    else
    {
        printf("[Child]: my pid is %d\n", (int) getpid());
    }

    exit(0);
}