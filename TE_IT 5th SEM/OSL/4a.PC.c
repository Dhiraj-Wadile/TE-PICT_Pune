#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0, NUM_CONSUMERS, NUM_PRODUCERS;
sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int producer_id = *((int *)arg);
    int item;

    while (1) {
        item = rand() % 100;

        if (count == BUFFER_SIZE) {
            printf("\t\t\t\t\t\t\t\t\t\t\tBUFFER FULL\n");
            sleep(1);
        }

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[count++] = item;
        printf("\t\t\t\tProducer %d produced Item Number: I0%d\n", producer_id, item);
        printf("\t\t\t\tBuffer Size: %d\n", count);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(1);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int consumer_id = *((int *)arg);
    int item;

    while (1) {
        if (count == 0) {
            printf("\t\t\t\t\t\t\t\t\t\t\tBUFFER EMPTY\n");
            sleep(2);
        }

        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[--count];
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\tConsumer %d consumed Item Number: I0%d\n", consumer_id, item);
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\tBuffer Size: %d\n", count);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(2);
    }

    pthread_exit(NULL);
}

int main() {
    printf("\t\t\t\t\t\t\t\t\t\tProducer Consumer Problem\n\n");
    printf("\t\t\t\tEnter Consumer and Producer count [P C]: ");
    scanf("%d %d", &NUM_PRODUCERS, &NUM_CONSUMERS);

    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    int producer_ids[NUM_PRODUCERS];
    int consumer_ids[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        producer_ids[i] = i + 1;
        pthread_create(&producer_threads[i], NULL, producer, &producer_ids[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumer_threads[i], NULL, consumer, &consumer_ids[i]);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
