#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#include "Utils.h"

int beers = 2000000;
pthread_mutex_t a_lock = PTHREAD_MUTEX_INITIALIZER;

void* drink_lots(void* a)
{
    pthread_mutex_lock(&a_lock);
    int i;
    for (i = 0; i < 100000; i++) {
        beers--;
    }
    pthread_mutex_unlock(&a_lock);
    return NULL;
}

int main()
{
    pthread_t threads[20];
    int t; 
    printf("%i bottles of beer on the wall\n%i bottles of beer\n", beers, beers);
    for (t = 0; t < 20; t++) {
        if (pthread_create(&threads[t], NULL, drink_lots, NULL) == -1)
            error("Couldn't create threads.");
     
    }
    void* result;
    for (t = 0; t < 20; t++) {
        pthread_join(threads[t], &result);
    }
    printf("There are now %i bottles of beer on the wall\n", beers);
    return 0;
}