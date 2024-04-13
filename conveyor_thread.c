#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include "conveyor_shared.h"

/*
 * O data_apply_values é envolto de um mutex para que somente uma thread
 * tente aplicar seu valor em um determinado momento.
 */
pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;
void thread_data_apply_values(double weight)
{

	pthread_mutex_lock  (&mx);
	data_apply_values(weight);
	pthread_mutex_unlock(&mx);

	return;
}

/* Thread da primeira esteira. */
void* thread_conveyor1(void* param)
{

	(void) param;

	while (true)
	{

		/* Grava o tempo de início */
		#ifdef TIMING
		timing_register(&conveyor1_timing_old);
		#endif

		/* Aplica o seu valor (peso) */
		thread_data_apply_values(CONVEYOR1_ITEM_WEIGHT);

		/* Grava o tempo de fim e loga a diferença */
		#ifdef TIMING
		timing_register(&conveyor1_timing_new);
		timing_log('1', &conveyor1_timing_old, &conveyor1_timing_new);
		#endif

		/* Dorme por determinado tempo */
		usleep                  (CONVEYOR1_WAIT_TIME);
	}

	pthread_exit((void*) -1);
}

/* Thread da segunda esteira. Identica à primeira, fora constantes. */
void* thread_conveyor2(void* param)
{
	(void) param;

	while (true)
	{

		#ifdef TIMING
		timing_register(&conveyor2_timing_old);
		#endif

		thread_data_apply_values(CONVEYOR2_ITEM_WEIGHT);

		#ifdef TIMING
		timing_register(&conveyor2_timing_new);
		timing_log('2', &conveyor2_timing_old, &conveyor2_timing_new);
		#endif

		usleep                  (CONVEYOR2_WAIT_TIME);
	}

	pthread_exit((void*) -1);
}

int main(void)
{

	/* O display_print_display não usa newline, então não buffaremos o stdout */
	setvbuf(stdout, NULL, _IONBF, 0);

	/* Threads */
	pthread_t tid_conveyor1, tid_conveyor2;
	pthread_attr_t attr;

	pthread_attr_init(&attr);

	pthread_create(&tid_conveyor1, &attr, thread_conveyor1, NULL);
	pthread_create(&tid_conveyor2, &attr, thread_conveyor2, NULL);

	/* Dorme um determinado tempo, atualiza a contagem e mostra o display */
	while (true)
		usleep(CONTROLLER_WAIT_TIME),
		display_update_count(),
		display_print_display();

	return -1;
}
