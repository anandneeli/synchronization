#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define LIMIT 100

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;
int count = 0;

void *PrintEven(void *args)
{
    while (count < LIMIT) {
        pthread_mutex_lock(&count_mutex);
        if (count%2 == 0) {
            printf("%d ", count);
            count++;
            pthread_cond_signal( &condition_var );
        } else {
            pthread_cond_wait( &condition_var, &count_mutex );
        }
        pthread_mutex_unlock( &count_mutex );
    }
}

void *PrintOdd(void *args)
{
    while(count < LIMIT) {
        pthread_mutex_lock(&count_mutex);
        if(count%2 != 0) {
            printf("%d ", count);
            count++;
            pthread_cond_signal( &condition_var );
        } else {
            pthread_cond_wait( &condition_var, &count_mutex );
        }
        pthread_mutex_unlock( &count_mutex );
    }
}


int main()
{
    mode_t mode = 0644;

    pthread_t odd_t, even_t;
    printf("Numbers using thread and mutex\n");

    pthread_create(&odd_t, NULL, PrintOdd, NULL);
    pthread_create(&even_t, NULL, PrintEven, NULL);

    pthread_join(odd_t, NULL);
    pthread_join(even_t, NULL);
    pthread_exit(NULL);
}
