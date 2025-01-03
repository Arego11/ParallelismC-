#include <iostream>
#include <pthread.h>
using namespace std;
#define NUM_THREADS 10
pthread_mutex_t mtx;

struct Args{
    int tid;
    int data;
};

void *thread_function(void *args){
    Args *local_args = (Args*)args;
    pthread_mutex_lock(&mtx);
    cout << "Printing from thread " << local_args-> tid << endl;
    cout << "Value of data is " << local_args-> data << endl;
    pthread_mutex_unlock(&mtx);
}

int main() {
    //this makes an array of 10 threads
    pthread_t threads[NUM_THREADS];
    Args per_thread_args[NUM_THREADS];

    pthread_mutex_init(&mtx, NULL); // Initialize mutex

    //this makes 10 threads
    for(int i = 0; i < NUM_THREADS; i++){
        per_thread_args[i].tid = i;
        per_thread_args[i].data = i * i;

        pthread_create(&threads[i], NULL, thread_function, (void *)&per_thread_args[i]);
        //1 -> pointer to pthread_t, 2 -> attributes for the thread, 3 -> entry routine, 4 -> Arguments.
        pthread_join(threads[i], NULL); // Wait for thread to finish before creating the next one
    }

    pthread_mutex_destroy(&mtx); // Destroy mutex

    return 0;
}
