#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <stdbool.h>
#include <pthread.h>
#include "conveyor_shared.h"
#ifdef WINDOWS
#include <windows.h>
#include <io.h>
#endif

pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;

/* É feito o mesmo bloqueio aqui que é feito no conveyor_thread.c */
void thread_data_apply_values(double weight)
{

	pthread_mutex_lock  (&mx);
	data_apply_values(weight);
	pthread_mutex_unlock(&mx);

	return;
}

struct pipe_ipc
{
	#ifdef WINDOWS
	HANDLE conveyor1_ipc[2];
	HANDLE conveyor2_ipc[2];

	FILE* conveyor1_readpoint;
	FILE* conveyor2_readpoint;
	#else
	int conveyor1_ipc[2];
	int conveyor2_ipc[2];

	FILE* conveyor1_readpoint;
	FILE* conveyor2_readpoint;
	#endif
} ipc;

#ifdef WINDOWS
void pipe_ipc_init(void)
{

	SECURITY_ATTRIBUTES attr =
	{
		.nLength              = sizeof(SECURITY_ATTRIBUTES),
		.lpSecurityDescriptor = NULL,
		.bInheritHandle       = true
	};

	bool err1 = CreatePipe(&ipc.conveyor1_ipc[0], &ipc.conveyor1_ipc[1], &attr, 0);
	bool err2 = CreatePipe(&ipc.conveyor2_ipc[0], &ipc.conveyor2_ipc[1], &attr, 0);
	if  (err1 == 0 || err2 == 0)
		fprintf(stderr, "error: at %s:%i: could not open pipes\n", __FILE__, __LINE__), exit(-1);

	ipc.conveyor1_readpoint  = _fdopen(_open_osfhandle((intptr_t) ipc.conveyor1_ipc[0], _O_RDONLY), "r");
	ipc.conveyor2_readpoint  = _fdopen(_open_osfhandle((intptr_t) ipc.conveyor2_ipc[0], _O_RDONLY), "r");

	return;
}
#else
void pipe_ipc_init(void)
{

	int err  = pipe(ipc.conveyor1_ipc);
	    err |= pipe(ipc.conveyor2_ipc);

	if (err)
		error_at_line(-1, errno, __FILE__, __LINE__, "could not open pipes");

	ipc.conveyor1_readpoint = fdopen(ipc.conveyor1_ipc[0], "r");
	ipc.conveyor2_readpoint = fdopen(ipc.conveyor2_ipc[0], "r");

	return;
}
#endif

void task_conveyor1(void)
{

	while (true)
	{

		#ifdef TIMING
		timing_register(&conveyor1_timing_old);
		#endif

		#ifdef WINDOWS

		static char output[128];
		size_t count = sprintf(output, "%lf\n", CONVEYOR1_ITEM_WEIGHT);
		WriteFile(ipc.conveyor1_ipc[1], output, count, NULL, NULL);

		#else

		dprintf(ipc.conveyor1_ipc[1], "%lf\n", CONVEYOR1_ITEM_WEIGHT);

		#endif

		#ifdef TIMING
		timing_register(&conveyor1_timing_new);
		timing_log('1', &conveyor1_timing_old, &conveyor1_timing_new);
		#endif

		usleep(CONVEYOR1_WAIT_TIME);
	}

}

void task_conveyor2(void)
{

	while (true)
	{

		#ifdef TIMING
		timing_register(&conveyor2_timing_old);
		#endif

		#ifdef WINDOWS

		static char output[128];
		size_t count = sprintf(output, "%lf\n", CONVEYOR2_ITEM_WEIGHT);
		WriteFile(ipc.conveyor2_ipc[1], output, count, NULL, NULL);

		#else

		dprintf(ipc.conveyor2_ipc[1], "%lf\n", CONVEYOR2_ITEM_WEIGHT);

		#endif

		#ifdef TIMING
		timing_register(&conveyor2_timing_new);
		timing_log('2', &conveyor2_timing_old, &conveyor2_timing_new);
		#endif

		usleep(CONVEYOR2_WAIT_TIME);
	}

}

/* Thread de leitura da primeira tarefa */
void* thread_leitura_conveyor1(void* param)
{

	(void) param;
	double conveyor1_res;

	while (true)
		fscanf(ipc.conveyor1_readpoint, "%lf\n", &conveyor1_res),
		thread_data_apply_values(conveyor1_res);

	pthread_exit((void*) -1);
}

/* Thread de leitura da segunda tarefa */
void* thread_leitura_conveyor2(void* param)
{

	(void) param;
	double conveyor2_res;

	while (true)
		fscanf(ipc.conveyor2_readpoint, "%lf\n", &conveyor2_res),
		thread_data_apply_values(conveyor2_res);

	pthread_exit((void*) -1);
}

int main(void)
{

	setvbuf(stdout, NULL, _IONBF, 0);

	pipe_ipc_init();

	pthread_t      tid_leitura_conveyor1, tid_leitura_conveyor2;
	pthread_attr_t attr;

	pthread_attr_init(&attr);

	pthread_create(&tid_leitura_conveyor1, &attr, thread_leitura_conveyor1, NULL);
	pthread_create(&tid_leitura_conveyor2, &attr, thread_leitura_conveyor2, NULL);

	/* 
	 * No windows é impossivel fazer um "fork()" como no UNIX.
	 * Por mais do NT ter suporte a tal operação, a userspace em sí
	 * não ter suporte. De qualquer modo, aqui criaremos um par de
	 * threads que larparão como processos. Elas usam o pipe para a comunicação.
	 */
	#ifdef WINDOWS

	pthread_t tid_task_conveyor1, tid_task_conveyor2;
	
	                                           /* Cast cabuloso pois task_conveyorN
						    * tem um protótipo diferente do
						    * requerido pelo pthread_create
						    * (não buga nada ignorar os valores
						    * que o pthread passa). */
	pthread_create(&tid_task_conveyor1, &attr, (void * (*)(void *))task_conveyor1, NULL);
	pthread_create(&tid_task_conveyor2, &attr, (void * (*)(void *))task_conveyor2, NULL);
	
	#else

	int pid_conveyor1 = fork();
	if (pid_conveyor1 == 0) task_conveyor1();
	int pid_conveyor2 = fork();
	if (pid_conveyor2 == 0) task_conveyor2();

	#endif

	while (true)
	{

		usleep(CONTROLLER_WAIT_TIME);

		/*
		 * Os fscanf() foram movidos para suas proprias threads, para que assim
		 * a leitura dos valores sejam feitas de forma assíncrona. Isto resolve
		 * ambos problemas citados anteriormente em conveyor_pipe_problematic.
		 */

		display_update_count();
		display_print_display();
	}

	return -1;
}
