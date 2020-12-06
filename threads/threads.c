#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/********* FUNCTION DECLARATION *********/
void *my_thread(void *args);

/********* MAIN STARTS HERE *********/
int main(void)
{
    pthread_t         thread_id;

    printf("This is before creating thread......\n");

    pthread_create(&thread_id, NULL, my_thread, NULL);
    pthread_join(thread_id, NULL);

    printf("This is after creating thread......\n");

    exit(0);
}

/********* FUNCTION DEFINITION *********/
void *my_thread(void *args)
{
    sleep(2);
    printf("I am printing from threads!!!!\n");
    sleep(2);

    return NULL;
}