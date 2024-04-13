#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <stdbool.h>
#include "conveyor_shared.h"

struct pipe_ipc
{
	int esteira1_ipc[2];
	int esteira2_ipc[2];

	FILE* esteira1_readpoint;
	FILE* esteira2_readpoint;
} ipc;

void pipe_ipc_init(void)
{

	int err  = pipe(ipc.esteira1_ipc);
	    err |= pipe(ipc.esteira2_ipc);

	if (err)
		error_at_line(-1, errno, __FILE__, __LINE__, "could not open pipes");

	ipc.esteira1_readpoint = fdopen(ipc.esteira1_ipc[0], "r");
	ipc.esteira2_readpoint = fdopen(ipc.esteira2_ipc[0], "r");

	return;
}

void task_esteira1(void)
{

	while (true)
		dprintf(ipc.esteira1_ipc[1], "%lf\n", ESTEIRA1_ITEM_WEIGHT),
		usleep(ESTEIRA1_WAIT_TIME);

}

void task_esteira2(void)
{

	while (true)
		dprintf(ipc.esteira2_ipc[1], "%lf\n", ESTEIRA2_ITEM_WEIGHT),
		usleep(ESTEIRA2_WAIT_TIME);

}

int main(void)
{

	setvbuf(stdout, NULL, _IONBF, 0);

	pipe_ipc_init();

	int pid_esteira1 = fork();
	if (pid_esteira1 == 0) task_esteira1();
	int pid_esteira2 = fork();
	if (pid_esteira2 == 0) task_esteira2();

	while (true)
	{

		usleep(CONTROLLER_WAIT_TIME);

		double esteira1_res, esteira2_res;
		fscanf(ipc.esteira1_readpoint, "%lf\n", &esteira1_res);
		fscanf(ipc.esteira2_readpoint, "%lf\n", &esteira2_res);

		data_apply_values(esteira1_res);
		data_apply_values(esteira2_res);

		display_update_count();
		display_print_display();
	}

	return -1;
}
