#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/********* MAIN STARTS HERE *********/
int main(void)
{
    char         *args_list[] = {"ls", "-l", "/", NULL};
    pid_t        child_pid;

    child_pid = fork();

    if (child_pid == 0)
    {
        printf("I am parent process, my PID is %d\n", (int) getpid());
    }
    else
    {
        wait(NULL);
        printf("I am child process, my PID is %d\n\n", child_pid);
        execvp("ls", args_list);
    }

    printf("I have executed completely, and I am Parent process with PID %d\n\n", (int) getpid());
    
    exit(0);
}