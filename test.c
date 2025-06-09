#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void    *infinite_loop(void *arg)
{
	(void)arg;
    while (1)
    {
        printf("infinite_loop\n");
        usleep(500000);
    }
    return (NULL);
}

void    *killer(void *arg)
{
	int i = 0;
	pthread_t *alive = (pthread_t *)arg;
	while (i < 10)
	{
		printf("killer_thread: %d\n", i);
		i++;
		usleep(500000);
	}
	pthread_detach(*alive);
	return (NULL);
}

int main(void)
{
	int i = 0;
	pthread_t infinite_thread;
	pthread_t killer_thread;

	pthread_create(&infinite_thread, NULL, infinite_loop, NULL);
	pthread_create(&killer_thread, NULL, killer, &infinite_thread);
	pthread_join(infinite_thread, NULL);
	return (0);
}