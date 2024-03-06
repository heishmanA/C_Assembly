/* main.c
   Aaron Heishman
   Lab2: Systems 2
   9/5/2023
*/

#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <signal.h>

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

/* locks and unlocks need to happen inside the producer and consumer threads */
void *producer(void *param) {
    buffer_item rand;
    unsigned int seed;
    int rc;
    int *id = (int *)param;
    while (1) {
        /* sleep for a random period of time */
        seed = time(NULL) ^ (*id); // creating seed based off current time XOR id
        sleep((rand_r(&seed) % 5) + 1); // sleep for 1 to 5 seconds]
        /* decrement empty slots*/
        rc = sem_wait(&empty); 
        assert(rc == 0);
        /* lock */
        rc = pthread_mutex_lock(&mutex); 
        assert (rc == 0);
        /* generate a random number and insert into the buffer */
        seed = time(NULL) ^ (*id); // creating seed based off current time XOR id
        rand = rand_r(&seed);
        // check for errors
        if (insert_item(rand) < 0) {
            printf("%d Error: Could not insert into buffer\n", *id);
            exit(EUSE);
        };
        /* unlock */
        rc = pthread_mutex_unlock(&mutex); 
        assert (rc == 0);
        /* increment full slots */
        rc = sem_post(&full); 
        assert (rc == 0);
    }
}

void *consumer(void *param) {
    buffer_item rand;
    unsigned int seed;
    int rc;
    int *id = (int *) param;
    while (1) {
        /* sleep for a random period of time */
        seed = time(NULL) ^ (*id); // creating seed based off current time XOR id
        sleep((rand_r(&seed) % 5) + 1); // sleep for 1 to 5 seconds
        /* decrement full slots - block if 0 */
        rc = sem_wait(&full); 
        assert(rc == 0);
        /* lock */
        rc = pthread_mutex_lock(&mutex);   
        assert (rc == 0);
        /* check for errors from remove_item */
        if (remove_item(&rand) < 0) {
            printf("%d Error: Could not remove from buffer\n", *id);
            exit(EUSE);
        }
        printf("consumer consumed %d\n", rand); // print before unlocking 
        /* unlock */
        rc = pthread_mutex_unlock(&mutex); 
        assert (rc == 0);
        /* increment empty */
        rc = sem_post(&empty); 
        assert (rc == 0);
    }
}

int main(int argc, char* argv[]) {
    /* Get command line arguments */
    assert (argc > 3);
    /*  convert args from ascii to integer and check they're within the correct range */
    int sleep_time = atoi(argv[1]), producer_count = atoi(argv[2]), consumer_count = atoi(argv[3]);
    assert(sleep_time >= 1 && sleep_time <= 10);
    assert(producer_count >= 1 && producer_count <= 5);
    assert(consumer_count >= 1 && consumer_count <= 5);
    /* Variable declarations */
    pthread_t producers[producer_count], consumers[consumer_count];
    pthread_attr_t attr;
    int *producer_arr, *consumer_arr;
    int rc, i;

    /* Initialize buffer, mutex, semaphores, other global vars */
    printf("Initializing..\n");
    rc = pthread_mutex_init(&mutex, NULL);
    assert(rc == 0);
    rc = sem_init(&empty, 0, BUFFER_SIZE);
    assert(rc == 0);
    rc = sem_init(&full, 0, 0); 
    assert(rc == 0);
    rc = pthread_attr_init(&attr);
    assert(rc == 0);
    

    /* Create producer thread(s) */
    printf("Creating %d producers..\n", producer_count);
    producer_arr = (int*)malloc(producer_count * sizeof(int));
    assert(producer_arr != NULL);
    memset(producer_arr, 0, producer_count * sizeof(int));
    for (i = 0; i < producer_count; i++) {
        producer_arr[i] = i; // ids for producer threads
    }
    
    for (i = 0; i < producer_count; i++) {
        rc = pthread_create(&producers[i], &attr, producer, (void *) &producer_arr[i]);
        assert(rc == 0);
    }

    printf("Creating %d consumers..\n", consumer_count);
    /* Create consumer thread(s) */
    consumer_arr = (int*)malloc(consumer_count * sizeof(int));
    assert(consumer_arr != NULL);
    
    memset(consumer_arr, 0, consumer_count * sizeof(int));
    for (i = 0; i < consumer_count; i++) {
        consumer_arr[i] = i + 4; // ids for consumer threads 
    }
    
    for (i = 0; i < consumer_count; i++) {
        rc = pthread_create(&consumers[i], &attr, consumer, &consumer_arr[i]);
        assert(rc == 0);
    }

    /* Sleep */
    printf("Main will now sleep for %d seconds\n", sleep_time);
    sleep(sleep_time);

    /* Release resources, e.g. destroy mutex and semaphores */
    printf("Main has woken up. Releasing resources..\n");
    rc = sem_destroy(&empty);
    assert (rc == 0);
    rc = sem_destroy(&full);
    assert(rc == 0);
    rc = pthread_attr_destroy(&attr);
    assert(rc == 0);
    rc = pthread_mutex_destroy(&mutex);
    assert (rc == 0);
    free(producer_arr);
    free(consumer_arr);
  /* Exit */
  return 0;
} 