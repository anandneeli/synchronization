#include <stdio.h>
#include <semaphore.h>
#define LIMIT 100

sem_t *s1 = NULL;
sem_t *s2 = NULL;

void print_even (void)
{
    int i = 2;
    while (i <= LIMIT) {
        sem_wait(s2);
        printf("%d ", i);
        fflush(stdout);
        i = i+2;
        sem_post(s1);
    }
    printf("\n");
}



int main()
{
    mode_t mode = 0644;
    s1 = sem_open("odd",O_CREAT,mode,1);
    s2 = sem_open("even",O_CREAT,mode,0);


    print_even();
    sem_close(s2);
    sem_unlink("odd");
    return 0;
}

