#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t rwlock, lock;
int readcount;
int data;

void *reader_thread(void *no);
void *writer_thread(void *no);

int main() {
    int res, nord, nowrt, i;
    int *arg;
    printf("\n============= CLASSICAL READERS-WRITERS PROBLEM ==============");
    printf("\nEnter the number of READERS: ");
    scanf("%d", &nord);
    printf("Enter the number of WRITERS: ");
    scanf("%d", &nowrt);

    pthread_t reader, writer;

    res = pthread_mutex_init(&rwlock, NULL);
    if (res != 0) {
        printf("ERROR: Mutex initialization failed\n");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&lock, NULL);
    if (res != 0) {
        printf("ERROR: Mutex initialization failed\n");
        exit(EXIT_FAILURE);
    }

    readcount = 0;

    printf("Creating Reader Threads\n");
    for (i = 1; i <= nord; i++) {
        printf("Creating Reader %d\n", i);
        arg = (int *)malloc(sizeof(int));
        *arg = i;
        res = pthread_create(&reader, NULL, reader_thread, arg);
        if (res != 0) {
            printf("ERROR: Thread Creation failed\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Creating Writer Threads\n");
    for (i = 1; i <= nowrt; i++) {
        printf("Creating Writer %d\n", i);
        arg = (int *)malloc(sizeof(int));
        *arg = i;
        res = pthread_create(&writer, NULL, writer_thread, arg);
        if (res != 0) {
            printf("ERROR: Thread Creation failed\n");
            exit(EXIT_FAILURE);
        }
    }

    pthread_join(reader, NULL);
    pthread_join(writer, NULL);

    pthread_mutex_destroy(&rwlock);
    pthread_mutex_destroy(&lock);

    return 0;
}

void *reader_thread(void *no) {
    int *num = (int *)no;
    while (1) {
        int temp = rand() % 2;
        if (temp == 0)
            temp = 2;
        sleep(temp);

        pthread_mutex_lock(&lock);
        readcount++;
        if (readcount == 1)
            pthread_mutex_lock(&rwlock);
        pthread_mutex_unlock(&lock);

        printf("\nReader %d: Entered", *num);
        sleep(temp);
        temp = data;
        printf("\nReader: Data => %d", temp);
        printf("\nReader %d: Exited", *num);

        pthread_mutex_lock(&lock);
        readcount--;
        if (readcount == 0)
            pthread_mutex_unlock(&rwlock);
        pthread_mutex_unlock(&lock);
    }
}

void *writer_thread(void *no) {
    int *num = (int *)no;
    while (1) {
        int temp = rand() % 7;
        if (temp == 0)
            temp = 2;
        sleep(temp);

        pthread_mutex_lock(&rwlock);
        printf("\nWriter %d: Entered", *num);
        data = temp * 12;
        printf("\nWriter: The data was changed to %d", data);
        printf("\nWriter %d: Exited", *num);
        pthread_mutex_unlock(&rwlock);
    }
}
