#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define BUFFER_SIZE 10

//Hunter Jenkins and Jack Utzerath
//Producer and Consumer


int buffer[BUFFER_SIZE];
int count = 0; // Number of items in the buffer
int produceIndex = 0; // Index at which to produce
int consumeIndex = 0; // Index at which to consume

// Synchronization primitives
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t can_produce = PTHREAD_COND_INITIALIZER;
pthread_cond_t can_consume = PTHREAD_COND_INITIALIZER;

void produce(int item) {
    // Wait until space is available for production
    pthread_mutex_lock(&mutex);
    while (count == BUFFER_SIZE) {
        pthread_cond_wait(&can_produce, &mutex);
    }

    // Add item to the buffer
    buffer[produceIndex] = item;
    printf("Producer: Put %d in slot %d\n", item, produceIndex);
    produceIndex = (produceIndex + 1) % BUFFER_SIZE;

    // Increase item count and signal to consumer
    count++;
    pthread_cond_signal(&can_consume);
    pthread_mutex_unlock(&mutex);
}

int consume() {
    // Wait until an item is available to consume
    pthread_mutex_lock(&mutex);
    while (count == 0) {
        pthread_cond_wait(&can_consume, &mutex);
    }

    // Remove item from the buffer
    int item = buffer[consumeIndex];
    printf("Consumer: Just consumed item %d from slot %d\n", item, consumeIndex);
    consumeIndex = (consumeIndex + 1) % BUFFER_SIZE;

    // Decrease item count and signal to producer
    count--;
    pthread_cond_signal(&can_produce);
    pthread_mutex_unlock(&mutex);

    return item;
}

void* producer_thread(void* args) {
    int item = 0;
    while (1) {
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            produce(++item);
        }
    }
    return NULL;
}

void* consumer_thread(void* args) {
    while (1) {
        // Let's wait until the buffer is full to start consuming
        pthread_mutex_lock(&mutex);
        while (count < BUFFER_SIZE) {
            pthread_cond_wait(&can_consume, &mutex);
        }
        pthread_mutex_unlock(&mutex);

        // Now consume all items
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            consume();
        }
    }
    return NULL;
}

int main() {
    pthread_t producer, consumer;

    // Create producer and consumer threads
    pthread_create(&producer, NULL, producer_thread, NULL);
    pthread_create(&consumer, NULL, consumer_thread, NULL);

    // Join threads with the main thread (though they will run indefinitely)
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    // Clean up, would normally never reach here
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&can_produce);
    pthread_cond_destroy(&can_consume);

    return 0;
}
