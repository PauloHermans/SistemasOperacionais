#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include "conveyor_shared.h"

pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;

void thread_data_apply_values(double weight)
{

	pthread_mutex_lock  (&mx);
	data_apply_values(weight);
	pthread_mutex_unlock(&mx);

	return;
}

void* thread_conveyor1(void* param)
{

	(void) param;

	while (true)
		thread_data_apply_values(CONVEYOR1_ITEM_WEIGHT),
		usleep                  (CONVEYOR1_WAIT_TIME);

	pthread_exit((void*) -1);
}

void* thread_conveyor2(void* param)
{
	(void) param;

	while (true)
		thread_data_apply_values(CONVEYOR2_ITEM_WEIGHT),
		usleep                  (CONVEYOR2_WAIT_TIME);

	pthread_exit((void*) -1);
}

int main(void)
{

	setvbuf(stdout, NULL, _IONBF, 0);

	pthread_t tid_conveyor1, tid_conveyor2;
	pthread_attr_t attr;

	pthread_attr_init(&attr);

	pthread_create(&tid_conveyor1, &attr, thread_conveyor1, NULL);
	pthread_create(&tid_conveyor2, &attr, thread_conveyor2, NULL);

	while (true)
		usleep(CONTROLLER_WAIT_TIME),
		display_update_count(),
		display_print_display();

	return -1;
}
