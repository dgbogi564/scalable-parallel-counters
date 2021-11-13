#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>

#define COUNTER_VALUE (1UL << 24)

int counter;

void count() {
    while(counter < COUNTER_VALUE) {
        counter++;
    }
}

int main(int argc, char** argv) {
    /* check argument */
    if(argc < 2) {
        printf("no argument supplied\n");
        exit(0);
    }
    errno = 0;
    long int num_threads = strtol(argv[1], NULL, 10);
    if(num_threads == 0) {
        printf("%s is not a positive integer\n", strerror(errno));
    }

    /* create thread array */
    pthread_t *th_id = malloc(sizeof(pthread_t)*num_threads);

    /* start timer */
    clock_t start, end;
    start = clock();

    /* create threads and run counting function */
    for(int x = 0; x < num_threads; x++) {
        pthread_create(&th_id[x], NULL, (void *(*)(void *)) count, NULL);
    }
    for(int x = 0; x < num_threads; x++) {
        pthread_join(th_id[x], NULL);
    }

    /* end timer */
    end = clock();

    /* get time */
    double time_ms =  (end - start)/(CLOCKS_PER_SEC/1000);

    /* print result */
    printf("Counter finish in %f ms\n", time_ms);
    printf("The value of counter should be %ld\n", COUNTER_VALUE);
    printf("The value of counter is %d\n", counter);

    /* free */
    free(th_id);

    /* end program */
    return 0;
}

