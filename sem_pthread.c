#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t *s1;
sem_t *s2;

void *PrintEven(void *args)
{
    for(int i=0;i<100;i+=2) {
        sem_wait(s2);
        printf("%d ", i);
        sem_post(s1);
    }
}

void *PrintOdd(void *args)
{
    for(int i=1;i<100;i+=2) {
        sem_wait(s1);
        printf("%d ", i);
        sem_post(s2);
    }
}


int main()
{
    mode_t mode = 0644;
    s1 = sem_open("odd",O_CREAT,mode,1);
    s2 = sem_open("even",O_CREAT,mode,0);

    pthread_t odd_t, even_t;

    pthread_create(&odd_t, NULL, PrintOdd, NULL);
    pthread_create(&even_t, NULL, PrintEven, NULL);


    pthread_join(odd_t, NULL);
    pthread_join(even_t, NULL);
    pthread_exit(NULL);
}
