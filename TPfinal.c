#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_BOOKS 5
#define NUM_PEOPLE 3

pthread_mutex_t book_mutex[NUM_BOOKS];

void* borrow_book(void* person_id) {
    int person = *((int*)person_id);

    // Simulate browsing before borrowing
    printf("Person %d is browsing...\n", person);
    sleep(rand() % 3 + 1);  // Simulate random browsing time

    // Choose a random book to borrow
    int book_to_borrow = rand() % NUM_BOOKS;

    // Lock the mutex for the chosen book
    pthread_mutex_lock(&book_mutex[book_to_borrow]);

    // Critical section: Borrow the book
    printf("Person %d is borrowing Book %d.\n", person, book_to_borrow);

    // Simulate reading or keeping the book for some time
    sleep(rand() % 4 + 2);

    // Return the book by unlocking the mutex
    pthread_mutex_unlock(&book_mutex[book_to_borrow]);
    printf("Person %d has returned Book %d.\n", person, book_to_borrow);

    pthread_exit(NULL);
}

int main() {
    pthread_t people_threads[NUM_PEOPLE];
    int person_ids[NUM_PEOPLE];

    // Initialize mutexes for each book
    for (int i = 0; i < NUM_BOOKS; ++i) {
        pthread_mutex_init(&book_mutex[i], NULL);
    }

    // Create threads for people (borrowers)
    for (int i = 0; i < NUM_PEOPLE; ++i) {
        person_ids[i] = i + 1;  // Person IDs start from 1
        pthread_create(&people_threads[i], NULL, borrow_book, (void*)&person_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_PEOPLE; ++i) {
        pthread_join(people_threads[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_BOOKS; ++i) {
        pthread_mutex_destroy(&book_mutex[i]);
    }

    return 0;
}
