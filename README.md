# The-last-Tp-OS-
TP EX5 Final


#### the object of this Tp :
it is explaine the process synchronization i  will expline this using example from life  :
 - Library book checkout: Borrowing a book requires accessing the shared resource (the book) in a controlled manner. Librarians use a system like a card catalog or computer log to ensure only one person borrows a specific book at a time, preventing conflicts and lost books

#### let's break down the code into individual lines with explanations:


- Constants: Define constants for the number of books and people.
```
#define NUM_BOOKS 5
#define NUM_PEOPLE 3

```
- Mutex Array: Declare an array of mutexes, each representing a book.

```
pthread_mutex_t book_mutex[NUM_BOOKS];


```
- Thread Function: Define a thread function borrow_book that takes a person ID as an argument.
```
 void* borrow_book(void* person_id) {
 int person = *((int*)person_id);

```
- Browsing Simulation: Simulate a person browsing for a random time.

```
    printf("Person %d is browsing...\n", person);
    sleep(rand() % 3 + 1);

```
-Random Book Selection: Choose a random book to borrow.

```
    int book_to_borrow = rand() % NUM_BOOKS;

```
- Lock Mutex: Lock the mutex for the chosen book.

```
        pthread_mutex_lock(&book_mutex[book_to_borrow]);

```
- Critical Section (Borrowing): Print a message indicating the person is borrowing a book and simulate reading or keeping the book.

```
    printf("Person %d is borrowing Book %d.\n", person, book_to_borrow);
    sleep(rand() % 4 + 2);

```

- Unlock Mutex (Return Book): 

```
    pthread_mutex_unlock(&book_mutex[book_to_borrow]);
    printf("Person %d has returned Book %d.\n", person, book_to_borrow);


```
- Mutex Initialization: Initialize mutexes for each book.


```
   for (int i = 0; i < NUM_BOOKS; ++i) {
        pthread_mutex_init(&book_mutex[i], NULL);
    }


```
-Thread Creation: Create threads for people with unique IDs, each running the borrow_book function.



```
    for (int i = 0; i < NUM_PEOPLE; ++i) {
        person_ids[i] = i + 1;
        pthread_create(&people_threads[i], NULL, borrow_book, (void*)&person_ids[i]);
    }


```
-Thread Joining: Wait for all threads to finish.

```
  for (int i = 0; i < NUM_PEOPLE; ++i) {
        pthread_join(people_threads[i], NULL);
    }
```
-Thread Joining: Wait for all threads to finish.

```
  for (int i = 0; i < NUM_PEOPLE; ++i) {
        pthread_join(people_threads[i], NULL);
    }
```


- the output of this code like this : 
```
    for (int i = 0; i < NUM_BOOKS; ++i) {
        pthread_mutex_destroy(&book_mutex[i]);
    }

```





```
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

// in Tp this is mean access 
    printf("Person %d is borrowing Book %d.\n", person, book_to_borrow);

    // Simulate reading or keeping the book for some time
    sleep(rand() % 4 + 2);

    // Return the book by unlocking the mutex
    pthread_mutex_unlock(&book_mutex[book_to_borrow]);
// in Tp this is mean modify it  

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
        // (void*)&person_ids[i]: This is a pointer to the argument that will be passed to the borrow_book function.

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

```
