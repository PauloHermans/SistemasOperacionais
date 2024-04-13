#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <stdbool.h>
#include "conveyor_shared.h"

/* 
 * Esta estrutura guarda os arquivos de pipe usados na comunicação
 * interprocesso.
 */
struct pipe_ipc
{
	/* Os filedescriptors */
	int conveyor1_ipc[2];
	int conveyor2_ipc[2];

	/* Os filestream.*/
	FILE* conveyor1_readpoint;
	FILE* conveyor2_readpoint;

	/* 
	 * Ambos são jeitos de identificar um arquivo, os fds vindo da POSIX,
	 * e os fstreams vindo do ISO C.
	 * Acontece de a função pipe() criar um par de arquivos anônimos via
	 * filedescriptor (pois é uma função originada no UNIX), já o scanf(),
	 * que é usado para a leitura dos valores, só aceita filestreams, então
	 * é necessário converter de um para o outro.
	 */
} ipc;

void pipe_ipc_init(void)
{

	/* Cria um pipe por tarefa */
	int err  = pipe(ipc.conveyor1_ipc);
	    err |= pipe(ipc.conveyor2_ipc);

	if (err)
		error_at_line(-1, errno, __FILE__, __LINE__, "could not open pipes");

	/* Converte de fd -> fstream */
	ipc.conveyor1_readpoint = fdopen(ipc.conveyor2_ipc[0], "r");
	ipc.conveyor2_readpoint = fdopen(ipc.conveyor2_ipc[0], "r");

	return;
}

/* 
 * Primeira tarefa. Similar ao conveyor_thread.c neste quesito, porém o data_apply_values
 * fica na tarefa controle, e o valor é transmitido via o pipe pelo dprintf().
 */
void task_conveyor1(void)
{

	while (true)
	{

		#ifdef TIMING
		timing_register(&conveyor1_timing_old);
		#endif

		/* Escreve o valor do peso como um double via printf no pipe */
		dprintf(ipc.conveyor1_ipc[1], "%lf\n", CONVEYOR1_ITEM_WEIGHT);

		#ifdef TIMING
		timing_register(&conveyor1_timing_new);
		timing_log('1', &conveyor1_timing_old, &conveyor1_timing_new);
		#endif

		usleep(CONVEYOR1_WAIT_TIME);
	}

}

/* Segunda tarefa. */
void task_conveyor2(void)
{

	while (true) 
	{

		#ifdef TIMING
		timing_register(&conveyor2_timing_old);
		#endif

		dprintf(ipc.conveyor2_ipc[1], "%lf\n", CONVEYOR2_ITEM_WEIGHT);

		#ifdef TIMING
		timing_register(&conveyor2_timing_new);
		timing_log('2', &conveyor2_timing_old, &conveyor2_timing_new);
		#endif

		usleep(CONVEYOR2_WAIT_TIME);
	}

}

int main(void)
{

	/* Veja conveyor_shared.h e conveyor_thread.c */
	setvbuf(stdout, NULL, _IONBF, 0);

	/* Inicializa os pipes */
	pipe_ipc_init();

	/* Cria as duas tarefas usando fork() */
	int pid_conveyor1 = fork();
	if (pid_conveyor1 == 0) task_conveyor1();
	int pid_conveyor2 = fork();
	if (pid_conveyor2 == 0) task_conveyor2();

	/* 
	 * Loop do controlador
	 *
	 * Note que devido a leitura dos pipes ser sequencial, isto acaba fazendo
	 * que a segunda tarefa, que normalmente mandaria um valor por segundo,
	 * seja bloqueada junto a primeira tarfa, que manda um valor a cada dois
	 * segundos. Foi implementado uma variante com threads.
	 *
	 * Note que a task não é realmente bloqueada, já que existe um buffer de pipe.
	 * Ela só perde sua autonomia quando o buffer enche. Mesmo assim isto acaba
	 * sendo um comportamento transparente à task de controle, já que há somente
	 * uma tentativa de leitura por iteração no while(true) abaixo.
	 */
	while (true)
	{

		/* Dorme um determinado tempo */
		usleep(CONTROLLER_WAIT_TIME);

		/* Lê os valores mandados das tarefas */
		double conveyor1_res, conveyor2_res;
		fscanf(ipc.conveyor1_readpoint, "%lf\n", &conveyor1_res);
		fscanf(ipc.conveyor2_readpoint, "%lf\n", &conveyor2_res);

		/* Aplica-os */
		data_apply_values(conveyor1_res);
		data_apply_values(conveyor2_res);

		/* Da update da contagem e mostra o display */
		display_update_count();
		display_print_display();
	}

	return -1;
}
