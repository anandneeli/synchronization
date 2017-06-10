#include <stdio.h>
#include <semaphore.h>
#define LIMIT 100

sem_t *s1 = NULL;
sem_t *s2 = NULL;

void print_odd (void)
{
    int i = 1;
    while (i <= LIMIT) {
        sem_wait(s1);
        printf("%d ", i);
        fflush(stdout);
        i = i+2;
        sem_post(s2);
    }
    printf("\n");
}



int main()
{
    mode_t mode = 0644;
    s1 = sem_open("odd",O_CREAT,mode,1);
    s2 = sem_open("even",O_CREAT,mode,0);


    print_odd();
    sem_close(s1);
    sem_unlink("even");
    return 0;
}

